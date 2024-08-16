#pragma once
#include "external/network/controller/RestController.h"
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include "program/Project.h"
#include <QVariant>
#include <QDateTime>

namespace Controller {

class Project : public RestController {
public:
    static constexpr auto Name = "projects";

    struct Request {
        struct Create {
            QString name;
            ::Project::Target target;
            QString description;

            QVariant serialize() const {
                return QVariantMap({
                    { "name", name },
                    { "target", int(target) },
                    { "description", description },
                });
            }
        };

        struct Update {
            QString name;
            QString description;

            QVariant serialize() const {
                return QVariantMap({
                    { "name", name },
                    { "description", description },
                });
            }
        };
    };

    struct Response {
        struct Create {
            Id id;

            static Create deserialize(const QVariant& value) {
                QVariantMap params = value.toMap();

                Create result;
                result.id = params["id"].toLongLong();

                return result;
            }
        };

        struct Get {
            Id id;
            QString name;
            ::Project::Target target;
            QString description;
            QDateTime createdTime;
            QDateTime updatedTime;

            static Get deserialize(const QVariant& value) {
                QVariantMap params = value.toMap();

                Get result;
                result.id = params["id"].toLongLong();
                result.name = params["name"].toString();
                result.target = static_cast<::Project::Target>(params["target"].toInt());
                result.description = params["description"].toString();
                result.createdTime = params["created_at"].toDateTime();
                result.updatedTime = params["updated_at"].toDateTime();

                return result;
            }
        };
    };

    Project(RestApi* restApi);

    QString name() const override;

    Async::Task<Response::Create> create(const Request::Create& params);
    Async::Task<void> update(Id id, const Request::Update& params);
    Async::Task<Response::Get> getOne(Id id);
    Async::Task<QList<Response::Get>> getAll();
    Async::Task<void> remove(Id id);
};

}
