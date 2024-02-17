#pragma once
#include <QString>
#include <QObject>

class Project {
public:
    enum class Target {
        Application,
        Library
    };

    enum class Location {
        Local,
        Remote
    };

    static QString targetString(Target target) {
        switch (target) {
            case Target::Application: return QObject::tr("Application");
            case Target::Library: return QObject::tr("Library");
        }

        return QString("n/a");
    }

    static QString locationString(Location location) {
        switch (location) {
            case Location::Local: return QObject::tr("Local");
            case Location::Remote: return QObject::tr("Remote");
        }

        return QString("n/a");
    }

    Project(Target target, Location location, const QString& name, const QString& description);

    Target target() const;
    Location location() const;
    QString name() const;
    QString description() const;

private:
    Target m_target;
    Location m_location;
    QString m_name;
    QString m_description;
};
