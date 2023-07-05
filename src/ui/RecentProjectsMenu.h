#pragma once
#include <QMenu>

class RecentProjectsMenu : public QMenu {
    Q_OBJECT
public:
    RecentProjectsMenu(const QString& title, QWidget* parent = nullptr);
    ~RecentProjectsMenu();

    void addPath(const QString& path);

signals:
    void activated(const QString& path);

private slots:
    void clear();
};
