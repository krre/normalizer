#pragma once
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QVariant>
#include <QDateTime>

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

        QVariant serialize() const {
            return QVariantMap({
                { "name", name },
                { "template", int(projectTemplate) },
                { "description", description },
            });
        }
    };

    struct UpdateProject {
        QString name;
        QString description;

        QVariant serialize() const {
            return QVariantMap({
                { "name", name },
                { "description", description },
            });
        }
    };

    struct GetProject {
        Id id;
        QString name;
        Template projectTemplate;
        QString description;
        QDateTime createdTime;
        QDateTime updatedTime;

        static GetProject parse(const QVariant& value) {
            QVariantMap params = value.toMap();

            GetProject result;
            result.id = params["id"].toLongLong();
            result.name = params["name"].toString();
            result.projectTemplate = static_cast<Template>(params["template"].toInt());
            result.description = params["description"].toString();
            result.createdTime = params["created_at"].toDateTime();
            result.updatedTime = params["updated_at"].toDateTime();

            return result;
        }
    };

    static QString templateToString(Template projectTemplate) {
        return projectTemplate == Template::Binary ? "Binary" : "Library";
    }

    virtual Async::Task<Id> create(const CreateProject& project) = 0;
    virtual Async::Task<void> update(Id id, const UpdateProject& project) = 0;
    virtual Async::Task<GetProject> getOne(Id id) = 0;
    virtual Async::Task<QList<GetProject>> getAll() = 0;
    virtual Async::Task<void> remove(Id id) = 0;
};

}
