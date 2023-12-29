#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class RenderView;
class TreeView;

class View : public QWidget {
    Q_OBJECT
public:
    View(const QUrl& editorUrl, Id projectId);

private:
    RenderView* m_renderView = nullptr;
    TreeView* m_treeView = nullptr;
};
