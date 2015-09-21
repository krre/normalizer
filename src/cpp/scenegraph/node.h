#pragma once
#include <QtCore>

class Node : public QObject
{
    Q_OBJECT
public:
    explicit Node(QObject *parent = 0);
};
