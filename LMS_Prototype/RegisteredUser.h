#pragma once
#include <iostream>
#include <string>
#include "User.h"
using namespace std;

class RegisteredUser : public User
{
private:
	string username, password, fullName, phone;
public:
	RegisteredUser();
	RegisteredUser(int id, aType aL, string u, string pw, string n, string ph);
	~RegisteredUser();

	void setUsername(string u);
	string getUsername();
	void setPassword(string pw);
	string getPassword();
	void setFullName(string n);
	string getFullName();
	void setPhone(string ph);
	string getPhone();

	virtual void accessBook(Book*); 

	RegisteredUser* login(vector<RegisteredUser*> uL);
	int logout();
};

