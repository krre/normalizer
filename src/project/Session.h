#pragma once
#include <QObject>

class Session : public QObject {
    Q_OBJECT
public:
    explicit Session(QObject* parent = nullptr);
    void create(const QString& projectPath);

private:
    QString m_dirPath;
};
