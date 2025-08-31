#include <iostream>
using namespace std;

// abstract interface for the object
class Character
{
public:
virtual string getAblities() const = 0;
virtual ~Character()=default;
};

// concrete impl
class Mario : public Character
{
public:
    string getAblities() const override
    {
        return "Mario\n";
    }
};

// Abstract Decorator: CharacterDecorator "is-a" Charatcer and "has-a" Character.
class CharacterDecorator : public Character
{
protected:
    Character *character; // wrapped component

public:
    CharacterDecorator(Character *character) : character(character) {}
};

// concrete Decorators
class HeightUp : public CharacterDecorator
{
public:
    HeightUp(Character *character) : CharacterDecorator(character) {}
    string getAblities() const override
    {
        return character->getAblities() + "With height up\n";
    }
};

class PowerUp : public CharacterDecorator
{
public:
    PowerUp(Character *character) : CharacterDecorator(character) {}
    string getAblities() const override
    {
        return character->getAblities() + "With power up\n";
    }
};

class ShieldUp : public CharacterDecorator
{
public:
    ShieldUp(Character *character) : CharacterDecorator(character) {}
    string getAblities() const override
    {
        return character->getAblities() + "With shield up\n";
    }
};

int main()
{
    Character *mario = new Mario();
    cout << mario->getAblities();

    mario = new HeightUp(mario);
    cout << "+" << mario->getAblities();

    mario = new PowerUp(mario);
    cout << "+" << mario->getAblities();

    mario = new ShieldUp(mario);
    cout << "+" << mario->getAblities();

    return 0;
}