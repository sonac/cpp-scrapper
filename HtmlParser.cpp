//
// Created by Andrii Sumko on 11.06.18.
//
#include <iostream>
#include <algorithm>
#include "HtmlParser.h"

static std::vector<std::string> void_elements = {"<area>", "<base>", "<br>", "<col>", "<command>", "<embed>", "<hr>", "<img>", "<input>", "<keygen>", "<link>", "<menuitem>", "<meta>", "<param>", "<source>", "<track>", "<wbr>"};

HtmlParser::HtmlParser(std::string &c_url, std::string &c_url_content) :url{c_url}, url_content{c_url_content}, unparsed_text{c_url_content} {
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
    std::string base_name = "<!DOCTYPE html>";
    HtmlElement base(base_name);
    std::string clean = unparsed_text.substr(16);
    HtmlElement newBase = parse_sub(base, clean);
    return newBase;
}

HtmlElement HtmlParser::parse_sub(HtmlElement cur_el, std::string cur_text) {
    if (cur_text.length() < 2 || checkNextTag(cur_text) != cur_text)
        return cur_el;
    std::string opening_tag = "<";
    std::string closing_tag = ">";
    std::string raw_tag = cur_text.substr(cur_text.find(opening_tag), cur_text.find(closing_tag) + 1);
    unsigned long len = raw_tag.length();
    std::string newTag;
    std::cout << "-----------" << std::endl << newTag << std::endl << raw_tag << std::endl;
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
        cur_el.addChild(newChild);
        std::cout <<  "void: " << newTag << std::endl;
        return parse_sub(cur_el, cur_text.substr(len));
    }
    else {
        if (raw_tag.at(1) == '/' || checkNextTag(cur_text.substr(len)) != cur_text.substr(len)) {
            std::cout << "closing: " << newTag << std::endl << cur_text;
            unparsed_text = cur_text.substr(len);
            return cur_el;
        }
        else {
            HtmlElement newChild(newTag);
            std::cout << "new kiddo: " << newTag << std::endl;
            HtmlElement tmpEl = parse_sub(newChild, cur_text.substr(len));
            cur_el.addChild(tmpEl);
            return parse_sub(cur_el, unparsed_text);
        }

    }


}

std::string HtmlParser::checkNextTag(std::string htmlText) {
    //std::cout << htmlText.substr(htmlText.find('<'), 1);
    if (htmlText.substr(htmlText.find('<'), 1) == "/") {
        return htmlText.substr(htmlText.find('>'), htmlText.length());
    }
    else
        return htmlText;
}