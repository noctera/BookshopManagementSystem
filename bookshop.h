#ifndef BOOKSHOP_H
#define BOOKSHOP_H
#include "book.h"
#include <string>
#include <vector>

class bookshop {
    public:
    void addBookRecords ();
    void showBookRecords ();
    bool checkAvailability ();
    void modifyBookRecords ();
    void deleteBookRecords ();

    private:
    std::vector<Book> books;
};

#endif