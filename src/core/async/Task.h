#pragma once
#include <coroutine>
#include <QDebug>

namespace Async {

template <typename T>
class Awaiter;

template <typename T>
class Waker {
public:
    void setAwaiter(Awaiter<T>* awaiter) {
        m_awaiter = awaiter;
    }

protected:
    Awaiter<T>* awaiter() const {
        return m_awaiter;
    }

private:
    Awaiter<T>* m_awaiter;
};

template <typename T>
class Awaiter {
public:
    Awaiter(std::unique_ptr<Waker<T>> waker) : m_waker(std::move(waker)) {
        m_waker->setAwaiter(this);
    }

    bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<> handle) noexcept {
        m_handle = handle;
    }

    T await_resume() {
        return m_value;
    }

    void resume(const T& value) {
        if (m_handle && !m_handle.done()) {
            m_value = value;
            m_handle.resume();
        }
    }

private:
    std::unique_ptr<Waker<T>> m_waker;
    T m_value;
    std::coroutine_handle<> m_handle;
};

template <>
class Awaiter<void> {
public:
    bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<> handle) noexcept {
        m_handle = handle;
    }

    void await_resume() {}

    void resume() {
        if (m_handle && !m_handle.done()) {
            m_handle.resume();
        }
    }

private:
    std::coroutine_handle<> m_handle;
};

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
