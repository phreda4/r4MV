// And this heinous piece of code is what happens if you hack stuff together
// as global code and then can't be bothered making it reminescent of sanity
var workerCounter = 0;
function JobQueue(numWorkers) {
    this.workersAvailable = true;
    this.intialised = false;
    var cancelled = false;
    if (numWorkers <= 0 || !window.Worker) {
        this.workersAvailable = false;
        var fallBackTask;
        this.initJobQueue = function (scene, task, done) {
            _scene = parse(scene)();
            fallBackTask = task;
            this.initialised = true;
            done();
        }
        this.runJobQueue = function(js, done) {
            cancelled = false;
            cancelCallback = undefined;
            jobs = js;
            function runTask(i) {
                if (cancelled) {
                    cancelCallback();
                    return;
                }
                var job = jobs[i];
                var result = parse(fallBackTask(parse(job.message)));
                if (job.done)
                    job.done(result);

                if (i === jobs.length - 1) {
                    done();
                    return;
                }

                setTimeout(function(){runTask(i+1);}, 10);
            };
            runTask(0);
        }
    } else {
        var jobs;
        var jobCount;
        var queueDone;
        var workers = [];
        var self = this;
        var cancelledWorkers = 0;
        var runningWorkers = 0;
        var cancelCallback;
        this.initJobQueue = function (scene, task, done) {
            var message = '({type:"init", scene:' + scene + ', processRenderCommand:'+task+'})';
            for (jobCount = 0; jobCount < numWorkers; ++jobCount) {
                worker = new Worker("render-task.js");
                worker.runNextTask = function() {
                    this.postMessage(this.queue.shift());
                }
                worker.onmessage = function() {
                    if (--jobCount === 0) {
                        self.initialised = true;
                        for (var i = 0; i < workers.length; ++i)
                            workers[i].onmessage = function(evt) {
                                if (cancelled) {
                                    if (++cancelledWorkers === runningWorkers) {
                                        cancelCallback();
                                    }
                                    return;
                                }
                                var res = parse(evt.data);
                                if (jobs[res.jobid].done)
                                    jobs[res.jobid].done(res.result);
                                if (--jobCount === 0)
                                        queueDone();
                                if (this.queue.length)
                                    this.runNextTask();
                                else
                                    --runningWorkers;
                            };
                        done();
                    }
                };
                worker.postMessage(message);
                workers[jobCount] = worker;
            }
        }
        this.runJobQueue = function(js, done) {
            cancelled = false;
            cancelCallback = undefined;
            cancelledWorkers = 0;
            jobs = js;
            queueDone = done;
            jobCount = jobs.length;
            for (var i = 0; i < workers.length; ++i)
                workers[i].queue = [];
            for (var i = 0; i < jobs.length; i++)
                workers[i%workers.length].queue.push("({jobid: " + i + ", command:"+jobs[i].message+"})");
            runningWorkers = workers.length;
            for (var i = 0; i < workers.length; ++i)
                workers[i].runNextTask();
        }
    }
    this.stop = function (f) {
        cancelled = true;
        cancelCallback = f;
    }
}
