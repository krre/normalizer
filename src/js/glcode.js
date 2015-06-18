Qt.include("../3rdparty/three.js")
Qt.include("../3rdparty/TrackballControls.js")

var camera, scene, renderer, clock, trackballControls
var geometry, material, mesh

function initializeGL(canvas, eventSource) {
    clock = new THREE.Clock();

    camera = new THREE.PerspectiveCamera(75, canvas.width / canvas.height, 1, 10000)
    camera.position.z = 10

    trackballControls = new THREE.TrackballControls(camera, eventSource)
    trackballControls.rotateSpeed = 1.0
    trackballControls.zoomSpeed = 1.0
    trackballControls.panSpeed = 1.0

    scene = new THREE.Scene()

    var axisHelper = new THREE.AxisHelper(5)
    scene.add(axisHelper)

    geometry = new THREE.BoxGeometry(1, 1, 1)
    material = new THREE.MeshBasicMaterial({ color: 0x00ff00, wireframe: true })

    mesh = new THREE.Mesh(geometry, material)
    scene.add(mesh)

    renderer = new THREE.Canvas3DRenderer({canvas: canvas, devicePixelRatio: canvas.devicePixelRatio})
    renderer.setSize(canvas.width, canvas.height)
    renderer.setClearColor(new THREE.Color(0.19, 0.12, 0.08), 1)

    loadModel(astModel)
}

function paintGL(canvas) {
    var delta = clock.getDelta();
    trackballControls.update(delta);

    renderer.clear()
    renderer.render(scene, camera)
}

function resizeGL(canvas) {
    if (camera === undefined) return

    camera.aspect = canvas.width / canvas.height
    camera.updateProjectionMatrix()

    renderer.setSize(canvas.width, canvas.height)
}

function loadModel(model) {
    print(JSON.stringify(model))
    for (var item in model) {
        var obj = model[item]
        print(model[item], item, typeof obj)
//        loadModel(obj)

    }

//    print(typeof model)
}


