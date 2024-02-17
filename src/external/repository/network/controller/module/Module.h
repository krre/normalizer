#pragma once
#include "external/repository/network/controller/RestController.h"
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

    struct CreateRequest {
        std::optional<Id> moduleId;

        QVariant serialize() const {
            return QVariantMap({
                { "module_id", QVariant::fromValue(moduleId) },
            });
        }
    };

    struct UpdateRequest {
        QString name;
        Visibility visibility;

        QVariant serialize() const {
            return QVariantMap({
                { "name", name },
                { "visibility", int(visibility) },
            });
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

    struct GetResponse {
        Id id;
        Id projectId;
        QString name;
        Visibility visibility;
        QDateTime updatedTime;

        static GetResponse deserialize(const QVariant& value) {
            QVariantMap params = value.toMap();

            GetResponse result;
            result.id = params["id"].toLongLong();
            result.projectId = params["project_id"].toLongLong();
            result.name = params["name"].toString();
            result.visibility = static_cast<Visibility>(params["visibility"].toInt());
            result.updatedTime = params["updated_at"].toDateTime();

            return result;
        }
    };

    Module(Id projectId, RestApi* restApi);

    QString name() const override;

    Async::Task<CreateResponse> create(std::optional<Id> moduleId = std::nullopt);
    Async::Task<void> update(Id id, const UpdateRequest& params);
    Async::Task<GetResponse> getOne(Id id);
    Async::Task<QList<GetResponse>> getAll();
    Async::Task<void> remove(Id id);

private:
    Id m_projectId;
};

}
