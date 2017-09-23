#pragma once
#include "../Sprout/SproutManager.h"
#include <QWidget>

class SproutManager;

class Editor3D : public QWidget {
    Q_OBJECT
public:
    explicit Editor3D(const QString& filePath);
    ~Editor3D();
    SproutManager* getSproutManager() const { return sproutManager; }

private:
    QString filePath;
    SproutManager* sproutManager;
};
