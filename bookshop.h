#ifndef BOOKSHOP_H
#define BOOKSHOP_H
#include "book.h"
#include <string>
#include <vector>

class Bookshop {
    public:
    void load ();
    void save ();
    void addBookRecords ();
    void showBookRecords ();
    bool checkAvailability ();
    void modifyBookRecords ();
    void deleteBookRecords ();
    template <class T> T fromString (const std::string& s);


    private:
    std::vector<Book> books;
};

#endif