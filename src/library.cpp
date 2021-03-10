#include "../headers/library.h"
#include "../headers/DBwrapper.h"

Library::Library()
{
	root = recreateCompositeFromDB();
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

void Library::showTransactions(int UID, bool showHistory, std::ostream& stream) 
{
    if (UID != getUID())
        clearBorrowLog();
    if (borrowLog.size() == 0)
        DB.getTransactions(UID, borrowLog);
        //DBwrapper::getTransactions(UID, borrowLog);
    for (auto& i : borrowLog)
        i->display(root, showHistory, stream);
}


void Library::borrow(Media* media)
{
}


