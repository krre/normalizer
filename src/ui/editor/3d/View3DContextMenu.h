#pragma once
#include <QMenu>

class View3DContextMenu : public QMenu {
    Q_OBJECT
public:
    enum class Action {
        AddModule
    };

    View3DContextMenu(QWidget* parent = nullptr);
};
