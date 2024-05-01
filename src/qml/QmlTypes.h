#pragma once
#include "Account.h"
#include <QQmlEngine>

namespace Qml {

class QmlTypes {
public:
    static void registerTypes() {
        qmlRegisterType<Account>("Normalizer", 1, 0, "Account");
    }
};

}
