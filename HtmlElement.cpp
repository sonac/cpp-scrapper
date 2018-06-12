//
// Created by Andrii Sumko on 09.06.18.
//

#include "HtmlElement.h"
#include <iostream>
#include <typeinfo>

static std::vector<HtmlElement*> nil;

HtmlElement::HtmlElement(std::string &c_name, std::vector<HtmlElement *> c_children, HtmlElement* c_parent) :element_name{c_name}, children{c_children}, parent{c_parent} {
    if (c_name.length() == 0)
        throw std::runtime_error("Element Name must not be empty");
}

HtmlElement::HtmlElement(std::string &c_name,  std::vector<HtmlElement*> c_children) :element_name{c_name}, children{c_children}, parent{NULL} {
    if (c_name.length() == 0)
        throw std::runtime_error("Element Name must not be empty");
}

HtmlElement::HtmlElement(std::string &c_name) :element_name{c_name}, children{nil}, parent{NULL} {
    if (c_name.length() == 0)
        throw std::runtime_error("Element Name must not be empty");
}

void HtmlElement::init(std::string &c_name, std::vector<HtmlElement*> c_children) {
    element_name = c_name;
    children = c_children;
}

void HtmlElement::displayInfo() {
    std::cout << "Type: " << element_name << std::endl;
    if (!(children.empty())) {
        std::cout << "Children { ";
        for (auto itm : children)
            std::cout << itm -> element_name << " ";
        std::cout << "}" << std::endl;
    }
}

std::string HtmlElement::getElementName() {
    return element_name;
}

std::vector<HtmlElement*> HtmlElement::getChildren() {
    return children;
}

void HtmlElement::addChild(HtmlElement& child) {
    children.push_back(&child);
}

void HtmlElement::popChild() {
    children.pop_back();
}

HtmlElement* HtmlElement::getChild(int i) {
    if (children.size() < i)
        return NULL;
    else
        return children.at(i);
}

HtmlElement* HtmlElement::getParent() {
    return parent;
}

void HtmlElement::setParent(HtmlElement *el) {
    parent = el;
}

bool HtmlElement::hasChildren() {
    return !children.empty();
}

bool HtmlElement::hasParent() {
    return !parent;
}