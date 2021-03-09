#include <iostream>
#include <iomanip>
#include <algorithm>

#include "../headers/iComponent.h"

Book::~Book() { }
void Book::display(const std::string& prepend, std::ostream& stream)
{
    stream << prepend << "[Book] " << this->title << std::endl;
        stream << prepend << "\t" << "Author: " << this->Author << std::endl;
        stream << prepend << "\t" << std::setw(28) << std::left << "Pages: " + std::to_string(contentLength);
                        stream << "ISBN: " << this->ISBN << std::endl;
        stream << prepend << "\t" << std::setw(28) << std::left << "Quantity Available: " + std::to_string(quantityAvailable);
                        stream << "Replacement Cost: " << this->cost << std::endl;
}

AudioBook::~AudioBook() { }
void AudioBook::display(const std::string& prepend, std::ostream& stream)
{
    stream << prepend << "[AudioBook] " << this->title << std::endl;
        stream << prepend << "\t" << "Narrator: " << this->Author << std::endl;
        stream << prepend << "\t" << "Minutes: " << this->contentLength << std::endl;
        stream << prepend << "\t" << std::setw(28) << std::left << "Quantity Available: " + std::to_string(quantityAvailable);
                        stream << "Replacement Cost: " << this->cost << std::endl;
}

DVD::~DVD() { }
void DVD::display(const std::string& prepend, std::ostream& stream)
{
    stream << prepend << "[DVD] " << this->title << std::endl;
        stream << prepend << "\t" << "Director: " << this->Author << std::endl;
        stream << prepend << "\t" << "Minutes: " << this->contentLength << std::endl;
        stream << prepend << "\t" << std::setw(28) << std::left << "Quantity Available: " + std::to_string(quantityAvailable);
                        stream << "Replacement Cost: " << this->cost << std::endl;
}



Category::~Category()
{
    for (auto& c : children)
    {
        //std::cout << "Destructor called for: " << c->getTitle() << std::endl;
        delete c;
    } 
}

const int Category::itemCount() const
{
    int i = 0;
    for (const auto& c : children)
    {
        if (Category* cat = dynamic_cast<Category*>(c))
            i += cat->itemCount();
        else if (Media* m = dynamic_cast<Media*>(c))
            ++i;
    }
    return i;
}

/* Category->add
    Returns a pointer to the child that was added, allowing for chain adding of categories.
    Currently not using a hashmap because:
    Using an ordered_map doesnt allow duplicate keys. 
        Using title as the key means Category and Media can't have the same title
        Possible Solution 1: Two add functions for Categories and Media, value is "MID/CID ###"
        Possible Solution 2: Boost::Multi_Index_Key
    {children2.insert(std::make_pair(component->getTitle(), component));}
*/
iComponent* Category::add(iComponent* component)
{
    children.push_back(component);
    return component;
}

void Category::remove(iComponent* cmp)
{    
    auto iter = std::find(children.begin(), children.end(), cmp);
    if (iter != children.end()) {
        children.erase(iter);
        delete cmp;
        return;
    }
    for (const auto& c : children)
        if (Category* cat = dynamic_cast<Category*>(c))
            cat->remove(cmp);    
}

Media* Category::findMedia(const std::string& title)
{
    for (const auto& c : children)
    {
        if (Category* cat = dynamic_cast<Category*>(c))
        {
            Media* temp = cat->findMedia(title);
            if (temp != nullptr) return temp;
        }
        else if (Media* m = dynamic_cast<Media*>(c))
            if (m->getTitle() == title) return m;
    }
    return nullptr;
}

Category* Category::findCategory(int CID)
{
    for (const auto& c : children)
    {
        if (Category* cat = dynamic_cast<Category*>(c))
        {
            if (cat->CID == CID) return cat;
            Category* temp = cat->findCategory(CID);
            if (temp != nullptr) return temp;
        }
    }
    return nullptr;
}

Category* Category::findCategory(const std::string& title)
{
    for (const auto& c : children)
    {
        if (Category* cat = dynamic_cast<Category*>(c))
        {
            if (cat->title == title) return cat;
            Category* temp = cat->findCategory(title);
            if (temp != nullptr) return temp;
        }
    }
    return nullptr;
}

std::vector<iComponent*>& Category::getChildren()
{
    return children;
}

void Category::display(const std::string& prepend, std::ostream& stream)
{   stream << prepend << std::endl;
    stream << prepend << "Category: " << title << std::endl;
    stream << prepend << "------------------------------------------------"  << std::endl;
    for (const auto& c : children) c->display(prepend + "\t", stream);
    //for (const auto& c : children2) c.second->display(prepend + "\t", stream);
}

void Category::display(bool isRoot, std::ostream& stream)
{
    if (isRoot)
    {
        for (const auto& c : children) c->display("", stream);
    }
}