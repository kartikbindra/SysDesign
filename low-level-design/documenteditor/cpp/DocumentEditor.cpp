#include <iostream>
#include <vector>
using namespace std;

class DocElement {
    public:
    virtual ~DocElement() = default;
};

class Text : public DocElement {
    string content;
    public:
    Text(string text){
        content = text;
    }
};

class Image : public DocElement {
    string path;
    public:
    Image(string imgPath){
        path = imgPath;
    }
};


class Document {
    vector<DocElement*> elements;
    
    public:
    void addElement(DocElement* ele){
        elements.push_back(ele);
    }
    
    vector<DocElement*> getElements(){
        return elements;
    }
};

class Persistence {
    public:
    virtual void save(Document& doc) = 0;
    
    virtual ~Persistence() = default;
};

class DBStorage : public Persistence {
    public:
    void save(Document& doc) override {
        cout << "Saving into Database..." << endl;
    }
};

class FileStorage : public Persistence {
    public:
    void save(Document& doc) override {
        cout << "Saving into File Storage..." << endl;
    }
};

class DocumentRenderer {
    public:
    DocumentRenderer(){}
    
    void render(Document& doc){
        const auto& elements = doc.getElements();
        cout << "Rendering document..." << endl;
    }
};
    

class DocumentEditor {
    Document& doc;
    DocumentRenderer& renderer;

    public:
    DocumentEditor(Document& doc, DocumentRenderer& renderer) : doc(doc), renderer(renderer) {}

    void addElement(DocElement* ele){
        doc.addElement(ele);
    }

    void render(){
        renderer.render(doc);
    }

    void save(Persistence& storage){
        storage.save(doc);
    }
};

int main(){
    Document doc;
    DocumentRenderer renderer;
    FileStorage file;
    DBStorage database;
    DocumentEditor docEditor(doc, renderer);

    Text text1("Start of the doc!");
    Text text2("Second text");
    Image image1("/users/pictures/picutre.png");

    docEditor.addElement(&text1);
    docEditor.addElement(&text2);
    docEditor.addElement(&image1);

    docEditor.render();
    docEditor.save(file);
    docEditor.save(database);

    return 0;
}