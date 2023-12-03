#include "RegisteredUser.h"

RegisteredUser::RegisteredUser() : User()
{
	username = password = fullName = phone = "";
}

RegisteredUser::RegisteredUser(int id, aType aL, string u, string pw, string n, string ph) : User(id, aL)
{
	setUsername(u);
	setPassword(pw);
	setFullName(n);
	setPhone(ph);
}

RegisteredUser::~RegisteredUser() {}

void RegisteredUser::setUsername(string u)
{
	username = u;
}

string RegisteredUser::getUsername()
{
	return username;
}

void RegisteredUser::setPassword(string pw)
{
	password = pw;
}

string RegisteredUser::getPassword()
{
	return password;
}

void RegisteredUser::setFullName(string n)
{
	fullName = n;
}

string RegisteredUser::getFullName()
{
	return fullName;
}

void RegisteredUser::setPhone(string ph)
{
	phone = ph;
}

string RegisteredUser::getPhone()
{
	return phone;
}

void RegisteredUser::accessBook(Book* B)
{
	cout << "Accessing book as REGISTERED_USER " << this->getID() << endl << endl;
	cout << "Book title: " << B->getTitle() << endl;
	cout << "Serial number: " << B->getSerialNumber() << endl;
	cout << "Author: " << B->getAuthor() << endl;
	cout << "Category: " << B->getCategory() << endl;
	cout << "Total of Pages: " << B->getPageCount() << endl;
	cout << "Available Pages: " << B->getFreePage() << endl;
}


RegisteredUser* RegisteredUser::login(vector<RegisteredUser*> userL)
{
	//int loginStatus;
	//string username, password;
	//cout << "Username: ";
	//cin >> username;
	//cout << "Password: ";
	//cin >> password;

	//RegisteredUser* logInAcc = new RegisteredUser();
	//bool accFound = false;

	//for (int i = 0; i < userL.size(); i++) {
	//	if (username == userL[i]->getUsername() && password == userL[i]->getPassword()) {
	//		accFound = true;
	//		logInAcc = userL[i];
	//		break;
	//	}
	//}

	//if (accFound == true) {
	//	return logInAcc;
	//}
	//else {
	//	cout << "Username or Password is Incorrect" << endl;
	//	return nullptr;
	//}
	return nullptr;
}

int RegisteredUser::logout() {
	username = password = fullName = phone = "";
	return GUEST;
}
