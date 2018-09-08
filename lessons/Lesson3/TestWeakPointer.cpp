#include "Person.h"
#include "../gtest/gmock.h"
#include <memory>
#include <list>

namespace
{
    using namespace testing;
    using namespace Lesson3;

    // www.cppreference.com
    // std::weak_ptr models temporary ownership: when an object needs to be accessed only if it exists,
    // and it may be deleted at any time by someone else
    // example usage: cache, observer pattern,

    class Babysitter
    {
    public:

        void Observe(std::shared_ptr<Person> kid)
        {
            _children.push_back(std::move(kid));
        }

        void Print()
        {
            GTEST_PRINTF("The babysitter is watching ");
            std::for_each(std::begin(_children), std::end(_children), [](auto&& kid)
            {
                if (auto stillAround = kid.lock())
                    std::cout << stillAround->GetName() << " ";
                else
                    std::cout << "<left> ";
            });
            std::cout << std::endl;
        }

        std::list<std::weak_ptr<Person>> _children;
    };

    TEST(WeakPointer, Observer)
    {
        std::vector<std::shared_ptr<Person>> children =
        {
            std::make_shared<Person>("Timmy"),
            std::make_shared<Person>("Sally"),
            std::make_shared<Person>("Gus"),
        };

        Babysitter babysitter;
        std::for_each(std::begin(children), std::end(children), [&](auto&& child) { babysitter.Observe(child); });
        babysitter.Print();

        // sally left
        children.erase(std::begin(children) + 1);

        // babysitter should be watching Timmy and Gus
        babysitter.Print();

        // everybody left
        children.clear();
        babysitter.Print();
    }
}