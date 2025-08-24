#include <iostream>
#include <string>

// abstract products
class Button
{
public:
    virtual ~Button() = default;
    virtual void render() const = 0;
};

class ScrollBar
{
public:
    virtual ~ScrollBar() = default;
    virtual void render() const = 0;
};

// concrete products
class WindowsButton : public Button
{
public:
    void render() const override
    {
        std::cout << "Rendering Windows-style button (flat, blue)." << std::endl;
    }
};

class WindowsScrollBar : public ScrollBar
{
public:
    void render() const override
    {
        std::cout << "Rendering Windows-style scrollbar (vertical, with arrows)." << std::endl;
    }
};

class MacButton : public Button
{
public:
    void render() const override
    {
        std::cout << "Rendering Mac-style button (rounded, gradient)." << std::endl;
    }
};

class MacScrollbar : public ScrollBar
{
public:
    void render() const override
    {
        std::cout << "Rendering Mac-style scrollbar (slim, fading)." << std::endl;
    }
};

// abstract factory
class GUIFactory
{
public:
    virtual ~GUIFactory() = default;
    virtual Button *createButton() const = 0;
    virtual ScrollBar *createScrollBar() const = 0;
};

// concrete factories
class WindowsGUIFactory : public GUIFactory
{
public:
    Button *createButton() const override
    {
        return new WindowsButton();
    }
    ScrollBar *createScrollBar() const override
    {
        return new WindowsScrollBar();
    }
};

class MacGUIFactory : public GUIFactory
{
public:
    Button *createButton() const override
    {
        return new MacButton();
    }
    ScrollBar *createScrollBar() const override
    {
        return new MacScrollbar();
    }
};

// client code
class Application
{
private:
    GUIFactory *guiFactory;
    Button *button;
    ScrollBar *scrollbar;

public:
    Application(GUIFactory *guiFactoryChoice)
    {
        guiFactory = guiFactoryChoice;
        button = guiFactory->createButton();
        scrollbar = guiFactory->createScrollBar();
    }

    void paint()
    {
        button->render();
        scrollbar->render();
    }

    ~Application()
    {
        delete button;
        delete scrollbar;
    }
};

int main()
{
    std::string os;
    std::cout << "Enter the current OS : ";
    std::cin >> os;

    GUIFactory *guiFactory;

    // mimic system oriented ui switching
    if (os == "windows")
        guiFactory = new WindowsGUIFactory();
    else if (os == "mac")
        guiFactory = new MacGUIFactory();
    else
        std::cout << "Sorry we dont support the os currently !" << std::endl;

    Application app(guiFactory);

    app.paint();

    delete guiFactory;

    return 0;
}