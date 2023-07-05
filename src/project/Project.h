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

    QProperty<bool> opened { false };

public slots:
    void save();
    void close();

private:
    QString m_path;
    Session* m_session = nullptr;
};
