#pragma once

namespace Api {

class ApiNetwork;

class ApiController {
public:
    ApiController(ApiNetwork* network);

    ApiNetwork* network() const;

private:
    ApiNetwork* m_network = nullptr;
};

}
