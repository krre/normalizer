#pragma once
#include "norm/Project.h"
#include <QObject>
#include <QProperty>

namespace Norm {
    class Project;
}

class Session;
class RenderView;

class ProjectExists : public std::exception {};

class Project : public QObject {
public:
    Project(RenderView* renderView, QObject* parent = nullptr);

    void create(const QString& name, const QString& directory, Norm::Project::Template projectTemplate);

    QBindable<QString> path() { return &m_path; } ;
    QBindable<bool> opened() { return &m_opened; };

public slots:
    void open(const QString& path);
    void save();
    void close();

private:
    void setPath(const QString& path);
    QString filePath() const;

    RenderView* m_renderView = nullptr;
    Session* m_session = nullptr;
    QScopedPointer<Norm::Project> m_normProject;

    QProperty<QString> m_path;
    QProperty<bool> m_opened { false };
};
