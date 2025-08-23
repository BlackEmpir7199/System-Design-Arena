#include <bits/stdc++.h>

using namespace std;

// ISP states that it is good to have many client oriented interfaces than general interface : SRP enforced
// this shape class fully forces its child class to override methods , that may not be of use , example in case of 2d shape
class Shape
{
public:
    virtual int area() = 0;
    virtual int volume() = 0;
};

class Square : public Shape
{
private:
    int a;

public:
    Square(int a) { this->a = a; }

    int area() override
    {
        return a * a;
    }

    int volume() override
    {
        throw logic_error("2d shapes dont have volume");
    }
};

class Cube : public Shape
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

    Shape *sq = new Square(10);
    Shape *cu = new Cube(10);

    try
    {
        cout << cu->area() << endl;
        cout << cu->volume() << endl;
        cout << sq->area() << endl;
        // will throw exception
        cout << sq->volume() << endl;
    }
    catch (logic_error e)
    {
        cout << e.what() << endl;
    }

    return 0;
}