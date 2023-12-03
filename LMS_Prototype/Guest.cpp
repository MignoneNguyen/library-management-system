#include "Guest.h"

Guest::Guest(BookCollection* sample)
{
	this->setID(latestUserID);
	this->setAccessibilityLevel(GUEST);
	subscribedCollection = sample;
}

void Guest::setCollection(BookCollection* bC)
{
	this->subscribedCollection = bC;
}

BookCollection* Guest::getCollection()
{
	return subscribedCollection;
}


Guest::Guest()
{
	subscribedCollection = nullptr;
}

Guest::~Guest()
{
	if (subscribedCollection) delete[] subscribedCollection;
}

void Guest::accessBook(Book* B)
{
	cout << "Accessing book as GUEST " << this->getID() << endl << endl;
	cout << "Book title: " << B->getTitle() << endl;
	cout << "Serial number: " << B->getSerialNumber() << endl;
	cout << "Author: " << B->getAuthor() << endl;
	cout << "Category: " << B->getCategory() << endl;
	cout << "Total of Pages: " << B->getPageCount() << endl;
	cout << "Available Pages: " << B->getFreePage() << endl;
}

Member* Guest::Register(vector<Member*> userL, BookCollection* sample)
{
	string username, password, fullName, phone;
	while (true) {
		cout << "Username: ";
		cin >> username;

		try {
			bool existUser = false;
			for (int i = 0; i < userL.size(); i++) {
				if (username == userL[i]->getUsername()) {
					existUser = true;
					throw "Username already existed.";
				}
			}
			if (existUser == false) {
				break;
			}

		}
		catch (const char* message) {
			cout << "ERROR: " << message << endl;
		}
	}
	cout << "Password: ";
	cin >> password;
	cout << "Full name: ";
	cin.ignore();
	getline(cin, fullName);
	cout << "Phone number: ";
	cin >> phone;

	cout << endl;
	Member* newUser = new Member(latestUserID++, MEMBER, username, password, fullName, phone, 2023, 2023 + 2, sample);
	return newUser;
}


