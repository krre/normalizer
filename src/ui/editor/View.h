#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class Settings;
class RenderView;
class TreeView;

class QComboBox;

class View : public QWidget {
    Q_OBJECT
public:
    View(const QUrl& editorUrl, Id projectId, Settings* settings);
    ~View();

private:
    RenderView* m_renderView = nullptr;
    TreeView* m_treeView = nullptr;
    Settings* m_settings = nullptr;

    QComboBox* pageComboBox = nullptr;
};
