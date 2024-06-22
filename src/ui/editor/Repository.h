#pragma once
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QScopedPointer>

class RestApi;

class Repository {
public:
    Repository(Id projectId, RestApi* restApi);
    ~Repository();

    Id projectId() const;

    Async::Task<void> getModules();
    Async::Task<void> createModule(std::optional<Id> moduleId = std::nullopt);

private:
    Id m_projectId = 0;
    RestApi* m_restApi = nullptr;
};
