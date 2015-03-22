// Patron.cpp is the Patron class function implementation file.
//
// Lucia Blackwell
// Created 11/29/14
// Last modified 12/5/14
//

#include "Patron.h"
#include "Book.h"
#include <string>
#include <vector>
using namespace std;

// Patron constructor (default)
Patron::Patron()
{
	;
}

// Patron constructor (with parameters)
Patron::Patron(string idn, string n)
{
	idNum = idn;
	name = n;
	fineAmount = 0;
}

// Get ID number
string Patron::getIdNum()
{
	return idNum;
}

// Get name
string Patron::getName()
{
	return name;
}

// Get checked out books
vector<Book*> Patron::getCheckedOutBooks()
{
	return checkedOutBooks;
}

// Add book
void Patron::addBook(Book* b)
{
	checkedOutBooks.push_back(b);
}

// Remove book
void Patron::removeBook(Book* b)
{
	// Make temporary book
	Book tempBook = *b;

	for(int i = 0; i < checkedOutBooks.size(); i++)
	{
		// Create second temporary book
		Book tempBook2 = *checkedOutBooks[i];

		if(tempBook2.getIdCode() == tempBook.getIdCode())
		{
			checkedOutBooks.erase(checkedOutBooks.begin() + i);
		}
	}
}

// Get fine amount
double Patron::getFineAmount()
{
	return fineAmount;
}

// Amend fine
void Patron::amendFine(double amount)
{
	fineAmount += amount;
}