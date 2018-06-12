//
// Created by Andrii Sumko on 11.06.18.
//

#ifndef CPP_SCRAPPER_HTMLPARSER_H
#define CPP_SCRAPPER_HTMLPARSER_H

#include <string>
#include <vector>

#include "HtmlElement.h"

class HtmlParser {
public:
    HtmlParser(std::string& c_url, std::string& c_url_content);
    std::string getUrl();
    std::string getContent();
    std::vector<HtmlElement> getTags();
    HtmlElement getNextTag();
    HtmlElement parse_sub(HtmlElement cur_el, std::string cur_text);
private:
    std::string url, url_content, unparsed_text;
    std::vector<HtmlElement> tags;
    void pushTag(HtmlElement el);
    std::string checkNextTag(std::string htmlText);
};


#endif //CPP_SCRAPPER_HTMLPARSER_H
