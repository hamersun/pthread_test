#include <iostream>
#include <memory>
#include <unistd.h>
#include "ThreadClass.h"

class TestT : public ThreadClass
{
public:
    TestT() : mRun(false){
        std::cout << "TestT ctor" << std::endl;
    }
    virtual ~TestT() {
        std::cout << "TestT dtor" << std::endl;
    }

    bool Start()
    {
        return StartThread();
    }

    void Stop()
    {
        mRun = false;
        WaitForThreadToExit();
    }

protected:
    virtual void InternalThreadEntry()
    {
        mRun = true;
        while (mRun) {
            std::cout << "print by TestT thread" << std::endl;
            usleep(500000);
        }
        std::cout << "TestT thread finished" << std::endl;
    }

private:
    bool mRun;
};

int main()
{
    std::shared_ptr<TestT> test;

    std::string input;
    while (true) {
        getline(std::cin, input);
        if (input.compare("exit") == 0) {
            break;
        } else if (input.compare("create") == 0) {
            if (!test) {
                test = std::make_shared<TestT>();
            }
        } else if (input.compare("start") == 0) {
            if (test) {
                test->Start();
            }
        } else if (input.compare("stop") == 0) {
            if (test) {
                test->Stop();
            }
        } else if (input.compare("release") == 0) {
            if (test) {
                test.reset();
            }
        } else {
            std::cerr << "unkonwn input: " << input << std::endl;
        }
    }
    std::cout << "exit this program" << std::endl;
    return 0;
}

