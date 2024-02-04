#pragma once
#include <Qt3DExtras/Qt3DWindow>

class Window3D : public Qt3DExtras::Qt3DWindow {
public:
    Window3D();

protected:
    void mousePressEvent(QMouseEvent* event) override;
};
