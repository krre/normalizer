#include "viewport.h"
#include <QtQuick>

Viewport::Viewport()
{
    setFlag(ItemHasContents, true);
}

void Viewport::setCamera(Camera *camera) {
    if (m_camera == camera)
        return;

    m_camera = camera;
    emit cameraChanged(camera);
}

void Viewport::setScene(Scene *scene) {
    if (m_scene == scene)
        return;

    m_scene = scene;
    emit sceneChanged(scene);
}

QSGNode* Viewport::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData*)
{
    QSGSimpleRectNode* n = static_cast<QSGSimpleRectNode*>(oldNode);
    if (!n) {
        n = new QSGSimpleRectNode();
        n->setColor(camera()->color());
    }
    n->setRect(boundingRect());

    return n;
}

