#include "Editor3D.h"
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

    Qt3DRender::QCamera* camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 5, -10.0f));
    camera->setViewCenter(QVector3D(0, 0 ,0));

    Qt3DExtras::QOrbitCameraController* cameraController = new Qt3DExtras::QOrbitCameraController(scene);
    cameraController->setLinearSpeed(500.0f);
    cameraController->setLookSpeed(1800.0f);
    cameraController->setCamera(camera);

    view->setRootEntity(scene);
}

Qt3DCore::QEntity* Editor3D::createScene() {
    Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity;

    // Material
    Qt3DRender::QMaterial* material = new Qt3DExtras::QPhongMaterial(rootEntity);

    // Plane
    Qt3DCore::QEntity* planeEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QPlaneMesh* planeMesh = new Qt3DExtras::QPlaneMesh;
    planeMesh->setWidth(10.f);
    planeMesh->setHeight(10.f);
    planeMesh->setMeshResolution(QSize(5, 5));

    Qt3DCore::QTransform* planeTransform = new Qt3DCore::QTransform;

    planeEntity->addComponent(planeMesh);
    planeEntity->addComponent(planeTransform);
    planeEntity->addComponent(material);

    return rootEntity;
}
