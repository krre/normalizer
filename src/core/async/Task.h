#pragma once
#include <coroutine>
#include <exception>

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

    struct FinalAwaiter {
        bool await_ready() const noexcept { return false; }
        std::coroutine_handle<> await_suspend(Handle handle) noexcept {
            auto& promise = handle.promise();

            if (promise.m_awatingHandle != nullptr) {
                return promise.m_awatingHandle;
            } else {
                return std::noop_coroutine();
            }
        }

        T await_resume() noexcept {
            return T{};
        }
    };

    struct TaskAwaiter {
        TaskAwaiter(Handle handle) : m_handle(handle)  { }

        bool await_ready() { return false; }

        void await_suspend(std::coroutine_handle<> awatingHandle) noexcept {
            m_handle.promise().setAwaitingHandle(awatingHandle);
        }

        T await_resume() {
            if (m_handle.promise().m_exception) {
                std::rethrow_exception(m_handle.promise().m_exception);
            }

            return m_handle.promise().m_value;
        }

        Handle m_handle;
    };

    struct promise_type {
        std::suspend_never initial_suspend() { return {}; }
        auto final_suspend() noexcept { return FinalAwaiter{}; }
        Task<T> get_return_object() { return Handle::from_promise(*this); }

        void unhandled_exception() {
            m_exception = std::current_exception();
        }
        void return_value(T value) {
            m_value = value;
        }

        void setAwaitingHandle(std::coroutine_handle<> handle) {
            m_awatingHandle = handle;
        }

        std::coroutine_handle<> m_awatingHandle;
        T m_value;
        std::exception_ptr m_exception = nullptr;
    };

    TaskAwaiter operator co_await() {
        return TaskAwaiter(m_handle);
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

    struct FinalAwaiter {
        bool await_ready() const noexcept { return false; }
        std::coroutine_handle<> await_suspend(Handle handle) noexcept {
            auto& promise = handle.promise();

            if (promise.m_awatingHandle != nullptr) {
                return promise.m_awatingHandle;
            } else {
                return std::noop_coroutine();
            }
        }
        void await_resume() noexcept {}
    };

    struct TaskAwaiter {
        TaskAwaiter(Handle handle) : m_handle(handle)  { }

        TaskAwaiter() {}

        bool await_ready() { return false; }

        void await_suspend(std::coroutine_handle<> awatingHandle) noexcept {
            m_handle.promise().setAwaitingHandle(awatingHandle);
        }

        void await_resume() {
            if (m_handle.promise().m_exception) {
                std::rethrow_exception(m_handle.promise().m_exception);
            }
        }

        Handle m_handle;
    };

    struct promise_type {
        std::suspend_never initial_suspend() { return {}; }
        auto final_suspend() noexcept { return FinalAwaiter{}; }
        Task<void> get_return_object() { return Handle::from_promise(*this); }

        void unhandled_exception() {
            m_exception = std::current_exception();
        }
        void return_void() {}

        void setAwaitingHandle(std::coroutine_handle<> handle) {
            m_awatingHandle = handle;
        }

        std::coroutine_handle<> m_awatingHandle;
        std::exception_ptr m_exception = nullptr;
    };

    TaskAwaiter operator co_await() {
        return TaskAwaiter(m_handle);
    }

private:
    Handle m_handle;
};

}
