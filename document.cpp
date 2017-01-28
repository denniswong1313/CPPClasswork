#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Element {
	public:
		std::string name;
		std::string type;
		std::string content;

		Element() {
				name = "";
				type = "";
				content = "";
			}

		std::string printElement(){

			if (content == ""){
				return content;
			}
			else{
				return content + "\n";
			}
		}
};

class TaggedElement : public Element {
	public:
		std::string tag;

		TaggedElement() {
			tag = "";
		}

		std::string output;

		std::string printElement(){

			if ((name == "") && (type == "")){

				if ((tag == "") && (content == "")){
					 return "<" + tag + ">\n" + content + "</"  + tag + ">\n";
				}
				if ((content == "") && (tag != "")){
					return "<" + tag + ">\n" + content + "</"  + tag + ">\n";
				}

				if ((tag == "") && (content != "")){
					return "<" + tag + ">\n" + content + "\n</"  + tag + ">\n";
				}
				if ((tag != "") && (content != "")){
					return "<" + tag + ">\n" + content + "\n</"  + tag + ">\n";
				}
			}

			else{
				if ((content != "") && (tag != "")){
					if ((name == "") && (type != "")){
						return "<" + tag + " TYPE = \"" + type + "\">\n" + content + "\n</"  + tag + ">\n";
					}
				
					if ((name != "") && (type == "")){
						return "<" + tag + " NAME = \"" + name + "\">\n" + content + "\n</"  + tag + ">\n";
					}

					if ((name != "") && (type != "")){
						return "<" + tag + " TYPE = \"" + type + "\" NAME = " + name + "\">\n" + content + "\n</"  + tag + ">\n";
					}
				}

				if ((content == "") && (tag != "")){
					if ((name == "") && (type != "")){
						return "<" + tag + " TYPE = \"" + type + "\">\n" + content + "</"  + tag + ">\n";
					}
				
					if ((name != "") && (type == "")){
						return "<" + tag + " NAME = \"" + name + "\">\n" + content + "</"  + tag + ">\n";
					}

					if ((name != "") && (type != "")){
						return "<" + tag + " TYPE = \"" + type + "\" NAME = " + name + "\">\n" + content + "</"  + tag + ">\n";
					}
				}

				if ((content != "") && (tag == "")){
					if ((name == "") && (type != "")){
						return "<" + tag + " TYPE = \"" + type + "\">\n" + content + "\n</"  + tag + ">\n";
					}
				
					if ((name != "") && (type == "")){
						return "<" + tag + " NAME = \"" + name + "\">\n" + content + "\n</"  + tag + ">\n";
					}

					if ((name != "") && (type != "")){
						return "<" + tag + " TYPE = \"" + type + "\" NAME = " + name + "\">\n" + content + "\n</"  + tag + ">\n";
					}
				}

				if ((content == "") && (tag == "")){
					if ((name == "") && (type != "")){
						return "<" + tag + " TYPE = \"" + type + "\">\n" + content + "</"  + tag + ">\n";
					}
				
					if ((name != "") && (type == "")){
						return "<" + tag + " NAME = \"" + name + "\">\n" + content + "</"  + tag + ">\n";
					}

					if ((name != "") && (type != "")){
						return "<" + tag + " TYPE = \"" + type + "\" NAME = " + name + "\">\n" + content + "</"  + tag + ">\n";
					}
				}
			}
		}

};

struct ParagraphElement : public TaggedElement {
	public:

		ParagraphElement() {
			tag = "P";
		}
};

struct BoldParagraphElement : public TaggedElement {
	public:

		BoldParagraphElement() {
			tag = "B";
		}
};

struct MarqueeElement : public TaggedElement {
	public:

	MarqueeElement() {
		tag = "MARQUEE";
	}
};

struct FormInputElement : public TaggedElement {
	public:

		FormInputElement() {
			tag = "INPUT";
		}
};

struct CheckBoxElement : public FormInputElement {
	public:

		CheckBoxElement() {
			type = "CHECKBOX";
		}
};

struct RadioButtonElement : public FormInputElement {
	public:

		RadioButtonElement() {
			type = "RADIO";
			name = "allButtonsOnPage";
		}
};

struct FormElement : public TaggedElement {
	public:

	FormElement() {
		tag = "FORM";
	}

	void addInput(FormInputElement i) {
		content += i.printElement();
	}
};

class WebDocument {
	public:
		std::string filename;
		std::string title;
		std::string backgroundColor;
		std::string font;

		WebDocument() {
			filename = "";
			title = "";
			backgroundColor = "";
			font = "";
		}

		std::vector<TaggedElement> elements;

		void appendToDocument(TaggedElement t){
			elements.push_back(t);
		}

		std::string printDocument(){
			string document;
			for (int i = 0; i < elements.size(); i++){
				document += elements[i].printElement();
			}
			return document;
		}

		int getDocumentSize(){
			return elements.size();
		}
};

class ProjectFolder {
	public:
		std::string filename;
		std::string title;
		std::string backgroundColor;
		std::string font;

		ProjectFolder() {
			filename = "";
			title = "";
			backgroundColor = "";
			font = "";
		}

		std::vector<WebDocument> documents;

		void appendWebDocument(WebDocument d){
			documents.push_back(d);
		}

		void removeDocument(std::string name) {
			for (int i = 0; i < documents.size();){
				if (documents[i].title == name){
					documents.erase (documents.begin()+i);
				}
				else {
					i++;
				}
			}
		}

		int getNumberOfDocuments() {
			return documents.size();
		}

};

int main() {
	WebDocument document;

ParagraphElement p;
	p.content = "This is paragraph element";
	doc.appendToDocument(p);

FormElement f1;
FormElement f2;

	RadioButtonElement d;
	d.content = "This is radio button element";
	f1.addInput(d);

doc.appendToDocument(f1);

CheckBoxElement c;
	c.content = "THIS IS A CHECKBOXELEMENT";
	f2.addInput(c);
	doc.appendToDocument(f2);

	MarqueeElement m;
	m.content = "This is a marqueeeeeeeee";
	doc.appendToDocument(m);

cout << doc.printDocument() << endl;

	return 0;
}
