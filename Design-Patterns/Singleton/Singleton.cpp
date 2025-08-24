#include <iostream>
#include <mutex>

using namespace std;

class Logger
{
private:
    static Logger *instance;
    static mutex mutex_;

    // private constructor
    Logger()
    {
        cout << "Created a instance of logger" << endl;
    }

public:
    // Static method to get the single instance (lazy initialization)
    static Logger *createInstance()
    {
        lock_guard<mutex> lock(mutex_);
        if (instance == nullptr)
        {
            instance = new Logger();
        }
        return instance;
    }

    void log(string msg)
    {
        cout << "Log: " << msg << endl;
    }

    static void destroyInstance()
    {
        lock_guard<mutex> lock(mutex_);
        delete instance;
        instance = nullptr;
        cout << "logger instance deleted" << endl;
    }
};

Logger *Logger::instance = nullptr;
mutex Logger::mutex_;

int main()
{

    Logger *logger1 = Logger::createInstance();
    logger1->log("1 st msg");

    Logger *logger2 = Logger::createInstance();
    logger2->log("2 nd msg");

    if (logger1 == logger2)
    {
        cout << "Only one instance exist" << endl;
    }

    Logger::destroyInstance();

    return 0;
}