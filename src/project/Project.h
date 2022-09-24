#pragma once
#include <QString>

class Project {
public:
    enum class Target {
        Application,
        Library
    };

    enum class Format {
        Binary,
        Json
    };

    Project();

    QString path() const;
    Target target() const;

    void create(const QString& path, Target target);
    void open(const QString& path);
    void close();

    void write(Format format);
    void read(const QString& path);

private:
    QString m_path;
    Target m_target;
};
