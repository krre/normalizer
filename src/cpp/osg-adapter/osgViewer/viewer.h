#pragma once
#include "renderthread.h"
#include <QtCore>
#include <QtQuick>
#include <osgViewer/Viewer>

class RenderThread;

class Viewer : public QQuickItem
{
    Q_OBJECT

public:
    Viewer();
    static QList<QThread*> threads;

public Q_SLOTS:
    void ready();

protected:
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*);
private:
    RenderThread *m_renderThread;
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
};
