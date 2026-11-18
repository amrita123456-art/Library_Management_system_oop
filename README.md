# Library Management System – OOP Mini Project

A menu-driven C++ console application for managing library books.

## Features
- Add and display books
- Search by book ID or exact title
- Issue books to students
- Return books
- Display currently issued books
- Save/load records using `books.txt` and `issues.txt`

## OOP concepts
- Classes and objects: `Book`, `Library`, `Person`, `Student`, `Librarian`
- Encapsulation: private data in `Book` and `Library`
- Inheritance: `Student` and `Librarian` derive from `Person`
- Abstraction: `Person` is an abstract class
- Runtime polymorphism: overridden `displayRole()` called using a base pointer
- Constructors: initialize objects
- Function overloading: `searchBook(int)` and `searchBook(string)`
- STL: `vector`
- File handling: persistent text-file storage

## Compile
```bash
g++ -std=c++11 -Wall -Wextra main.cpp -o library
```

## Run
Windows PowerShell:
```powershell
.\library.exe
```
Linux/macOS:
```bash
./library
```

Run the program from this project folder so it can find/create `books.txt` and `issues.txt`.
