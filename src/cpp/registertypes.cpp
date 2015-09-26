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
    qmlRegisterType<Console>("Greenery", 0, 1, "Console");
    qmlRegisterType<SproutDb>("Greenery", 0, 1, "SproutDb");

    // Osg
    qmlRegisterType<Viewport>("Osg", 1, 0, "Viewport");
}

