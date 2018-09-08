#include <string>
#include <iostream>
#include <chrono>

namespace Lesson7
{
    struct Timer
    {
        Timer(std::chrono::nanoseconds t) : _duration(t) {}

        bool HasExpired();
        std::chrono::nanoseconds _duration;
    };

    // hard to test DoWork
    struct PeriodicTask
    {
        PeriodicTask() : _timer(std::chrono::seconds(1)) {}

        void DoWork()
        {
            if (_timer.HasExpired())
            {
                // ...
            }
        }

        Timer _timer;
    };

    struct Timer2
    {
        Timer2(std::chrono::nanoseconds t) : _duration(t) {}

        bool HasExpired() { return true; }
        void ExpiresNow() {}

        std::chrono::nanoseconds _duration;
    };

    // refactor to pass timer to constructor or PeriodicTask
    struct PeriodicTask2
    {
        PeriodicTask2(Timer2& t) : _timer(t) {}
        void DoWork();

        Timer2& _timer;
    };

    void Run()
    {
        Timer2 timer(std::chrono::nanoseconds(1));
        PeriodicTask2 task(timer);
        
        // ...
        timer.ExpiresNow();
    }
}