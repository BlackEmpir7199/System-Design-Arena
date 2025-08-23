#include <bits/stdc++.h>

using namespace std;

// ISP states that it is good to have many client oriented interfaces than general interface : SRP enforced
// Separate Classes for 2D shapes and 3D shapes

class twoDShape
{
public:
    virtual int area() = 0;
};

class threeDShape
{
public:
    virtual int area() = 0;
    virtual int volume() = 0;
};

class Square : public twoDShape
{
private:
    int a;

public:
    Square(int a) { this->a = a; }

    int area() override
    {
        return a * a;
    }
};

class Cube : public threeDShape
{
private:
    int a;

public:
    Cube(int a) { this->a = a; }
    int area() override
    {
        return a * a;
    }

    int volume() override
    {
        return a * a * a;
    }
};

int main()
{

    twoDShape *sq = new Square(10);
    threeDShape *cu = new Cube(10);

    cout << cu->area() << endl;
    cout << cu->volume() << endl;
    cout << sq->area() << endl;

    return 0;
}