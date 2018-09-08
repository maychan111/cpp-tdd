#include "../gtest/gmock.h"
#include <thread>

namespace 
{
    using namespace testing;
       
    class Computation
    {
    public:
        virtual void ModifyState(int input)
        {
            _state = input + std::rand(); 
        }

        int Square()
        {
            ModifyState(_state);
            return _state * _state;
        }

    protected:
        int _state = 0;
    };

    struct MockComputation : public Computation
    {
        MOCK_METHOD1(ModifyState, void(int));

        void SetState(int input) { _state = input;}
    };

    TEST(MockInvoke, InvokeDifferentFunction)
    {
        MockComputation computation;
        ON_CALL(computation, ModifyState(_)).WillByDefault(InvokeWithoutArgs([&]() { computation.SetState(5); }));
        EXPECT_CALL(computation, ModifyState(_));
        EXPECT_THAT(computation.Square(), Eq(25));
    }
}