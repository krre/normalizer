#include "ComponentBuilder.h"
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QAttribute>
#include <QVector3D>

ComponentBuilder::ComponentBuilder() {

}

Qt3DRender::QGeometryRenderer* ComponentBuilder::createGridPlaneMesh(int lineCount) {
    Qt3DRender::QGeometryRenderer* planeMesh = new Qt3DRender::QGeometryRenderer();
    Qt3DRender::QGeometry* planeGeometry = new Qt3DRender::QGeometry(planeMesh);
    Qt3DRender::QBuffer* planeDataBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, planeGeometry);
    QByteArray vertexBufferData;
    QVector<QVector3D> vertices;

    // lineCount lines on x and z directions, each with two vector3Ds
    vertices.resize(lineCount * 2 * 2);
    vertexBufferData.resize(vertices.size() * 3 * sizeof(float));

    for (int i = 0; i < lineCount; i++) {
        int index = i * 2;
        vertices[index] = QVector3D(-1.0f + (float(i) * (2.0 / (lineCount - 1))), -1.0f, 0.0f);
        vertices[index + 1] = QVector3D(-1.0f + (float(i) * (2.0 / (lineCount - 1))), 1.0f, 0.0f);
        vertices[index + lineCount * 2] = QVector3D(-1.0f, -1.0f + (float(i) * (2.0 / (lineCount - 1))), 0.0f);
        vertices[index + lineCount * 2 + 1] = QVector3D(1.0f, -1.0f + (float(i) * (2.0 / (lineCount - 1))), 0.0f);
    }

    float* rawVertexArray = reinterpret_cast<float*>(vertexBufferData.data());
    int idx = 0;
    for (const auto& v : vertices) {
        rawVertexArray[idx++] = v.x();
        rawVertexArray[idx++] = v.y();
        rawVertexArray[idx++] = v.z();
    }

    planeDataBuffer->setData(vertexBufferData);

    addPositionAttributeToGeometry(planeGeometry, planeDataBuffer, lineCount * 4);

    planeMesh->setInstanceCount(1);
    planeMesh->setIndexOffset(0);
    planeMesh->setFirstInstance(0);
    planeMesh->setVertexCount(lineCount * 4);
    planeMesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    planeMesh->setGeometry(planeGeometry);

    return planeMesh;
}

Qt3DRender::QGeometryRenderer* ComponentBuilder::createLineMesh(const QVector3D& pos1, const QVector3D& pos2) {
    Qt3DRender::QGeometryRenderer* lineMesh = new Qt3DRender::QGeometryRenderer();
    Qt3DRender::QGeometry* lineGeometry = new Qt3DRender::QGeometry(lineMesh);
    Qt3DRender::QBuffer* lineDataBuffer = new Qt3DRender::QBuffer(Qt3DRender::QBuffer::VertexBuffer, lineGeometry);
    QByteArray vertexBufferData;
    QVector<QVector3D> vertices(2);
    vertexBufferData.resize(vertices.size() * 3 * sizeof(float));

    vertices[0] = pos1;
    vertices[1] = pos2;

    float* rawVertexArray = reinterpret_cast<float*>(vertexBufferData.data());
    int idx = 0;
    for (const auto& v : vertices) {
        rawVertexArray[idx++] = v.x();
        rawVertexArray[idx++] = v.y();
        rawVertexArray[idx++] = v.z();
    }

    lineDataBuffer->setData(vertexBufferData);

    addPositionAttributeToGeometry(lineGeometry, lineDataBuffer, 2);

    lineMesh->setInstanceCount(1);
    lineMesh->setIndexOffset(0);
    lineMesh->setFirstInstance(0);
    lineMesh->setVertexCount(2);
    lineMesh->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    lineMesh->setGeometry(lineGeometry);

    return lineMesh;
}

void ComponentBuilder::addPositionAttributeToGeometry(Qt3DRender::QGeometry* geometry, Qt3DRender::QBuffer* buffer, int count) {
    Qt3DRender::QAttribute* posAttribute = new Qt3DRender::QAttribute();
    posAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    posAttribute->setBuffer(buffer);
    posAttribute->setDataType(Qt3DRender::QAttribute::Float);
    posAttribute->setDataSize(3);
    posAttribute->setByteOffset(0);
    posAttribute->setByteStride(0);
    posAttribute->setCount(count);
    posAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());

    geometry->addAttribute(posAttribute);
}
