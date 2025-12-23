#pragma once
#include <coroutine>
#include <memory>

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

class AwaiterBase {
public:
    bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<> handle) noexcept {
        m_handle = handle;
    }

protected:
    std::coroutine_handle<> handle() const { return m_handle; }

private:
    std::coroutine_handle<> m_handle;
};

template <typename T>
class Awaiter : public AwaiterBase {
public:
    Awaiter(std::unique_ptr<Waker<T>> waker) : m_waker(std::move(waker)) {
        m_waker->setAwaiter(this);
    }

    Awaiter() {}

    T await_resume() {
        return m_value;
    }

    void resume(const T& value) {
        if (handle() && !handle().done()) {
            m_value = value;
            handle().resume();
        }
    }

private:
    std::unique_ptr<Waker<T>> m_waker;
    T m_value;
};

template <>
class Awaiter<void> : public AwaiterBase {
public:
    void await_resume() {}

    void resume() {
        if (handle() && !handle().done()) {
            handle().resume();
        }
    }
};

}
