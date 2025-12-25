#pragma once
#include "network/api/Controller.h"
#include <QVersionNumber>

namespace Api {

class Workspace : public Controller {
public:
    enum class Method : MethodCode {
        Create = 0x00
    };

    Workspace(Network* network);

    Name name() const;

    Async::Task<Id> create(const QString& name);
};

}
