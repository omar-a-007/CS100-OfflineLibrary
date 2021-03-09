#ifndef __DBwrapper_H__
#define __DBwrapper_H__

#include <string>
#include <list>

#include <SQLiteCpp/SQLiteCpp.h>

#include "iComponent.h"

class DBwrapper {
    private:
        const static std::string DBfile;
        
        std::string DBversion;
        const std::string checkDBversion() const;
        void setDBversion();
    public:
        DBwrapper();

        void initDB();
        void initPopulateDB();

        static int login(const std::string& username, const std::string& password);
        static bool createAccount(const std::string& username, const std::string& password, int privelageLevel);
        static bool deleteAccount(const std::string& username, const std::string& password);
        static bool changePassword(const std::string& username, const std::string& cur_pass, const std::string& new_pass);
	static bool changePrivelageLevel(const std::string& username, int priv);
        int addCategory(const int ParentID, const std::string& Title);
        int addMedia(const int CID, const std::string& mediaType, const std::string& Title, const std::string& Author, const double Cost, const int Quantity, const int Length, const std::string& ISBN);

        void getCategories(std::list<Category*>& v);
        void getMedia(std::list<Media*>& v);
};

#endif
