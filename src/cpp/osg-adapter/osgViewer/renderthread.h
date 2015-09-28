#pragma once
#include <QtCore>
#include <QtGui>
#include <osgViewer/Viewer>
#include <osg/Texture2D>
#include "viewer.h"

// Based on Qt example "Scene Graph - Rendering FBOs in a thread"
class Viewer;
/*
 * The render thread shares a context with the scene graph and will
 * render into two separate FBOs, one to use for display and one
 * to use for rendering
 */
class RenderThread : public QThread
{
    Q_OBJECT
public:
    RenderThread(const QSize& size, osgViewer::Viewer* viewer, osg::Texture2D* fboTexture);
    QOffscreenSurface* surface = nullptr;
    QOpenGLContext* context = nullptr;

public slots:
    void renderNext();
    void shutDown();

signals:
    void textureReady(int id, const QSize &size);

private:
    QOpenGLFramebufferObject* m_renderFbo = nullptr;
    QOpenGLFramebufferObject* m_displayFbo = nullptr;

//    LogoRenderer *m_logoRenderer;
    osgViewer::Viewer* osgViewer;
    osg::Texture2D* fboTexture;
    QSize m_size;
};
