#pragma once
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QString>
#include <QJsonObject>

namespace Controller {

class Project {
public:
    enum class Template {
        Binary,
        Library
    };

    struct CreateProject {
        QString name;
        Template projectTemplate;
        QString description;

        QJsonObject toJson() const {
            return {
                { "name", name },
                { "template", int(projectTemplate) },
                { "description", description },
            };
        }
    };

    struct UpdateProject {
        QString name;
        QString description;

        QJsonObject toJson() const {
            return {
                { "name", name },
                { "description", description },
            };
        }
    };

    struct GetProject {
        Id id;
        QString name;
        Template projectTemplate;
        QString description;

        static GetProject fromVariantMap(const QVariantMap& params) {
            GetProject result;
            result.id = params["id"].toLongLong();
            result.name = params["name"].toString();
            result.projectTemplate = static_cast<Template>(params["template"].toInt());
            result.description = params["description"].toString();

            return result;
        }
    };

    virtual Async::Task<Id> create(const CreateProject& project) = 0;
    virtual Async::Task<void> update(Id id, const UpdateProject& project) = 0;
    virtual Async::Task<GetProject> getOne(Id id) = 0;
    virtual Async::Task<QList<GetProject>> getList() = 0;
    virtual Async::Task<void> remove(Id id) = 0;
};

}
