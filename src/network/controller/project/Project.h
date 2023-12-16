#pragma once
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QString>

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
    };

    struct UpdateProject {
        QString name;
        QString description;
    };

    struct GetProject {
        Id id;
        QString name;
        Template projectTemplate;
        QString description;
    };

    virtual Async::Task<Id> create(const CreateProject& project) = 0;
    virtual Async::Task<void> update(Id id, const UpdateProject& project) = 0;
    virtual Async::Task<GetProject> getOne(Id id) = 0;
    virtual Async::Task<QList<GetProject>> getList() = 0;
    virtual Async::Task<void> remove(Id id) = 0;
};

}
