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
    scene = new THREE.Scene()
    var axisHelper = new THREE.AxisHelper(5)
    scene.add(axisHelper)

    var rootItemCount = model.length
    if (rootItemCount) {
        var step = Math.PI * 2 / rootItemCount
        var radius = 2
        var startLinePos
        var firstListPos
        for (var i in model) {
            var x = radius * Math.cos(step * i)
            var z = radius * Math.sin(step * i)
            var item
            var origin = new THREE.Vector3(0, 0, 0)
            var itemPos = new THREE.Vector3(x, 0, z)
            if (typeof model[i] === "object") {
                item = createSphere(itemPos)
                addBranch(model[i], origin, itemPos)
            } else {
                item = createBox(itemPos)
            }
            item.lookAt(origin)
            scene.add(item)
            if (!firstListPos) {
                firstListPos = itemPos
            }

            if (startLinePos) {
                scene.add(createLine(startLinePos, itemPos))
            }
            startLinePos = itemPos
        }
        scene.add(createLine(itemPos, firstListPos))
    }
}

function addBranch(branch, origin, direction) {
//    new THREE.Ray(origin, new THREE.Vector3(x, 0, z).normalize())
    print(JSON.stringify(origin))
}

function createBox(pos) {
    var geometry = new THREE.BoxGeometry(boxSize, boxSize, boxSize)
    var material = new THREE.MeshBasicMaterial({ color: 0x00ff00, wireframe: true })
    var box = new THREE.Mesh(geometry, material)
    box.position.x = pos.x
    box.position.y = pos.y
    box.position.z = pos.z
    return box
}

function createSphere(pos) {
    var geometry = new THREE.SphereGeometry(sphereSize)
    var material = new THREE.MeshBasicMaterial({ color: 0x00ff00, wireframe: true })
    var sphere = new THREE.Mesh(geometry, material)
    sphere.position.x = pos.x
    sphere.position.y = pos.y
    sphere.position.z = pos.z
    return sphere
}

function createLine(startPos, endPos) {
    var material = new THREE.LineBasicMaterial({ color: 0xff000ff })
    var geometry = new THREE.Geometry()
    geometry.vertices.push(startPos, endPos)
    var line = new THREE.Line(geometry, material)
    return line
}


