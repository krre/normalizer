#pragma once
#include <QWidget>

namespace Qt3DCore {
    class QEntity;
}

namespace Qt3DRender {
    class QCamera;
}

namespace IrbisUnitBuilder {

class DatabaseManager;

class Editor3D : public QWidget {
    Q_OBJECT

public:
    explicit Editor3D(const QString& filePath);
    void resetViewport();
    void addUnit();

private:
    Qt3DCore::QEntity* createScene();
    Qt3DCore::QEntity* createGridPlane(Qt3DCore::QEntity* parent);
    Qt3DCore::QEntity* createOriginAxises(Qt3DCore::QEntity* parent);
    Qt3DRender::QCamera* camera;
    Qt3DCore::QEntity* gridPlane;
    Qt3DCore::QEntity* axises;
    DatabaseManager* databaseManager;
};

} // IrbisUnitBuilder
