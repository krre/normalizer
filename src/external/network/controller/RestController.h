#pragma once
#include "core/CommonTypes.h"
#include <QString>

class HttpRestApi;

namespace Controller {

class RestController {
public:
    RestController(HttpRestApi* network);
    virtual QString name() const = 0;

    virtual QString endpoint() const;
    virtual QString endpoint(Id id) const;

protected:
    HttpRestApi* network() const;

private:
    HttpRestApi* m_network = nullptr;
};

}
