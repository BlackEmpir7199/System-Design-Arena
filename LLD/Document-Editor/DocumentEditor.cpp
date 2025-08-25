#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// absract class
class DocumentElement
{
public:
    virtual ~DocumentElement() = default;
    virtual std::string render() = 0;
};

// concrete impl
class TextElement : public DocumentElement
{
private:
    std::string txtElement;

public:
    TextElement(std::string txtElement)
    {
        this->txtElement = txtElement;
    }
    std::string render()
    {
        return txtElement;
    }
};

class ImageElement : public DocumentElement
{
private:
    std::string imgPath;

public:
    ImageElement(std::string imgPath)
    {
        this->imgPath = imgPath;
    }
    std::string render()
    {
        return "Image : [ " + imgPath + " ]";
    }
};

class NewLineElement : public DocumentElement
{
public:
    std::string render()
    {
        return "\n";
    }
};

class TabSpaceElement : public DocumentElement
{
public:
    std::string render()
    {
        return "\t";
    }
};

// Document class which holds the collection of document elements
class Document
{
private:
    std::vector<DocumentElement *> elements;

public:
    Document() {}
    void addElement(DocumentElement *newElement)
    {
        elements.push_back(newElement);
    }

    std::string render()
    {
        std::string result;
        for (DocumentElement *ele : elements)
        {
            result += ele->render();
        }
        return result;
    }
};

// abstract class for persistence
class Persistence
{
public:
    virtual void save(std::string data) = 0;
};

// concrete impl
class saveToFile : public Persistence
{
public:
    void save(std::string data)
    {
        std::ofstream outFile("document.txt");
        if (outFile)
        {
            outFile << data;
            outFile.close();
            std::cout << "document.txt has been created successfully" << std::endl;
        }
        else
        {
            std::cout << "Error while opening document" << std::endl;
        }
    }
};

// Document Editor class for client interaction
class DocumentEditor
{
private:
    Document *document;
    Persistence *persistence;
    std::string renderedDoc;

public:
    DocumentEditor(Document *doc, Persistence *per)
    {
        this->document = doc;
        this->persistence = per;
    }
    void addText(std::string text)
    {
        document->addElement(new TextElement(text));
    }
    void addImage(std::string imgPath)
    {
        document->addElement(new ImageElement(imgPath));
    }
    void addNewLine()
    {
        document->addElement(new NewLineElement());
    }
    void addTabSpaceElement()
    {
        document->addElement(new TabSpaceElement());
    }

    std::string renderDocument()
    {
        if (renderedDoc.empty())
        {
            renderedDoc = document->render();
        }
        return renderedDoc;
    }

    void saveDocument()
    {
        persistence->save(renderDocument());
    }
};

int main()
{
    Document *document = new Document();
    Persistence *persistence = new saveToFile();

    DocumentEditor *editor = new DocumentEditor(document, persistence);

    editor->addText("Hello Everyone!");
    editor->addNewLine();
    editor->addImage("A-pic-of-mine.jpg");
    editor->addNewLine();
    editor->addTabSpaceElement();
    editor->addTabSpaceElement();
    editor->addText("Signature");

    std::cout << editor->renderDocument() << std::endl;

    editor->saveDocument();

    return 0;
}