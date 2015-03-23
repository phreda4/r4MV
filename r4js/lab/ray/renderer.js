// this camera code is from notes i made ages ago, it is from *somewhere* -- i cannot remember where
// that somewhere is
function Camera(origin, lookat, up) {
    var zaxis = normaliseVector(subVector(lookat, origin));
    var xaxis = normaliseVector(cross(up, zaxis));
    var yaxis = normaliseVector(cross(xaxis, subVector([0,0,0], zaxis)));
    var m = [];
    m[0] = xaxis[0]; m[1] = xaxis[1]; m[2] = xaxis[2];
    m[4] = yaxis[0]; m[5] = yaxis[1]; m[6] = yaxis[2];
    m[8] = zaxis[0]; m[9] = zaxis[1]; m[10] = zaxis[2];
    invertMatrix(m);
    m[3] = 0; m[7] = 0; m[11] = 0;
    this.origin = origin;
    var directions = this.directions = [0,0,0,0];
    directions[0] = normalise([-0.7,  0.7, 1]);
    directions[1] = normalise([ 0.7,  0.7, 1]);
    directions[2] = normalise([ 0.7, -0.7, 1]);
    directions[3] = normalise([-0.7, -0.7, 1]);
    directions[0] = transformMatrix(m, directions[0]);
    directions[1] = transformMatrix(m, directions[1]);
    directions[2] = transformMatrix(m, directions[2]);
    directions[3] = transformMatrix(m, directions[3]);
}

Camera.prototype.generateRayPair = function(y) {
    rays = [new Object(), new Object()];
    rays[0].origin = rays[1].origin = this.origin;
    var directions = this.directions;
    rays[0].dir = addVector(scale(directions[0], y), scale(directions[3], 1 - y));
    rays[1].dir = addVector(scale(directions[1], y), scale(directions[2], 1 - y));
    return rays;
}

function parse(s) { return eval(s); }
var _scene;

function processRenderCommand(args) {
    var scene = _scene;
    var width = args[0];
    var commands = args[1];
    var vadd = addVector;
    var vscale = scale;
    var vnormalise = normaliseVector;
    var data = new Array(width * commands.length * 3);
    var ncommands = commands.length;
    var index = -1;
    for (var c = 0; c < ncommands; ++c) {
        var command = commands[c];
        var r0origin = command[0];
        var r1origin = command[1];
        var r0dir = command[2];
        var r1dir = command[3];
    
        for (var x = 0; x < width; x++) {
            var xp = x / width;
            var origin = vadd(vscale(r0origin, xp), vscale(r1origin, 1 - xp));
            var dir = vnormalise(vadd(vscale(r0dir, xp), vscale(r1dir, 1 - xp)));
            var l = scene.intersect(origin, dir, 0.00001, 100000);
            data[++index]=(l[0]*255 + 0.5) | 0;
            data[++index]=(l[1]*255 + 0.5) | 0;
            data[++index]=(l[2]*255 + 0.5) | 0;
        }
    }
    return '[' + data.toString() + ']';
}

var global = this;
function renderRows(queue, camera, _scene, canvas, width, height, useImageData) {
    var index = -1;
    var y = height - 1;
    var stepSize = window.blockSize;
    if (!queue.workersAvailable) {
        var iSize = (1200 / width + 1) | 0;
        if (stepSize > iSize)
            stepSize = iSize;
    }

    function blitResults(result) {
        var result = parse(result);
        var i = -1;
        var index = (height - this.starty) * width * 4 - 1;
        for (var y = 0; y < stepSize; y++)
            for (var x = 0; x < width; x++) {
                data[++index] = result[++i];
                data[++index] = result[++i];
                data[++index] = result[++i];
                data[++index] = 255;
            }
        if (!window.animate || !vsync)
            canvas.putImageData(imageData, 0, 0, 0, height-this.starty, width, stepSize);
    };

    function paintResults(result) {
        var result = parse(result);
        var i = -1;
        var step = (result.length / 3) / width;
        for (var y = this.starty; i < result.length - 1; y--)
            for (var x = 0; x < width; x++) {
                canvas.setFillColor(result[++i]/255, result[++i]/255, result[++i]/255, 1);
                canvas.fillRect(x,height-y,1,1);
            }
        
    };

    var renderFunc = paintResults;
    if (useImageData && canvas.putImageData) {
        var imageData = canvas.createImageData(width, height);
        var data = imageData.data;
        renderFunc = blitResults;
    }

    // create jobs
    var jobs = [];
    while (y >= 0) {
        var commands = "[";
        var job = {starty: y};
        for (var i = 0; i < stepSize; i++) {
            var rays = camera.generateRayPair((y - i + stepSize) / height);
            commands += '[[' + rays[0].origin.toString() + '],' +
                         '[' + rays[1].origin.toString() + '],' +
                         '[' + rays[0].dir.toString() + '],' +
                         '[' + rays[1].dir.toString() + ']]';
            if (i < stepSize)
                commands += ',';
        }
        job.message = '[' + width + "," + commands + ']]';
        job.done = renderFunc;
        y -= stepSize;
        jobs[jobs.length] = job;
    }

    function go(){
        queue.runJobQueue(jobs, function(){
            if (useImageData)
                canvas.putImageData(imageData, 0, 0);
            if (camera.onFinished)
                camera.onFinished();
        })
    }
    if (queue.initialised)
        go();
    else
        queue.initJobQueue(_scene, processRenderCommand, go);
}

Camera.prototype.render = function(queue, scene, canvas, width, height, useImageData) {
    if (!canvas.createImageData)
        canvas.createImageData = function (w,h) { return this.getImageData(0,0,w,h); }
    if (window.CanvasRenderingContext2D && !CanvasRenderingContext2D.prototype.setFillColor)
        CanvasRenderingContext2D.setFillColor = function(r,g,b, a) {
            canvas.fillStyle = "rgb("+[result[++i]*255|0,result[++i]*255|0,result[++i]]*255|0+")";
        }
    renderRows(queue, this, scene, canvas, width, height, useImageData);
}

