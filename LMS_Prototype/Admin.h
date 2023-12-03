#pragma once

#include <iostream>

#include "Book.h"
#include "BookCollection.h"
#include "RegisteredUser.h"
#include "Menu.h"

using namespace std;

class Admin : public RegisteredUser
{
private:
	enum BOOK_EDIT_ACTIONS {
		
		SHOW_OR_HIDE,
		EDIT_TITLE,
		EDIT_AUTHOR,
		EDIT_TOTAL_PAGES,
		EDIT_FREE_PAGES,
		EDIT_CATEGORY,
		REMOVE_BOOK,
		EXIT_BOOK_SETTING
	};

	enum MANAGE_COLLECTIONS {
		ADD_COLLECTION,
		EDIT_COLLECTION_NAME,
		ADD_BOOK_TO_COLLECTION,
		REMOVE_BOOK_FROM_COLLECTION,
		EXIT_COLLECTION_SETTING
	};
public:
	Admin() : RegisteredUser() {}

	//test
	Admin(aType aL, string u, string pw) {
		setAccessibilityLevel(aL);
		setUsername(u);
		setPassword(pw);
	}

	Admin(int id, aType aL, string u, string pw, string n, string ph) : RegisteredUser(id, aL = ADMIN, u, pw, n, ph) {}
	~Admin();

	Book* search(vector<Book*> bookList);
	void accessBook(Book*, vector<Book*>);

	Book* addBooks(vector <Book*> bookList);
	
	Book* removeBook(Book* B, vector<Book*> bL);
	void editBook(Book* book, int action);
	void addCollection(vector<BookCollection*>& cL, vector<Book*> bookLib);
	void manageCollection(vector<BookCollection*> cL, vector<Book*> bookLib);

	void showOrHide(Book* B);

	Admin* login(vector<Admin*> uL);

};

