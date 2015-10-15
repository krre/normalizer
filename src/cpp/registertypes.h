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
#include "osgbridge/osg/positionattitudetransform.h"
#include "osgbridge/osg/drawable.h"
#include "osgbridge/osg/shape.h"
#include "osgbridge/osg/shapedrawable.h"
#include "osgbridge/osg/box.h"
#include "osgbridge/osg/sphere.h"
#include "osgbridge/osg/cylinder.h"
#include "osgbridge/osg/camera.h"
#include "osgbridge/osg/boundingsphere.h"

#include "osgbridge/osgText/textbase.h"
#include "osgbridge/osgText/text.h"
#include "osgbridge/osgText/text3d.h"

#include "osgbridge/osgDB/osgdb.h"

static QObject* osgdb_singletontype_provider(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new OsgDb();
}

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
    qmlRegisterType<PositionAttitudeTransform>("OsgBridge", 1, 0, "PositionAttitudeTransform");
    qmlRegisterType<ShapeDrawable>("OsgBridge", 1, 0, "ShapeDrawable");
    qmlRegisterType<Box>("OsgBridge", 1, 0, "Box");
    qmlRegisterType<Sphere>("OsgBridge", 1, 0, "Sphere");
    qmlRegisterType<Cylinder>("OsgBridge", 1, 0, "Cylinder");
    qmlRegisterType<Camera>("OsgBridge", 1, 0, "Camera");
    qmlRegisterUncreatableType<Object>("OsgBridge", 1, 0, "Object", "Object is uncreatable type");
    qmlRegisterUncreatableType<Drawable>("OsgBridge", 1, 0, "Drawable", "Drawable is uncreatable type");
    qmlRegisterUncreatableType<Shape>("OsgBridge", 1, 0, "Shape", "Shape is uncreatable type");
    qmlRegisterUncreatableType<BoundingSphere>("OsgBridge", 1, 0, "BoundingSphere", "BoundingSphere is uncreatable type");

    // osgText
    qmlRegisterType<Text>("OsgBridge", 1, 0, "Text");
    qmlRegisterType<Text3D>("OsgBridge", 1, 0, "Text3D");
    qmlRegisterUncreatableType<TextBase>("OsgBridge", 1, 0, "TextBase", "TextBase is uncreatable type");

    // osgDB
    qmlRegisterSingletonType<OsgDb>("OsgBridge", 1, 0, "OsgDb", osgdb_singletontype_provider);
}
