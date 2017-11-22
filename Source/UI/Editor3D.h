#pragma once
#include <QWidget>

namespace Qt3DCore {
    class QEntity;
}

class Editor3D : public QWidget {
    Q_OBJECT

public:
    explicit Editor3D(const QString& filePath);

private:
    Qt3DCore::QEntity* createScene();
};
