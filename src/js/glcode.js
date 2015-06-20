Qt.include("../3rdparty/three.js")
Qt.include("../3rdparty/TrackballControls.js")
Qt.include("../3rdparty/fonts/helvetiker_bold.typeface.js")
Qt.include("../3rdparty/fonts/helvetiker_regular.typeface.js")

var camera, scene, renderer, clock, trackballControls
var rectSize = 1

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

    scene = new THREE.Scene()

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
    scene.add(createLine(new THREE.Vector3(0, 2, 0), new THREE.Vector3(0, -2, 0)))

    var rootItemCount = model.length
    if (rootItemCount) {
        var step = Math.PI * 2 / rootItemCount
        var radius = 1
        for (var i in model) {
            var x = radius * Math.cos(step * i)
            var z = radius * Math.sin(step * i)
            var origin = new THREE.Vector3(0, 0, 0)
            var itemPos = new THREE.Vector3(x, 0, z)
            var item = createItem(itemPos, model[i])
            item.lookAt(origin)
            scene.add(item)
            scene.add(createLine(origin, itemPos))
        }
    }
}

function createItem(pos, obj) {
    var item = new THREE.Object3D()
    var rect = createRectanle()
    item.add(rect)

    var text = createText(obj)
    text.position.y = rectSize / 2
    item.add(text)

    item.position.x = pos.x
    item.position.y = pos.y
    item.position.z = pos.z
    return item
}

function addBranch(branch, ray) {
    var step = Math.PI * 2 / branch.length
    var radius = 2
    for (var i in branch) {
        var y = radius * Math.cos(step * i)
        var z = radius * Math.sin(step * i)
        var item
        var itemPos = new THREE.Vector3(ray.origin.x + sphereSize, y, z)
        if (typeof branch[i] === "object") {
            item = createExpression(itemPos)
            var branchPos = itemPos.multiplyScalar(sphereSize)
            addBranch(branch[i], new THREE.Ray(itemPos, branchPos))
        } else {
            item = createLiteral(itemPos, branch[i])
        }
        item.lookAt(ray.origin)
        scene.add(item)
        scene.add(createLine(ray.origin, itemPos))
    }
}

function createLine(startPos, endPos) {
    var material = new THREE.LineBasicMaterial({ color: 0xff00ff })
    var geometry = new THREE.Geometry()
    geometry.vertices.push(startPos, endPos)
    var line = new THREE.Line(geometry, material)
    return line
}

function createRectanle() {
    var geometry = new THREE.BoxGeometry(rectSize, rectSize, 0)
    var material = new THREE.MeshBasicMaterial({color: 0x00ff00, wireframe: true })
    var rectMesh = new THREE.Mesh(geometry, material)
    return rectMesh
}

function createText(text) {
    var options = {
        size: 0.5,
        height: 0,
        weight: 'normal',
        font: 'helvetiker',
        style: 'normal',
        bevelThickness: 2,
        bevelSize: 4,
        bevelSegments: 3,
        bevelEnabled: false,
        curveSegments: 2,
        steps: 1
    }

    var textGeo = new THREE.TextGeometry(text, options)
    textGeo.computeBoundingBox()
    textGeo.computeVertexNormals()
    var textMat = new THREE.MeshBasicMaterial({ color: 0x00ff00, wireframe: true })
    var textMesh = new THREE.Mesh(textGeo, textMat)
    textMesh.rotation.y = Math.PI
    textMesh.position.x = textGeo.boundingBox.max.x / 2

    return textMesh
}

