#pragma once
#include <QString>

class HttpNetwork;

namespace Controller {

class HttpController {
public:
    HttpController(HttpNetwork* network);
    virtual QString name() const = 0;

protected:
    HttpNetwork* network() const;

private:
    HttpNetwork* m_network = nullptr;
};

}
