#include "User.h"

int User::latestUserID = 0;

User::User() {
	ID = latestUserID;
	accesssiblityLevel = GUEST;
}

User::User(int id, aType aL)
{
	setID(id);
	setAccessibilityLevel(aL);
}

User::~User()
{
}

Book* User::search(vector<Book*> bookList)
{
	cout << "1. Search by title" << endl << "2. Search by serial number" << endl;
	while (true) {
		bool bookFound = false;
		Book* foundBook = new Book();
		int userOption;
		cout << "Your option: ";
		cin >> userOption;
		if (userOption != 1 && userOption != 2) {
			cout << "ERROR: Invalid Option." << endl << endl;
			cin.clear();
			cin.ignore();
			break;
		}
		else {
			if (userOption == 1) {		//User chose to search by title
				cout << "Enter title: ";
				string title;
				cin.clear();
				cin.ignore();
				getline(cin, title);
				for (int i = 0; i < bookList.size(); i++) {
					if ((bookList[i]->getVisibility() == true) && (title == bookList[i]->getTitle())) {
						foundBook = bookList[i];
						bookFound = true;
						break;
					}
				}

			}
			else {
				cout << "Enter serial number: ";
				int serialNum;
				cin >> serialNum;
				for (int i = 0; i < bookList.size(); i++) {
					if ((bookList[i]->getVisibility() == true) && (serialNum == bookList[i]->getSerialNumber())) {
						foundBook = bookList[i];
						bookFound = true;
						break;
					}
				}
			}
		}

		if (bookFound == true) {
			cout << "Book found. Access it? Type 1 for 'yes' and other keys for 'no': ";
			string gotoAccess;
			cin >> gotoAccess;
			if (gotoAccess == "1")
			{
				accessBook(foundBook);
			}
			return foundBook;
		}
		else {
			cout << "Cannot find the book." << endl << endl;
			return nullptr;
		}
	}
}

void User::setID(int id)
{
	try {
		if (id < 0) {
			throw "Invalid ID.";
		}
		else {
			ID = id;
		}
	}
	catch (const char* message) {
		cout << "ERROR: " << message << endl;
	}
}

int User::getID()
{
	return this->ID;
}

void User::setAccessibilityLevel(aType aL)
{
	try {
		if (aL != GUEST && aL != MEMBER && aL != ADMIN) { // <7pm-29/4>fix from number to enum
			throw "Invalid accessibility.";
		}
		else {
			accesssiblityLevel = aL;
		}
	}
	catch (const char* message) {
		cout << "ERROR: " << message << endl;
	}
}

aType User::getAccessibilityLevel()
{
	return accesssiblityLevel;
}
