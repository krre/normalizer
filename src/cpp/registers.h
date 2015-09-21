#pragma once

#include "cyberspace/viewport.h"
#include "console.h"
#include "sproutdb.h"

static void registerQmlModules() {
    qmlRegisterType<Console>("Greenery", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery", 1, 0, "SproutDb");
    qmlRegisterType<Viewport>("Greenery", 1, 0, "Viewport");
}
