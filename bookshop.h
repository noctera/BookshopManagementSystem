#ifndef BOOKSHOP_H
#define BOOKSHOP_H
#include "database.h"
#include <sqlite3.h>
#include <string>
#include <vector>

class Bookshop {
    public:
    Bookshop (const char* dir) : dir (dir), database (dir) {
    }
    void createTable ();
    void addBookRecords ();
    void buyBook ();
    void showBookRecords ();
    void modifyBookRecords ();
    void deleteBookRecords ();

    private:
    const char* dir;
    Database database;
};

#endif