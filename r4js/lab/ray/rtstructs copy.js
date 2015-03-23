function createVector(x,y,z) {
    return [x,y,z];
}

function sqrLengthVector(self) {
    var s0 = self[0];
    var s1 = self[1];
    var s2 = self[2];
    return s0 * s0 + s1 * s1 + s2 * s2;
}

var sqrt = Math.sqrt;

function lengthVector(self) {
    var s0 = self[0];
    var s1 = self[1];
    var s2 = self[2];
    return sqrt(s0 * s0 + s1 * s1 + s2 * s2);
}

function addVector(self, v) {
    self[0] += v[0];
    self[1] += v[1];
    self[2] += v[2];
    return self;
}

function subVector(self, v) {
    self[0] -= v[0];
    self[1] -= v[1];
    self[2] -= v[2];
    return self;
}

function scaleVector(self, scale) {
    self[0] *= scale;
    self[1] *= scale;
    self[2] *= scale;
    return self;
}

function normaliseVector(self) {
    var s0 = self[0];
    var s1 = self[1];
    var s2 = self[2];
    var len = Math.sqrt(s0 * s0 + s1 * s1 + s2 * s2);
    self[0] /= len;
    self[1] /= len;
    self[2] /= len;
    return self;
}

function add(v1, v2) {
    return [v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]];
}

function sub(v1, v2) {
    return [v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]];
}

function scalev(v1, v2) {
    return [v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]];
}

function dot(v1, v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

function scale(v, scale) {
    return [v[0] * scale, v[1] * scale, v[2] * scale];
}

function cross(v1, v2) {
	var v10 = v1[0];
	var v11 = v1[1];
	var v12 = v1[2];
	var v20 = v2[0];
	var v21 = v2[1];
	var v22 = v2[2];
    return [v11 * v22 - v12 * v21, 
            v12 * v20 - v10 * v22,
            v10 * v21 - v11 * v20];

}

function normalise(v) {
    var len = lengthVector(v);
    return [v[0] / len, v[1] / len, v[2] / len];
}

function transformMatrix(self, v) {
	var vals = self;
	var x  = vals[0] * v[0] + vals[1] * v[1] + vals[2] * v[2] + vals[3];
	var y  = vals[4] * v[0] + vals[5] * v[1] + vals[6] * v[2] + vals[7];
	var z  = vals[8] * v[0] + vals[9] * v[1] + vals[10] * v[2] + vals[11];
	return [x, y, z];
}

function invertMatrix(self) {
	var temp = [];
	var tx = -self[3];
	var ty = -self[7];
	var tz = -self[11];
	for (h = 0; h < 3; h++) 
	    for (v = 0; v < 3; v++) 
			temp[h + v * 4] = self[v + h * 4];
	for (i = 0; i < 11; i++)
	    self[i] = temp[i];
	self[3] = tx * self[0] + ty * self[1] + tz * self[2];
	self[7] = tx * self[4] + ty * self[5] + tz * self[6];
	self[11] = tx * self[8] + ty * self[9] + tz * self[10];
	return self;
}

function copyArray() {
    res = [];
    for (var i = 0; i < this.length; i++)
        res[i] = this[i];
    res.copy = this.copy;
    res.longestAxis = this.longestAxis;
	return res;
}

function bounds(args) {
    var p1 = args[0];
    var dims = [p1[0], p1[1], p1[2], p1[0], p1[1], p1[2]];
    for (var i = 1; i < args.length; i++) {
        var p = args[i];
        for (var axis = 0; axis < 3; axis++) {
            if (p[axis] < dims[axis])
                dims[axis] = p[axis];
            if (dims[axis + 3] < p[axis]) 
                dims[axis + 3] = p[axis];
        }
    }
    
    var longest = dims[dims.length] = dims[3] - dims[0];
    dims.longestAxis = 0;
    for (var axis = 1; axis < 3; axis++) {
        var size = dims[axis + 3] - dims[axis];
        dims[dims.length] = size;
        if (longest < size) {
            dims.longestAxis = axis;
            longest = size;
		}
	}
	dims.copy = copyArray;
	
    return dims;    
}

// Triangle intersection using barycentric coord method
function Triangle(p1, p2, p3) {
    this.blockers = [0,0,0,0,0,0,0,0,0,0];
    this.pos = [p1,p2,p3];
    //this.bounds = bounds(this.pos);
    var edge1 = sub(p3, p1);
    var edge2 = sub(p2, p1);
    var normal = cross(edge1, edge2);
    if (Math.abs(normal[0]) > Math.abs(normal[1]))
        if (Math.abs(normal[0]) > Math.abs(normal[2]))
            this.axis = 0; 
        else 
            this.axis = 2;
    else
        if (Math.abs(normal[1]) > Math.abs(normal[2])) 
            this.axis = 1;
        else 
            this.axis = 2;
    var axis = this.axis;
    var u = (axis + 1) % 3;
    var v = (axis + 2) % 3;
    var u1 = edge1[u];
    var v1 = edge1[v];
    
    var u2 = edge2[u];
    var v2 = edge2[v];
    this.normal = normalise(normal);
    this.nu = normal[u] / normal[axis];
    this.nv = normal[v] / normal[axis];
    this.nd = dot(normal, p1) / normal[axis];
    var det = u1 * v2 - v1 * u2;
    this.eu = p1[u];
    this.ev = p1[v]; 
    this.nu1 = u1 / det;
    this.nv1 = -v1 / det;
    this.nu2 = v2 / det;
    this.nv2 = -u2 / det; 
    this.material = [0.7, 0.7, 0.7];
}
Triangle.prototype.toString = function TriangleToString (){ return "Triangle"; }
Triangle.prototype.intersect = function TriangleIntersect (orig, dir, near, far) {
    var axis = this.axis;
    var u = (axis + 1) % 3;
    var v = (axis + 2) % 3;
    var nu = this.nu;
    var nv = this.nv;
    var d = dir[axis] + nu * dir[u] + nv * dir[v];
    var t = (this.nd - orig[axis] - nu * orig[u] - nv * orig[v]) / d;
    if (t < near || t > far)
        return null;
    var Pu = orig[u] + t * dir[u] - this.eu;
    var Pv = orig[v] + t * dir[v] - this.ev;
    var a2 = Pv * this.nu1 + Pu * this.nv1;
    if (a2 < 0) 
        return null;
    var a3 = Pu * this.nu2 + Pv * this.nv2;
    if (a3 < 0) 
        return null;

    if ((a2 + a3) > 1) 
        return null;
    return t;
}

function Scene(a_triangles, intersectorClass) {
    this.triangles = a_triangles;
    if (intersectorClass)
        this.intersector = new intersectorClass(a_triangles);
    this.lights = [];
    this.ambient = [0,0,0];
    this.background = [0.8,0.8,1];
}
var zero = [0,0,0];

Scene.prototype.intersect = function SceneIntersect (origin, dir, near, far) {
    var closest = null;
	var count = this.triangles.length
	var triangles = this.triangles;
	for (i = 0; i < count; i++) {
		var triangle = triangles[i];   
		var d = triangle.intersect(origin, dir, near, far);
		if (d == null || d > far || d < near)
			continue;
		far = d;
		closest = triangle;
	}
	var background = this.background;
	if (!closest)
		return [background[0],background[1],background[2]];
        
    var normal = closest.normal;
    var hit = add(origin, scale(dir, far)); 
    if (dot(dir, normal) > 0)
        normal = [-normal[0], -normal[1], -normal[2]];
    
    var colour = null;
    if (closest.shader) {
        colour = closest.shader(closest, hit, dir);
    } else {
        colour = closest.material;
    }
    
    // do reflection
    var reflected = null;
    if (colour.reflection > 0.001) {
		var reflection = addVector(scale(normal, -2*dot(dir, normal)), dir);
        reflected = this.intersect(hit, reflection, 0.0001, 1000000);
        if (colour.reflection >= 0.999999)
            return reflected;
    }
    var ambient = this.ambient;
    var l = [ambient[0], ambient[1], ambient[2]];
    var lightCount = this.lights.length;
    for (var i = 0; i < lightCount; i++) {
        var light = this.lights[i];
        var toLight = sub(light, hit);
        var distance = lengthVector(toLight);
        scaleVector(toLight, 1.0/distance);
        distance -= 0.0001;
        if (this.blocked(hit, toLight, distance))
            continue;

        var nl = dot(normal, toLight);
        if (nl > 0)
            addVector(l, scale(light.colour, nl));
    }
    l = scalev(l, colour);
    if (reflected)
        l = addVector(scaleVector(l, 1 - colour.reflection), scaleVector(reflected, colour.reflection));

    return l;
}

Scene.prototype.blocked = function SceneBlocked (O, D, far) {
    var near = 0.0001;
    var closest = null;
    var triangles = this.triangles;
    var triangleCount = triangles.length;
    for (i = 0; i < triangleCount; i++) {
        var triangle = triangles[i];
        var d = triangle.intersect(O, D, near, far);
        if (d == null || d > far || d < near)
            continue;
        return true;
    }
    
    return false;
}
