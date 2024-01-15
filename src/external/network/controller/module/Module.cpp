#include "Module.h"
#include "external/network/RestApi.h"

namespace Controller {

Module::Module(RestApi* restApi) : RestController(restApi) {

}

QString Module::name() const {
    return "module";
}

Async::Task<Id>Module::create(const CreateModule& module) {
    QVariant response = co_await restApi()->post(endpoint(), module.serialize());
    co_return response.toMap()["id"].toLongLong();
}

Async::Task<void>Module::update(Id id, const UpdateModule& module) {
    co_await restApi()->put(endpoint(id), module.serialize());
}

Async::Task<Module::GetModule> Controller::Module::getOne(Id id) {
    QVariant response = co_await restApi()->get(endpoint(id));
    co_return Module::GetModule::parse(response);
}

Async::Task<QList<Module::GetModule>>Module::getAll() {
    QVariant response = co_await restApi()->get(endpoint());
    QList<Module::GetModule> result;

    for (const auto& item : response.toList()) {
        result.append(Module::GetModule::parse(item));
    }

    co_return result;
}

Async::Task<void>Module::remove(Id id) {
    co_await restApi()->del(endpoint(id));
}

}
