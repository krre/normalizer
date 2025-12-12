#pragma once
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

private:
    Network* m_network = nullptr;
};

}
