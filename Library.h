//
//  Library.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//

#ifndef __examples__Library__
#define __examples__Library__

#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

class Patron;
class Book;

class Library
{
private:
    vector<Book> holdings;
    vector<Patron> members;
    int currentDate;
public:
    static const double DAILY_FINE;
    Library();
    void addBook();
    void addMember();
    void checkOutBook(string patronID, string bookID);
    void returnBook(string bookID);
    void requestBook(string patronID, string bookID);
    void incrementCurrentDate();
    void payFine(string patronID, double payment);
    void viewPatronInfo(string patronID);
    void viewBookInfo(string bookID);
};

#endif /* defined(__examples__Library__) */
