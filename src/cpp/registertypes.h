#pragma once
#include <QtQml>
#include <sprout/sproutdb.h>
#include "process.h"

static void registerTypes() {
    qmlRegisterType<Process>("Greenery", 1, 0, "Process");
    qmlRegisterType<SproutDb>("Greenery", 1, 0, "SproutDb");
}

