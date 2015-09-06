#include "sproutc.h"
#include "defines.h"

SproutC::SproutC(QObject *parent) : QObject(parent)
{

}

QVariantMap SproutC::version()
{
    QVariantMap version;
    QMapIterator<QString, int> i(Defines::version());
    while (i.hasNext()) {
        i.next();
        version[i.key()] = i.value();
    }
    return version;
}

