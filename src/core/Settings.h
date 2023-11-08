#pragma once
#include "core/Constants.h"
#include <QSettings>
#include <QDir>
#include <QHostAddress>

class Settings {
public:
    template <typename T>
    class Key {
    public:
        using value_type = T;

        Key(const QString& key, T defaultValue = T{}) : m_key(key), m_default(defaultValue) {
        }

        const QString& key() const { return m_key; }
        T defaultValue() const { return m_default; }

    private:
        QString m_key;
        T m_default;
    };

    static void init() {
        #ifdef Q_OS_WIN
            QSettings::setDefaultFormat(QSettings::IniFormat);
        #endif
    }

    template <typename K>
    static void setValue(K::value_type value) {
        QSettings settings;
        settings.setValue(K().key(), value);
    }

    template <typename K>
    static K::value_type value() {
        K key;
        QSettings settings;
        return settings.value(key.key(), key.defaultValue()).template value<typename K::value_type>();
    }

    template <typename K>
    static bool contains() {
        QSettings settings;
        return settings.contains(K().key());
    }
};

namespace General {

struct Geometry : public Settings::Key<QByteArray> {
    Geometry() : Key("geometry") {}
};

struct State : public Settings::Key<QByteArray> {
    State() : Key("state") {}
};

struct Workspace : public Settings::Key<QString> {
    Workspace() : Key("workspace", QDir::homePath() + "/" + Const::Project::WorkspaceDir) {}
};

struct LastProject : public Settings::Key<QString> {
    LastProject() : Key("lastProject") {}
};

}

namespace Server {

struct Host : public Settings::Key<QString> {
    Host() : Key("Server/host", "api.norm.dev") {}
};

struct Port : public Settings::Key<quint16> {
    Port() : Key("Server/port", 80) {}
};

}

namespace Account {

struct Token : public Settings::Key<QString> {
    Token() : Key("Account/token") {}
};

}
