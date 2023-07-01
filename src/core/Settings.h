#pragma once
#include "core/Constants.h"
#include <QSettings>
#include <QDir>

class Settings {
public:
    template <typename T>
    class Key {
    public:
        Key(const QString& key, T defaultValue = T{}) : m_key(key), m_default(defaultValue) {}

        const QString& key() const { return m_key; }
        T defaultValue() const { return m_default; }

    private:
        QString m_key;
        T m_default;
    };

    struct Geometry : public Key<QByteArray> {
        Geometry() : Key("geometry") {}
    };

    struct State : public Key<QByteArray> {
        State() : Key("state") {}
    };

    struct Workspace : public Key<QString> {
        Workspace() : Key("workspace", QDir::homePath() + "/" + Const::Project::WorkspaceDir) {}
    };

    template <typename T>
    static void setValue(const Key<T>& key, T value) {
        QSettings settings;
        settings.setValue(key.key(), value);
    }

    template <typename T>
    static T value(const Key<T>& key) {
        QSettings settings;
        return settings.value(key.key(), key.defaultValue()).template value<T>();
    }

    template <typename T>
    static bool contains(const Key<T>& key) {
        QSettings settings;
        return settings.contains(key.key());
    }
};
