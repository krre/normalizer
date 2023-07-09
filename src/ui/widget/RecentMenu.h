#pragma once
#include <QMenu>

class RecentMenu : public QMenu {
    Q_OBJECT
public:
    RecentMenu(const QString& title, QWidget* parent = nullptr);

    void addPath(const QString& path);

    QStringList pathes() const;
    void setPathes(const QStringList& pathes);

signals:
    void activated(const QString& path);

private slots:
    void clear();
};
