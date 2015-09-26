#pragma once
#include <QQuickItem>
#include <osgViewer/Viewer>

class Viewer : public QQuickItem
{
    Q_OBJECT

public:
    Viewer();

protected:
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*);
private:
    osgViewer::Viewer* viewer;
};
