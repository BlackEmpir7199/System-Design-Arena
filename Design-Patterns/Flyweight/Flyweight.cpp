#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// flyweight interface
class Icon
{
public:
    virtual ~Icon() = default;
    // put the extrinsic state in here
    virtual void draw(int x, int y) = 0;
};

// concrete flyweight
class FileIcon : public Icon
{
    // define the intrinsic states
private:
    string color;
    string imgPath;

public:
    FileIcon(string color, string imgPath)
        : color(color), imgPath(imgPath) {}
    void draw(int x, int y)
    {
        cout << "Drawing File icon in " << color
             << " color with the image " << imgPath << endl;
    }
};

class FolderIcon : public Icon
{
    // define the intrinsic states
private:
    string color;
    string imgPath;

public:
    FolderIcon(string color, string imgPath)
        : color(color), imgPath(imgPath) {}
    void draw(int x, int y)
    {
        cout << "Drawing Folder icon in " << color
             << " color with the image " << imgPath << endl;
    }
};

class IconFactory
{
    unordered_map<string, Icon *> pool;

public:
    Icon *getIcon(string color, string icon)
    {
        string key = color + icon;
        if (pool.find(key) == pool.end())
        {
            Icon *newIcon;
            if (icon == "file")
            {
                newIcon = new FileIcon(color, "file.png");
            }
            else if (icon == "folder")
            {
                newIcon = new FolderIcon(color, "folder.png");
            }
            else
            {
                throw logic_error("No such icon type exists");
            }

            pool[key] = newIcon;
        }
        return pool[key];
    }

    int getPoolSize()
    {
        return pool.size();
    }
};

int main()
{
    IconFactory If;
    // org
    Icon *whiteFile1 = If.getIcon("white", "file");
    Icon *orangeFolder1 = If.getIcon("orange", "folder");

    // dups
    Icon *whiteFile2 = If.getIcon("white", "file");
    Icon *orangeFolder2 = If.getIcon("orange", "folder");

    whiteFile1->draw(10, 5);
    whiteFile2->draw(20, 7);

    orangeFolder1->draw(10, 2);
    orangeFolder2->draw(20, 2);

    cout << "Are files same objs : " << boolalpha << (whiteFile1 == whiteFile2) << endl;
    cout << "Are folders same objs : " << boolalpha << (orangeFolder1 == orangeFolder2) << endl;

    cout << "Size of pool:" << If.getPoolSize();

    return 0;
}