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
    var axis;
    if (Math.abs(normal[0]) > Math.abs(normal[1]))
        if (Math.abs(normal[0]) > Math.abs(normal[2]))
            axis = 0; 
        else 
            axis = 2;
    else
        if (Math.abs(normal[1]) > Math.abs(normal[2])) 
            axis = 1;
        else 
            axis = 2;
    var u = (axis + 1) % 3;
    var v = (axis + 2) % 3;
    var normal = normalise(normal);
    var nu = normal[u] / normal[axis];
    var nv = normal[v] / normal[axis];
    var nd = dot(normal, p1) / normal[axis];
    var eu = p1[u];
    var ev = p1[v]; 
    var d = (edge1[u] * edge2[v] - edge1[v] * edge2[u]);
    var nu1 =  edge1[u] / d;
    var nv1 = -edge1[v] / d;
    var nu2 =  edge2[v] / d;
    var nv2 = -edge2[u] / d;
    var dir = ["dx", "dy", "dz"];
    var orig = ["ox", "oy", "oz"];
	var func = new Function("ox, oy, oz, dx, dy, dz, near, far",
		"var d = " + dir[axis] + (nu ? (" - " + (-nu) + " * " + dir[u]) : "") + (nv ? (" - " + (-nv) + " * " + dir[v]) : "") +";\n" +
		"var t = (" + nd + " - " + orig[axis] + (nu ? (" - " + nu + " * " + orig[u]) : "") + (nv ? (" - " + nv + " * " + orig[v]) : "") + ") / d;\n" +
		"if (t < near || t > far)\n" +
		"	return t;\n" +
		"var Pu = " + orig[u] + " + t * " + dir[u] + " - " + eu + ";\n" +
		"var Pv = " + orig[v] + " + t * " + dir[v] + " - " + ev + ";\n" +
		"var a2 = Pv * " + nu1 + " - Pu * " + (-nv1) + ";\n" +
		"if (a2 < 0)\n" +
		"	return -10000000;\n" +
		"var a3 = Pu * " + (-nu2) + " - Pv * " + nv2 + ";\n" +
		"if (a3 > 0)\n" +
		"	return -10000000;\n" +
	
		"if ((a2 - a3) > 1)\n" +
		"	return -10000000;\n" +
		"return t;\n"
	)
	func.normal = normal;
	func.material = [0.7, 0.7, 0.7];
	return func;
}
Triangle.prototype.toString = function TriangleToString (){ return "Triangle"; }

function Circle(pos, radius) {
    var cx = pos[0];
    var cy = pos[1];
    var cz = pos[2];
    var r2 = radius * radius;
    var f = function(ox, oy, oz, dx, dy, dz, near, far){
        var dirx = cx - ox;
        var diry = cy - oy;
        var dirz = cz - oz;
        var dDotDir = dirx * dx + diry * dy + dirz * dz;
        var dDorDirSqr = dDotDir * dDotDir;
        var dirLengthSqr = dirx * dirx + diry * diry + dirz * dirz;
        var D = dDorDirSqr - dirLengthSqr;
        if (D >= 0)
             return -10000000;
        var t = -dDorDirSqr - sqrt(-D);
        if (t < near || t > far)
             return t;
        f.normal = [(t * dx + dirx) / radius,
                    (t * dy + diry) / radius,
                    (t * dz + dirz) / radius];
        return t;
    }
	f.normal = [0,0,0];
	f.material = [0.7, 0.7, 0.7];
    return f;
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
	var dx = dir[0];
	var dy = dir[1];
	var dz = dir[2];
	var ox = origin[0];
	var oy = origin[1];
	var oz = origin[2];
	for (i = 0; i < count; i++) {
		var f = triangles[i];   
		var d = f(ox, oy, oz, dx, dy, dz, near, far);
		if (d < near || d > far)
			continue;
		far = d;
		closest = f;
	}

	if (!closest) {
		var background = this.background;
		return [background[0],background[1],background[2]];
	}

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
	var dx = D[0];
	var dy = D[1];
	var dz = D[2];
	var ox = O[0];
	var oy = O[1];
	var oz = O[2];
    for (i = 0; i < triangleCount; i++) {
        var d = triangles[i](ox, oy, oz, dx, dy, dz, near, far);
        if (d < near || d > far)
            continue;
        return true;
    }
    
    return false;
}
