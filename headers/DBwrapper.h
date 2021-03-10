#ifndef __DBwrapper_H__
#define __DBwrapper_H__

#include <string>
#include <list>

#include <SQLiteCpp/SQLiteCpp.h>

#include "iComponent.h"
#include "transaction.h"
#include "user.h"


class DBwrapper {
    private:
        const static std::string DBfile;
        
        std::string DBversion;
        const std::string checkDBversion() const;
        void setDBversion();
        void initDB();
        void initPopulateDB();
    public:
        DBwrapper();

        static bool login(User& userClass, const std::string& username, const std::string& password);
        static bool createAccount(const std::string& username, const std::string& password, int privelageLevel);
        static bool deleteAccount(const std::string& username, const std::string& password);
        static bool changePassword(const std::string& username, const std::string& cur_pass, const std::string& new_pass);
        static bool changePrivelageLevel(const std::string& username, int priv);
  
        static int addCategory(int ParentID, const std::string& Title);
        static int addMedia(int CID, const std::string& mediaType, const std::string& Title, const std::string& Author, double Cost, int Quantity, int Length, const std::string& ISBN);

        static void getCategories(std::list<Category*>& v);
        static void getMedia(std::list<Media*>& v);

        static int addTransaction(int UID, int MID, long DueDate);
        static bool modifyTransaction(int TID, long DueDate);
        static void getTransactions(int UID, std::list<Transaction*>& v);
};

#endif
