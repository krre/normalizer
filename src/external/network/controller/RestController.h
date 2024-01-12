#pragma once
#include "core/CommonTypes.h"
#include <QString>

class RestApi;

namespace Controller {

class RestController {
public:
    RestController(RestApi* restApi);

    virtual QString name() const = 0;

    virtual QString endpoint() const;
    virtual QString endpoint(Id id) const;

protected:
    RestApi* restApi() const;

private:
    RestApi* m_restApi = nullptr;
};

}
