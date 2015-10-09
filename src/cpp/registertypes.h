#pragma once
#include <QtQml>
#include <sprout/sproutdb.h>
#include "console.h"
#include "osgbridge/osgViewer/viewer.h"

#include "osgbridge/osg/object.h"
#include "osgbridge/osg/node.h"
#include "osgbridge/osg/geode.h"
#include "osgbridge/osg/group.h"
#include "osgbridge/osg/transform.h"
#include "osgbridge/osg/drawable.h"
#include "osgbridge/osg/shape.h"
#include "osgbridge/osg/shapedrawable.h"
#include "osgbridge/osg/box.h"
#include "osgbridge/osg/sphere.h"

#include "osgbridge/osgText/textbase.h"
#include "osgbridge/osgText/text.h"

static void registerTypes() {
    // Greenery
    qmlRegisterType<Console>("Greenery", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery", 1, 0, "SproutDb");

    // osg
    qmlRegisterType<Viewer>("OsgBridge", 1, 0, "Viewer");
    qmlRegisterType<Node>("OsgBridge", 1, 0, "Node");
    qmlRegisterType<Geode>("OsgBridge", 1, 0, "Geode");
    qmlRegisterType<Group>("OsgBridge", 1, 0, "Group");
    qmlRegisterType<Transform>("OsgBridge", 1, 0, "Transform");
    qmlRegisterType<ShapeDrawable>("OsgBridge", 1, 0, "ShapeDrawable");
    qmlRegisterType<Box>("OsgBridge", 1, 0, "Box");
    qmlRegisterType<Sphere>("OsgBridge", 1, 0, "Sphere");
    qmlRegisterUncreatableType<Object>("OsgBridge", 1, 0, "Object", "Object is uncreatable type");
    qmlRegisterUncreatableType<Drawable>("OsgBridge", 1, 0, "Drawable", "Drawable is uncreatable type");
    qmlRegisterUncreatableType<Shape>("OsgBridge", 1, 0, "Shape", "Shape is uncreatable type");

    // osgText
    qmlRegisterType<Text>("OsgBridge", 1, 0, "Text");
    qmlRegisterUncreatableType<TextBase>("OsgBridge", 1, 0, "TextBase", "TextBase is uncreatable type");
}
