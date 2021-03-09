#ifndef __iCOMPONENT_H__
#define __iCOMPONENT_H__

#include <string>
#include <list>
#include <iostream>
#include <unordered_map>

class iComponent{
    protected:        std::string title;
    public:
        iComponent(const std::string& title)
            : title(title) { }
        virtual ~iComponent() { }
        virtual void display(const std::string& prepend = "", std::ostream& stream = std::cout) = 0;

        const std::string& getTitle() const         {return this->title;}
        void setTitle(const std::string& Title)     {this->title = Title;}

        virtual iComponent* add(iComponent*)        {return nullptr;}
};

class Media : public iComponent{
    protected:
        std::string Author;
        int contentLength;  //pages, minutes, etc
        double cost;
        int MID;
        int CID;
        int quantityAvailable;
    public:
        Media(const std::string& Title, const std::string& Author, int contentLength, double cost, int MID = 0, int CID = 0, int quantityAvailable = 0)
            : iComponent(Title), Author(Author), contentLength(contentLength), cost(cost), MID(MID), CID(CID), quantityAvailable(quantityAvailable) {};
        virtual ~Media() {};

        virtual void display(const std::string& prepend = "", std::ostream& stream = std::cout) = 0;

        const std::string& getAuthor() const        {return this->Author;}
        void setAuthor(const std::string& Author)   {this->Author = Author;}

        const int getContentLength() const          {return this->contentLength;}
        void setContentLength(int contentLength)    {this->contentLength = contentLength;}

        const int getQuantityAvailable() const      {return this->quantityAvailable;}
        void setQuantityAvailable(int quantity)     {this->quantityAvailable = quantity;}

        const double getCost() const                {return this->cost;}
        void setCost(double cost)                   {this->cost = cost;}

        const int getMID() const                    {return this->MID;}
        void setMID(int MID)                        {this->MID = MID;}

        const int getCID() const                    {return this->CID;}
        void setCID(int CID)                        {this->CID = CID;}
};

class DVD : public Media {
    public:
        DVD(const std::string& Title, const std::string& Author, int contentLength, double Cost = 19.99, int MID = 0, int CID = 0, int quantityAvailable = 0)
            : Media(Title, Author, contentLength, Cost, MID, CID, quantityAvailable) {};
        ~DVD();
        void display(const std::string& prepend = "", std::ostream& stream = std::cout) override;
};

class Book : public Media {
    private:
        std::string ISBN;
    public:
        Book(const std::string& Title, const std::string& Author, const std::string& ISBN, int contentLength, double Cost = 9.99, int MID = 0, int CID = 0, int quantityAvailable = 0)
            :Media(Title, Author, contentLength, Cost, MID, CID, quantityAvailable), ISBN(ISBN) { }
        ~Book();
        void display(const std::string& prepend = "", std::ostream& stream = std::cout) override;

        const std::string& getISBN() const        {return this->ISBN;}
        void setISBN(const std::string& ISBN)     {this->ISBN = ISBN;}
};

class AudioBook : public Media {
    public:
        AudioBook(const std::string& Title, const std::string& Author, int contentLength, double Cost = 19.99, int MID = 0, int CID = 0, int quantityAvailable = 0)
            : Media(Title, Author, contentLength, Cost, MID, CID, quantityAvailable) { }
        ~AudioBook();
        void display(const std::string& prepend = "", std::ostream& stream = std::cout) override;
};



class Category : public iComponent{
    private:
        int CID;
        int PID;
        std::list<iComponent *> children;
        //std::unordered_map<std::string, iComponent*> children2;
    public:
        Category(const std::string& title, int CID = 0, int PID = 0)
            : iComponent(title), CID(CID), PID(PID) { }
        ~Category() override;
        void display(const std::string& prepend = "", std::ostream& stream = std::cout) override;
        void display(bool isRoot, std::ostream& stream = std::cout);

        const int getCID() const                    {return this->CID;}
        void setCID(int CID)                        {this->CID = CID;}

        const int getPID() const                    {return this->PID;}
        void setPID(int PID)                        {this->PID = PID;}

        const int itemCount() const;
        iComponent* add(Category* component);
        iComponent* add(Media* component);
        void remove(iComponent* component);

        Media* findMedia(const std::string& title);
        Category* findCategory(int CID);
        Category* findCategory(const std::string& title);

        std::list<iComponent*>& getChildren();  // <-- is this even needed? may remove it.
};

#endif
