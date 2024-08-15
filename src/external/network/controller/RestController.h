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

    template <typename Request, typename Response>
    Async::Task<Response> create(const Request& params) {
        QVariant response = co_await m_restApi->post(endpoint(), params.serialize());
        co_return Response::deserialize(response);
    }

    template <typename Request>
    Async::Task<void> update(Id id, const Request& params) {
        co_await m_restApi->put(endpoint(id), params.serialize());
    }

    template <typename Response>
    Async::Task<Response> getOne(Id id) {
        QVariant response = co_await m_restApi->get(endpoint(id));
        co_return Response::deserialize(response);
    }

    template <typename Response>
    Async::Task<QList<Response>> getAll() {
        QVariant response = co_await restApi()->get(endpoint());
        QList<Response> result;

        for (const auto& item : response.toList()) {
            result.append(Response::deserialize(item));
        }

        co_return result;
    }

    Async::Task<void> remove(Id id);

private:
    RestApi* m_restApi = nullptr;
};

}
