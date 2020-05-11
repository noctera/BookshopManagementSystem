#ifndef BOOK_H
#define BOOK_H
#include <string>

class Book {
    public:
    Book (std::string name, std::string author, int numberOfCopies) : name (name), author (author), numberOfCopies (numberOfCopies) {
    }
    std::string name;
    std::string author;
    unsigned int numberOfCopies;
};

#endif