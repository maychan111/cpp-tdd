#include "TaskQueue.h"

namespace Lesson6
{
    // Discussions:
    //     This is a typicaly "consumer-producer" pattern
    //
    //     Difference between std::unique_lock and std::lock_guard
    //     RAII design pattern is used in std::unique_lock and std::lock_guard
    //     How to use std::condition_variable and std::mutex

    TaskQueue::TaskQueue()
    {
        _stopped = false;
        _thread = std::thread(&TaskQueue::Run, this);
    }

    TaskQueue::~TaskQueue()
    {
        Stop();
    }

    bool TaskQueue::IsStopped() const
    {
        return _stopped;
    }

    void TaskQueue::Stop()
    {
        if (!_stopped)
        {
            _stopped = true;
            _tasksChanged.notify_all();
            if (_thread.joinable())
                _thread.join();
        }
    }

    // this is the producer
    void TaskQueue::Enqueue(Task t)
    {
        // comment out the usage of lock here should result in undefined behavior

        std::unique_lock<std::mutex> lock(_mutex);
        _tasks.push(std::move(t));
        lock.unlock();

        _tasksChanged.notify_all();
    }

    // this is the consumer
    void TaskQueue::Run()
    {
        try
        {
            std::unique_lock<std::mutex> lock(_mutex);
            while (!_stopped)
            {
                if (_tasks.empty())
                {
                    _tasksChanged.notify_all();
                    _tasksChanged.wait_for(lock, std::chrono::seconds(1));
                }

                while (!_tasks.empty() && !_stopped)
                {
                   auto task = std::move(_tasks.front());
                    _tasks.pop();
                    lock.unlock();
                    task();
                    lock.lock();
                }
            }
        }
        catch (const std::exception&)
        {
            _exception = std::current_exception();

            // so that you can rethrow it in main thread like this
            // if (_exception)
            //     std::rethrow_exception(_exception);
        }
    }

    void TaskQueue::WaitUntilNoTasks()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        while (!_tasks.empty() && !_stopped)
            _tasksChanged.wait_for(lock, std::chrono::seconds(1));
    }

    size_t TaskQueue::NumPendingTasks() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _tasks.size();
    }
}