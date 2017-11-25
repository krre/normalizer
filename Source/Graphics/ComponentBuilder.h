#pragma once

namespace Qt3DRender {
    class QGeometryRenderer;
    class QGeometry;
    class QBuffer;
}

class ComponentBuilder {

public:
    ComponentBuilder();
    static Qt3DRender::QGeometryRenderer* createGridPlane(int lineCount);
    static void addPositionAttributeToGeometry(Qt3DRender::QGeometry *geometry, Qt3DRender::QBuffer *buffer, int count);

};
