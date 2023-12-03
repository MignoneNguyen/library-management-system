#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "RegisteredUser.h"
#include "Book.h"
using namespace std;

class BookCollection
{
private:
	int ID;
	string name;
	vector<Book*> bookList;
	vector<RegisteredUser*> subcribedUserList;

public:
	static int latestCollectionID;
	BookCollection();
	BookCollection(string n, int id = latestCollectionID++);
	~BookCollection();

	void setCollectionID(int Cid);
	int getCollectionID();

	void setCollectionName(string n);
	string getCollectionName();

	void addBookList(Book* book);
	void removeBook(Book* book); 

	void addUserList(RegisteredUser* user);
	void removeUser(RegisteredUser* user);

	vector <Book*> getBooksFromCollection();

	void displayBooks();
};