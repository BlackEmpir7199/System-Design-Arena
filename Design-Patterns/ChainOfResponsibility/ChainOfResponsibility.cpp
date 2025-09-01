#include <iostream>
using namespace std;

// abstract handler
class Handler
{
public:
    virtual void setNext(Handler *next) = 0;
    virtual void handleRequest(string request) = 0;
    virtual ~Handler() = default;
};

// concrete handler
class UserNamePasswordHandler : public Handler
{
    Handler *next;

public:
    UserNamePasswordHandler() {}
    void setNext(Handler *nextHandler)
    {
        next = nextHandler;
    }
    void handleRequest(string request)
    {
        if (request == "username_password")
        {
            cout << "Auth success via username password" << endl;
            cout << "Handled at level 1" << endl;
        }
        else if (next)
        {
            cout << "Rerouting to next level..." << endl;
            next->handleRequest(request);
        }
        else
        {
            cout << "Invalid reuqest" << endl;
        }
    }
};

class AuthTokenHandler : public Handler
{
    Handler *next;
    
    public:
    AuthTokenHandler() {}
    void setNext(Handler *nextHandler)
    {
        next = nextHandler;
    }
    void handleRequest(string request)
    {
        if (request == "auth_token")
        {
            cout << "Auth success via auth token" << endl;
            cout << "Handled at level 2" << endl;
        }
        else if (next)
        {
            cout << "Rerouting to next level..." << endl;
            next->handleRequest(request);
        }
        else
        {
            cout << "Invalid reuqest" << endl;
        }
    }
};

int main()
{
    Handler *usernameHandle = new UserNamePasswordHandler();
    AuthTokenHandler *authHandle = new AuthTokenHandler();

    usernameHandle->setNext(authHandle);

    usernameHandle->handleRequest("username_password");
    usernameHandle->handleRequest("auth_token");

    delete usernameHandle;
    delete authHandle;

    return 0;
}