#pragma once

namespace Qt3DRender {
    class QGeometryRenderer;
    class QGeometry;
    class QBuffer;
}

class QVector3D;

class ComponentBuilder {

public:
    ComponentBuilder();
    static Qt3DRender::QGeometryRenderer* createGridPlaneMesh(int lineCount);
    static Qt3DRender::QGeometryRenderer* createLineMesh(const QVector3D& pos1, const QVector3D& pos2);
    static void addPositionAttributeToGeometry(Qt3DRender::QGeometry *geometry, Qt3DRender::QBuffer *buffer, int count);

};
