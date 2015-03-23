function BIHTree(triangles) {
	this.triangles = triangles;
	function build(triangles, a_Root, a_Left, a_Right, a_Box, a_SBox, a_Depth) {
	    var forceAxis = 0;
		do {
			if (((a_Right - a_Left) < 2) || (a_Depth > 15)) { 
				// turn 'a_Root' into a leaf 
				a_Root.m_leaf = true;
				a_Root.m_index = a_Left; 
				a_Root.m_items = (a_Right - a_Left) + 1;
				a_Root.toString = function(){ return "Leaf: " + this.m_items +"\n" + "triangles: " + triangles.slice(a_Left, a_Right); }
				return; 
			} 
			
			// partition 
			var maxa = -1000000, minb = 1000000, candidate; 
			var i, axis, pivotidx = a_Left; 
			if (forceAxis) {
			    axis = forceAxis - 1;
			    forceAxis = 0;
			} else
				for (i = 0; i < 3; i++) { 
					axis = a_SBox.longestAxis; 
					candidate = (a_SBox[axis] + a_SBox[axis+3]) / 2;
					if (candidate >= a_Box[axis + 3])
						a_SBox[axis + 3] = candidate; 
					else if (candidate <= a_Box[axis])
						a_SBox[axis] = candidate; 
					else 
						break; 
				} 
			
			for (i = pivotidx; i <= a_Right; i++) { 
				var primbox = triangles[i].bounds; 
				if ((primbox[axis] + primbox[axis + 3]) / 2 < candidate) { 
					if (primbox[axis + 3] > maxa) 
						maxa = primbox[axis + 3];
					var temp = triangles[pivotidx];
					triangles[pivotidx] = triangles[i];
					triangles[i] = temp;
					pivotidx++; 
				} else if (primbox[axis] < minb) 
					minb = primbox[axis]; 
			} 
			
			// extra test 
			var lsbox = a_SBox.copy(), rsbox = a_SBox.copy(); 
			lsbox[axis + 3] = rsbox[axis] = candidate; 
			if ((pivotidx == a_Left) && (minb == a_Box[axis])) { 
				// left side is empty 
				a_SBox = rsbox.copy();
				//forceAxis = (axis + 1 % 3) + 1; 
				a_Depth++; 
				continue; 
			}

			if ((pivotidx > a_Right) && (maxa == a_Box[axis + 3])) { 
				// right side is empty 
				a_SBox = lsbox.copy(); 
				//forceAxis = (axis + 1 % 3) + 1;
				a_Depth++; 
				continue; 
			} 
			
            if (!((maxa != minb) || ((pivotidx > a_Left) && (pivotidx <= a_Right))))
			    alert("argh!");

			// update tree node box 
			var lbox = a_Box.copy(), rbox = a_Box.copy(); 
			lbox[axis + 3] = maxa; 
			rbox[axis] = minb; 
			// recurse 
			var lnode = [{},{}];
			a_Root.m_leaf = false;
			a_Root.m_children = lnode;
			a_Root.m_axis =  axis;
			a_Root.m_clip = [maxa, minb]; 
			
			// recurse 
			build(triangles, lnode[0], a_Left, pivotidx - 1, lbox, lsbox, a_Depth + 1); 
			build(triangles, lnode[1], pivotidx, a_Right, rbox, rsbox, a_Depth + 1); 
			break;
		} while(1);
	}
	this.root = {};
	var tempPoints = [];
	for (var t = 0; t < triangles.length; t++) {
	    for (var p = 0; p < 3; p++)
	        tempPoints.push(triangles[t].pos[p]);
	}
	var b = bounds(tempPoints);
	build(triangles, this.root, 0, triangles.length - 1, b, b, 0);
	document.getElementById("console").innerHTML = dumpTree(this.root);
	//throw "foo";
    return this;
}

function dumpTree(node) {
    if (node.m_leaf) 
        return "<li>("+[node.m_index,node.m_items,node.m_index+node.m_items-1]+")</li>";
    return "<li>branch<ul>"+dumpTree(node.m_children[0])+dumpTree(node.m_children[1])+"</ul></li>";
}

BIHTree.prototype.intersect = function(origin, dir, near, far, result) {
    var closest = null;
    var depth = 0;
  
    function traverse(triangles, node, origin, dir, near, far, result) {
		if (node.m_leaf) {
			var hit = false;
			var item = node.m_index;
			const end = item + node.m_items;
			for (; item < end; item++) {
				var triangle = triangles[item];   
				var d = triangle.intersect(origin, dir, near, far);
				if (d == null || d > far || d < near)
					continue;
				far = d;
				closest = triangle;
			}
			result.closest = closest;
			result.far = far;
			return !!closest;
		}
		var axis = node.m_axis;
	    if(Math.abs(dir[axis])<(0.00001)){
			//ray parallel to split plane
			if (origin[axis] <= node.m_clip[0])
				hit = traverse(triangles, node.m_children[0], origin, dir, near, far, result);
			if (hit)
			    far = result.far;
			if (origin[axis] >= node.m_clip[1])
				hit = traverse(triangles, node.m_children[1], origin, dir, near, far, result) || hit;
			return hit;
			
		}
		var ltr = dir[axis] > 0;
		var orig_near = near;
		var orig_far  = far;
		var inear = ltr^1;
		var ifar = inear^1;
		var nearClip = (node.m_clip[inear] - origin[axis]) / dir[axis];
		var farClip = (node.m_clip[ifar] - origin[axis]) / dir[axis];
		
		far = Math.min(nearClip + 0.001, far);
		var hit_near = false;
		if (near < far)
		    hit_near = traverse(triangles, node.m_children[inear], origin, dir, near, far, result);
		if (!hit_near)
			far = orig_far;
		else
		    far = result.far;
		    
		near = Math.max(farClip - 0.001, near);
		var hit_far = false;
		if (near < far)
		    hit_far = traverse(triangles, node.m_children[ifar], origin, dir, near, far, result);
		return hit_near || hit_far;
	}
    return traverse(this.triangles, this.root, origin, dir, near, far, result);
    /*
    
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
    result.closest = closest;
    result.far = far;
    */
    return !!closest;
}

BIHTree.prototype.blocked = function(O, D, far) {
    var near = 0.0001;
    var closest = null;
    var triangles = this.triangles;
    var triangleCount = triangles.length;
    for (i = 0; i < triangleCount; i++) {
        var triangle = triangles[i];   
        var d = triangle.intersect(O, D, near, far);
        if (d == null || d > far || d < near)
            continue;
        return triangle;
    }
    
    return false;
}
