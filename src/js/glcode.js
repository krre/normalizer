Qt.include("../3rdparty/three.js")
Qt.include("../3rdparty/TrackballControls.js")

var camera, scene, renderer, clock, trackballControls
var geometry, material, mesh
var boxSize = 1
var sphereSize = 1

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
    var rootItemCount = model.length
    if (rootItemCount) {
        var step = Math.PI * 2 / rootItemCount
        var radius = 2
        for (var i in model) {
            var x = radius * Math.cos(step * i)
            var z = radius * Math.sin(step * i)
            if (typeof model[i] === "object") {
                scene.add(createSphere(x, 0, z))
            } else {
                scene.add(createBox(x, 0, z))
            }
        }
    }
}

function createBox(x, y, z) {
    var geometry = new THREE.BoxGeometry(boxSize, boxSize, boxSize)
    var material = new THREE.MeshBasicMaterial({ color: 0x00ff00, wireframe: true })
    var box = new THREE.Mesh(geometry, material)
    box.position.x = x
    box.position.y = y
    box.position.z = z
    return box
}

function createSphere(x, y, z) {
    var geometry = new THREE.SphereGeometry(sphereSize)
    var material = new THREE.MeshBasicMaterial({ color: 0x00ff00, wireframe: true })
    var sphere = new THREE.Mesh(geometry, material)
    sphere.position.x = x
    sphere.position.y = y
    sphere.position.z = z
    return sphere
}


