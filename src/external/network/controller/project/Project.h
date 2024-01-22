#pragma once
#include "external/network/controller/RestController.h"
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QVariant>
#include <QDateTime>

namespace Controller {

class Project : public RestController {
public:
    enum class Template {
        Binary,
        Library
    };

    struct CreateParams {
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

    struct UpdateParams {
        QString name;
        QString description;

        QVariant serialize() const {
            return QVariantMap({
                { "name", name },
                { "description", description },
            });
        }
    };

    struct GetParams {
        Id id;
        QString name;
        Template projectTemplate;
        QString description;
        QDateTime createdTime;
        QDateTime updatedTime;

        static GetParams deserialize(const QVariant& value) {
            QVariantMap params = value.toMap();

            GetParams result;
            result.id = params["id"].toLongLong();
            result.name = params["name"].toString();
            result.projectTemplate = static_cast<Template>(params["template"].toInt());
            result.description = params["description"].toString();
            result.createdTime = params["created_at"].toDateTime();
            result.updatedTime = params["updated_at"].toDateTime();

            return result;
        }
    };

    struct CreateResponse {
        Id id;

        static CreateResponse deserialize(const QVariant& value) {
            QVariantMap params = value.toMap();

            CreateResponse result;
            result.id = params["id"].toLongLong();

            return result;
        }
    };

    Project(RestApi* restApi);

    QString name() const override;

    static QString templateToString(Template projectTemplate) {
        return projectTemplate == Template::Binary ? "Binary" : "Library";
    }

    Async::Task<CreateResponse> create(const CreateParams& params);
    Async::Task<void> update(Id id, const UpdateParams& params);
    Async::Task<GetParams> getOne(Id id);
    Async::Task<QList<GetParams>> getAll();
    Async::Task<void> remove(Id id);
};

}
