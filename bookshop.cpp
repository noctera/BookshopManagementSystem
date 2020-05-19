#include "bookshop.h"
#include "database.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <string>


// This funktion loads the data from a txt file and stores it into the vector

void Bookshop::createTable () {
    database.addTableDb ();
}

void Bookshop::addBookRecords () {
    std::cout << "You want to add a new Book" << std::endl;
    std::cout << "Title: ";
    std::string name;
    std::getline (std::cin, name);
    std::cout << "Author: ";
    std::string author;
    std::getline (std::cin, author);
    std::cout << "Pages: ";
    int pages;
    std::cin >> pages;
    std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
    std::cout << "Genre: ";
    std::string genre;
    std::getline (std::cin, genre);
    std::cout << "Publisher: ";
    std::string publisher;
    std::getline (std::cin, publisher);
    std::cout << "ISBN: ";
    std::string isbn;
    std::getline (std::cin, isbn);
    std::cout << "Number of Copies: ";
    int numberOfCopies;
    std::cin >> numberOfCopies;
    std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
    database.addRecordToTable (name, author, pages, genre, publisher, isbn, numberOfCopies);
    std::cout << "Book was stored" << std::endl;
}


void Bookshop::buyBook () {
    std::cout << "You want to buy a book" << std::endl;
    std::cout << "Title/ISBN: ";
    std::string input;
    std::getline (std::cin, input);
    std::cout << "How many: ";
    int number;
    std::cin >> number;
    std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
    database.buyRecord (input, number);
}

void Bookshop::showBookRecords () {
    std::cout << "You want to search for a Book" << std::endl;
    std::cout << "Name/ISBN: ";
    std::string searchName;
    std::getline (std::cin, searchName);
    database.searchRecord (searchName);
}

void Bookshop::modifyBookRecords () {
    std::cout << "You want to modify a book" << std::endl;
    std::cout << "Title/ISBN: ";
    std::string input;
    std::getline (std::cin, input);
    bool isAvailable = database.checkAvailability (input);
    database.closeDb ();
    if (isAvailable) {
        std::cout << "Title: ";
        std::string title;
        std::getline (std::cin, title);
        std::cout << "Author: ";
        std::string author;
        std::getline (std::cin, author);
        std::cout << "Pages: ";
        int pages;
        std::cin >> pages;
        std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
        std::cout << "Genre: ";
        std::string genre;
        std::getline (std::cin, genre);
        std::cout << "Publisher: ";
        std::string publisher;
        std::getline (std::cin, publisher);
        std::cout << "ISBN: ";
        std::string isbn;
        std::getline (std::cin, isbn);
        std::cout << "Number of Copies: ";
        int numberOfCopies;
        std::cin >> numberOfCopies;
        std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
        database.updateRecord (input, title, author, pages, genre, publisher, isbn, numberOfCopies);
    }
    else {
        std::cout << "The book was not found" << std::endl;
    }
}

void Bookshop::deleteBookRecords () {
    std::cout << "You want to delete a book" << std::endl;
    std::cout << "Name/ISBN: ";
    std::string name;
    std::getline (std::cin, name);
    std::cout << "To confirm type in \"Delete\": " << std::endl;
    std::string confirmation;
    std::cin >> confirmation;
    std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
    if (confirmation == "Delete" || confirmation == "delete") {
        database.deleteRecord (name);
    }
    else {
        std::cout << "Wrong confirmation, books was not deleted";
    }
}