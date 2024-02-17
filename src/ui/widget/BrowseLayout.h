#pragma once
#include <QHBoxLayout>

class QLineEdit;

class BrowseLayout : public QHBoxLayout {
public:
    BrowseLayout(const QString& text = {});

    QString text() const;
    void setFocus();

private slots:
    void onClicked();

private:
    QLineEdit* m_lineEdit = nullptr;
};
