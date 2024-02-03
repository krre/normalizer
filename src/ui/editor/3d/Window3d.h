#pragma once
#include <Qt3DExtras/Qt3DWindow>

class Window3d : public Qt3DExtras::Qt3DWindow {
public:
    Window3d();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};
