#include "Person.h"
#include "../gtest/gmock.h"
#include <memory>
#include <list>

namespace
{
    using namespace testing;
    using namespace Lesson3;

    class SharedPointer : public testing::Test
    {
    public:
        std::list<std::shared_ptr<Person>> _people;

    protected:
        void SetUp() override
        {
            GTEST_PRINTF("SharedPointer SetUp\n");
            _people.push_back(std::make_shared<Person>("Anna"));
            _people.push_back(std::make_shared<Person>("Buddy"));
            _people.push_back(std::make_shared<Person>("Carter"));
        }

        void TearDown() override
        {
            GTEST_PRINTF("SharedPointer TearDown\n");
        }

        void Print()
        {
            GTEST_PRINTF("SharedPointer ");
            std::for_each(std::begin(_people), std::end(_people), [](auto i) { std::cout << i->GetName() << " "; });
            GTEST_PRINTF("\n");

        }
    };

    TEST_F(SharedPointer, SharedContainer)
    {
        auto sameGroupOfPeople = _people;
        EXPECT_THAT(_people.size(), Eq(3u));
        EXPECT_THAT(sameGroupOfPeople.size(), Eq(3u));

        this->Print();
    }

    TEST_F(SharedPointer, SharedItem)
    {
        EXPECT_THAT(_people.size(), Eq(3u));
        auto firstPerson = _people.front();

        this->Print();
        _people.clear();

        firstPerson->Print();
    }
}