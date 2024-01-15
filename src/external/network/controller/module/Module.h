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

    struct CreateModule {
        Id projectId;
        QString name;
        Visibility visibility;

        QVariant serialize() const {
            return QVariantMap({
                { "project_id", projectId },
                { "name", name },
                { "visibility", int(visibility) },
            });
        }
    };

    struct UpdateModule {
        QString name;
        Visibility visibility;

        QVariant serialize() const {
            return QVariantMap({
                { "name", name },
                { "visibility", int(visibility) },
            });
        }
    };

    struct GetModule {
        Id id;
        Id projectId;
        QString name;
        Visibility visibility;
        QDateTime updatedTime;

        static GetModule parse(const QVariant& value) {
            QVariantMap params = value.toMap();

            GetModule result;
            result.id = params["id"].toLongLong();
            result.projectId = params["project_id"].toLongLong();
            result.name = params["name"].toString();
            result.visibility = static_cast<Visibility>(params["visibility"].toInt());
            result.updatedTime = params["updated_at"].toDateTime();

            return result;
        }
    };

    Module(RestApi* restApi);

    QString name() const override;

    Async::Task<Id> create(const CreateModule& module);
    Async::Task<void> update(Id id, const UpdateModule& module);
    Async::Task<GetModule> getOne(Id id);
    Async::Task<QList<GetModule>> getAll();
    Async::Task<void> remove(Id id);
};

}
