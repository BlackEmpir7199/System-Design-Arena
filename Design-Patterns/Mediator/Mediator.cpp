#include <iostream>
#include <string>
#include <vector>
using namespace std;

// forward declaration to refer for
class Colleague;

// abstract mediator
class Mediator
{
public:
    virtual void send(string from, string msg) = 0;
    virtual void registerColleague(Colleague *col) = 0;
    virtual ~Mediator() = default;
};

// abstract colleage
class Colleague
{
protected:
    Mediator *mediator;

public:
    Colleague(Mediator *m)
    {
        mediator = m;
        mediator->registerColleague(this);
    }
    virtual void receive(string from, string msg) = 0;
    virtual void send(string msg) = 0;
    virtual string getName() = 0;
    virtual ~Colleague() = default;
};

// concrete mediator
class ChatRoomMediator : public Mediator
{
    vector<Colleague *> members;

public:
    void registerColleague(Colleague *col)
    {
        members.push_back(col);
    }
    void send(string from, string msg)
    {
        for (Colleague *mem : members)
        {
            if (mem->getName() != from)
                mem->receive(from, msg);
        }
    }
};
// concrete colleague
class User : public Colleague
{
    string name;

public:
    User(string n, Mediator *m) : Colleague(m)
    {
        name = n;
    }
    string getName() { return name; }
    void receive(string from, string msg)
    {
        cout << "Hey, " << name << " You have a new msg in the group:" << "\n[ " << from << " ] :" << " " << msg << endl;
    }
    void send(string msg)
    {
        mediator->send(name, msg);
    }
};

int main()
{
    Mediator *m = new ChatRoomMediator();

    Colleague *ram = new User("ram", m);
    Colleague *somu = new User("somu", m);
    Colleague *venu = new User("venu", m);

    venu->send("Hello guys, did you guys finish mediator pattern ? ");
    ram->send("yep done 80 percent ");
    somu->send("impressive ram");

    return 0;
}