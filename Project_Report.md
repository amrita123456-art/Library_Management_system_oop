# OOP Mini Project Report: Library Management System Using C++

## Introduction
The Library Management System is a menu-driven C++ application. It manages books and basic issue/return activities. Records are stored in text files and loaded when the program starts.

## Problem Statement
Manual management of book details and issue records can be time-consuming. This project provides a simple computerized method to store and manage those records.

## Objectives
- Develop a menu-driven C++ application.
- Apply object-oriented programming concepts.
- Add, display and search books.
- Issue and return books.
- Save and retrieve data using files.

## Software Requirements
- Language: C++
- Standard: C++11 or later
- IDE: Visual Studio Code
- Compiler: GCC (g++)

## Classes
- `Person`: Abstract base class for common person details.
- `Student`: Derived class representing a student.
- `Librarian`: Derived class representing a librarian.
- `Book`: Stores book ID, title, author and availability.
- `Library`: Manages books and issue records.

## OOP Concepts Used
1. Encapsulation: Book details are private and accessed through public methods.
2. Inheritance: Student and Librarian inherit from Person.
3. Abstraction: Person contains a pure virtual function.
4. Runtime polymorphism: displayRole() is overridden and called through a Person pointer.
5. Function overloading: searchBook() searches by ID or title.
6. Constructors: Constructors initialize objects.

## Modules
1. Add Book – accepts ID, title and author.
2. Display Books – displays all books and availability.
3. Search Book – searches by ID or exact title.
4. Issue Book – checks availability and records student details.
5. Return Book – validates the active issue record and updates availability.
6. Display Issued Books – lists active issue records.
7. File Handling – saves and loads book and issue records.

## Algorithm
1. Start.
2. Create a Library object and load saved data.
3. Display the menu.
4. Read the user's choice.
5. Perform the selected operation.
6. Save data after changes.
7. Repeat until Exit is selected.
8. Save data and stop.

## Test Cases
| Test | Action | Expected result |
|---|---|---|
| Add book | Add ID 101 and book details | Book added |
| Display | Select display option | Book list appears |
| Valid search | Search ID 101 | Matching book appears |
| Invalid search | Search ID 999 | Book not found |
| Issue | Issue available book 101 | Issue successful |
| Duplicate issue | Issue book 101 again | Already issued message |
| Return | Return with matching student ID | Return successful |
| Restart | Reopen program | Saved records load |

## Advantages
- Simple menu-driven interface.
- Reduces manual record keeping.
- Demonstrates important OOP concepts.
- Retains data between runs.

## Limitations
- Console interface only.
- No password-based authentication.
- Uses text files instead of a database.
- Title search requires an exact match.

## Future Scope
- Add a graphical user interface.
- Add due dates and fine calculation.
- Store records in a database.
- Add separate student and librarian login.

## Conclusion
The Library Management System was implemented successfully in C++. It demonstrates classes, objects, encapsulation, inheritance, abstraction, runtime polymorphism, function overloading, vectors and file handling.
