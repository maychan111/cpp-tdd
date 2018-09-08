#include <string>
#include <iostream>

namespace Lesson7
{
    // Curiously Recurring Template Pattern for code reuse

    // repeat the following code for each class you want to make have single instance capability
    class Foo
    {
    public:
        Foo()
        {
            if (_instance == nullptr)
                _instance = this;
        }

        ~Foo()
        {
            if (_instance == this)
                _instance = nullptr;
        }

        void MakeGlobal() { _instance = this; }
        static Foo& Instance() { return *_instance; }

    private:
        static Foo *_instance;
    };

    // scroll down after discussion














    // Recfactor to use CRTP  
    template<typename T>
    class RefactoredSingleInstance
    {
    public:

        RefactoredSingleInstance()
        {
            if (_instance == nullptr)
                _instance = (T *) this;
        }

        ~RefactoredSingleInstance()
        {
            if (_instance == this)
                _instance = nullptr;
        }

        RefactoredSingleInstance(const RefactoredSingleInstance&) = delete;
        RefactoredSingleInstance& operator=(const RefactoredSingleInstance&) = delete;

        void MakeGlobal() { _instance = (T *) this; }

        static T& Instance() { return *_instance; }

    private:
        static T *_instance;
    };

    template<typename T> T *RefactoredSingleInstance<T>::_instance = nullptr;

    // Example usage
    class Logger : public RefactoredSingleInstance<Logger>
    {
    public:
        void Write(const std::string& message)
        {
            std::cout << message << std::endl;
        }

        FILE *_file;
    };

    void NeedToLogSomething(const std::string& message)
    {
        Logger::Instance().Write(message);
    }
}