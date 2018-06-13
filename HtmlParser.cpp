//
// Created by Andrii Sumko on 11.06.18.
//
#include <iostream>
#include <algorithm>
#include "HtmlParser.h"

std::string g_root_name = "<!DOCTYPE html>";
HtmlElement g_root(g_root_name);

static std::vector<std::string> void_elements = {"<area>", "<base>", "<br>", "<col>", "<command>", "<embed>", "<hr>", "<img>", "<input>", "<keygen>", "<link>", "<menuitem>", "<meta>", "<param>", "<source>", "<track>", "<wbr>"};


std::string& HtmlParser::ltrim(std::string& s, const char* t)
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

HtmlParser::HtmlParser(std::string &c_url, std::string &c_url_content) :url{c_url}, url_content{c_url_content}, unparsed_text{c_url_content}, root{g_root} {
    if (c_url.length() < 1 || c_url_content.length() < 1)
        throw std::runtime_error("url and its content shouldn't be emprty");
}

std::string HtmlParser::getUrl() {
    return url;
}

std::string HtmlParser::getContent() {
    return url_content;
}

void HtmlParser::pushTag(HtmlElement el) {
    tags.push_back(el);
}

HtmlElement HtmlParser::getNextTag() {
    std::string clean = unparsed_text.substr(16);
    HtmlElement newBase = loopParse(clean);
    root.displayInfo();
    //newBase.displayInfo();
    return newBase;
}

HtmlElement HtmlParser::parse_sub(HtmlElement cur_el, std::string cur_text) {
    if (cur_text.length() < 3 || unparsed_text.length() < 3) {
        root = *&cur_el;
        return cur_el;
    }
    if (cur_text.at(1) == '/') {
        unparsed_text = cur_text.substr(cur_text.find(">") + 1);
        if (unparsed_text.length() < 3) {
            root = *&cur_el;
            return cur_el;
        }
        if (unparsed_text.at(0) == '\n')
            unparsed_text = unparsed_text.substr(1);
        unparsed_text = ltrim(unparsed_text);
        return cur_el;
    }
    std::string raw_tag = cur_text.substr(cur_text.find("<"), cur_text.find(">") + 1);
    unsigned long len = raw_tag.length();
    std::string newTag;
    //std::cout << "-----------" << std::endl << newTag << std::endl << raw_tag << std::endl;
    if (raw_tag.at(2) == '/')
        newTag = "<" + raw_tag.substr(2, raw_tag.find('/')) + ">";
    else {
        unsigned long cl_pos;
        if (raw_tag.find(' ') < raw_tag.find('>') && raw_tag.find(' ') != -1)
            cl_pos = raw_tag.find(' ');
        else
            cl_pos = raw_tag.find('>');
        newTag = raw_tag.substr(0, cl_pos) + ">";
        //std::cout << "HEY THERE " << raw_tag.find('>') << std::endl;
    }
    if (std::find(void_elements.begin(), void_elements.end(), newTag) != void_elements.end()){
        HtmlElement newChild(newTag);
        cur_el.addChild(&newChild);
        //std::cout <<  "void: " << newTag << std::endl;
        return parse_sub(cur_el, cur_text.substr(len));
    }
    else {
        std::string nextChunk = checkNextTag(cur_text.substr(len));
        if (nextChunk != cur_text.substr(len)) {
            unparsed_text = nextChunk;
            if (unparsed_text.at(0) == '\n')
                unparsed_text = unparsed_text.substr(1);
            unparsed_text = ltrim(unparsed_text);
            HtmlElement scChild(newTag);
            cur_el.addChild(&scChild);
            return parse_sub(cur_el, unparsed_text);
        }
        else {
            HtmlElement newChild(newTag);
            //std::cout << "new kiddo: " << newTag << std::endl;
            HtmlElement tmpEl = parse_sub(newChild, cur_text.substr(len));
            cur_el.addChild(&tmpEl);
            //cur_el.getChild(0) -> displayInfo();
            return parse_sub(cur_el, unparsed_text);
        }

    }


}

std::string HtmlParser::checkNextTag(std::string htmlText) {
    //std::cout << htmlText.substr(htmlText.find('<'), 1);
    std::string tt = htmlText.substr(htmlText.find('<') + 1, 1);
    if ( tt == "/" ) {
        return htmlText.substr(htmlText.find('<', 2) + 1, htmlText.length());
    }
    else
        return htmlText;
}

HtmlElement HtmlParser::getRoot() {
    return root;
}

std::string HtmlParser::getTag(std::string raw_text) {
    int cl_pos = 0;
    if (raw_text.find(' ') < raw_text.find('>') && raw_text.find(' ') != -1)
        cl_pos = raw_text.find(' ');
    else
        cl_pos = raw_text.find('>');
    return raw_text.substr(0, cl_pos) + ">";
}

HtmlElement HtmlParser::loopParse(std::string cur_text) {
    HtmlElement l_root(g_root_name);
    HtmlElement *cur_parent = &l_root;
    //HtmlElement cur_child = l_root;
    int i = 0;
    while (i < cur_text.length()) {
        if (cur_text.at(i) == '<') {
            std::string cur_tag = getTag(cur_text.substr(i));
            int tag_diff = cur_text.substr(i + 1).length() - checkNextTag(cur_text.substr(i + 1)).length();
            //if tag is closing current parent tag
            if (cur_text.at(i + 1) == '/') {
                //move one level upper
                HtmlElement *tmpParent = (cur_parent -> getParent());
                //cur_child = cur_parent;
                cur_parent = tmpParent;
                i += cur_text.substr(i).find('>');
            }
            //check if tag is void (do not require closing tag), in this case just add it as a child to current parent
            else if (std::find(void_elements.begin(), void_elements.end(), cur_tag) != void_elements.end()) {
                cur_parent -> addChild(new HtmlElement(cur_tag));
                i += cur_text.substr(i).find('>');
            }
            //check if next tag closing current tag, in this case it should be treated as void tag and i should be moved respectively
            else if (tag_diff > 0) {
                cur_parent -> addChild(new HtmlElement(cur_tag));
                i += tag_diff + 1;
            }
            else {
                cur_parent -> addChild(new HtmlElement(cur_tag));
                cur_parent = cur_parent->popChild();
                i += cur_text.substr(i).find('>');
            }
        }
        else
            i++;
    }
    return *cur_parent;
}