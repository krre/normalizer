#pragma once
#include "Project.h"

class HttpNetwork;

namespace Controller {

class NormProject : public Project {
public:
    NormProject(HttpNetwork* httpNetwork);

    static constexpr auto NAME = "project";

    Async::Task<Id> create(const CreateProject& project) override;
    Async::Task<void> update(Id id, const UpdateProject& project) override;
    Async::Task<GetProject> getOne(Id id) override;
    Async::Task<QList<GetProject>> getList() override;
    Async::Task<void> remove(Id id) override;

private:
    HttpNetwork* m_httpNetwork = nullptr;
};

}
