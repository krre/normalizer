#pragma once
#include "core/CommonTypes.h"
#include "core/async/Task.h"
#include "NetworkController.h"
#include "manager/network/NetworkManager.h"
#include <QJsonObject>
#include <QUrlQuery>

namespace Controller {

class NetworkController;

namespace Action {

class AbstractAction {
public:
    AbstractAction(NetworkController* controller);

protected:
    NetworkController* controller() const { return m_controller; }

private:
    NetworkController* m_controller = nullptr;
};

template <typename Request, typename Response>
class Create : public AbstractAction {
public:
    Create(NetworkController* controller) : AbstractAction(controller) {}

    virtual Async::Task<Response> create(const Request& request) {
        QJsonObject data = request.serialize();
        QVariant response = co_await controller()->networkManager()->post(controller()->name(), data);
        co_return Response::parse(response);
    }
};

template <typename Request>
class Update : public AbstractAction {
public:
    Update(NetworkController* controller) : AbstractAction(controller) {}

    virtual Async::Task<void> update(const Request& request) {
        QJsonObject data = request.serialize();
        co_await controller()->networkManager()->put(controller()->name(), data);
    }
};

template <typename Response>
class GetById : public AbstractAction {
public:
    GetById(NetworkController* controller) : AbstractAction(controller) {}

    virtual Async::Task<Response> getById(Id id) {
        QUrlQuery query;
        query.addQueryItem("id", QString::number(id));

        QVariant response = co_await controller()->networkManager()->get(controller()->name(), query);
        co_return Response::parse(response);
    }
};

}

}
