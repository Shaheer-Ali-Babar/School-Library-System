#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// structure of book
struct Book {
	int bookID;
	string title;
	string author;
};

// structure of student
struct Student {
	int studentID;
	string name;
	int age;
	string bookTitle;
	string bookISBN;
	int duration;
};

// login function
bool login() {
	string username, password;
	cout << "\nEnter login credentials:\n";
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	if (username == "admin" && password == "1234") {
		return true;
	}
	else {
		cout << "Invalid credentials.\n";
		return false;
	}
}

// add book function
void addBook() {
	ofstream outFile("book.txt", ios::app);
	Book newBook;
	cout << "Enter Book ID: ";
	cin >> newBook.bookID;
	cout << "Enter Book Title: ";
	cin.ignore();
	cin >> newBook.title;
	cout << "Enter Author Name: ";
	cin >> newBook.author;
	// Write book information to the file
	outFile << newBook.bookID << "," << newBook.title << "," << newBook.author << endl;
	cout << "Book added successfully!\n";
	outFile.close();
}

// book display function
void displayBook(string title) {
	ifstream inFile("book.txt");
	string line;
	bool found = false;
	// Read each line in the file and search for the book title
	while (getline(inFile, line)) {
		string bookTitle = line.substr(line.find(",") + 1, line.find(",",
			line.find(",") + 1) - line.find(",") - 1);
		if (bookTitle == title) {
			cout << "Book Information:\n";
			cout << line << endl;
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "Book not found.\n";
	}
	inFile.close();
}

// display all books record function
void displayAllBooks() {
	ifstream inFile("book.txt");
	string line;
	cout << "All Books:\n";
	while (getline(inFile, line)) {
		stringstream ss(line);
		string bookID, title, author;
		if (getline(ss, bookID, ',') && getline(ss, title, ',') && getline(ss,
			author)) {
			cout << "Book ID: " << bookID << endl;
			cout << "Title: " << title << endl;
			cout << "Author: " << author << endl;
			cout << endl;
		}
	}
	inFile.close();
}

// book issue function
void issueBook() {
	ofstream outFile("issued_book.txt", ios::app);
	Student newStudent;
	cout << "Enter Student ID: ";
	cin >> newStudent.studentID;
	cout << "Enter Student Name: ";
	cin.ignore();
	cin >> newStudent.name;
	cout << "Enter Student Age: ";
	cin >> newStudent.age;
	cout << "Enter Book Title: ";
	cin.ignore();
	cin >> newStudent.bookTitle;
	cout << "Enter Book ISBN: ";
	cin >> newStudent.bookISBN;
	cout << "Enter Duration (in months): ";
	cin >> newStudent.duration;
	// Write student information to the file
	outFile << newStudent.studentID << "," << newStudent.name << "," << newStudent.age
		<< ","
		<< newStudent.bookTitle << "," << newStudent.bookISBN << "," <<
		newStudent.duration << endl;
	cout << "Book issued successfully!\n";
	outFile.close();
}

// main 
int main() {
	int choice;
	bool loggedIn = false;
	cout << "\n\t --- School Library System ---\n";
	do {
		cout << "\n1. User Login\n";
		cout << "2. Add Book\n";
		cout << "3. Display Book Information\n";
		cout << "4. Display all books\n";
		cout << "5. Issue books\n";

		cout << "Enter your choice (0 to exit): ";
		cin >> choice;
		switch (choice) {
		case 0:
			cout << "Exiting program...\n";
			break;
		case 1:
			loggedIn = login();
			break;
		case 2:
			if (loggedIn) {
				addBook();
			}
			else {
				cout << "You must login first.\n";
			}
			break;
		case 3:
			if (loggedIn) {
				string title;
				cout << "Enter the book title: ";
				cin.ignore();
				getline(cin, title);
				displayBook(title);
			}
			else {
				cout << "You must login first.\n";
			}
			break;
		case 4:
			if (loggedIn) {
				displayAllBooks();
			}
			else {
				cout << "You must login first.\n";
			}
			break;
		case 5:
			if (loggedIn) {
				issueBook();
			}
			else {
				cout << "You must login first.\n";
			}
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
			break;
		}
	} while (choice != 0);
	return 0;
}