#pragma once
#include <QObject>

class Session;

class Project : public QObject {
public:
    enum class Template {
        Binary,
        Library
    };

    Project(QObject* parent = nullptr);
    void create(const QString& name, const QString& directory, Template projectTemplate);

private:
    QString m_path;
    Session* m_session = nullptr;
};
