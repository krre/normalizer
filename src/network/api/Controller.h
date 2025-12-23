#pragma once
#include "core/async/Task.h"
#include <QByteArray>
#include <cstdint>

namespace Api {

class Network;

using ControllerCode = uint8_t;
using MethodCode = uint8_t;
using ErrorCode = uint8_t;

class Controller {
public:
    enum class Name : ControllerCode {
        Server = 0x00
    };

    Controller(Network* network);

    virtual Name name() const = 0;

    Network* network() const;

protected:
    Async::Task<QByteArray> send(MethodCode method, const QByteArray& params = QByteArray());

private:
    Network* m_network = nullptr;
};

}
