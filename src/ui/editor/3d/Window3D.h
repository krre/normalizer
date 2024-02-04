#pragma once
#include <Qt3DExtras/Qt3DWindow>

class NodeManager;

class Window3D : public Qt3DExtras::Qt3DWindow {
public:
    Window3D(NodeManager* nodeManager);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    NodeManager* m_nodeManager = nullptr;
};
