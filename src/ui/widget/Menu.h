#pragma once
#include "Action.h"
#include <QMenu>

class Action;

class Menu : public QMenu {
    Q_OBJECT
public:
    Menu(const QString& title, QWidget* parent = nullptr) : QMenu(title, parent) {}

    template <typename Func>
    Action* addBindableAction(const QString& text, const QKeySequence& shortcut, const typename QtPrivate::FunctionPointer<Func>::Object* receiver, Func slot) {
        auto action = new Action(text, shortcut, receiver, slot, this);
        addAction(action);
        return action;
    }
};
