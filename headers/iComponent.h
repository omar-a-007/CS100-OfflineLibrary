#ifndef __iCOMPONENT_H__
#define __iCOMPONENT_H__

#include <string>
#include <vector>

class iComponent{
    protected:        std::string title;
    public:
        iComponent(std::string title)
            :title(title) {};
        virtual ~iComponent() {};
        virtual void display() = 0;
};

class Category : public iComponent{
    private:
        int CID;
        std::vector<iComponent *> children;
    public:
        Category(std::string Title)
            :iComponent(Title) {};
        ~Category() override;
        void display() override
            {for (auto c : children) c->display();}
        int itemCount() const
            {return children.size();};
        void add(iComponent *);
        void remove(iComponent *);
        iComponent* getChildren();  // <-- is this even needed with the children vector ?
};

class Media : public iComponent{
    protected:
        int MID;
        std::string Author;
        int quantityAvailable;
        int contentLength;  //pages, minutes, etc
        double cost;
    public:
        Media(std::string Title, std::string Author, int contentLength, double cost)
            : iComponent(Title), Author(Author), contentLength(contentLength), cost(cost) {};
        virtual ~Media() {};
        virtual void display() = 0;
        std::string getTitle() const                {return this->title;};
        void setTitle(const std::string& Title)     {this->title = Title;};
        void setQuantityAvailable(int quantity)     {this->quantityAvailable = quantity;};
        int getQuantityAvailable() const            {return this->quantityAvailable;};
        void setCost(double cost)                   {this->cost = cost;};
};

class DVD : public Media {
    public:
        DVD(std::string Title, std::string Author, int contentLength, double Cost = 19.99)
            : Media(Title, Author, contentLength, Cost) {};
        ~DVD();
        void display() override {};
};

class Book : public Media {
    private:
        std::string ISBN;
    public:
        Book(std::string Title, std::string Author, std::string ISBN, int contentLength, double Cost = 9.99)
            :Media(Title, Author, contentLength, Cost), ISBN(ISBN) {};
        ~Book();
        void display() override;
};

class AudioBook : public Media {
    public:
        AudioBook(std::string Title, std::string Author, int contentLength, double Cost = 9.99)
            :Media(Title, Author, contentLength, Cost) {};
        ~AudioBook();
        void display() override;
};

#endif