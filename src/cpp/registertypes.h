#pragma once
#include <QtQml>
#include <sprout/sproutdb.h>
#include "console.h"
//#include "osg-adapter/osgViewer/viewer.h"
//#include "osg-adapter/osgViewer/view.h"

static void registerTypes() {
    // Greenery
    qmlRegisterType<Console>("Greenery", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery", 1, 0, "SproutDb");

    // osgViewer
//    qmlRegisterType<View>("Osg", 1, 0, "View");
//    qmlRegisterType<Viewer>("Osg", 1, 0, "Viewer");
}
