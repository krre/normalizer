#pragma once
#include <QObject>
#include <QProperty>

class Session;

class Project : public QObject {
public:
    enum class Template {
        Binary,
        Library
    };

    Project(QObject* parent = nullptr);

    void create(const QString& name, const QString& directory, Template projectTemplate);
    void open(const QString& path);

    QBindable<QString> path() { return &m_path; } ;
    QBindable<bool> opened() { return &m_opened; };

public slots:
    void save();
    void close();

private:
    Session* m_session = nullptr;

    QProperty<QString> m_path;
    QProperty<bool> m_opened { false };
};
