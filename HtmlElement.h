//
// Created by Andrii Sumko on 09.06.18.
//
#include <vector>
#include <string>

#ifndef CPP_SCRAPPER_HTML_ELEMENT_H
#define CPP_SCRAPPER_HTML_ELEMENT_H

class HtmlElement {
public:
    HtmlElement(std::string &c_name, std::vector<HtmlElement*> c_children, HtmlElement* c_parent);
    HtmlElement(std::string &c_name,  std::vector<HtmlElement*> c_children);
    HtmlElement(std::string &c_name);
    void init(std::string& c_name, std::vector<HtmlElement*> c_children);
    void displayInfo();
    std::string getElementName();
    std::vector<HtmlElement*> getChildren();
    HtmlElement* getChild(int i);
    HtmlElement* getParent();
    void addChild(HtmlElement& child);
    void popChild();
    void setParent(HtmlElement* el);
    bool hasChildren();
    bool hasParent();
private:
    std::string element_name;
    HtmlElement* parent;
    std::vector<HtmlElement*> children;
};


#endif //CPP_SCRAPPER_HTML_ELEMENT_H
