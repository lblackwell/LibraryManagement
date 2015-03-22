// Book.cpp is the Book class function implementation file.
//
// Lucia Blackwell
// Created 11/29/14
// Last modified 12/5/14
//

#include "Book.h"
#include "Patron.h"
#include <string>
#include <vector>
using namespace std;

// Checkout length constant
const int Book::CHECK_OUT_LENGTH = 21;

// Book constructor (default)
Book::Book()
{
	;
}

// Book constructor (with parameters)
Book::Book(string idc, string t, string a)
{
	idCode = idc;
	title = t;
	author = a;
	checkedOutBy = NULL;
	requestedBy = NULL;
	location = ON_SHELF;
}

// Get ID idCode
string Book::getIdCode()
{
	return idCode;
}

// Get title
string Book::getTitle()
{
	return title;
}

// Get author
string Book::getAuthor()
{
	return author;
}

// Get location
Locale Book::getLocation()
{
	return location;
}

// Set location
void Book::setLocation(Locale lo)
{
	location = lo;
}

// Get checked out by
Patron* Book::getCheckedOutBy()
{
	return checkedOutBy;
}

// Set checked out by
void Book::setCheckedOutBy(Patron* p)
{
	checkedOutBy = p;
}

// Get requested by
Patron* Book::getRequestedBy()
{
	return requestedBy;
}

// Set requested by
void Book::setRequestedBy(Patron* p)
{
	requestedBy = p;
}

// Get date checked out
int Book::getDateCheckedOut()
{
	return dateCheckedOut;
}

// Set date checked out
void Book::setDateCheckedOut(int d)
{
	dateCheckedOut = d;
}