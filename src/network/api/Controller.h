#pragma once

namespace Api {

class Network;

class Controller {
public:
    Controller(Network* network);

    Network* network() const;

private:
    Network* m_network = nullptr;
};

}
