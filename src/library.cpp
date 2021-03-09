#include "../headers/library.h"

Library::Library()
{
	manager.root = recreateCompositeFromDB();
}

Category* Library::recreateCompositeFromDB()
{
	std::list<Category*> DBcategories;
    std::list<Media*> DBmedia;

    DB.getCategories(DBcategories);
    DB.getMedia(DBmedia);

    Category* root = new Category("Root");    // Root Composite Node
    
    for (auto c : DBcategories)
    {   
        int PID = c->getPID();
        if (PID != 0)   { root->findCategory(PID)->add(c); }
        else            { root->add(c); }
    }
    for (auto m : DBmedia)
    {   
        int CID = m->getCID();
        if (CID != 0)   { root->findCategory(CID)->add(m); }
        else            { root->add(m); }
    }

	return root;
}

Library::~Library()
{
	
}


void Library::borrow(Media* media)
{
}


