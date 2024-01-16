#pragma once
#include "external/network/RestApi.h"
#include "core/async/Task.h"
#include "core/CommonTypes.h"
#include <QString>

class RestApi;

namespace Controller {

class RestController {
public:
    RestController(RestApi* restApi);

    virtual QString name() const = 0;

    virtual QString endpoint() const;
    virtual QString endpoint(Id id) const;

protected:
    RestApi* restApi() const;

    template <typename T>
    Async::Task<Id> create(const T& params) {
        QVariant response = co_await m_restApi->post(endpoint(), params.serialize());
        co_return response.toMap()["id"].toLongLong();
    }

    template <typename T>
    Async::Task<void> update(Id id, const T& params) {
        co_await m_restApi->put(endpoint(id), params.serialize());
    }

    template <typename T>
    Async::Task<T> getOne(Id id) {
        QVariant response = co_await m_restApi->get(endpoint(id));
        co_return T::deserialize(response);
    }

    template <typename T>
    Async::Task<QList<T>> getAll() {
        QVariant response = co_await restApi()->get(endpoint());
        QList<T> result;

        for (const auto& item : response.toList()) {
            result.append(T::deserialize(item));
        }

        co_return result;
    }

    Async::Task<void> remove(Id id);

private:
    RestApi* m_restApi = nullptr;
};

}
