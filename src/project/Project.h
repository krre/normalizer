#pragma once
#include <QObject>

class Project : public QObject {
public:
    enum class Template {
        Binary,
        Library
    };

    Project(QObject* parent = nullptr);
    void create(const QString& name, const QString& directory, Template projectTemplate);
};
