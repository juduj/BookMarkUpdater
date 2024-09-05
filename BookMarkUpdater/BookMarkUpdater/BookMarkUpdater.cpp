#include <iostream>
#include <fstream>
#include <string>
#include <map>


void DisplayBooks(const std::map<std::string, int>& books);
bool ClearBook(std::string bookPath, std::map<std::string, int>& books);
void WriteBooksToFile(const std::string& filePath, const std::map<std::string, int>& books);

int main() {
    std::string bookReadLocation = "C:\\Users\\Robed\\OneDrive\\Documents\\Judah.site\\book_keep.txt";
    std::map<std::string, int> books;
    std::string bookName;
    int pageNumber;

    // Read books and pages from file
    std::ifstream infile(bookReadLocation);
    while (infile >> bookName >> pageNumber) {
        books[bookName] = pageNumber;
    }
    infile.close();

    while (true) {
        std::cout << "Current bookmarks:" << std::endl;
        DisplayBooks(books);

        std::cout << "Enter the book name to update or 'clear' to clear all, 'exit' to quit: ";
        std::cin >> bookName;

        if (bookName == "clear") {
            ClearBook(bookReadLocation, books);
            std::cout << "Book list cleared!" << std::endl;
            continue;
        }
        if (bookName == "exit") {
            break;
        }

        std::cout << "Enter the new page number: ";
        if (!(std::cin >> pageNumber) || pageNumber <= 0) {
            std::cout << "Invalid page number!" << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            continue;
        }

        // Update page number for the book
        books[bookName] = pageNumber;
        WriteBooksToFile(bookReadLocation, books);

        std::cout << "Bookmark updated!" << std::endl;
    }

    return 0;
}

void DisplayBooks(const std::map<std::string, int>& books) {
    if (books.empty()) {
        std::cout << "No books available." << std::endl;
    }
    else {
        for (const auto& [book, page] : books) {
            std::cout << "Book: " << book << ", Page: " << page << std::endl;
        }
    }
}

bool ClearBook(std::string bookPath, std::map<std::string, int>& books) {
    // Clear the file and the in-memory list
    std::ofstream book(bookPath, std::ofstream::out | std::ofstream::trunc);
    book.close();
    books.clear();
    return true;
}

void WriteBooksToFile(const std::string& filePath, const std::map<std::string, int>& books) {
    std::ofstream outfile(filePath);
    for (const auto& [book, page] : books) {
        outfile << book << " " << page << std::endl;
    }
    outfile.close();
}

