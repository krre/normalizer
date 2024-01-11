#pragma once
#include "external/network/controller/RestController.h"
#include "Project.h"

namespace Controller {

class NormProject : public RestController, public Project {
public:
    NormProject(HttpNetwork* network);
    QString name() const override;

    Async::Task<Id> create(const CreateProject& project) override;
    Async::Task<void> update(Id id, const UpdateProject& project) override;
    Async::Task<GetProject> getOne(Id id) override;
    Async::Task<QList<GetProject>> getAll() override;
    Async::Task<void> remove(Id id) override;
};

}
