#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class NodeModel;

class Space3d : public QWidget {
public:
    Space3d(NodeModel* model, Id projectId);

private:
    NodeModel* m_model = nullptr;
    Id m_projectId;
};
