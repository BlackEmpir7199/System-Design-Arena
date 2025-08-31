#include <iostream>
using namespace std;

class Document
{
public:
    virtual void read() = 0;
    virtual ~Document() = default;
};

class RealDocument : public Document
{
private:
    string docName;
    string content;

public:
    RealDocument(string content, string docName)
        : content(content), docName(docName) {}
    void read()
    {
        cout << docName << ":" << endl;
        cout << content << endl;
    }
};

class ProtectedDocument : public Document
{
private:
    string password;
    RealDocument *realDoc;

public:
    // see how we create a proxy over the real doc and delegate needed stuff to it and we only check the password protection alone
    ProtectedDocument(string content, string docName, string password)
        : password(password)
    {
        realDoc = new RealDocument(content, docName);
    }

    void read()
    {
        string input;
        cout << "Enter the password to access the document: " << endl;
        cin >> input;
        if (input == password)
            realDoc->read();
        else
            cout << "The password you entered is wrong" << endl;
    }
};

int main()
{
    Document *doc = new ProtectedDocument("To master recursion first master recursion", "Forbidden C++", "cpp");
    doc->read();
    return 0;
}