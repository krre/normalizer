#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class Settings;
class Space3d;
class NodeTree;

class QComboBox;

class CodeEditor : public QWidget {
    Q_OBJECT
public:
    CodeEditor(const QUrl& webUrl, Id projectId, Settings* settings);
    ~CodeEditor();

private:
    Space3d* m_space3d = nullptr;
    NodeTree* m_nodeTree = nullptr;
    Settings* m_settings = nullptr;

    QComboBox* pageComboBox = nullptr;
};
