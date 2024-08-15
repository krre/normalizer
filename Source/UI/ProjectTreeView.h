#pragma once
#include <QTreeView>

class QMenu;

namespace IrbisCave {

class ProjectTreeView : public QTreeView {
    Q_OBJECT

public:
    explicit ProjectTreeView(QWidget* parent = nullptr);
    ~ProjectTreeView();

signals:
    void openActivated(const QString& filePath);
    void removeActivated(const QString& filePath);

private slots:
    void onMousePressed(const QModelIndex& index);
    void onDoubleClicked(const QModelIndex& index);
    void onFileRemove();
    void onFileRename();

private:
    QMenu* contextMenu;
    QString selectedFile;

};

} // IrbisCave
