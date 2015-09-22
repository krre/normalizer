#pragma once
#include <QtCore>
#include <QtGui>

class Camera : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)


public:
    explicit Camera(QObject *parent = 0);
    QColor color() const;
    void setColor(QColor color);

private:
    QColor m_color;

signals:
    void colorChanged(QColor color);
};
