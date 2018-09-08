#include "Person.h"
#include "../gtest/gmock.h"
#include <memory>
#include <list>

namespace
{
    using namespace testing;
    using namespace Lesson3;

    // problems with shared_ptr:
    // 1. assignment requires lock, slower
    // 2. can cause memory leak if not used carefully

    struct Partner : public Person
    {
        Partner(std::string name) : Person(name) {}

        void SetPartner(std::shared_ptr<Person> person)
        {
            _partner = std::move(person);
        }

        std::shared_ptr<Person> _partner;
    };

    TEST(SharedProblem, CircularReference)
    {
        auto mary = std::make_shared<Partner>("Mary");
        auto paul = std::make_shared<Partner>("Paul");

        mary->SetPartner(paul);
        paul->SetPartner(mary);
    }
}