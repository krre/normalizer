#pragma once
#include <QtGlobal>

template <class T> class Singleton {

public:
    Singleton() {
        Q_ASSERT(m_instance == nullptr && "Singleton instance already exists!");
        m_instance = static_cast<T*>(this);
    }

    virtual ~Singleton() {
        m_instance = nullptr;
    }

    static T* instance() {
        Q_ASSERT(m_instance != nullptr && "Singleton instance is not initialized");
        return m_instance;
    }

    static void release() {
        if (m_instance != nullptr) {
            delete m_instance;
            m_instance = nullptr;
        }
    }

private:
    static T* m_instance;
};

template <class T> T* Singleton<T>::m_instance = nullptr;
