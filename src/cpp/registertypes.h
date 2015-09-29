#pragma once
#include <QtQml>
#include <sprout/sproutdb.h>
#include "console.h"
#include "scenegraph/viewport.h"
#include "scenegraph/scene.h"
#include "scenegraph/camera.h"
#include "scenegraph/node.h"
//#include "osg-adapter/osgViewer/viewer.h"
//#include "osg-adapter/osgViewer/view.h"

static void registerTypes() {
    // Greenery
    qmlRegisterType<Console>("Greenery", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery", 1, 0, "SproutDb");
    qmlRegisterType<Viewport>("Greenery", 1, 0, "Viewport");
    qmlRegisterType<Scene>("Greenery", 1, 0, "Scene");
    qmlRegisterType<Camera>("Greenery", 1, 0, "Camera");
    qmlRegisterType<Node>("Greenery", 1, 0, "Node");

    // osgViewer
//    qmlRegisterType<View>("Osg", 1, 0, "View");
//    qmlRegisterType<Viewer>("Osg", 1, 0, "Viewer");
}
