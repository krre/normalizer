#pragma once
#include <QAction>
#include <QBindable>

class Action : public QAction {
    Q_OBJECT
public:
    template <typename Func>
    Action(const QString& text, const QKeySequence& shortcut, const typename QtPrivate::FunctionPointer<Func>::Object* receiver, Func slot, QObject* parent = nullptr) : QAction(text, parent) {
        setShortcut(shortcut);
        connect(this, &Action::triggered, receiver, slot);
    }

    QBindable<bool> enabled() { return QBindable<bool>(this, "enabled"); }
};
