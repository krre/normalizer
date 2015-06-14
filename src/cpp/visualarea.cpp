#include "visualarea.h"
#include <QDebug>

void VisualArea::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(0.19, 0.12, 0.08, 1.0);
}

void VisualArea::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void VisualArea::resizeGL(int w, int h) {
    Q_UNUSED(w)
    Q_UNUSED(h)
}

