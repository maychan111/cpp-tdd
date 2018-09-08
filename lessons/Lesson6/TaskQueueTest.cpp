#include "TaskQueue.h"
#include "Random.h"
#include "Task1.h"
#include "Task2.h"
#include "../gtest/gmock.h"
#include "../gtest/MainTest.h"
#include <vector>

namespace
{
    using namespace Lesson6;
    using namespace testing;

    TEST(TaskQueue, Execute)
    {
        TaskQueue queue;
        Random<int> random(1, 100);
        std::vector<int> counts;

        auto addToCounts = [&counts, &random]()
        {
            for (int i = 0; i < 100; i++)
                counts.push_back(random.Get());
        };

        auto addToQueue = [&](int numTasks)
        {
            for (int i = 0; i < numTasks; i++)
            {
                queue.Enqueue(addToCounts);
            }
        };

        std::thread t1(addToQueue, 50);
        std::thread t2(addToQueue, 50);

        t1.join();
        t2.join();

        queue.WaitUntilNoTasks();
        queue.Stop();

        EXPECT_THAT(counts.size(), Eq(10000u));
        GTEST_INFO("count size = %s\n", std::to_string(counts.size()).c_str());
    }

    TEST(TaskQueue, ExecutTaskWithObjects)
    {
        PowerRepeater repeater("foo ");
        Factorial factorial(5);

        TaskQueue queue;

        queue.Enqueue(std::ref(repeater));
        queue.Enqueue(std::bind(&Factorial::DoWork, std::ref(factorial)));
        queue.Enqueue(std::ref(repeater));
        queue.Enqueue(std::ref(repeater));

        queue.WaitUntilNoTasks();

        GTEST_INFO("Text result: %s\n", repeater._text.c_str());
        GTEST_INFO("Factorial result is %llu\n", factorial._result);
    }
}