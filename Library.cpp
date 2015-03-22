// Library.cpp is the Library class function implementation file.
//
// Lucia Blackwell
// Created 11/29/14
// Last modified 12/5/14
//

#include "Library.h"
#include "Book.h"
#include "Patron.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Daily fine constant
const double Library::DAILY_FINE = 0.1;

// Constructor (default)
Library::Library()
{
	currentDate = 0;
}

// Add book function
void Library::addBook()
{
	// Declare variables
	string newBookID, newTitle, newAuthor;
	bool uniqueID = true;

	// Get book ID from user
	cout << "Book ID code: ";
	cin >> newBookID;
	cout << endl;

	// If this isn't the first member:
	if(holdings.empty() == false)
	{
		// Make sure ID is unique
		// Loop through to find potential ID matches
		for(int i = 0; i < holdings.size(); i++)
		{
			if(newBookID == holdings[i].getIdCode())
			{
				uniqueID = false;
			}
		}

	}

	// If ID was not unique, go back to menu
	if(uniqueID == false)
	{
		cout << "That ID is already in use." << endl << endl;
	}

	else
	{
		// Get title from user
		cout << "Title: ";
		cin.ignore();
		getline(cin, newTitle);

		// Get author from user
		cout << "Author: ";
		getline(cin, newAuthor);
		cout << endl;

		// Create book
		Book newBook(newBookID, newTitle, newAuthor);

		// Add to holdings vector
		holdings.push_back(newBook);

		// Confirm for user
		cout << "Got it. New book added." << endl << endl;
	}
}

// Add member function
void Library::addMember()
{
	// Declare variables
	string newMemID, newName;
	bool uniqueID = true;

	// Get member ID from user
	cout << "Member ID number: ";
	cin >> newMemID;

	// If this isn't the first member:
	if(members.empty() == false)
	{
		// Make sure ID is unique
		// Loop through to find potential ID matches
		for(int i = 0; i < members.size(); i++)
		{
			if(newMemID == members[i].getIdNum())
			{
				uniqueID = false;
			}
		}
	}

	// If ID was not unique, return to menu
	if(uniqueID == false)
	{
		cout << "That ID is already in use." << endl << endl;
	}

	else
	{
		// Get name from user
		cout << "Name: ";
		cin.ignore();
		getline(cin, newName);
		cout << endl;

		// Create patron
		Patron newPatron(newMemID, newName);

		// Add to members vector
		members.push_back(newPatron);

		// Confirm for user
		cout << "Got it. New member added." << endl << endl;
	}
	
}

// Check out book function
void Library::checkOutBook(string patronID, string bookID)
{
	// Declare variables
	bool bookExists = false, patronExists = false;
	int whichBook, whichPatron;

	// Loop through books in library to find whether that ID exists
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
			bookExists = true;
			whichBook = i;
		}
	}

	// Loop through patrons in members to find whether that ID exists
	for(int j = 0; j < members.size(); j++)
	{
		if(members[j].getIdNum() == patronID)
		{
			patronExists = true;
			whichPatron = j;
		}
	}

	// Create variables to keep track of this book and patron
	Book *b = &holdings[whichBook];
	Patron *p = &members[whichPatron];
	Patron *pReq = b -> getRequestedBy();

	// If book and member both exist:
	if(bookExists && patronExists)
	{
		// If the book is available to this patron:
		if(b -> getLocation() == ON_SHELF || b -> getLocation() == ON_HOLD)
		{
			// If no one requested it
			if(pReq == NULL)
			{
				// Set book's checkedOutBy to this patron
				b -> setCheckedOutBy(p);

				// Set book's dateCheckedOut to this date
				b -> setDateCheckedOut(currentDate);

				// Set book's location to checked out
				b -> setLocation(CHECKED_OUT);

				// Add book to member's checked out books
				members[whichPatron].addBook(b);

				// Print confirmation
				cout << b -> getTitle() << " checked out to "
					 << p -> getName() << "." << endl << endl;				
			}

			else
			{
				// If this patron requested it
				if(pReq -> getIdNum() == patronID)
				{
					// Set book's checkedOutBy to this patron
					b -> setCheckedOutBy(p);

					// Set book's dateCheckedOut to this date
					b -> setDateCheckedOut(currentDate);

					// Set book's location to checked out
					b -> setLocation(CHECKED_OUT);

					// Add book to member's checked out books
					members[whichPatron].addBook(b);

					// Print confirmation
					cout << b -> getTitle() << " checked out to "
						 << p -> getName() << "." << endl << endl;

					// Clear hold
					b -> setRequestedBy(NULL);
				}
			}
		}

		// If book is checked out:
		else if(b -> getLocation() == CHECKED_OUT)
		{
			// Tell user book is unavailable
			cout << "That book is currently checked out." << endl << endl;
		}

		// If book is on hold shelf for someone else:
		if(b -> getLocation() == ON_HOLD && pReq -> getIdNum() != patronID)
		{
			// Tell user book is unavailable
			cout << "That book is currently requested by another member."
				 << endl << endl;
		}

	}

	// If book does not exist:
	else if(bookExists == false)
	{
		// Print book does not exist
		cout << "Book ID does not exist." << endl << endl;
	}

	// If patron does not exist:
	else if(patronExists == false)
	{
		// Print patron does not exist
		cout << "Member ID does not exist." << endl << endl;
	}
}

// Return book function
void Library::returnBook(string bookID)
{
	// Declare variables
	bool bookExists = false;
	int whichBook, patronID;

	// Loop through books in library to find whether that ID exists
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
			bookExists = true;
			whichBook = i;
		}
	}

	// If book exists:
	if(bookExists)
	{
		// Create variable to keep track of this book
		Book *b = &holdings[whichBook];

		// Get patron
		Patron *p = b -> getCheckedOutBy();

		// Check whether book is currently checked out
		if(b -> getLocation() != NULL)
		{
			if(b -> getLocation() != CHECKED_OUT)
			{
				// Print book is not checked out
				cout << "Book is not currently checked out." << endl << endl;
			}

			// Otherwise, update data
			else
			{
				// Remove book from patron's list of checked out books
				p -> removeBook(b);

				// Place in appropriate location
				if(b -> getRequestedBy() != NULL)
				{
					b -> setLocation(ON_HOLD);
					cout << "Book placed on hold shelf." << endl << endl;
				}
				else
				{
					b -> setLocation(ON_SHELF);
					cout << "Book placed on shelf." << endl << endl;
				}
			}
		}

		else
		{
			cout << "This book has not been checked out yet." << endl << endl;
		}
	}

	// If book does not exist, print error message
	else
	{
		cout << "Book ID does not exist." << endl << endl;
	}
}

// Request book function
void Library::requestBook(string patronID, string bookID)
{
	// Declare variables
	bool bookExists = false, patronExists = false;
	int whichBook, whichPatron;

	// Loop through books in library to find whether that ID exists
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
			bookExists = true;
			whichBook = i;
		}
	}

	// Loop through patrons in members to find whether that ID exists
	for(int j = 0; j < members.size(); j++)
	{
		if(members[j].getIdNum() == patronID)
		{
			patronExists = true;
			whichPatron = j;
		}
	}

	// If book and member both exist:
	if(bookExists && patronExists)
	{
		// Create variables to keep track of this book and patron
		Book *b = &holdings[whichBook];
		Patron *p = &members[whichPatron];

		// Make sure getRequestedBy and getLocation are not null
		if(b -> getRequestedBy() != NULL)
		{
			// Check whether book is requested by someone else
			if(b -> getRequestedBy() -> getIdNum() != patronID)
			{
				cout << "This book is already on request by another member."
					 << endl << endl;
			}

			// Check whether this patron has already requested the book
			else if(b -> getRequestedBy() -> getIdNum() == patronID)
			{
				cout << "This book is already on request for this member." << endl
					 << endl;
			}
		}

		// If book is not on request for anyone, request for this member
		else
		{
			// Set requested by
			b -> setRequestedBy(p);

			// If book is on shelf, put it on hold shelf
			if(b -> getLocation() == ON_SHELF)
			{
				b -> setLocation(ON_HOLD);
			}
			
			// Print confirmation
			cout << b -> getTitle() << " is now on request for "
				 << p -> getName() << endl << endl;
		}
	}

	else if(bookExists && !patronExists)
	{
		cout << "Member ID does not exist." << endl << endl;
	}

	else if(!bookExists && patronExists)
	{
		cout << "Book ID does not exist." << endl << endl;
	}

	else
	{
		cout << "Book ID and member ID do not exist." << endl << endl;
	}
}

// Increment current date function
void Library::incrementCurrentDate()
{
	// Increase current date by 1
	currentDate++;

	// Loop through members
	for(int i = 0; i < members.size(); i++)
	{
		// Create variable to keep track of patron
		Patron *p = &members[i];

		// If member has any books checked out:
		if(p -> getCheckedOutBooks().empty() == false)
		{
			// Loop through list of books to find overdue books
			for(int j = 0; j < (p -> getCheckedOutBooks().size()); j++)
			{
				// Create variable to keep track of book
				Book *b = (p -> getCheckedOutBooks()[j]);

				// If overdue book is found, incur a fine on that member
				if((currentDate - (b -> getDateCheckedOut())) > (b -> CHECK_OUT_LENGTH))
				{
					members[i].amendFine(DAILY_FINE);
				}
			}
		}
		
	}

	// Display new date
	cout << "The date is now " << currentDate << "." << endl << endl;
}

// Pay fine function
void Library::payFine(string patronID, double payment)
{
	// Declare variables
	bool patronExists = false;
	int whichPatron;

	// Loop through members to find matching patron
	for(int i = 0; i < members.size(); i++)
	{
		if(members[i].getIdNum() == patronID)
		{
			patronExists = true;
			whichPatron = i;
		}
	}

	// If patron exists:
	if(patronExists)
	{
		// Create variable to keep track of this patron
		Patron *p = &members[whichPatron];

		// Run amendFine using this amount
		p -> amendFine(-payment);

		// Print confirmation
		cout << "Fines for " << p -> getName() << " are now $" << fixed
			 << setprecision(2) << p -> getFineAmount() << "." << endl;
	}

	// If patron does not exist, print error
	else
	{
		cout << "Member ID does not match any existing members." << endl << endl;
	}
}

// View patron information function
void Library::viewPatronInfo(string patronID)
{
	// Declare variables
	bool patronExists = false;
	int whichPatron;

	// Loop through members to find matching patron
	for(int i = 0; i < members.size(); i++)
	{
		if(members[i].getIdNum() == patronID)
		{
			patronExists = true;
			whichPatron = i;
		}
	}

	// If patron exists, print information
	if(patronExists)
	{
		// Create variable to keep track of this patron
		Patron *p = &members[whichPatron];

		cout << "Member ID: " << p -> getIdNum() << endl;
		cout << "Name: " << p -> getName() << endl;
		cout << "Fines owed: $" << fixed << setprecision(2) 
			 << p -> getFineAmount() << endl << endl;
	}

	// Otherwise, print that patron does not exist
	else
	{
		cout << "Member ID does not exist." << endl << endl;
	}
}

// View book information function
void Library::viewBookInfo(string bookID)
{
	// Declare variables
	bool bookExists = false;
	int whichBook;

	// Loop through holdings to find matching book
	for(int i = 0; i < holdings.size(); i++)
	{
		if(holdings[i].getIdCode() == bookID)
		{
			bookExists = true;
			whichBook = i;
		}
	}

	// If book exists, print information
	if(bookExists)
	{
		// Create variable to keep track of this book
		Book *b = &holdings[whichBook];

		// Print book ID
		cout << "Book ID: " << b -> getIdCode() << endl;

		// Print title
		cout << "Title: " << b -> getTitle() << endl;

		// Print author
		cout << "Author: " << b -> getAuthor() << endl;

		// Print location
		// On shelf:
		if(b -> getLocation() == ON_SHELF)
		{
			cout << "Location: On shelf" << endl << endl;
		}

		// On hold:
		else if(b -> getLocation() == ON_HOLD)
		{
			cout << "Location: On hold shelf" << endl;

			// Print who has requested the book
			cout << "Requested by: " << b -> getRequestedBy() -> getName() 
				 << endl << endl;
		}

		// Checked out:
		else
		{
			cout << "Location: Checked out" << endl;

			// Print who has checked out the book
			cout << "Checked out by: " << b -> getCheckedOutBy() -> getName() << endl;

			// Print due date
			cout << "Due back on day: "
				 << (b -> getDateCheckedOut() + b -> CHECK_OUT_LENGTH) << endl
				 << endl;
		}
	}

	// Otherwise, print that book does not exist
	else
	{
		cout << "Book ID does not exist." << endl << endl;
	}
}