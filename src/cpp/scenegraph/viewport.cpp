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
    if (transformNode == nullptr) {
        transformNode = new QSGTransformNode;
    }

    if (!n) {
        n = new QSGSimpleRectNode();

        if (m_scene != nullptr) {
            n->setColor(m_scene->color());
            n->appendChildNode(transformNode);
            transformNode->appendChildNode(m_scene->rootNode());
        }
    }

    if (matrix != nullptr) {
        delete matrix;
    }
    matrix = new QMatrix4x4;
    matrix->translate(width() / 2.0, height() / 2.0, 0);
//    matrix->rotate(45, width() / 2, 0, 0);
    if (m_camera != nullptr) {
        matrix->perspective(m_camera->verticalAngle(), m_camera->aspectRatio(), m_camera->nearPlane(), m_camera->farPlane());
//        qDebug() << *matrix;
    }
    transformNode->setMatrix(*matrix);
    n->setRect(boundingRect());

    return n;
}
