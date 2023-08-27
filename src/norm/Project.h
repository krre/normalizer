#pragma once
#include <QString>

namespace Norm {

class Project {
public:
    enum class Template {
        Binary,
        Library
    };

    Project(const QString& name, Template projectTemplate);
    Project() = default;

    void setName(const QString& name);
    QString name() const;

    Template projectTemplate() const;

private:
    QString m_name;
    Template m_projectTemplate;
};

}
