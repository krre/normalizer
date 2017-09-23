#pragma once
#include <QObject>
#include <QString>

class SproutManager : public QObject {
    Q_OBJECT
public:
    explicit SproutManager(const QString& filePath, QObject* parent = nullptr);
    ~SproutManager();
    void create();
    void open();

private:
    QString filePath;
};
