#pragma once
#include <iostream>
#include <string>

#include "Book.h"
#include "User.h"
#include "Member.h"
using namespace std;

class Guest : public User
{
	BookCollection* subscribedCollection;
public:
	Guest();
	~Guest();
	Guest(BookCollection*);
	void setCollection(BookCollection* bC);
	BookCollection* getCollection();

	void accessBook(Book*);
	Member* Register(vector<Member*>, BookCollection* sample);
};

