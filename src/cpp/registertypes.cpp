#include "registerTypes.h"
#include "console.h"
#include "osg-adapter/viewport.h"
#include <sprout/sproutdb.h>
#include <QtQml>

RegisterTypes::RegisterTypes(QObject *parent) : QObject(parent)
{

}

void RegisterTypes::run()
{
    // Greenery
    qmlRegisterType<Console>("Greenery", 1, 0, "Console");
    qmlRegisterType<SproutDb>("Greenery", 1, 0, "SproutDb");

    // Osg
    qmlRegisterType<Viewport>("Osg", 1, 0, "Viewport");
}

