#pragma once
#include <QObject>
#include <QProperty>

class Session;
class RenderView;

class ProjectExists : public std::exception {};

class Project : public QObject {
public:
    enum class Template {
        Binary,
        Library
    };

    Project(RenderView* renderView, QObject* parent = nullptr);

    void create(const QString& name, const QString& directory, Template projectTemplate);

    QBindable<QString> path() { return &m_path; } ;
    QBindable<bool> opened() { return &m_opened; };

public slots:
    void open(const QString& path);
    void save();
    void close();

private:
    void setPath(const QString& path);

    RenderView* m_renderView = nullptr;
    Session* m_session = nullptr;

    QProperty<QString> m_path;
    QProperty<bool> m_opened { false };
};
