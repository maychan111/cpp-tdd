#include "../gtest/gmock.h"
#include <thread>

namespace 
{
    using namespace testing;

    /*
        Source: http://martinfowler.com/articles/mocksArentStubs.html
                http://stackoverflow.com/questions/3459287/whats-the-difference-between-a-mock-stub

        Goal: test a class in as much isolation as make sense.  So we use test double to emulate or setup
              expected behavior of the class's dependencies.

        "Test Double" is an object used in place of a real object for testing purposes

        Types of test double:
        1. Dummy - objects passed around but never really used, usually just to fill parameter lists
        2. Stubs - provide canned answers to calls made during tests, sometimes records stats (also call Test Spy)
        3. Fakes - objects actually have working implementation, but with shortcuts.  E.g. memory database
        4. Mocks - objects pre-programmed with expectations which form a speciication of the calls they are expected to receive.

        Another explanation: fake is a smarter stub, mock is a smarter fake.

        Why use mock frameworks:
            - help reduce boilerplate code for stubs.
            - used to test interactions between objects by setting up expectations.
    */
       
    struct Computation
    {
        virtual int FetchValue()
        {
            return std::rand(); 
        }

        int Square()
        {
            auto value = FetchValue();
            return value * value;
        }
    };

    struct MockComputation : public Computation
    {
        MOCK_METHOD0(FetchValue, int());
    };

    TEST(Mock, VirtualFunction)
    {
        MockComputation computation;
        EXPECT_CALL(computation, FetchValue()).WillOnce(Return(5));

        EXPECT_THAT(computation.Square(), Eq(25));
    }
}