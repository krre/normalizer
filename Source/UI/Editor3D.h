#pragma once
#include <QWidget>

namespace Qt3DCore {
    class QEntity;
}

namespace Qt3DRender {
    class QCamera;
}

class Editor3D : public QWidget {
    Q_OBJECT

public:
    explicit Editor3D(const QString& filePath);
    void resetViewport();

private:
    Qt3DCore::QEntity* createScene();
    Qt3DRender::QCamera* camera;
};
