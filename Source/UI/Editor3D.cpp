#include "Editor3D.h"
#include "Graphics/ComponentBuilder.h"
#include <QtWidgets>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

Editor3D::Editor3D(const QString& filePath) {
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget* container = QWidget::createWindowContainer(view);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(container);

    Qt3DCore::QEntity* scene = createScene();

    camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

    Qt3DExtras::QOrbitCameraController* cameraController = new Qt3DExtras::QOrbitCameraController(scene);
#ifdef Q_OS_WIN
    cameraController->setLinearSpeed(50.0f);
    cameraController->setLookSpeed(180.0f);
#else
    cameraController->setLinearSpeed(500.0f);
    cameraController->setLookSpeed(1800.0f);
#endif
    cameraController->setCamera(camera);

    view->setRootEntity(scene);

    resetViewport();
}

void Editor3D::resetViewport() {
    camera->setPosition(QVector3D(0, -2, 2));
    camera->setViewCenter(QVector3D(0, 0 ,0));
    camera->setUpVector(QVector3D(0, 1, 0));
}

Qt3DCore::QEntity* Editor3D::createScene() {
    Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity;

    Qt3DCore::QEntity* planeEntity = new Qt3DCore::QEntity(rootEntity);

    Qt3DRender::QGeometryRenderer* planeMesh = ComponentBuilder::createGridPlaneMesh(11);
    planeEntity->addComponent(planeMesh);

    Qt3DRender::QMaterial* material = new Qt3DExtras::QPhongMaterial;
    planeEntity->addComponent(material);

    return rootEntity;
}
