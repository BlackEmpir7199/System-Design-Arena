#include <iostream>
#include <vector>
using namespace std;

// forward declarations
class TextFile;
class ImageFile;
class VideoFile;

// abstract visitor
class FileSystemVisitor
{
public:
    virtual ~FileSystemVisitor() = default;
    virtual void visit(TextFile *Tfile) = 0;
    virtual void visit(ImageFile *Ifile) = 0;
    virtual void visit(VideoFile *Vfile) = 0;
};

// abstract class for the class hierarchy
class FileSystemItem
{
    string name;

public:
    virtual ~FileSystemItem() = default;
    FileSystemItem(string name) : name(name) {}
    virtual void accept(FileSystemVisitor *visitor) = 0;
    string getName() { return name; }
};

// concrete impl of the class above
class TextFile : public FileSystemItem
{

    string content;

public:
    TextFile(string name, string content)
        : FileSystemItem(name), content(content) {}
    void accept(FileSystemVisitor *visitor)
    {
        visitor->visit(this);
    }
    string getContent() { return content; }
};

class ImageFile : public FileSystemItem
{
public:
    ImageFile(string name)
        : FileSystemItem(name) {}
    void accept(FileSystemVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class VideoFile : public FileSystemItem
{
public:
    VideoFile(string name)
        : FileSystemItem(name) {}
    void accept(FileSystemVisitor *visitor)
    {
        visitor->visit(this);
    }
};

// concrete visitors
class VirusScanVisitor : public FileSystemVisitor
{
public:
    VirusScanVisitor() {}
    void visit(TextFile *tFile)
    {
        cout << "Scanning for virus in the text file : " << tFile->getName() << endl;
    }
    void visit(ImageFile *iFile)
    {
        cout << "Scanning for virus in the image file : " << iFile->getName() << endl;
    }
    void visit(VideoFile *vFile)
    {
        cout << "Scanning for virus in the video file : " << vFile->getName() << endl;
    }
};

class OpenFileVisitor : public FileSystemVisitor
{
public:
    OpenFileVisitor() {}
    void visit(TextFile *Tfile)
    {
        cout << "Openning the text file : " << Tfile->getName() << endl;
        cout << "Content : " << Tfile->getContent() << endl;
    }
    void visit(ImageFile *Ifile)
    {
        cout << "Openning the image file : " << Ifile->getName() << endl;
    }
    void visit(VideoFile *Vfile)
    {
        cout << "Openning the video file : " << Vfile->getName() << endl;
    }
};

int main()
{
    vector<FileSystemItem *> fileItems = {new TextFile("recursion.txt", "to master recursion master recurion first"), new ImageFile("bug.png"), new VideoFile("visitor.mp4")};

    FileSystemVisitor *virusScanner = new VirusScanVisitor();
    FileSystemVisitor *readFile = new OpenFileVisitor();

    for (FileSystemItem *ft : fileItems)
    {
        ft->accept(virusScanner);
        ft->accept(readFile);
    }

    for (FileSystemItem *ft : fileItems)
    {
        delete ft;
        ft = nullptr;
    }

    return 0;
}