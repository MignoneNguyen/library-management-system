#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Book.h"

using namespace std;

enum aType {
	GUEST,
	MEMBER,
	ADMIN
};

class User
{
private:
	int ID;
	aType accesssiblityLevel;
public:
	static int  latestUserID;
	User();
	User(int id, aType);
	~User();

	Book* search(vector<Book*> bookList);

	void setID(int id);
	int getID();

	void setAccessibilityLevel(aType);
	aType getAccessibilityLevel();

	virtual void accessBook(Book*) = 0;
};



