#pragma once
#include "external/network/controller/RestController.h"
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QVariant>
#include <QDateTime>

namespace Controller {

class Project : public RestController {
public:
    enum class Target {
        Application,
        Library
    };

    struct CreateRequest {
        QString name;
        Target target;
        QString description;

        QVariant serialize() const {
            return QVariantMap({
                { "name", name },
                { "target", int(target) },
                { "description", description },
            });
        }
    };

    struct UpdateRequest {
        QString name;
        QString description;

        QVariant serialize() const {
            return QVariantMap({
                { "name", name },
                { "description", description },
            });
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

    struct GetResponse {
        Id id;
        QString name;
        Target target;
        QString description;
        QDateTime createdTime;
        QDateTime updatedTime;

        static GetResponse deserialize(const QVariant& value) {
            QVariantMap params = value.toMap();

            GetResponse result;
            result.id = params["id"].toLongLong();
            result.name = params["name"].toString();
            result.target = static_cast<Target>(params["target"].toInt());
            result.description = params["description"].toString();
            result.createdTime = params["created_at"].toDateTime();
            result.updatedTime = params["updated_at"].toDateTime();

            return result;
        }
    };

    Project(RestApi* restApi);

    QString name() const override;

    static QString targetToString(Target target) {
        switch (target) {
            case Target::Application: return QObject::tr("Application");
            case Target::Library: return QObject::tr("Library");
        }

        return QString("n/a");
    }

    Async::Task<CreateResponse> create(const CreateRequest& params);
    Async::Task<void> update(Id id, const UpdateRequest& params);
    Async::Task<GetResponse> getOne(Id id);
    Async::Task<QList<GetResponse>> getAll();
    Async::Task<void> remove(Id id);
};

}
