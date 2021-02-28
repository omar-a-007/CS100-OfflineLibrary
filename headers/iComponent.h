#ifndef __iCOMPONENT_H__
#define __iCOMPONENT_H__

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

class iComponent{
    protected:        std::string title;
    public:
        iComponent(const std::string& title)
            : title(title) {};
        virtual ~iComponent() {};
        virtual void display(const std::string& prepend = "", std::ostream& stream = std::cout) = 0;
        const std::string& getTitle() const {return this->title;};
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

        const std::string& getTitle() const         {return this->title;};
        void setTitle(const std::string& Title)     {this->title = Title;};

        void setQuantityAvailable(int quantity)     {this->quantityAvailable = quantity;};
        const int getQuantityAvailable() const      {return this->quantityAvailable;};

        void setCost(double cost)                   {this->cost = cost;};
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
            :Media(Title, Author, contentLength, Cost, MID, CID, quantityAvailable), ISBN(ISBN) {};
        ~Book();
        void display(const std::string& prepend = "", std::ostream& stream = std::cout) override;
};

class AudioBook : public Media {
    public:
        AudioBook(const std::string& Title, const std::string& Author, int contentLength, double Cost = 19.99, int MID = 0, int CID = 0, int quantityAvailable = 0)
            : Media(Title, Author, contentLength, Cost, MID, CID, quantityAvailable) {};
        ~AudioBook();
        void display(const std::string& prepend = "", std::ostream& stream = std::cout) override;
};



class Category : public iComponent{
    private:
        int CID;
        int PID;
        std::vector<iComponent *> children;
        //std::unordered_map<std::string, iComponent*> children2;
    public:
        Category(const std::string& title, int CID = 0, int PID = 0)
            : iComponent(title) {};
        ~Category() override;
        void display(const std::string& prepend = "", std::ostream& stream = std::cout) override;

        const int itemCount() const;
        void add(iComponent* component);
        void remove(iComponent* component);

        Media* findMedia(std::string title);
        


        std::vector<iComponent*> getChildren();  // <-- is this even needed with the children vector ?
};

#endif
