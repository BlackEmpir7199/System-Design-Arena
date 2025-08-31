#include <iostream>
using namespace std;

class Service
{
public:
    virtual void request() = 0;
    virtual ~Service() = default;
};

class RealService : public Service
{
public:
    void request()
    {
        cout << "Real service is running..." << endl;
    }
};

class RemoteProxy : public Service
{
    RealService *realService;

public:
    RemoteProxy()
    {
        // in remote(delegate) and protection(delegate+proctection) we load the object at instantiation but in virtual we lazy load(delegate+replica) it
        realService = new RealService();
    }
    void request()
    {
        cout << "connecting via network..." << endl;
        realService->request();
    }
};

int main()
{
    Service *remote = new RemoteProxy();
    remote->request();
    return 0;
}