#include "settings.h"

Settings::Settings(QObject* parent) : QObject(parent)
{
    QString path = qApp->applicationDirPath() + QDir::separator() + "settings.ini";
    settings = new QSettings(path, QSettings::IniFormat, this);
    settings->setIniCodec("UTF-8");
}

void Settings::setGeometry(const QMap<QString, int> &geometry)
{
    settings->beginGroup("Geometry");
        settings->setValue("x", geometry["x"]);
        settings->setValue("y", geometry["y"]);
        settings->setValue("width", geometry["width"]);
        settings->setValue("height", geometry["height"]);
    settings->endGroup();
}

QMap<QString, int> Settings::geometry()
{
    settings->beginGroup("Geometry");
        QMap<QString, int> map;
        QStringList keys = settings->allKeys();
        if (keys.count()) {
            map["x"] = settings->value("x").toInt();
            map["y"] = settings->value("y").toInt();
            map["width"] = settings->value("width").toInt();
            map["height"] = settings->value("height").toInt();
        }
    settings->endGroup();

    return map;
}

void Settings::setLang(const QString& lang)
{
    settings->beginGroup("i18n");
        settings->setValue("lang", lang);
    settings->endGroup();
}

QString Settings::lang()
{
    return settings->value("i18n/lang").toString();
}

void Settings::setRecentFiles(const QStringList& fileList)
{
    settings->remove("Recent");

    settings->beginGroup("Recent");
        for (int i = 0; i < fileList.count(); i++) {
            settings->setValue(QString::number(i), fileList.at(i));
        }
    settings->endGroup();
}

QStringList Settings::recentFiles()
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

void Settings::setSession(const QStringList& fileList)
{
    settings->remove("Session");

    settings->beginGroup("Session");
        for (int i = 0; i < fileList.count(); i++) {
            settings->setValue(QString::number(i), fileList.at(i));
        }
    settings->endGroup();
}

QStringList Settings::session()
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

void Settings::setSproutPath(const QString& path)
{
    settings->beginGroup("Sprout");
        settings->setValue("path", path);
    settings->endGroup();
}

QString Settings::sproutPath()
{
    return settings->value("Sprout/path").toString();
}

void Settings::setRecentDirectory(const QString& path)
{
    settings->beginGroup("RecentDirectory");
        settings->setValue("path", path);
    settings->endGroup();
}

QString Settings::recentDirectory()
{
    return settings->value("RecentDirectory/path").toString();
}

void Settings::setAutoLoadSession(bool value)
{
    settings->beginGroup("AutoLoad");
        settings->setValue("session", value);
    settings->endGroup();
}

bool Settings::autoLoadSession()
{
    return settings->value("AutoLoad/session").toBool();
}
