Qt.include("three.js")
//var gl

 var camera, scene, renderer;
 var geometry, material, mesh;

 function initializeGL(canvas) {

     camera = new THREE.PerspectiveCamera( 75, canvas.width / canvas.height, 1, 10000 );
     camera.position.z = 1000;

     scene = new THREE.Scene();

     geometry = new THREE.BoxGeometry( 200, 200, 200 );
     material = new THREE.MeshBasicMaterial( { color: 0xff0000, wireframe: true } );

     mesh = new THREE.Mesh( geometry, material );
     scene.add( mesh );

     renderer = new THREE.Canvas3DRenderer( {canvas: canvas, devicePixelRatio: canvas.devicePixelRatio});
     renderer.setSize( canvas.width, canvas.height );
 }

 function paintGL(canvas) {

     mesh.rotation.x += 0.01;
     mesh.rotation.y += 0.02;

     renderer.render( scene, camera );

 }

 function resizeGL(canvas) {

     if (camera === undefined) return;

     camera.aspect = canvas.width / canvas.height;
     camera.updateProjectionMatrix();

     renderer.setSize( canvas.width, canvas.height );

 }

//function initializeGL(canvas) {
//    canvas3d = canvas
//    try {
//        gl = canvas.getContext("canvas3d")
//        gl.clearColor(0.19, 0.12, 0.08, 1.0)
//    } catch(e) {
//        print("initializeGL FAILURE!")
//        print(""+e)
//        print(""+e.message)
//    }
//}

//function paintGL(canvas) {
//    gl.clear(gl.COLOR_BUFFER_BIT)
//}

