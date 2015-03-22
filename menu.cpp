/* *********************************************************************
 * Author:   Lucia Blackwell
 * Created:  November 29, 2014
 * Modified: December 5, 2014
 * Filename: menu.cpp
 *
 * Overview: This program simulates a library management system. The
 *           user may enter a book into the collection, enter a new
 *           library member, check out a book to a member, return a
 *           previously checked out book, put a book on hold for a
 *           member, increment the current date, allow a member to pay
 *           an outstanding late fine, view member information, or view
 *           book information.
 *
 * Input:    The user will input a menu option (0-9), then book
 *           information, patron information, or late fee amount to be
 *           paid, depending on the function being performed.
 *
 *           Example input: 3 (Check out a book)
 *                          Member ID: 081988
 *                          Book ID: 22788
 *
 * Output:   The output of this program will be a confirmation, patron
 *           information, or book information, depending on the function
 *           being carried out.
 *
 *           Example output: Miles Learns to Love checked out to James.
 * ********************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include "Book.h"
#include "Patron.h"
#include "Library.h"
using namespace std;

int main()
{
	// Declare variables
	char menuOption;
	string patronID, bookID;
	double payment;

	// Instantiate Library
	Library library;

	// Welcome user
	cout << "Welcome to Generic Library Software" << endl << endl;

	// Do-while loop to display menu, get input, and run Library functions
	do
	{
		// Display menu options
		cout << "Please choose from the following options:" << endl;
		cout << "1 - Add a book to the collection" << endl;
		cout << "2 - Add a new library member" << endl;
		cout << "3 - Check out a book" << endl;
		cout << "4 - Return a book" << endl;
		cout << "5 - Request a book" << endl;
		cout << "6 - Increment today's date" << endl;
		cout << "7 - Pay a fine" << endl;
		cout << "8 - View patron information" << endl;
		cout << "9 - View book information" << endl;
		cout << "0 - Quit" << endl;

		//Ask user for choice
		cout << "Enter your selection:" << endl;
		cin >> menuOption;

		// If/else for options

		// Add book
		if(menuOption == '1')
		{
			library.addBook();
		}

		// Add member
		else if(menuOption == '2')
		{
			library.addMember();
		}

		// Check out book
		else if(menuOption == '3')
		{
			// Get patron ID
			cout << "Member ID: ";
			cin >> patronID;
			cout << endl;

			// Get book ID
			cout << "Book ID: ";
			cin >> bookID;
			cout << endl;

			// Run checkOutBook function using these variables
			library.checkOutBook(patronID, bookID);
		}

		// Return book
		else if(menuOption == '4')
		{
			// Get book ID
			cout << "Book ID: ";
			cin >> bookID;
			cout << endl;

			// Run returnBook function using this book
			library.returnBook(bookID);
		}

		// Request book
		else if(menuOption == '5')
		{
			// Get patron ID
			cout << "Member ID: ";
			cin >> patronID;
			cout << endl;

			// Get book ID
			cout << "Book ID: ";
			cin >> bookID;
			cout << endl;

			// Run requestBook function using these variables
			library.requestBook(patronID, bookID);
		}

		// Increment current date
		else if(menuOption == '6')
		{
			library.incrementCurrentDate();
		}

		// Pay a fine
		else if(menuOption == '7')
		{
			// Get patron ID
			cout << "Member ID: ";
			cin >> patronID;
			cout << endl;

			// Ask how much they are paying
			cout << "Amount being paid today: ";
			cin >> payment;
			cout << endl;

			// Run payFine function with these values
			library.payFine(patronID, payment);
		}

		// View patron info
		else if(menuOption == '8')
		{
			// Get patron ID
			cout << "Member ID: ";
			cin >> patronID;
			cout << endl;

			// Run viewPatronInfo with this ID
			library.viewPatronInfo(patronID);
		}

		// View book info
		else if(menuOption == '9')
		{
			// Get book ID
			cout << "Book ID: ";
			cin >> bookID;
			cout << endl;

			// Run viewBookInfo with this ID
			library.viewBookInfo(bookID);
		}

		// Quit
		else if(menuOption == '0')
		{
			;
		}

		// Otherwise tell the user input was invalid and let loop again
		else
		{
			cout << endl << "I'm sorry, I didn't recognize that input." << endl;
			cout << "Let's try that again." << endl << endl;
			cin.clear();
			cin.ignore(999, '\n');
		}

	} while(menuOption != '0');

	// When user quits, let them know
	cout << "Now quitting. Goodbye!" << endl;

	// End program
	return 0;
}