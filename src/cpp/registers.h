#pragma once

#include "cyberspace/viewport.h"
#include "console.h"
#include "sproutdb.h"

static void registerQmlModules() {
    qmlRegisterType<Console>("Greenery", 0, 1, "Console");
    qmlRegisterType<SproutDb>("Greenery", 0, 1, "SproutDb");
    qmlRegisterType<Viewport>("Cyberspace", 0, 1, "Viewport");
}
