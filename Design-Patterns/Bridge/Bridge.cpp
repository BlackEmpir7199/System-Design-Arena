#include <iostream>
using namespace std;

// has 1. abstraction (hlp)
// has 2. implementation (llp)

// abstract implementor
class Color
{
public:
    virtual void applyColor() = 0;
    virtual ~Color() = default;
};

// concrete implementors
class Red : public Color
{
public:
    void applyColor()
    {
        cout << "Red" << endl;
    }
};

class Blue : public Color
{
public:
    void applyColor()
    {
        cout << "Blue" << endl;
    }
};

// abstract abstractor (the one which communicates with the abstract implementor)
class Shape
{
protected:
    Color *color;

public:
    Shape(Color *color) : color(color) {}
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

// concrete impl of abstractors
class Square : public Shape
{
public:
    Square(Color *color) : Shape(color) {}
    void draw()
    {
        // do some work and delegate using the abstraction
        cout << "Drawing the sqaure in ";
        color->applyColor();
    }
};

class Circle : public Shape
{
public:
    Circle(Color *color) : Shape(color) {}
    void draw()
    {
        // do some work and delegate using the abstraction
        cout << "Drawing the circle in ";
        color->applyColor();
    }
};

//

int main()
{
    Color *red = new Red();
    Color *blue = new Blue();

    Shape *sqaure = new Square(red);
    Shape *circle = new Circle(blue);

    sqaure->draw();
    circle->draw();

    return 0;
}