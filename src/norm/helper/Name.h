#pragma once
#include <QString>

namespace Norm {

class Name;

namespace Helper {

class Name {
public:
    Name();

    Norm::Name* name() const;
    void setName(Norm::Name* name);

private:
    Norm::Name* m_name = nullptr;
};

}

}
