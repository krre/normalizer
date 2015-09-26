#pragma once
#include <QtQml>
#include <sprout/sproutdb.h>
#include "console.h"
#include "osg-adapter/osgViewer/viewer.h"
#include "osg-adapter/scene.h"
#include "osg-adapter/camera.h"
#include "osg-adapter/node.h"

static void registerTypes() {
    // Greenery
    qmlRegisterType<Console>("Greenery", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery", 1, 0, "SproutDb");

    // Osg
    qmlRegisterType<Viewer>("Osg", 1, 0, "Viewer");
    qmlRegisterType<Scene>("Osg", 1, 0, "Scene");
    qmlRegisterType<Camera>("Osg", 1, 0, "Camera");
    qmlRegisterType<Node>("Osg", 1, 0, "Node");
}
