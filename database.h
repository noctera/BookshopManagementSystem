#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <sqlite3.h>
#include <string>

class Database {
    public:
    Database (const char* m_dir) : dir (m_dir) {
    }
    void openDb (const char* dir);
    void closeDb ();
    bool checkAvailability (std::string& input);
    bool checkAvailability (int& input);
    void addTableDb ();
    void addRecordToTable (std::string& title, std::string& author, int& pages, std::string& genre, std::string& publisher, std::string& isbn, int& numberOfCopies);
    void searchRecord (std::string& input);
    void deleteRecord (std::string& input);
    void buyRecord (std::string& input, int& number);
    void updateRecord (const std::string& input,
                       const std::string& title,
                       const std::string& author,
                       const int& pages,
                       const std::string& genre,
                       const std::string& publisher,
                       const std::string& isbn,
                       const int& numberOfCopies);
    Database () = delete;

    private:
    // variables for Sqlite3
    const char* dir;
    sqlite3* db;
    int rc = 0;
};
#endif