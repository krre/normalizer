#pragma once
#include <QtGlobal>

template <class T> class Singleton {

public:
    Singleton() {
        Q_ASSERT(_instance == nullptr && "Singleton instance already exists!");
        _instance = static_cast<T*>(this);
    }

    virtual ~Singleton() {
        _instance = nullptr;
    }

    static T* instance() {
        Q_ASSERT(_instance != nullptr && "Singleton instance is not initialized");
        return _instance;
    }

    static void release() {
        if (_instance != nullptr) {
            delete _instance;
            _instance = nullptr;
        }
    }

private:
    static T* _instance;
};

template <class T> T* Singleton<T>::_instance = nullptr;
