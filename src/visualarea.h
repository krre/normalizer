#ifndef VISUALAREA_H
#define VISUALAREA_H

#include <QOpenGLWidget>
#include <QWidget>

class VisualArea : public QOpenGLWidget {
    Q_OBJECT
public:
    VisualArea(QWidget *parent=0);
};

#endif // VISUALAREA_H
