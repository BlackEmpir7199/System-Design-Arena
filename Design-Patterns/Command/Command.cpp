#include <iostream>
using namespace std;

// Receivers
class Light
{
public:
    void on()
    {
        cout << "Light on" << endl;
    }
    void off()
    {
        cout << "Light off" << endl;
    }
};

class Ac
{
public:
    void on()
    {
        cout << "AC on" << endl;
    }
    void off()
    {
        cout << "AC off" << endl;
    }
};

// command interface (abstract)
class ICommand
{
public:
    virtual void exec() = 0;
    virtual void undo() = 0;
    virtual ~ICommand() = default;
};

// concrete Commands
class LightCommand : public ICommand
{
    Light *light;

public:
    // we delete it to the light object
    LightCommand(Light *light) : light(light) {}
    void exec()
    {
        light->on();
    }
    void undo()
    {
        light->off();
    }
};

class AcCommand : public ICommand
{
    Ac *ac;

public:
    // we delete it to the Ac object
    AcCommand(Ac *ac) : ac(ac) {}
    void exec()
    {
        ac->on();
    }
    void undo()
    {
        ac->off();
    }
};

// The invoker (controller)
class RemoteController
{
    static const int numOfBtns = 3;
    ICommand *buttons[numOfBtns];
    bool isPressed[numOfBtns];

public:
    RemoteController()
    {
        // init the buttons arr
        for (int i = 0; i < numOfBtns; i++)
        {
            buttons[i] = nullptr;
            isPressed[i] = false;
        }
    }

    void setCommand(int idx, ICommand *cmd)
    {
        if (idx >= 0 && idx < numOfBtns)
        {
            if (buttons[idx] != nullptr)
            {
                delete buttons[idx];
            }
            buttons[idx] = cmd;
            isPressed[idx] = false;
        }
    }

    void pressButton(int idx)
    {
        if (idx >= 0 && idx < numOfBtns)
        {
            if (buttons[idx] == nullptr)
            {
                cout << "The button is not set to any command" << endl;
                return;
            }

            if (isPressed[idx] == false)
            {
                buttons[idx]->exec();
                isPressed[idx] = true;
            }
            else
            {
                buttons[idx]->undo();
                isPressed[idx] = false;
            }
        }
        else
        {
            cout << "Button is not within the range" << endl;
        }
    }

    ~RemoteController()
    {
        for (int i = 0; i < numOfBtns; i++)
        {
            delete buttons[i];
            buttons[i] = nullptr;
            isPressed[i] = false;
        }
    }
};

int main()
{
    Light *light = new Light();
    Ac *ac = new Ac();

    RemoteController *rc = new RemoteController();
    rc->setCommand(0, new LightCommand(light));
    rc->setCommand(1, new AcCommand(ac));

    rc->pressButton(0);
    rc->pressButton(1);
    rc->pressButton(0);
    rc->pressButton(1);
    rc->pressButton(2);
    rc->pressButton(6);

    return 0;
}