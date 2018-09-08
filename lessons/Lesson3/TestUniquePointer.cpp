#include "Person.h"
#include "../gtest/gmock.h"
#include "../gtest/MainTest.h"
#include <memory>
#include <vector>

namespace
{
    using namespace testing;
    using namespace Lesson3;

    // www.cppreference.com
    // std::unique_ptr is a smart pointer that retains sole ownership of an object through a pointer and
    // destroys that object when the unique_ptr goes out of scope.
    // No two unique_ptr instances can manage the same object.

    struct UniquePointer : public testing::Test
    {
        void SetUp() override { GTEST_PRINTF("UniquePointer SetUp\n"); }
        void TearDown() override { GTEST_PRINTF("UniquePointer TearDown\n"); }
    };

    TEST_F(UniquePointer, ResetToNull)
    {
        auto person = std::make_unique<Person>("Joe");
        person->Print();
        person.reset();

        ASSERT_THAT(person, Eq(nullptr));
    }

    TEST_F(UniquePointer, ChangeOwnership)
    {
        auto person = std::make_unique<Person>("Peter");
        person->Print();

        person.reset(new Person("Betty"));
        person->Print();

        ASSERT_THAT(person, Ne(nullptr));
    }

    TEST_F(UniquePointer, UseInVector)
    {
        std::vector<std::unique_ptr<Person>> people;

        // perfect forwarding allows the pointer to be constructed directly in the vector
        people.push_back(std::make_unique<Person>("Tom"));

        // cannot push_back because std::unique_ptr is not copyable
        auto p = std::make_unique<Person>("Sue");
        // people.push_back(p);

        // however, we can move it into the vector
        people.push_back(std::move(p));

        // cannot copy the vector because the pointers are not copyable
        // auto people2 = people;

        // you can move the vector
        auto emigrated = std::move(people);

        EXPECT_THAT(people.size(), Eq(0u));
        EXPECT_THAT(emigrated.size(), Eq(2u));
    }

    TEST_F(UniquePointer, ReturnUniquePointer)
    {
        auto createMary = []() { return std::make_unique<Person>("Mary"); };

        auto createJackOrJill = [](bool shouldCreateJack)
        {
            std::unique_ptr<Person> person;
            if (shouldCreateJack)
            {
                // NRVO
                person = std::make_unique<Person>("Jack");
                return person;
            }
            // RVO
            return std::make_unique<Person>("Jill");
        };

        auto mary = createMary();
        auto jackOrJill = createJackOrJill(true);

        mary->Print();
        jackOrJill->Print();
    }
}