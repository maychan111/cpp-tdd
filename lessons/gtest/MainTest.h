#pragma once
#include <mutex>

namespace testing
{
    extern std::mutex gtest_mutex;

    class MainTest
    {
    public:
        MainTest(int argc, char *argv[]);
        ~MainTest();
        
        int Run();
        
    private:
        int _argc;
        char **_argv;
    };  

    // hacking into using Google test internals, may break in future versions of Google test libraries
    namespace internal
    {
        enum GTestColor
        {
            COLOR_DEFAULT,
            COLOR_RED,
            COLOR_GREEN,
            COLOR_YELLOW
        };
        extern void ColoredPrintf(GTestColor color, const char* fmt, ...);
    }

#define GTEST_PRINTF(...)  \
do { \
  std::lock_guard<std::mutex> lock(testing::gtest_mutex); \
  testing::internal::ColoredPrintf(testing::internal::COLOR_GREEN, "[          ] "); \
  testing::internal::ColoredPrintf(testing::internal::COLOR_DEFAULT, __VA_ARGS__); } \
while(0)

#define GTEST_INFO(...)  do { \
  std::lock_guard<std::mutex> lock(testing::gtest_mutex); \
  testing::internal::ColoredPrintf(testing::internal::COLOR_GREEN, "[          ] "); \
  testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, __VA_ARGS__); } \
while(0)

}
