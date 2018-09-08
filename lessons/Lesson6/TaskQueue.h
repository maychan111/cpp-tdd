#pragma once
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>

namespace Lesson6
{
    // uses std::thread, std::lock_guard, std::unique_lock, std::mutex, std::condition_variable
    // other concepts: mutable

    class TaskQueue
    {
    public:

        using Task = std::function<void()>;

        TaskQueue();
        ~TaskQueue();

        void Stop();
        bool IsStopped() const;

        void Enqueue(Task t);
        void WaitUntilNoTasks();
        size_t NumPendingTasks() const;

    private:

        void Run();

        bool _stopped;
        mutable std::mutex _mutex;

        std::queue<Task> _tasks;
        std::condition_variable _tasksChanged;
        std::thread _thread;
        std::exception_ptr _exception;
    };
}
