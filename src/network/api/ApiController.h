#pragma once

namespace Api {

class Network;

class ApiController {
public:
    ApiController(Network* network);

    Network* network() const;

private:
    Network* m_network = nullptr;
};

}
