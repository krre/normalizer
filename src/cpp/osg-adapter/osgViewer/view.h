#pragma once
#include <QtCore>
#include <QQuickItem>
#include <osgViewer/View>
#include <osg/Camera>
#include <osg/GraphicsContext>

class View : public QQuickItem
{
    Q_OBJECT
public:
    explicit View();
private:
    osgViewer::View* view;
    osg::Camera* camera;
    osg::GraphicsContext* graphicsContext;
    void geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry) override;
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*) override;
};
