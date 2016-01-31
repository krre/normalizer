var gl
var isLogEnabled = true
var isInitLogEnabled = false

function log(message) {
    if (isLogEnabled) {
        print(message)
    }
}

function initLog(message) {
    if (isInitLogEnabled) {
        print(message)
    }
}

function initializeGL(canvas) {
    initLog("*******************************************************************************************")
    initLog("initializeGL ENTER...")
    try {
        initLog("Getting Context");
        gl = canvas.getContext("canvas3d", { depth: true, antialias: true, alpha: false })
        initLog("Context received " + gl)

        var contextConfig = gl.getContextAttributes()
        initLog("Depth: " + contextConfig.alpha)
        initLog("Stencil: " + contextConfig.stencil)
        initLog("Antialiasing: " + contextConfig.antialias)
        initLog("Premultiplied alpha: " + contextConfig.premultipliedAlpha)
        initLog("Preserve drawingbuffer: " + contextConfig.preserveDrawingBuffer)
        initLog("Prefer Low Power To High Performance: " + contextConfig.preferLowPowerToHighPerformance)
        initLog("Fail If Major Performance Caveat: " + contextConfig.failIfMajorPerformanceCaveat)

        // Setup the OpenGL state
        gl.enable(gl.DEPTH_TEST)
        gl.enable(gl.CULL_FACE)

        gl.frontFace(gl.CCW)
        gl.cullFace(gl.BACK)

        gl.disable(gl.BLEND)

        gl.clearColor(0.19, 0.12, 0.08, 1.0)
        gl.clearDepth(1.0)

        // Set viewport
        gl.viewport(0, 0, canvas.width * canvas.devicePixelRatio,
                    canvas.height * canvas.devicePixelRatio)
    } catch (e){
        initLog("*******************************************************************************************")
        initLog("...initializeGL FAILURE!")
        print(e.message)
    }
    initLog("*******************************************************************************************")
}

function resizeGL(canvas) {
    var pixelRatio = canvas.devicePixelRatio;
    canvas.pixelSize = Qt.size(canvas.width * pixelRatio, canvas.height * pixelRatio)
    if (gl) {
        gl.viewport(0, 0, canvas.width * canvas.devicePixelRatio,
                    canvas.height * canvas.devicePixelRatio)
    }
}

function paintGL(canvas) {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT)
}
