#pragma once
#include "external/network/controller/RestController.h"
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QVariant>
#include <QDateTime>

namespace Controller {

class Module : public RestController {
public:
    static constexpr auto Name = "modules";

    enum class Visibility {
        Public,
        Private
    };

    struct Request {
        struct Create {
            std::optional<Id> moduleId;

            QVariant serialize() const {
                return QVariantMap({
                    { "module_id", QVariant::fromValue(moduleId) },
                });
            }
        };

        struct Update {
            QString name;
            Visibility visibility;

            QVariant serialize() const {
                return QVariantMap({
                    { "name", name },
                    { "visibility", int(visibility) },
                });
            }
        };
    };

    struct Response {
        struct Create {
            Id id;
            QString name;
            Visibility visibility;

            static Create deserialize(const QVariant& value) {
                QVariantMap params = value.toMap();

                Create result;
                result.id = params["id"].toLongLong();
                result.name = params["name"].toString();
                result.visibility = static_cast<Visibility>(params["visibility"].toInt());

                return result;
            }
        };

        struct Get {
            Id id;
            Id projectId;
            QString name;
            Visibility visibility;
            QDateTime updatedTime;

            static Get deserialize(const QVariant& value) {
                QVariantMap params = value.toMap();

                Get result;
                result.id = params["id"].toLongLong();
                result.projectId = params["project_id"].toLongLong();
                result.name = params["name"].toString();
                result.visibility = static_cast<Visibility>(params["visibility"].toInt());
                result.updatedTime = params["updated_at"].toDateTime();

                return result;
            }
        };
    };

    Module(Id projectId, RestApi* restApi);

    QString name() const override;

    Async::Task<Response::Create> create(std::optional<Id> moduleId = std::nullopt);
    Async::Task<void> update(Id id, const Request::Update& params);
    Async::Task<Response::Get> getOne(Id id);
    Async::Task<QList<Response::Get>> getAll();
    Async::Task<void> remove(Id id);

private:
    Id m_projectId;
};

}
