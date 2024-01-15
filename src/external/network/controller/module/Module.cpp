#include "Module.h"
#include "external/network/RestApi.h"

namespace Controller {

Module::Module(RestApi* restApi) : RestController(restApi) {

}

QString Module::name() const {
    return "module";
}

Async::Task<Id>Module::create(const CreateModule& module) {
    co_return co_await RestController::create(module);
}

Async::Task<void>Module::update(Id id, const UpdateModule& module) {
    co_await RestController::update(id, module);
}

Async::Task<Module::GetModule> Controller::Module::getOne(Id id) {
    co_return co_await RestController::getOne<Module::GetModule>(id);
}

Async::Task<QList<Module::GetModule>>Module::getAll() {
    co_return co_await RestController::getAll<Module::GetModule>();
}

Async::Task<void>Module::remove(Id id) {
    co_await RestController::remove(id);
}

}
