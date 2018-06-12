//
// Created by Andrii Sumko on 11.06.18.
//

#include <gmock/gmock-matchers.h>
#include "../HtmlElement.h"

using testing::Eq;

namespace {
class ClassDeclaration : public testing::Test {
protected:
    HtmlElement obj;
    std::vector<HtmlElement*> els;
    ClassDeclaration() :obj{obj}, els{els} {};
};
}
std::string html_name = "<html>";
std::string body_name = "<body>";
std::string h1_name = "<h1>";
HtmlElement base(html_name);
HtmlElement tag1(body_name);
HtmlElement tag2(h1_name);

TEST_F(ClassDeclaration, simpleHtmlElelemtCreation) {
    obj.init(html_name, els);
    ASSERT_EQ(obj.getElementName(), "<html>");
};

TEST_F(ClassDeclaration, childrenCorrectlyCreated) {
    base.addChild(tag1);
    //base.displayInfo();
    ASSERT_EQ(base.getElementName(), html_name);
};

TEST_F(ClassDeclaration, nestingChildren) {
    tag1.addChild(tag2);
    tag1.displayInfo();
    ASSERT_EQ(tag1.getChildren().size(), 1);
};


TEST_F(ClassDeclaration, poppingChild) {
    tag1.popChild();
    ASSERT_EQ(tag1.getChildren().size(), 0);
};


