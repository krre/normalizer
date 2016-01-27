var gl
var isLogEnabled = true

function log(message) {
    if (isLogEnabled) {
        print(message)
    }
}

function initializeGL(canvas) {
    log("*******************************************************************************************")
    log("initializeGL ENTER...")
    try {
        log("Getting Context");
        gl = canvas.getContext("canvas3d", { depth:true, antialias:true, alpha:false })
        log("Context received " + gl)

        var contextConfig = gl.getContextAttributes()
        log("Depth: " + contextConfig.alpha)
        log("Stencil: " + contextConfig.stencil)
        log("Antialiasing: " + contextConfig.antialias)
        log("Premultiplied alpha: " + contextConfig.premultipliedAlpha)
        log("Preserve drawingbuffer: " + contextConfig.preserveDrawingBuffer)
        log("Prefer Low Power To High Performance: " + contextConfig.preferLowPowerToHighPerformance)
        log("Fail If Major Performance Caveat: " + contextConfig.failIfMajorPerformanceCaveat)

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
        log("*******************************************************************************************")
        print("...initializeGL FAILURE!")
        print(e)
        print(e.message)
    }
    log("*******************************************************************************************")
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
