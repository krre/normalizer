#pragma once
#include <QHBoxLayout>

class QLineEdit;

class BrowseLineEdit : public QHBoxLayout {
    Q_OBJECT
public:
    BrowseLineEdit(const QString& text = QString());

    QString text() const;
    void setText(const QString& text);

signals:
    void textChanged(const QString& text);

private slots:
    void onBrowseClicked();

private:
    QLineEdit* lineEdit = nullptr;
};
