#pragma once
#include "network/api/Controller.h"
#include <QVersionNumber>

namespace Api {

class Workspace : public Controller {
public:
    using Id = uint16_t;

    enum class Method : MethodCode {
        Create = 0x00
    };

    Workspace(Network* network);

    Name name() const;

    Async::Task<Workspace::Id> create(const QString& name);
};

}
