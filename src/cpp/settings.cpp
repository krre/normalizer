#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    QString path = qApp->applicationDirPath() + QDir::separator() + "settings.ini";
    settings = new QSettings(path, QSettings::IniFormat, this);
    settings->setIniCodec("UTF-8");
}

void Settings::setLang(QString lang)
{
    settings->beginGroup("i18n");
        settings->setValue("lang", lang);
    settings->endGroup();
}

QString Settings::getLang()
{
    return settings->value("i18n/lang").toString();
}

void Settings::setRecentFiles(QStringList fileList)
{
    settings->remove("Recent");

    settings->beginGroup("Recent");
        for (int i = 0; i < fileList.count(); i++) {
            settings->setValue(QString::number(i), fileList.at(i));
        }
    settings->endGroup();
}

QStringList Settings::getRecentFiles()
{
    settings->beginGroup("Recent");
        QStringList keys = settings->allKeys();
        QStringList values;
        for (int i = 0; i < keys.count(); i++) {
            values.append(settings->value(keys.at(i)).toString());
        }
    settings->endGroup();

    return values;
}

void Settings::setSession(QStringList fileList)
{
    settings->remove("Session");

    settings->beginGroup("Session");
        for (int i = 0; i < fileList.count(); i++) {
            settings->setValue(QString::number(i), fileList.at(i));
        }
        settings->endGroup();
}

QStringList Settings::getSession()
{
    settings->beginGroup("Session");
        QStringList keys = settings->allKeys();
        QStringList values;
        for (int i = 0; i < keys.count(); i++) {
            values.append(settings->value(keys.at(i)).toString());
        }
    settings->endGroup();

    return values;
}
