#include "bookshop.h"
#include <fstream>
#include <iostream>
#include <string>
// This funktion loads the data from a txt file and stores it into the vector
void Bookshop::load () {
    std::ifstream inputFile ("file.txt");
    if (!(inputFile.is_open ())) {
        std::cout << "Error while opening the file" << std::endl;
    } else {
        while (inputFile) {
            std::string name;
            std::getline (inputFile, name);
            if (name == "#") {
                break;
            }
            std::string author;
            std::getline (inputFile, author);
            std::string numberOfCopies;
            std::getline (inputFile, numberOfCopies);
            int numberOfCopies_int = fromString<int> (numberOfCopies);
            books.push_back (Book (name, author, numberOfCopies_int));
        }
    }
    inputFile.close ();
}

void Bookshop::save () {
    std::ofstream outputFile ("file.txt");
    if (!(outputFile.is_open ())) {
        std::cout << "Error while opening the file" << std::endl;
    } else {
        for (auto it = books.begin (); it != books.end (); ++it) {
            outputFile << it->name << std::endl << it->author << std::endl << it->numberOfCopies << std::endl;
        }
        outputFile << "#" << std::endl;
    }
    outputFile.close ();
}
// funktion is here to convert the string variable in Bookshop::load to an int, because std::getline does not support int
template <class T> T Bookshop::fromString (const std::string& s) {
    std::istringstream stream (s);
    T t;
    stream >> t;
    return t;
}