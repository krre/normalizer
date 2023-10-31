#pragma once
#include "Awaiter.h"
#include <coroutine>
#include <QDebug>

namespace Async {

template <typename T>
class Task {
public:
    struct promise_type;
    using Handle = std::coroutine_handle<promise_type>;

    Task(Handle handle) : m_handle(handle) {}

    ~Task() {
        if (m_handle.done()) {
            m_handle.destroy();
        }
    }

    struct promise_type {
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        Task<T> get_return_object() { return Handle::from_promise(*this); }
        void unhandled_exception() {}
        void return_value(T value) {}
    };

    Awaiter<T> operator co_await() {
        return Awaiter<T>{};
    }

private:
    Handle m_handle;
};

template <>
class Task<void> {
public:
    struct promise_type;
    using Handle = std::coroutine_handle<promise_type>;

    Task(Handle handle) : m_handle(handle) {}

    ~Task() {
        if (m_handle.done()) {
            m_handle.destroy();
        }
    }

    struct promise_type {
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        Task<void> get_return_object() { return Handle::from_promise(*this); }
        void unhandled_exception() {}
        void return_void() {}
    };

    Awaiter<void> operator co_await() {
        return Awaiter<void>{};
    }

private:
    Handle m_handle;
};

}
