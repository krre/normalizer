.import "../style.js" as Style

function initializeGL(canvas) {
    logger.initLog("*******************************************************************************************")
    try {
        logger.initLog("Getting Context");
        gl = canvas.getContext("canvas3d", { depth: true, antialias: true, alpha: false })
        logger.initLog("Context received " + gl)

        var contextConfig = gl.getContextAttributes()
        logger.initLog("Depth: " + contextConfig.alpha)
        logger.initLog("Stencil: " + contextConfig.stencil)
        logger.initLog("Antialiasing: " + contextConfig.antialias)
        logger.initLog("Premultiplied alpha: " + contextConfig.premultipliedAlpha)
        logger.initLog("Preserve drawingbuffer: " + contextConfig.preserveDrawingBuffer)
        logger.initLog("Prefer Low Power To High Performance: " + contextConfig.preferLowPowerToHighPerformance)
        logger.initLog("Fail If Major Performance Caveat: " + contextConfig.failIfMajorPerformanceCaveat)

        // Setup the OpenGL state
        gl.enable(gl.DEPTH_TEST)
        gl.enable(gl.CULL_FACE)

        gl.frontFace(gl.CCW)
        gl.cullFace(gl.BACK)

        gl.disable(gl.BLEND)

        gl.clearColor(Style.bg.r, Style.bg.g, Style.bg.b, Style.bg.a)
        gl.clearDepth(1.0)

        // Set viewport
        gl.viewport(0, 0, canvas.width * canvas.devicePixelRatio,
                    canvas.height * canvas.devicePixelRatio)
    } catch (e){
        logger.initLog("*******************************************************************************************")
        logger.initLog("...initializeGL FAILURE!")
        print(e.message)
    }
    logger.initLog("*******************************************************************************************")
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
    scene.render()
}
