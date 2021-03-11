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

    Category* root = new Category("Root", 0, 0);    // Root Composite Node
    
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
        DBwrapper::getTransactions(UID, borrowLog);
    for (auto& i : borrowLog)
        i->display(root, showHistory, stream);
}


bool Library::borrow(Media* media)
{
    if (media == nullptr) return false;
    if (!media->getQuantityAvailable()) return false;

    Transaction* t = new Transaction(getUID(), media->getMID(), false);
    bool result = t->createTransaction();

    if (result) {
        borrowLog.push_back(t);
        media->setQuantityAvailable(media->getQuantityAvailable() - 1);
        DBwrapper::setMediaQty(media->getMID(), media->getQuantityAvailable());
    }
    else {delete t;}
    return result;
}


