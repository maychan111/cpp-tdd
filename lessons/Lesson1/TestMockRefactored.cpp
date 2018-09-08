#include "../gtest/gmock.h"
#include <thread>

namespace 
{
    using namespace testing;

    // The original Computation class is hard to test because it is not Single Responsibility.
    // It fetches values and perform computations.  
    // We will refactor the class to use dependency injection.

    struct Fetcher
    {
        int FetchValue() { return std::rand(); }
    };

    template<typename FetcherT = Fetcher>
    class Computation2
    {
    public:

        Computation2(FetcherT& fetcher) : _fetcher(fetcher) {}

        int Square() 
        { 
            auto value = _fetcher.FetchValue();
            return value * value;
        }

    private:
        FetcherT& _fetcher;
    };

    // we can mock the fetcher class to test Computation2
    struct MockFetcher
    {
        MOCK_METHOD0(FetchValue, int());
    };

    TEST(MockRefactored, DependencyInjection)
    {
        // production code looks like this
        // Fetcher fetcher;
        // auto c = Computation2<>(fetcher);

        MockFetcher mockFetcher;
        auto computation = Computation2<MockFetcher>(mockFetcher);

        EXPECT_CALL(mockFetcher, FetchValue()).WillOnce(Return(0)).WillRepeatedly(Return(3));

        EXPECT_THAT(computation.Square(), Eq(0));
        EXPECT_THAT(computation.Square(), Eq(9));
        EXPECT_THAT(computation.Square(), Eq(9));
    }
}