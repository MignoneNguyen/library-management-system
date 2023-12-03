#pragma once
#include <iostream>
#include <vector>
#include "RegisteredUser.h"
#include "BookCollection.h"
#include "Book.h"

#include "Menu.h"
using namespace std;

class Member : public RegisteredUser
{
private:
	int endOfMembership;
	int startOfMembership;
	vector <Book*> borrowedBook;
	vector <BookCollection*> subcribedCollection;

	enum MEMBER_ACTIONS {
		SUBCRIBE,
		UNSUB,
		SUB_LIST,
		UNSUB_LIST,
		BORROW,
		RETURN,
		EXIT_COLLECTION_ACCESS,
		ACCESS_BOOK,

	};

public:
	Member() : RegisteredUser() {};
	Member(int id, aType aL, string u, string pw, string n, string ph, int start, int end, BookCollection* sampla);
	~Member();

	void subcribe(vector<BookCollection*> colList);
	void unsubcribe(BookCollection*);

	vector<Book*> getBorrowedBooks();
	void displayBorrowedBooks();
	Book* getBookFromList(int);

	void setEndOfMembership(int e);
	int getEndOfMembership();

	void setStartOfMembership(int s);
	int getStartOfMembership();

	void borrowBook(Book* b);
	void returnBook(Book* b);

	Member* login(vector<Member*> uL);

	void accessBook (Book*);
	Book* search(vector<Book*> bookList);

	void accessCollection(vector<BookCollection*> colList);
};

