#pragma once
#include <QTreeView>

class QMenu;

class ProjectTreeView : public QTreeView {
    Q_OBJECT

public:
    explicit ProjectTreeView(QWidget* parent = nullptr);
    ~ProjectTreeView();

protected:
    void onMousePressed(const QModelIndex& index);

private:
    QMenu* contextMenu;

};
