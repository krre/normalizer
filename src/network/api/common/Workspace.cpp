#include "Workspace.h"

namespace Api {

Workspace::Workspace(Network* network) : Controller(network) {

}

Async::Task<Workspace::Id> Workspace::create(const QString& name) {
    QByteArray params;

    QByteArray nameBa = name.toUtf8();
    params += static_cast<uint8_t>(nameBa.size());
    params += nameBa;

    auto response = co_await send(static_cast<MethodCode>(Method::Create), params);
    Id id = 0;

    if (response.has_value()) {
        QDataStream stream(response.value());
        stream.setByteOrder(QDataStream::BigEndian);
        stream >> id;
    }

    co_return id;
}

Controller::Name Workspace::name() const {
    return Name::Workspace;
}

}
