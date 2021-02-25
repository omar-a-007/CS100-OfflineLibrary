#ifndef __iCOMPONENT_H__
#define __iCOMPONENT_H__

#include <string>
#include <vector>

class iComponent{
    protected:        std::string title;
    public:
        iComponent(){};
        virtual ~iComponent();
        virtual void display() = 0;
};

class Category : public iComponent{
    private:
        std::vector<iComponent *> children;
    public:
        Category(std::string title);
        ~Category() override;
        void display() override
            {for (auto c : children) c->display();}
        int itemCount();
        void add(iComponent *);
        void remove(iComponent *);
        iComponent* getChildren();  // <-- is this even needed with the children vector ?
};

class Media : public iComponent{
    protected:
        std::string Author;
        int quantityAvailable;
        double cost;
    public:
        Media(std::string Title, std::string Author, double Cost);
        virtual ~Media();
        virtual void display() = 0;
        std::string getTitle();
        void setTitle(std::string Title);
        void setQuantityAvailable(int quantity);
        int getQuantityAvailable();
        void setCost(double cost);
};

class DVD : public Media {
    private:
        int numMins;
    public:
        DVD(std::string Title, std::string Author, int numMins, double Cost = 19.99);
        ~DVD();
        void display() override;
};

class Book : public Media {
    private:
        int numPages;
        std::string ISBN;
    public:
        Book(std::string Title, std::string Author, std::string ISBN, int numPages, double Cost = 9.99);
        ~Book();
        void display() override ;
};

class AudioBook : public Media {
    private:
        int numMins;
    public:
        AudioBook(std::string Title, std::string Author, int numMins, double Cost = 9.99);
        ~AudioBook();
        void display() override;
};

#endif