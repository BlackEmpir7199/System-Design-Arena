#include <iostream>
using namespace std;

// adapter interface - client expects this
class GameController
{
public:
    virtual void pressA() = 0;
    virtual void pressB() = 0;
};

// adaptee - legacy already there
class PsController
{
public:
    void circle()
    {
        cout << "Action for circle in game" << endl;
    }
    void cross()
    {
        cout << "Action for cross in game" << endl;
    }
};

// adapter wriiten to talk with the client
class uniController : public GameController
{
    PsController *ps;

public:
    uniController(PsController *ps) : ps(ps) {}
    // delegates the op to the ps
    void pressA()
    {
        ps->circle();
    }
    void pressB()
    {
        ps->cross();
    }
};

// client which accpets a GameController
class client
{
public:
    void playGame(GameController *gc)
    {
        cout << "Game Started" << endl;
        gc->pressA();
        gc->pressB();
    }
};

int main()
{
    PsController *ps = new PsController();
    GameController *gc = new uniController(ps);

    client c;
    c.playGame(gc);

    return 0;
}