#pragma once

#include "console.h"
#include "sproutdb.h"
#include "scenegraph/viewport.h"
#include "scenegraph/scene.h"
#include "scenegraph/camera.h"

static void registerQmlModules() {
    qmlRegisterType<Console>("Greenery", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery", 1, 0, "SproutDb");
    qmlRegisterType<Viewport>("Greenery", 1, 0, "Viewport");
    qmlRegisterType<Scene>("Greenery", 1, 0, "Scene");
    qmlRegisterType<Scene>("Greenery", 1, 0, "Camera");
}
