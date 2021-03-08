#ifndef __iComponent_TEST_HPP__
#define __iComponent_TEST_HPP__

#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <sstream>

#include "../headers/library.h"

using namespace std;

TEST(iComponentTest, simpleBookLeaf) {
    Book* test = new Book("BookTitle", "SomeAuthor", "123980X", 120);

    EXPECT_EQ(test->getTitle(), "BookTitle");
    test->setTitle("A Title");
    EXPECT_EQ(test->getTitle(), "A Title");

    EXPECT_EQ(test->getQuantityAvailable(), 0);
    test->setQuantityAvailable(1);
    EXPECT_EQ(test->getQuantityAvailable(), 1);

    EXPECT_NEAR(test->getCost(), 9.99, 0.01);
    test->setCost(1.50);
    EXPECT_NEAR(test->getCost(), 1.50, 0.01);

    EXPECT_EQ(test->getAuthor(), "SomeAuthor");
    test->setAuthor("Somebody Else");
    EXPECT_EQ(test->getAuthor(), "Somebody Else");

    EXPECT_EQ(test->getMID(), 0);
    test->setMID(1);
    EXPECT_EQ(test->getMID(), 1);

    EXPECT_EQ(test->getCID(), 0);
    test->setCID(1);
    EXPECT_EQ(test->getCID(), 1);

    EXPECT_EQ(test->getISBN(), "123980X");
    test->setISBN("X123980");
    EXPECT_EQ(test->getISBN(), "X123980");

    stringstream testDisplay;
    test->display("", testDisplay);
    EXPECT_EQ(testDisplay.str(), "[Book] A Title\n\tAuthor: Somebody Else\n\tPages: 120                  ISBN: X123980\n\tQuantity Available: 1       Replacement Cost: 1.5\n");

    delete test;
}


TEST(iComponentTest, emptyComposite) {
    Category* test = new Category("Main Category");
    
    EXPECT_EQ(test->itemCount(), 0);

    EXPECT_EQ(test->getTitle(), "Main Category");
    test->setTitle("Root Category");
    EXPECT_EQ(test->getTitle(), "Root Category");

    EXPECT_EQ(test->getCID(), 0);
    test->setCID(0);
    EXPECT_EQ(test->getCID(), 0);

    EXPECT_EQ(test->getPID(), 0);
    test->setPID(1);
    EXPECT_EQ(test->getPID(), 1);

    EXPECT_EQ(test->getChildren().size(), 0);

    stringstream testDisplay;
    test->display("", testDisplay);
    EXPECT_EQ(testDisplay.str(), "\nCategory: Root Category\n------------------------------------------------\n");

    delete test;
}

TEST(iComponentTest, simpleComposite) {
    Book* b1 = new Book("BookTitle", "SomeAuthor", "123980X", 120);
    Category* test = new Category("Main Category");
    test->add(b1);
    
    EXPECT_EQ(test->itemCount(), 1);
    EXPECT_EQ(test->getCID(), 0);
    
    EXPECT_EQ(test->getChildren().size(), 1);

    stringstream testDisplay;
    test->display("", testDisplay);
    EXPECT_EQ(testDisplay.str(), "\nCategory: Main Category\n------------------------------------------------\n\t[Book] BookTitle\n\t\tAuthor: SomeAuthor\n\t\tPages: 120                  ISBN: 123980X\n\t\tQuantity Available: 0       Replacement Cost: 9.99\n");

    EXPECT_EQ(test->findMedia("BookTitle")->getTitle(), "BookTitle");
    

    delete test;
}

TEST(iComponentTest, findMedia_DNE) {
    Book* b1 = new Book("BookTitle", "SomeAuthor", "123980X", 120);
    Category* test = new Category("Main Category");
    test->add(b1);

    EXPECT_EQ(test->findMedia("My Hero"), nullptr);

    delete test;
}

TEST(iComponentTest, findCategory_DNE) {
    Category* c1 = new Category("Sub Category");
    Category* test = new Category("Main Category");
    test->add(c1);

    EXPECT_EQ(test->findCategory("My Hero"), nullptr);

    delete test;
}

TEST(iComponentTest, nestedComposite_recusriveDisplay) {
    Book* b1 = new Book("BookTitle", "SomeAuthor", "123980X", 120);
    Category* c2 = new Category("Sub Sub Category");
    Category* c1 = new Category("Sub Category");
    Category* test = new Category("Main Category");
    test->add(c1); c1->add(c2); c2->add(b1);

    stringstream testDisplay;
    test->display("", testDisplay);
    EXPECT_EQ(testDisplay.str(), "\nCategory: Main Category\n------------------------------------------------\n\t\n\tCategory: Sub Category\n\t------------------------------------------------\n\t\t\n\t\tCategory: Sub Sub Category\n\t\t------------------------------------------------\n\t\t\t[Book] BookTitle\n\t\t\t\tAuthor: SomeAuthor\n\t\t\t\tPages: 120                  ISBN: 123980X\n\t\t\t\tQuantity Available: 0       Replacement Cost: 9.99\n");

    delete test;
}

TEST(iComponentTest, nestedCompsosite_recursiveFunctions) {
    Book* b2 = new Book("BookTwo", "SomeAuthor", "1239XXX", 123);
    Book* b1 = new Book("BookTitle", "SomeAuthor", "123980X", 120);
    Category* c2 = new Category("Sub Sub Category");
    Category* c1 = new Category("Sub Category");
    Category* test = new Category("Main Category");
    test->add(c1)->add(c2);

    EXPECT_EQ(test->getChildren().size(), 1);   // test contains c1 in its children vector
    EXPECT_EQ(test->itemCount(), 0);            // recusively check all children for media

    c2->add(b1); c2->add(b2);                   // add media to Sub Sub Category
    EXPECT_EQ(test->itemCount(), 2);
    EXPECT_EQ(test->findMedia("BookTitle")->getAuthor(), "SomeAuthor");

    delete test;
}

#endif