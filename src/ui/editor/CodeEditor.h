#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class Settings;
class Space3d;
class NodeTree;
class NodeModel;

class QComboBox;

class CodeEditor : public QWidget {
    Q_OBJECT
public:
    CodeEditor(Id projectId, Settings* settings);
    ~CodeEditor();

private:
    QScopedPointer<NodeModel> m_nodeModel;

    Space3d* m_space3d = nullptr;
    NodeTree* m_nodeTree = nullptr;
    Settings* m_settings = nullptr;

    QComboBox* pageComboBox = nullptr;
};
