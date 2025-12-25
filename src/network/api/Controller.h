#pragma once
#include "core/async/Task.h"
#include <QByteArray>
#include <expected>
#include <cstdint>

class Network;

namespace Api {

using ResponseTypeCode = uint8_t;
using ControllerCode = uint8_t;
using MethodCode = uint8_t;
using ErrorCode = uint8_t;

using Id = uint8_t;

class Controller {
public:
    enum class ResponseType : ResponseTypeCode {
        Success = 0x00,
        Error = 0x01
    };

    enum class Name : ControllerCode {
        Server = 0x00,
        Workspace = 0x01
    };

    Controller(Network* network);

    virtual Name name() const = 0;

    Network* network() const;

protected:
    Async::Task<std::expected<QByteArray, ErrorCode>> send(MethodCode method, const QByteArray& params = QByteArray());

private:
    Network* m_network = nullptr;
};

}
