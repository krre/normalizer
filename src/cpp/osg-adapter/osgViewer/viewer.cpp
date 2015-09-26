#include "viewer.h"
#include <QtQuick>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>

Viewer::Viewer()
{
    setFlag(ItemHasContents, true);
    viewer = new osgViewer::Viewer;
    viewer->setUpViewInWindow(0, 0, 800, 600);
    viewer->setSceneData(osgDB::readNodeFile("cow.osgt"));
    viewer->run();
}

QSGNode* Viewer::updatePaintNode(QSGNode* oldNode, QQuickItem::UpdatePaintNodeData*)
{
    return oldNode;
}
