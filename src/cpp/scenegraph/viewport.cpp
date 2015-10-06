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
            n->appendChildNode(m_scene->transformNode());
        }
    }

    if (matrix != nullptr) {
        delete matrix;
    }
    matrix = new QMatrix4x4;

    if (m_camera != nullptr) {
        matrix->translate(width() / 2.0, height() / 2.0, 0); // move scene to origin
        matrix->perspective(m_camera->verticalAngle(), m_camera->aspectRatio(), m_camera->nearPlane(), m_camera->farPlane());
        matrix->translate(m_camera->position());
    }
    m_scene->transformNode()->setMatrix(*matrix);

    n->setRect(boundingRect());

    return n;
}
