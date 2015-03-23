function createScene() {
	var numTriangles = 2 * 6;
	var triangles = [];//new Array(numTriangles);
	var tfl = [-10,  10, -10];
	var tfr = [ 10,  10, -10];
	var tbl = [-10,  10,  10];
	var tbr = [ 10,  10,  10];
	var bfl = [-10, -10, -10];
	var bfr = [ 10, -10, -10];
	var bbl = [-10, -10,  10];
	var bbr = [ 10, -10,  10];
	
	// cube!!!
	// front
	var i = 0;
	
	triangles[i++] = new Triangle(tfl, tfr, bfr);
	triangles[i++] = new Triangle(tfl, bfr, bfl);
	// back
	triangles[i++] = new Triangle(tbl, tbr, bbr);
	triangles[i++] = new Triangle(tbl, bbr, bbl);
//        triangles[i-1].material = [0.7,0.2,0.2];
//            triangles[i-1].material.reflection = 0.8;
	// left
	triangles[i++] = new Triangle(tbl, tfl, bbl);
//            triangles[i-1].reflection = 0.6;
	triangles[i++] = new Triangle(tfl, bfl, bbl);
//            triangles[i-1].reflection = 0.6;
	// right
	triangles[i++] = new Triangle(tbr, tfr, bbr);
	triangles[i++] = new Triangle(tfr, bfr, bbr);
	// top
	triangles[i++] = new Triangle(tbl, tbr, tfr);
	triangles[i++] = new Triangle(tbl, tfr, tfl);
	// bottom
	triangles[i++] = new Triangle(bbl, bbr, bfr);
	triangles[i++] = new Triangle(bbl, bfr, bfl);

   // triangles[i++] = new Circle(tfl, 5);

	//Floor!!!!
	var green = [0.0, 0.4, 0.0];
	var grey = [0.4, 0.4, 0.4];
	grey.reflection = 1.0;
	var floorShader = function(tri, pos, view) {
		var x = ((pos[0]/32) % 2 + 2) % 2;
		var z = ((pos[2]/32 + 0.3) % 2 + 2) % 2;
		if (x < 1 != z < 1) {
			//in the real world we use the fresnel term...
		//    var angle = 1-dot(view, tri.normal);
		 //   angle *= angle;
		  //  angle *= angle;
		   // angle *= angle;
			//grey.reflection = angle;
			return grey;
		} else 
			return green;
	}
	var ffl = [-1000, -30, -1000];
	var ffr = [ 1000, -30, -1000];
	var fbl = [-1000, -30,  1000];
	var fbr = [ 1000, -30,  1000];
	triangles[i++] = new Triangle(fbl, fbr, ffr);
	triangles[i-1].shader = floorShader;
	triangles[i++] = new Triangle(fbl, ffr, ffl);
	triangles[i-1].shader = floorShader;
	
	var _scene = new Scene(triangles);//, BIHTree);
	_scene.lights[0] = [20, 38, -22];
	_scene.lights[0].colour = [0.7, 0.3, 0.3];
	_scene.lights[1] = [-23, 40, 17];
	_scene.lights[1].colour = [0.7, 0.3, 0.3];
	_scene.lights[2] = [23, 20, 17];
	_scene.lights[2].colour = [0.7, 0.7, 0.7];
	_scene.ambient = [0.1, 0.1, 0.1];
	return _scene;
}
