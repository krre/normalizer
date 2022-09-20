#pragma once
#include <QLabel>

class SelectableLabel : public QLabel {
public:
    SelectableLabel(const QString& text, QWidget* parent = nullptr);
    SelectableLabel(QWidget* parent = nullptr);

private:
    void setup();
};
