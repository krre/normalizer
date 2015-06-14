#ifndef VISUALAREA_H
#define VISUALAREA_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class VisualArea : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    VisualArea() {}
private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

};

#endif // VISUALAREA_H
