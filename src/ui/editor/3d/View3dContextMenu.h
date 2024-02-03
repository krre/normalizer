#pragma once
#include <QMenu>

class View3dContextMenu : public QMenu {
    Q_OBJECT
public:
    enum class Action {
        AddModule
    };

    View3dContextMenu(QWidget* parent = nullptr);
};
