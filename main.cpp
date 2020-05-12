#include "bookshop.h"
#include <cstdlib>
#include <iostream>
#include <limits>

int main () {
    Bookshop bookshop;
    bookshop.load ();
    while (true) {
        std::cout << "----------------------------" << std::endl << "|Bookshop Management System|" << std::endl << "----------------------------" << std::endl;
        std::cout << "1. Add book" << std::endl
                  << "2. Buy book" << std::endl
                  << "3. Show book information" << std::endl
                  << "4. Modify book" << std::endl
                  << "5. Delete book" << std::endl
                  << "6. Close program" << std::endl;
        std::cout << "input: ";
        int input;
        while (true) {
            std::cin >> input;
            std::cin.ignore (std::numeric_limits<std::streamsize>::max (), '\n');
            if (input < 1 || input > 6) {
                std::cout << "Wrong input, re-enter: ";
            }
            else {
                break;
            }
        }
        std::system ("clear");
        // executing the methods
        if (input == 1) {
            bookshop.addBookRecords ();
            std::cin.get ();
            std::system ("clear");
        }
        else if (input == 2) {
            bookshop.buyBook ();
            std::cin.get ();
            std::system ("clear");
        }
        else if (input == 3) {
            bookshop.showBookRecords ();
            std::cin.get ();
            std::system ("clear");
        }
        else if (input == 4) {
            bookshop.modifyBookRecords ();
            std::cin.get ();
            std::system ("clear");
        }
        else if (input == 5) {
            bookshop.deleteBookRecords ();
            std::cin.get ();
            std::system ("clear");
        }
        else if (input == 6) {
            break;
        }
    }
    bookshop.save ();
}