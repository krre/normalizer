#pragma once
#include <QDialog>

class QLayout;
class QDialogButtonBox;

class StandardDialog : public QDialog {
public:
    StandardDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QDialogButtonBox* buttonBox() const;

    void setContentWidget(QWidget* contentWidget, bool stretchAfter = true);
    void setExpandContentWidget(QWidget* contentWidget, int stretch = 1);

    void setContentLayout(QLayout* contentLayout, bool stretchAfter = true);
    void setExpandContentLayout(QLayout* contentLayout, int stretch = 1);

    void setLayoutToFixedSize();
    void resizeToWidth(int width);

    void setOkButtonEnabled(bool enabled);

private:
    QDialogButtonBox* m_buttonBox = nullptr;
};
