#pragma once

class ApiNetwork;

namespace Api {

class ApiController {
public:
    ApiController(ApiNetwork* network);

    ApiNetwork* network() const;

private:
    ApiNetwork* m_network = nullptr;
};

}
