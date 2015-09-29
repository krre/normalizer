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

        static QSGGeometry::Attribute Vertex3D_Attributes[] = {
            QSGGeometry::Attribute::create(0, 3, GL_FLOAT, true)
        };

        static QSGGeometry::AttributeSet Vertex3D_AttributeSet = {
            1,
            sizeof(Vertex3D),
            Vertex3D_Attributes
        };

        QSGGeometry* geometry = new QSGGeometry(Vertex3D_AttributeSet, 4);
        geometry->setLineWidth(3);
        geometry->setDrawingMode(GL_LINES);

        Vertex3D* vertices = static_cast<Vertex3D*>(geometry->vertexData());
        vertices[0].set(0, 0, -3);
        vertices[1].set(0, height(), -3);
        vertices[2].set(width(), 0, 0);
        vertices[3].set(width(), height(), 0);

        QSGFlatColorMaterial* material = new QSGFlatColorMaterial;
        material->setColor(QColor(255, 0, 0));

        QSGTransformNode* transformNode = new QSGTransformNode;
        QMatrix4x4* matrix = new QMatrix4x4;
        matrix->perspective(45, width() / height(), 0, 10000);
        matrix->translate(0, 0, -1);
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
