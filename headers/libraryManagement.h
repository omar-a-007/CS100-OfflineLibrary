#ifndef __LIBRARY_MANAGEMENT_H__
#define __LIBRARY_MANAGEMENT_H__

#include <vector>

#include "exporter.h"
#include "iComponent.h"

class LibraryManagement {
    private:
        std::vector<Category *> categories;
        Exporter* exporter;

    public:
        void display(std::string sort = "");
        void listCategories();
        Media* findMedia(std::string query);
        Category* findCategory(std::string query);
        void createCategory(iComponent *);
        void removeCategory(iComponent *);
        void addMediaToCategory(iComponent* category, iComponent* Media);
        void setExporter(Exporter * exporter) 
            {this->exporter = exporter;};
};


#endif