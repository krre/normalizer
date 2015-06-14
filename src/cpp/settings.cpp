#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    QString path = qApp->applicationDirPath() + QDir::separator() + "settings.ini";
    settings = new QSettings(path, QSettings::IniFormat, this);
    settings->setIniCodec("UTF-8");
}

void Settings::setGeometry(const QVariantMap &geometry)
{
    settings->beginGroup("Geometry");
        settings->setValue("x", geometry["x"].toString());
        settings->setValue("y", geometry["y"].toString());
        settings->setValue("width", geometry["width"].toString());
        settings->setValue("height", geometry["height"].toString());
        settings->setValue("split", geometry["split"].toString());
    settings->endGroup();
}

QVariantMap Settings::getGeometry()
{
    settings->beginGroup("Geometry");
        QVariantMap map;
        QStringList keys = settings->allKeys();
        if (keys.count()) {
            map["x"] = settings->value("x").toString();
            map["y"] = settings->value("y").toString();
            map["width"] = settings->value("width").toString();
            map["height"] = settings->value("height").toString();
            map["split"] = settings->value("split").toString();
        }
    settings->endGroup();

    return map;
}

void Settings::setLang(const QString &lang)
{
    settings->beginGroup("i18n");
        settings->setValue("lang", lang);
    settings->endGroup();
}

QString Settings::getLang()
{
    return settings->value("i18n/lang").toString();
}

void Settings::setRecentFiles(const QStringList &fileList)
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

void Settings::setSession(const QStringList &fileList)
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
