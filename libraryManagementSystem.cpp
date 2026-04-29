#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Book
{
private:
    int bookId;
    char title[50];
    char author[50];
    bool issued;

public:
    void addBook()
    {
        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cin.ignore();
        cout << "Enter Title: ";
        cin.getline(title, 50);

        cout << "Enter Author: ";
        cin.getline(author, 50);

        issued = false;
    }

    void displayBook() const
    {
        cout << "\nBook ID   : " << bookId;
        cout << "\nTitle     : " << title;
        cout << "\nAuthor    : " << author;
        cout << "\nStatus    : " << (issued ? "Issued" : "Available") << endl;
    }

    int getBookId() const
    {
        return bookId;
    }

    const char *getTitle() const
    {
        return title;
    }

    const char *getAuthor() const
    {
        return author;
    }

    bool isIssued() const
    {
        return issued;
    }

    void issueBook()
    {
        issued = true;
    }

    void returnBook()
    {
        issued = false;
    }
};

// Add Book
void addNewBook()
{
    Book b;
    ofstream file("library.dat", ios::binary | ios::app);

    b.addBook();
    file.write((char *)&b, sizeof(b));

    file.close();
    cout << "\nBook Added Successfully!\n";
}

// Display All Books
void displayAllBooks()
{
    Book b;
    ifstream file("library.dat", ios::binary);

    cout << "\n===== BOOK LIST =====\n";

    while (file.read((char *)&b, sizeof(b)))
    {
        b.displayBook();
        cout << "----------------------";
    }

    file.close();
}

// Search by Title
void searchByTitle()
{
    Book b;
    char searchTitle[50];
    bool found = false;

    cin.ignore();
    cout << "\nEnter Title to Search: ";
    cin.getline(searchTitle, 50);

    ifstream file("library.dat", ios::binary);

    while (file.read((char *)&b, sizeof(b)))
    {
        if (strcmp(b.getTitle(), searchTitle) == 0)
        {
            b.displayBook();
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook Not Found!\n";
}

// Search by Author
void searchByAuthor()
{
    Book b;
    char searchAuthor[50];
    bool found = false;

    cin.ignore();
    cout << "\nEnter Author Name to Search: ";
    cin.getline(searchAuthor, 50);

    ifstream file("library.dat", ios::binary);

    while (file.read((char *)&b, sizeof(b)))
    {
        if (strcmp(b.getAuthor(), searchAuthor) == 0)
        {
            b.displayBook();
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook Not Found!\n";
}

// Issue Book
void issueBook()
{
    Book b;
    int id;
    bool found = false;

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while (file.read((char *)&b, sizeof(b)))
    {
        if (b.getBookId() == id)
        {
            if (!b.isIssued())
            {
                b.issueBook();

                file.seekp(-static_cast<streamoff>(sizeof(b)), ios::cur);
                file.write((char *)&b, sizeof(b));

                cout << "\nBook Issued Successfully!\n";
            }
            else
            {
                cout << "\nBook Already Issued!\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook Not Found!\n";
}

// Return Book
void returnBook()
{
    Book b;
    int id;
    bool found = false;

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while (file.read((char *)&b, sizeof(b)))
    {
        if (b.getBookId() == id)
        {
            if (b.isIssued())
            {
                b.returnBook();

                file.seekp(-static_cast<streamoff>(sizeof(b)), ios::cur);
                file.write((char *)&b, sizeof(b));

                cout << "\nBook Returned Successfully!\n";
            }
            else
            {
                cout << "\nBook Was Not Issued!\n";
            }

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook Not Found!\n";
}

// Main Menu
int main()
{
    int choice;

    do
    {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search by Title\n";
        cout << "4. Search by Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addNewBook();
            break;
        case 2:
            displayAllBooks();
            break;
        case 3:
            searchByTitle();
            break;
        case 4:
            searchByAuthor();
            break;
        case 5:
            issueBook();
            break;
        case 6:
            returnBook();
            break;
        case 7:
            cout << "\nThank You!\n";
            break;
        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}