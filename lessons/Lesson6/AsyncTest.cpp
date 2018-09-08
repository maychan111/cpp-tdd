#include "Task1.h"
#include "../gtest/gmock.h"
#include "../gtest/MainTest.h"
#include <future>

constexpr uint64_t Factorial(uint64_t n)
{
   return n <= 1 ? 1 : n * Factorial(n - 1);
}

namespace
{
    using namespace Lesson6;
    using namespace testing;

    // motivation to use tasked based programming instead of thread based programming
    //   no direct way to return values from std::thread
    //   problems with manual thread management: thread exhaustion, oversubscription, load balancing, etc.
    //   manually managing threads with states usually need mutexes/condition variable
    //
    // task based programming is a higher level abstraction than thread based programming
    //
    // limitiations and proposals to advance task based programming
    //   C++17 will allow future composition
    //   GCC version of std::async does not use thread pool, MSVC version does
    //   alternatives: OpenMP (uses compiler directives, supported by GCC and MSVC)

    TEST(Async, Constexpr)
    {
        auto result = Factorial(4);
        printf("result is %llu\n", (long long unsigned int) result);
    }

    TEST(Async, Future)
    {
        auto futureText = std::async(std::launch::async, PowerRepeater{ "future! ", 3 });
        auto futureFactorialResult = std::async(std::launch::async, Factorial, 8);

        GTEST_INFO("factorial result: %llu\n", futureFactorialResult.get());
        GTEST_INFO("text repeater result: %s\n", futureText.get().c_str());
    }

    // more complicated example when futures need to be accessed from multiple threads and
    // when threads need to wait on one another
    // source: http://en.cppreference.com/w/cpp/thread/shared_future

    TEST(Async, Promise)
    {
        std::promise<void> t1_ready_promise;
        std::promise<void> t2_ready_promise;

        std::promise<void> ready_promise;
        std::shared_future<void> ready_future(ready_promise.get_future());

        std::chrono::time_point<std::chrono::high_resolution_clock> start;

        auto fun1 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
        {
            t1_ready_promise.set_value();
            ready_future.wait(); // waits for the signal from main()
            return std::chrono::high_resolution_clock::now() - start;
        };

        auto fun2 = [&, ready_future]() -> std::chrono::duration<double, std::milli>
        {
            t2_ready_promise.set_value();
            ready_future.wait(); // waits for the signal from main()
            return std::chrono::high_resolution_clock::now() - start;
        };

        auto result1 = std::async(std::launch::async, fun1);
        auto result2 = std::async(std::launch::async, fun2);

        // wait for the threads to become ready
        t1_ready_promise.get_future().wait();
        t2_ready_promise.get_future().wait();

        // the threads are ready, start the clock
        start = std::chrono::high_resolution_clock::now();

        // signal the threads to go
        ready_promise.set_value();

        GTEST_INFO("Task 1 received the signal %f ms after start\n", result1.get().count());
        GTEST_INFO("Task 2 received the signal %f ms after start\n", result2.get().count());
    }
}