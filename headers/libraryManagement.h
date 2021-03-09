#ifndef __LIBRARY_MANAGEMENT_H__
#define __LIBRARY_MANAGEMENT_H__

#include <list>

#include "exporter.h"
#include "iComponent.h"

class LibraryManagement {
    public:
        Exporter* exporter;
        Category* root;

        ~LibraryManagement() { delete root; delete exporter;}

        void display(std::string sort = "");
        void listCategories();
        
        Media* findMedia(std::string query);
        
        Category* findCategory(std::string query);

        void createCategory(iComponent *);
        void removeCategory(iComponent *);

        void addMediaToCategory(iComponent* category, iComponent* Media);
};


#endif