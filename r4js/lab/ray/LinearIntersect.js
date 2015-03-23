function LinearIntersect(triangles) {
    this.triangles = triangles;
    return this;
}

LinearIntersect.prototype.intersect = function(origin, dir, near, far, result) {
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
    result.closest = closest;
    result.far = far;
    return !!closest;
}
