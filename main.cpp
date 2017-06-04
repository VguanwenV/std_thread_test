#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>

class TestT
{
public:
    TestT() {
        std::cout << "TestT ctor" << std::endl;
    }
    ~TestT() {
        std::cout << "Test dtor" << std::endl;
    }

    void Start()
    {
        if (mpThread == nullptr) {
            mpThread = new std::thread(std::bind(&TestT::run, this));
        }
    }

    void Stop()
    {
        mRun = false;
        if (mpThread) {
            if (mpThread->joinable())
                mpThread->join();
            delete mpThread;
        }
        mpThread = nullptr;
    }

private:
    void run()
    {
        mRun = true;
        while (mRun) {
            std::cout << "print by TestT thread" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << "TestT thread finished" << std::endl;
    }

private:
    std::thread *mpThread;
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
