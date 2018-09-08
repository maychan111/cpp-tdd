#include <string>
#include <iostream>
#include <ctime>

namespace Lesson7
{
    // mixin to avoid multiple inheritence
    // example taken from: http://www.thinkbottomup.com.au/site/blog/C%20%20_Mixins_-_Reuse_through_inheritance_is_good

    struct BaseTask
    {
        virtual void Execute() = 0;
    };

    struct LoggingTask : public BaseTask
    {
        void Execute() override;
    };

    struct TimingTask : public BaseTask
    {
        void Execute() override;
    };

    // MyTask wants to have both logging and timing functionality ...

    // option 1: pontential diamond problem
    struct MyTask : public LoggingTask, public TimingTask
    {
        void Execute() override;
    };

    // option 2: duplicate code to make different permutations
    struct LoggingTimingTask : public TimingTask
    {
        void Execute() override;
    };

    struct MyTask : public LoggingTimingTask
    {
        void Execute() override;
    };

    // scroll down after discussion














    // refactor: use CRTP (https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)
    template <typename T>
    struct LoggingTask2 : public T
    {
        void Execute()
        {
            std::cout << "Executing task" << std::endl;
            T::Execute();
        }
    };

    template <typename T>
    struct TimingTask2 : public T
    {
        void Execute()
        {
            _startTime = time(nullptr);
            T::Execute();
            _endTime = time(nullptr);
        }
        std::time_t _startTime;
        std::time_t _endTime;
    };

    struct MyTask : BaseTask
    {
        void Execute() override;
    };

    void Work()
    {
        TimingTask2<LoggingTask2<MyTask>> task;
        task.Execute();

        std::cout << "elapsed time: " << task._endTime - task._startTime << std::endl;
    }
}