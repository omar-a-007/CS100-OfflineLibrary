#ifndef __LIBRARY_MANAGEMENT_H__
#define __LIBRARY_MANAGEMENT_H__

#include <list>
#include <iostream>

#include "exporter.h"
#include "iComponent.h"

class LibraryManagement {
    private:
        void listCategories_recursive(Category* node, const std::string& prepend, std::ostream& stream) {
            for (const auto& c : node->getChildren())
            {
                if (Category* cat = dynamic_cast<Category*>(c))
                {
                    stream << prepend << cat->getTitle() << "\n";
                    listCategories_recursive(cat, prepend + "\t", stream);
                }
            }
        }

    public:
        Exporter* exporter;
        Category* root;

        LibraryManagement ()                                     { exporter = nullptr;}
        ~LibraryManagement()                                     { delete root; delete exporter;}

        void display(std::ostream& stream = std::cout)           { root->display(true, "", stream); }
        void simpleDisplay(std::ostream& stream = std::cout)	   { root->simpleDisplay("", stream); }
        void listCategories(std::ostream& stream = std::cout)    { listCategories_recursive(root, "", stream); }
        
        Media* findMedia(int MID)                                { return root->findMedia(MID);      }
        Media* findMedia(const std::string& title)               { return root->findMedia(title);    }
        Category* findCategory(int CID)                          { return root->findCategory(CID);   }
        Category* findCategory(const std::string& title)         { return root->findCategory(title); }

        void createCategory(iComponent *);
        void removeCategory(iComponent *);

        void addMediaToCategory(iComponent* category, iComponent* Media);
};


#endif
