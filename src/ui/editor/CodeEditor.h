#pragma once
#include "core/CommonTypes.h"
#include <QWidget>

class RestApi;
class Settings;
class Space3d;
class NodeTree;
class NodeModel;
class NodeManager;

class QComboBox;

class CodeEditor : public QWidget {
    Q_OBJECT
public:
    CodeEditor(Id projectId, RestApi* restApi, Settings* settings);
    ~CodeEditor();

private:
    QScopedPointer<NodeModel> m_nodeModel;
    QScopedPointer<NodeManager> m_nodeManager;

    Space3d* m_space3d = nullptr;
    NodeTree* m_nodeTree = nullptr;
    Settings* m_settings = nullptr;

    QComboBox* pageComboBox = nullptr;
};
