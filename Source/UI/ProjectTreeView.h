#pragma once
#include <QTreeView>

class QMenu;

class ProjectTreeView : public QTreeView {
    Q_OBJECT

public:
    explicit ProjectTreeView(QWidget* parent = nullptr);
    ~ProjectTreeView();

signals:
    void openActivated(const QString& filePath);

private:
    void onMousePressed(const QModelIndex& index);
    void onDoubleClicked(const QModelIndex& index);

private:
    QMenu* _contextMenu;
    QString _selectedFile;

};
