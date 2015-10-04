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
        if (m_camera != nullptr) {
            n->setColor(m_camera->color());
        }

        static QSGGeometry::Attribute Vertex3D_Attributes[] = {
            QSGGeometry::Attribute::create(0, 3, GL_FLOAT, true)
        };

        static QSGGeometry::AttributeSet Vertex3D_AttributeSet = {
            1,
            sizeof(Vertex3D),
            Vertex3D_Attributes
        };

        QSGGeometry* geometry = new QSGGeometry(Vertex3D_AttributeSet, 4, 4);
        geometry->setLineWidth(3);
        geometry->setDrawingMode(GL_LINE_LOOP);

        Vertex3D* vertices = static_cast<Vertex3D*>(geometry->vertexData());
        vertices[0].set(0, 0, 0);
        vertices[1].set(0, height(), 0);
        vertices[2].set(width(), height(), 0);
        vertices[3].set(width(), 0, 0);

        quint16* indices = geometry->indexDataAsUShort();
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 3;

        QSGFlatColorMaterial* material = new QSGFlatColorMaterial;
        material->setColor(QColor(255, 0, 0));

        QSGTransformNode* transformNode = new QSGTransformNode;
        QMatrix4x4* matrix = new QMatrix4x4;
        if (m_camera != nullptr) {
            matrix->perspective(m_camera->verticalAngle(), m_camera->aspectRatio(), m_camera->nearPlane(), m_camera->farPlane());
        }
        matrix->translate(width() / 2.0, height() / 2.0, 0);
        matrix->scale(0.5);
        transformNode->setMatrix(*matrix);

        QSGGeometryNode* node = new QSGGeometryNode;
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);

        transformNode->appendChildNode(node);

        n->appendChildNode(transformNode);
    }

    n->setRect(boundingRect());

    return n;
}
