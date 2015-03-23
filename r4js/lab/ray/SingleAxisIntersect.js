function SingleAxisIntersect(triangles) {
    this.left = [];
    this.right = [];
    this.leftOnly = [];
    this.rightOnly = [];
    var left = this.left;
    var right = this.right;
    var leftOnly = this.leftOnly;
    var rightOnly = this.rightOnly;
    for (var i = 0; i < triangles.length; i++) {
        var triangle = triangles[i];
        var isLeft = false;
        var isRight = false;
        for (var p = 0; p < 3; p++) {
            if (triangle.pos[p][1] <= 0)
                isLeft = true;
            if (triangle.pos[p][1] > 0)
                isRight = true;
        }
        if (isLeft) {
            left[left.length] = triangle;
            if (!isRight)
                leftOnly[leftOnly.length] = triangle;
        }
        if (isRight) {
            right[right.length] = triangle;
            if (!isLeft)
                rightOnly[rightOnly.length] = triangle;
        }
    }
    alert("Triangles: "+triangles.length+"; left.length: "+left.length+" right.length: " + right.length);
    return this;
}

SingleAxisIntersect.prototype.intersect = function(origin, dir, near, far, result) {
    var closest = null;
    /*var count = this.triangles.length
    var triangles = this.triangles;
    for (i = 0; i < count; i++) {
        var triangle = triangles[i];   
        var d = triangle.intersect(origin, dir, near, far);
        if (d == null || d > far || d < near)
            continue;
        far = d;
        closest = triangle;
    }*/
    if (origin[1] <= 0) {
        var count = this.left.length
		var triangles = this.left;
		for (i = 0; i < count; i++) {
			var triangle = triangles[i];   
			var d = triangle.intersect(origin, dir, near, far);
			if (d == null || d > far || d < near)
				continue;
			far = d;
			closest = triangle;
		}
		if (!closest && dir[1]>0) {
			triangles = this.rightOnly;
			count = this.rightOnly.length
			for (i = 0; i < count; i++) {
				var triangle = triangles[i];   
				var d = triangle.intersect(origin, dir, near, far);
				if (d == null || d > far || d < near)
					continue;
				far = d;
				closest = triangle;
			}
		}
    } else {
        var count = this.right.length
		var triangles = this.right;
		for (i = 0; i < count; i++) {
			var triangle = triangles[i];   
			var d = triangle.intersect(origin, dir, near, far);
			if (d == null || d > far || d < near)
				continue;
			far = d;
			closest = triangle;
		}
		if (!closest && dir[1]<0) {
			triangles = this.leftOnly;
			count = this.leftOnly.length
			for (i = 0; i < count; i++) {
				var triangle = triangles[i];   
				var d = triangle.intersect(origin, dir, near, far);
				if (d == null || d > far || d < near)
					continue;
				far = d;
				closest = triangle;
			}
		}
    
    }
    result.closest = closest;
    result.far = far;
    return !!closest;
}
