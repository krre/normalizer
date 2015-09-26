#include "registerTypes.h"
#include "console.h"
#include <sprout/sproutdb.h>
#include <QtQml>

RegisterTypes::RegisterTypes(QObject *parent) : QObject(parent)
{

}

void RegisterTypes::run()
{
    qmlRegisterType<Console>("Greenery", 0, 1, "Console");
    qmlRegisterType<SproutDb>("Greenery", 0, 1, "SproutDb");
}

