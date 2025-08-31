#include <iostream>
using namespace std;

// abstract subject
class Image
{
public:
    virtual void render() = 0;
    virtual ~Image() = default;
};

// concrete subject that should be proxied (intensive)
class RealImage : public Image
{
    string fileName;

public:
    RealImage(string fileName) : fileName(fileName)
    {
        cout << "Loading image from disk" << endl;
    }

    void render()
    {
        cout << "Image is being rendered : " << fileName << endl;
    }
};

// proxy for the concrete subject
class ProxyImage : public Image
{
    // mimic the behavoiur of the real image so that the client dooes not have to worry about anything
    string name;
    RealImage *realImage;

public:
    ProxyImage(string name) : name(name) {}

    // lazy loading and delegate it to the real image
    void render()
    {
        if (realImage == nullptr)
            realImage = new RealImage(name);
        realImage->render();
    }
};

int main()
{
    Image *img = new ProxyImage("lion.png");
    img->render();

    return 0;
}