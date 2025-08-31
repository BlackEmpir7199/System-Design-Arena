#include <iostream>
#include <memory>
using namespace std;

// we have to create a clone of a existing class so that we can continue from there on
// best for time consuming creations that are often the same

// we will use unique_ptr<> and enforce this cloning such that we only produce deep copies

class Prototype
{
public:
    virtual unique_ptr<Prototype> clone() = 0;
    virtual void info() = 0;
    virtual ~Prototype() = default;
};

class Soldier : public Prototype
{
    string weapon;

public:
    Soldier(string weapon) : weapon(weapon)
    {
        cout << "New Soldier created" << endl;
    }
    void info()
    {
        cout << "Soldier with: " << weapon << endl;
    }
    unique_ptr<Prototype> clone()
    {
        return make_unique<Soldier>(*this);
    }
};

class Monster : public Prototype
{
    int health;

public:
    Monster(int health) : health(health)
    {
        cout << "New Monster created" << endl;
    }
    void info()
    {
        cout << "Monster with HealthBar: " << health << endl;
    }
    unique_ptr<Prototype> clone()
    {
        return make_unique<Monster>(*this);
    }
};

int main()
{
    unique_ptr<Prototype> monster1 = make_unique<Monster>(10);
    unique_ptr<Prototype> soldier1 = make_unique<Soldier>("AK-47");

    unique_ptr<Prototype> soldier2 = soldier1->clone();
    unique_ptr<Prototype> monster2 = monster1->clone();

    monster1->info();
    monster2->info();

    soldier1->info();
    soldier2->info();

    // since we make a deep copy this is gonna be false
    cout << "Are both monsters same ? " << boolalpha << (monster1 == monster2) << endl; // false
    cout << "Are both soldiers same ? " << boolalpha << (monster1 == monster2) << endl; // false

    return 0;
}