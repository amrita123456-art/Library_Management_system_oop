#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

class Person {
protected:
    string name;
    int id;
public:
    Person(string n, int i) : name(n), id(i) {}
    virtual void displayRole() const = 0;
    virtual ~Person() {}
};

class Student : public Person {
public:
    Student(string n, int i) : Person(n, i) {}
    void displayRole() const override {
        cout << "Student: " << name << " (ID: " << id << ")\n";
    }
    string getName() const { return name; }
    int getId() const { return id; }
};

class Librarian : public Person {
public:
    Librarian(string n, int i) : Person(n, i) {}
    void displayRole() const override {
        cout << "Librarian: " << name << " (ID: " << id << ")\n";
    }
};

class Book {
private:
    int bookId;
    string title, author;
    bool available;
public:
    Book() : bookId(0), available(true) {}
    Book(int id, string t, string a, bool status = true)
        : bookId(id), title(t), author(a), available(status) {}

    int getId() const { return bookId; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isAvailable() const { return available; }
    void issue() { available = false; }
    void giveBack() { available = true; }

    void display() const {
        cout << bookId << " | " << title << " | " << author << " | "
             << (available ? "Available" : "Issued") << '\n';
    }
};

struct IssueRecord {
    int bookId, studentId;
    string bookTitle, studentName;
    bool active;
    IssueRecord(int b, string t, string n, int s, bool a = true)
        : bookId(b), studentId(s), bookTitle(t), studentName(n), active(a) {}
};

class Library {
private:
    vector<Book> books;
    vector<IssueRecord> records;

    int findBookIndex(int id) const {
        for (int i = 0; i < (int)books.size(); ++i)
            if (books[i].getId() == id) return i;
        return -1;
    }

public:
    Library() { loadData(); }

    void addBook(const Book& book) {
        if (findBookIndex(book.getId()) != -1) {
            cout << "Book ID already exists.\n";
            return;
        }
        books.push_back(book);
        saveData();
        cout << "Book added successfully.\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books found.\n";
            return;
        }
        cout << "\nID | Title | Author | Status\n";
        for (const Book& b : books) b.display();
    }

    void searchBook(int id) const {
        int index = findBookIndex(id);
        if (index == -1) cout << "Book not found.\n";
        else books[index].display();
    }

    void searchBook(const string& title) const {
        bool found = false;
        for (const Book& b : books) {
            if (b.getTitle() == title) {
                b.display();
                found = true;
            }
        }
        if (!found) cout << "Book not found.\n";
    }

    void issueBook(int bookId, const Student& student) {
        int index = findBookIndex(bookId);
        if (index == -1) {
            cout << "Book ID does not exist.\n";
            return;
        }
        if (!books[index].isAvailable()) {
            cout << "Book is already issued.\n";
            return;
        }
        books[index].issue();
        records.push_back(IssueRecord(bookId, books[index].getTitle(),
                                      student.getName(), student.getId()));
        saveData();
        cout << "Book issued successfully.\n";
    }

    void returnBook(int bookId, int studentId) {
        int index = findBookIndex(bookId);
        if (index == -1) {
            cout << "Book ID does not exist.\n";
            return;
        }
        for (IssueRecord& r : records) {
            if (r.bookId == bookId && r.studentId == studentId && r.active) {
                r.active = false;
                books[index].giveBack();
                saveData();
                cout << "Book returned successfully.\n";
                return;
            }
        }
        cout << "No active issue record found.\n";
    }

    void displayIssuedBooks() const {
        bool found = false;
        cout << "\nCurrently Issued Books:\n";
        for (const IssueRecord& r : records) {
            if (r.active) {
                cout << r.bookTitle << " | Book ID: " << r.bookId
                     << " | Student: " << r.studentName
                     << " | Student ID: " << r.studentId << '\n';
                found = true;
            }
        }
        if (!found) cout << "No books are currently issued.\n";
    }

    void saveData() const {
        ofstream bf("books.txt");
        for (const Book& b : books)
            bf << b.getId() << '|' << b.getTitle() << '|'
               << b.getAuthor() << '|' << b.isAvailable() << '\n';
        ofstream rf("issues.txt");
        for (const IssueRecord& r : records)
            rf << r.bookId << '|' << r.bookTitle << '|' << r.studentName
               << '|' << r.studentId << '|' << r.active << '\n';
    }

    void loadData() {
        string line;
        ifstream bf("books.txt");
        while (getline(bf, line)) {
            stringstream ss(line);
            string id, title, author, status;
            if (getline(ss, id, '|') && getline(ss, title, '|') &&
                getline(ss, author, '|') && getline(ss, status))
                books.push_back(Book(stoi(id), title, author, status == "1"));
        }
        ifstream rf("issues.txt");
        while (getline(rf, line)) {
            stringstream ss(line);
            string bid, title, student, sid, active;
            if (getline(ss, bid, '|') && getline(ss, title, '|') &&
                getline(ss, student, '|') && getline(ss, sid, '|') &&
                getline(ss, active))
                records.push_back(IssueRecord(stoi(bid), title, student,
                                              stoi(sid), active == "1"));
        }
    }
};

int main() {
    Library library;
    Librarian librarian("Library Admin", 1);
    int choice;
    cout << "===== LIBRARY MANAGEMENT SYSTEM =====\n";
    librarian.displayRole();

    do {
        cout << "\n1. Add book\n2. Display all books\n3. Search by ID\n"
             << "4. Search by title\n5. Issue book\n6. Return book\n"
             << "7. Display issued books\n0. Exit\nEnter choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            int id;
            string title, author;
            cout << "Book ID: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Book title: ";
            getline(cin, title);
            cout << "Author: ";
            getline(cin, author);
            library.addBook(Book(id, title, author));
        } else if (choice == 2) {
            library.displayBooks();
        } else if (choice == 3) {
            int id;
            cout << "Enter book ID: ";
            cin >> id;
            library.searchBook(id);
        } else if (choice == 4) {
            string title;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter exact title: ";
            getline(cin, title);
            library.searchBook(title);
        } else if (choice == 5) {
            int bookId, studentId;
            string studentName;
            cout << "Book ID: ";
            cin >> bookId;
            cout << "Student ID: ";
            cin >> studentId;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Student name: ";
            getline(cin, studentName);
            Student student(studentName, studentId);
            const Person* p = &student;
            p->displayRole();
            library.issueBook(bookId, student);
        } else if (choice == 6) {
            int bookId, studentId;
            cout << "Book ID: ";
            cin >> bookId;
            cout << "Student ID: ";
            cin >> studentId;
            library.returnBook(bookId, studentId);
        } else if (choice == 7) {
            library.displayIssuedBooks();
        } else if (choice == 0) {
            library.saveData();
            cout << "Data saved. Goodbye!\n";
        } else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
