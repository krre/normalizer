#pragma once
#include <QtQml>
#include "process.h"

static void registerTypes() {
    qmlRegisterType<Process>("Greenery", 1, 0, "Process");
}

