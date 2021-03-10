#include "../headers/transaction.h"
#include "../headers/DBwrapper.h"

bool Transaction::createTransaction() {
    DueDate = std::time(nullptr)+(86400*60); // 60 days
    TID = DBwrapper::addTransaction(UID, MID, DueDate);
    return TID > 0 ? true : false;
}

bool Transaction::modifyDueDate(int days_delta) {
    if (!DueDate) return false; // No DueDate yet? Nothing to modify then!

    DueDate += (days_delta*86400);
    return DBwrapper::modifyTransaction(TID, DueDate);
}

bool Transaction::removeTransaction() {
    DueDate = REMOVED;
    return DBwrapper::modifyTransaction(TID, DueDate);
}

bool Transaction::satisfyTransaction() {
    DueDate = RETURNED;
    return DBwrapper::modifyTransaction(TID, DueDate);
}

void Transaction::checkIfOverdue() {
    if (DueDate > 0 && DueDate <= std::time(nullptr))
    {
        DueDate = PASTDUE;
        DBwrapper::modifyTransaction(TID, DueDate);  
        /* Need to charge the users account as well! */
        /* Need to charge the users account as well! */
        /* Need to charge the users account as well! */
    }
}

void Transaction::display (Category* root, bool showHistory, std::ostream& stream) {
    if (!showHistory && DueDate < 1)  return;
    switch (DueDate) {
        case REMOVED:  stream << "[ID: " << TID << std::setw(17) << std::left << " | Removed] ";      break;
        case RETURNED: stream << "[ID: " << TID << std::setw(17) << std::left << " | Returned] ";     break;
        case PASTDUE:  stream << "[ID: " << TID << std::setw(17) << std::left << " | Fee Charged] ";  break;
        default: stream << "[ID: " << TID << "] ";
    }

    stream << root->findMedia(MID)->getTitle() << "\n";
    if (DueDate > 0) {
        int DueIn = (DueDate - std::time(nullptr)) / 86400;
        std::string DueStr = DueIn == 0 ? "Due Today!" : (DueIn == 1 ? "Due Tomorrow!" : "Due in: " + std::to_string(DueIn) + " days");
        stream << "     ---" << DueStr << "\n";
    }
}