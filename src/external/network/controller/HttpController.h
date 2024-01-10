#pragma once
#include "core/CommonTypes.h"
#include <QString>

class HttpNetwork;

namespace Controller {

class HttpController {
public:
    HttpController(HttpNetwork* network);
    virtual QString name() const = 0;

    virtual QString endpoint() const;
    virtual QString endpoint(Id id) const;

protected:
    HttpNetwork* network() const;

private:
    HttpNetwork* m_network = nullptr;
};

}
