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
    if (m_scene != nullptr) {
        m_camera->setScene(m_scene);
    }
    emit cameraChanged(camera);
}

void Viewport::setScene(Scene *scene) {
    if (m_scene == scene)
        return;

    m_scene = scene;
    if (m_camera != nullptr) {
        m_camera->setScene(m_scene);
    }
    emit sceneChanged(scene);
}

QSGNode* Viewport::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData*)
{
    QSGSimpleRectNode* n = static_cast<QSGSimpleRectNode*>(oldNode);
    if (!n) {
        n = new QSGSimpleRectNode();
        if (m_scene != nullptr) {
            n->setColor(m_scene->color());
            n->appendChildNode(&transformNode);
            transformNode.appendChildNode(m_scene->rootNode());
        }

//        QSGTransformNode* transformNode = new QSGTransformNode;
//        QMatrix4x4* matrix = new QMatrix4x4;
//        if (m_camera != nullptr) {
//            matrix->perspective(m_camera->verticalAngle(), m_camera->aspectRatio(), m_camera->nearPlane(), m_camera->farPlane());
//        }
//        matrix->translate(width() / 2.0, height() / 2.0, 0);
//        matrix->scale(0.5);
//        transformNode->setMatrix(*matrix);

//        transformNode->appendChildNode(node);

//        n->appendChildNode(transformNode);
    }

    matrix.translate(width() / 2.0, height() / 2.0, 0);
    transformNode.setMatrix(matrix);
    n->setRect(boundingRect());

    return n;
}
