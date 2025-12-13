#pragma once
#include <QByteArray>
#include <cstdint>

namespace Api {

class Network;

class Controller {
public:
    enum class Name : uint8_t {
        Server = 0x00
    };

    Controller(Network* network);

    virtual Name name() const = 0;

    Network* network() const;

protected:
    void send(uint8_t method, const QByteArray& params = QByteArray());

private:
    Network* m_network = nullptr;
};

}
