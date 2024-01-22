#pragma once
#include "external/network/controller/RestController.h"
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QVariant>
#include <QDateTime>

namespace Controller {

class Module : public RestController {
public:
    enum class Visibility {
        Public,
        Private
    };

    struct CreateParams {
        std::optional<Id> moduleId;

        QVariant serialize() const {
            return QVariantMap({
                { "module_id", QVariant::fromValue(moduleId) },
            });
        }
    };

    struct UpdateParams {
        QString name;
        Visibility visibility;

        QVariant serialize() const {
            return QVariantMap({
                { "name", name },
                { "visibility", int(visibility) },
            });
        }
    };

    struct GetParams {
        Id id;
        Id projectId;
        QString name;
        Visibility visibility;
        QDateTime updatedTime;

        static GetParams deserialize(const QVariant& value) {
            QVariantMap params = value.toMap();

            GetParams result;
            result.id = params["id"].toLongLong();
            result.projectId = params["project_id"].toLongLong();
            result.name = params["name"].toString();
            result.visibility = static_cast<Visibility>(params["visibility"].toInt());
            result.updatedTime = params["updated_at"].toDateTime();

            return result;
        }
    };

    struct CreateResponse {
        Id id;
        QString name;
        Visibility visibility;

        static CreateResponse deserialize(const QVariant& value) {
            QVariantMap params = value.toMap();

            CreateResponse result;
            result.id = params["id"].toLongLong();
            result.name = params["name"].toString();
            result.visibility = static_cast<Visibility>(params["visibility"].toInt());

            return result;
        }
    };

    Module(Id projectId, RestApi* restApi);

    QString name() const override;

    Async::Task<CreateResponse> create(std::optional<Id> moduleId = std::nullopt);
    Async::Task<void> update(Id id, const UpdateParams& params);
    Async::Task<GetParams> getOne(Id id);
    Async::Task<QList<GetParams>> getAll();
    Async::Task<void> remove(Id id);

private:
    Id m_projectId;
};

}
