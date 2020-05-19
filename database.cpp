#include "database.h"
#include <iostream>


void Database::openDb (const char* dir) {
    rc = sqlite3_open (dir, &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening Database " << sqlite3_errmsg (db) << std::endl;
    }
}

void Database::closeDb () {
    sqlite3_close (db);
}


// Checks if the field is in the database. Function overloading instead of templates
// because of bind_text and bind_int
bool Database::checkAvailability (std::string& input) {
    openDb (dir);
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2 (db, "SELECT * FROM Books WHERE Title = ? OR Isbn = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cout << sqlite3_errmsg (db);
        closeDb ();
        return false;
    }
    sqlite3_bind_text (stmt, 1, input.c_str (), input.length (), NULL);
    sqlite3_bind_text (stmt, 2, input.c_str (), input.length (), NULL);

    if (sqlite3_step (stmt) == SQLITE_ROW) {
        return true;
        sqlite3_finalize (stmt);
        sqlite3_close (db);
    }
    else {
        return false;
        sqlite3_finalize (stmt);
        sqlite3_close (db);
    }
}


void Database::addTableDb () {
    openDb (dir);

    rc = sqlite3_exec (db,
                       "CREATE TABLE IF NOT EXISTS Books(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, Title TEXT NOT NULL, Author TEXT NOT NULL, Pages INT NOT NULL, "
                       "Genre TEXT NOT NULL, Publisher TEXT NOT NULL, Isbn TEXT NOT NULL, Copies INT NOT NULL)",
                       NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating Tabel " << sqlite3_errmsg (db) << std::endl;
    }
    closeDb ();
}

// Adds the given parameters to the table
void Database::addRecordToTable (std::string& title, std::string& author, int& pages, std::string& genre, std::string& publisher, std::string& isbn, int& numberOfCopies) {
    openDb (dir);
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2 (db, "INSERT INTO Books (Title, Author, Pages, Genre, Publisher, Isbn, Copies) VALUES (?, ?, ?, ?, ?, ?, ?)", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg (db) << std::endl;
    }
    // binds the parameter values to the statement
    rc = sqlite3_bind_text (stmt, 1, title.c_str (), title.length (), NULL);
    rc = sqlite3_bind_text (stmt, 2, author.c_str (), author.length (), NULL);
    rc = sqlite3_bind_int (stmt, 3, pages);
    rc = sqlite3_bind_text (stmt, 4, genre.c_str (), genre.length (), NULL);
    rc = sqlite3_bind_text (stmt, 5, publisher.c_str (), publisher.length (), NULL);
    rc = sqlite3_bind_text (stmt, 6, isbn.c_str (), isbn.length (), NULL);
    rc = sqlite3_bind_int (stmt, 7, numberOfCopies);
    if (rc != SQLITE_OK) {
        std::cout << sqlite3_errmsg (db) << std::endl;
    }
    sqlite3_step (stmt);
    sqlite3_finalize (stmt);
    // closeDb ();
    closeDb ();
}

void Database::searchRecord (std::string& input) {
    openDb (dir);
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2 (db, "SELECT * FROM Books WHERE Title = ? OR Isbn = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg (db) << std::endl;
    }
    rc = sqlite3_bind_text (stmt, 1, input.c_str (), input.length (), NULL);
    rc = sqlite3_bind_text (stmt, 2, input.c_str (), input.length (), NULL);
    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg (db) << std::endl;
    }
    // if the row was found, output everything from this row
    if (sqlite3_step (stmt) == SQLITE_ROW) {
        std::cout << "------------------------------------------" << std::endl;
        std::cout << "Name:        " << sqlite3_column_text (stmt, 1) << std::endl;
        std::cout << "Author:      " << sqlite3_column_text (stmt, 2) << std::endl;
        std::cout << "Pages:       " << sqlite3_column_int (stmt, 3) << std::endl;
        std::cout << "Genre:       " << sqlite3_column_text (stmt, 4) << std::endl;
        std::cout << "Publisher:   " << sqlite3_column_text (stmt, 5) << std::endl;
        std::cout << "ISBN:        " << sqlite3_column_text (stmt, 6) << std::endl;
        std::cout << "Copies:      " << sqlite3_column_int (stmt, 7) << std::endl;
        std::cout << "------------------------------------------" << std::endl;
    }
    else {
        std::cout << "Book was not found" << std::endl;
    }
    sqlite3_finalize (stmt);

    closeDb ();
}
// Deletes a whole row when the title or isbn is correct
void Database::deleteRecord (std::string& input) {
    openDb (dir);
    sqlite3_stmt* stmt;
    // first checks if the row is available
    rc = sqlite3_prepare_v2 (db, "SELECT * FROM Books WHERE Title = ? or Isbn = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg (db);
    }
    rc = sqlite3_bind_text (stmt, 1, input.c_str (), input.length (), NULL);
    rc = sqlite3_bind_text (stmt, 2, input.c_str (), input.length (), NULL);
    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg (db);
    }
    // check if the row was found
    if (sqlite3_step (stmt) == SQLITE_ROW) {
        // Then deletes the whole row
        sqlite3_stmt* deleteStmt;
        sqlite3_prepare_v2 (db, "DELETE FROM Books WHERE Title = ? or Isbn = ?", -1, &deleteStmt, NULL);
        sqlite3_bind_text (deleteStmt, 1, input.c_str (), input.length (), NULL);
        sqlite3_bind_text (deleteStmt, 2, input.c_str (), input.length (), NULL);
        sqlite3_step (deleteStmt);
        std::cout << "Book was deleted" << std::endl;
        sqlite3_finalize (deleteStmt);
    }
    else {
        // if books or isbn was not found in db, method is closed without any changes;
        std::cout << "The book was not found" << std::endl;
    }
    sqlite3_finalize (stmt);
}


// method to decrease copies value by the number the user gave
void Database::buyRecord (std::string& input, int& number) {
    openDb (dir);
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2 (db, "SELECT * FROM Books WHERE Title = ? OR Isbn = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg (db);
    }
    rc = sqlite3_bind_text (stmt, 1, input.c_str (), input.length (), NULL);
    rc = sqlite3_bind_text (stmt, 2, input.c_str (), input.length (), NULL);
    if (sqlite3_step (stmt) == SQLITE_ROW) {
        // fetch the number of copies and store it in a variable to calculate
        int origNumber = sqlite3_column_int (stmt, 7);
        if (origNumber - number < 0) {
            std::cout << "Error, not enough books available" << std::endl;
        }
        else {
            origNumber -= number;
            sqlite3_stmt* updateStmt;
            rc = sqlite3_prepare_v2 (db, "UPDATE Books SET Copies = ? WHERE Title = ? OR Isbn = ?", -1, &updateStmt, NULL);
            if (rc != SQLITE_OK) {
                std::cerr << sqlite3_errmsg (db);
            }
            sqlite3_bind_int (updateStmt, 1, origNumber);
            sqlite3_bind_text (updateStmt, 2, input.c_str (), input.length (), NULL);
            sqlite3_bind_text (updateStmt, 3, input.c_str (), input.length (), NULL);
            sqlite3_step (updateStmt);
            sqlite3_finalize (updateStmt);
            std::cout << "You bought " << number << " book/s" << std::endl;
        }
    }
    else {
        std::cout << "The book was not found in the database" << std::endl;
    }
    sqlite3_finalize (stmt);
}

// Method updates the whole row with the values from the parameter list
void Database::updateRecord (const std::string& input,
                             const std::string& title,
                             const std::string& author,
                             const int& pages,
                             const std::string& genre,
                             const std::string& publisher,
                             const std::string& isbn,
                             const int& numberOfCopies) {
    openDb (dir);
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2 (db, "UPDATE Books SET Title = ?, Author = ?, Pages = ?, Genre = ?, Publisher = ?, Isbn = ?, Copies = ? WHERE Title = ? OR Isbn = ?", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg (db);
        closeDb ();
    }
    sqlite3_bind_text (stmt, 1, title.c_str (), title.length (), NULL);
    sqlite3_bind_text (stmt, 2, author.c_str (), author.length (), NULL);
    sqlite3_bind_int (stmt, 3, pages);
    sqlite3_bind_text (stmt, 4, genre.c_str (), genre.length (), NULL);
    sqlite3_bind_text (stmt, 5, publisher.c_str (), publisher.length (), NULL);
    sqlite3_bind_text (stmt, 6, isbn.c_str (), isbn.length (), NULL);
    sqlite3_bind_int (stmt, 7, numberOfCopies);
    sqlite3_bind_text (stmt, 8, input.c_str (), input.length (), NULL);
    sqlite3_bind_text (stmt, 9, input.c_str (), input.length (), NULL);
    rc = sqlite3_step (stmt);
    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg (db);
    }
    else {
        std::cout << "books was updated successfully" << std::endl;
    }
    sqlite3_finalize (stmt);
    closeDb ();
}
