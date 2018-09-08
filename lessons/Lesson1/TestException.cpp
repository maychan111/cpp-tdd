#include "../gtest/gmock.h"
#include "../gtest/MainTest.h"
#include <stdexcept>
#include <fstream>
#include <string>

namespace
{
    // use tests for quick prototyping
    // example: see how std::nested_exception works

    using namespace testing;

    void print_exception(const std::exception& e, int level = 0)
    {
        GTEST_PRINTF("%s exception: %s\n", std::string(level, ' ').c_str(), e.what());
        try 
        {
            std::rethrow_if_nested(e);
        }
        catch (const std::exception& e) 
        {
            print_exception(e, level + 1);
        }
        catch (...)
        {
            GTEST_PRINTF("catch ...\n");
        }
    }

    template<typename E>
    void rethrow_unwrapped(const E& e)
    {
        try 
        {
            std::rethrow_if_nested(e);
        }
        catch (const std::nested_exception& e) 
        {
            rethrow_unwrapped(e);
        }
        catch (...) 
        {
            throw;
        }
    }

    // sample function that catches an exception and wraps it in a nested exception
    void open_file(const std::string& s)
    {
        try 
        {
            std::ifstream file(s);
            file.exceptions(std::ios_base::failbit);
        }
        catch (...) 
        {
            std::throw_with_nested(std::logic_error("couldn't open " + s));
        }
    }

    TEST(Exception, Nested)
    {
        auto run = []()
        {
            try
            {
                open_file("nonexistent.file");
            }
            catch (...)
            {
                std::throw_with_nested(std::runtime_error("run() failed"));
            }
        };

        try
        {
            run();
        }
        catch (const std::exception& e)
        {
            print_exception(e);
        }
    }
}