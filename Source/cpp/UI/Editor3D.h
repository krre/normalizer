#pragma once
#include <QWidget>

class Editor3D : public QWidget {
    Q_OBJECT
public:
    explicit Editor3D(const QString& filePath);
    ~Editor3D();

signals:

public slots:

private:
    QString filePath;
};
