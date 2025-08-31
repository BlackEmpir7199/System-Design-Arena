#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class FileItem
{
public:
    virtual void getDetails() = 0;
    virtual ~FileItem() = default;
};

class File : public FileItem
{
private:
    string name;

public:
    File(string name) : name(name) {}
    void getDetails()
    {
        cout << "File: " << name << endl;
    }
};

class Folder : public FileItem
{
private:
    string name;
    vector<FileItem *> children;

public:
    Folder(string name) : name(name) {}

    void add(FileItem *ft)
    {
        children.push_back(ft);
    }

    void remove(FileItem *ft)
    {
        auto it = find(begin(children), end(children), ft);
        if (it == children.end())
            cout << "No such file item exist" << endl;
        else
            children.erase(it);
    }

    void getDetails()
    {
        cout << "Folder: " << name << endl;
        for (FileItem *ft : children)
        {
            ft->getDetails();
        }
    }
};

int main()
{
    File *file1 = new File("android.txt");
    File *file2 = new File("ios.txt");

    Folder *folder1 = new Folder("Learn Android");
    Folder *folder2 = new Folder("Learn Ios");

    folder1->add(file1);
    folder2->add(file2);

    Folder *root = new Folder("App dev");
    root->add(folder1);
    root->add(folder2);

    root->getDetails();

    return 0;
}