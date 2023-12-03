#include "BookCollection.h"

int BookCollection::latestCollectionID = 0;		//0 for sample collection

BookCollection::BookCollection()
{
	ID = 0;
	name = "Default Collection Name";
	bookList.clear();
	subcribedUserList.clear();
}

BookCollection::BookCollection(string n, int id)
{
	name = n;
	ID = id;
	bookList.clear();
	subcribedUserList.clear();
}

BookCollection::~BookCollection()
{
}

void BookCollection::setCollectionID(int Cid)
{
	ID = Cid;
}

int BookCollection::getCollectionID()
{
	return ID;
}

void BookCollection::setCollectionName(string n)
{
	name = n;
}

string BookCollection::getCollectionName()
{
	return name;
}

void BookCollection::addBookList(Book* book)
{
	this->bookList.push_back(book);
}

void BookCollection::removeBook(Book* book)
{
	for (int i = 0; i < bookList.size(); i++) {
		if (bookList[i]->getSerialNumber() == book->getSerialNumber()) {
			delete bookList[i];
			bookList.erase(bookList.begin() + i);
			break;
		}
	}
}

void BookCollection::addUserList(RegisteredUser* user)
{
	this->subcribedUserList.push_back(user);
}

void BookCollection::removeUser(RegisteredUser* user)
{
	for (int i = 0; i < subcribedUserList.size(); i++) {
		if (user->getID() == subcribedUserList[i]->getID()) {
			subcribedUserList.erase(subcribedUserList.begin() + i);
			break;
		}
	}
}

vector <Book*> BookCollection::getBooksFromCollection()
{
	return bookList;
}

void BookCollection::displayBooks()
{
	cout << " ====== " << this->name << " ===== " << endl;
	cout << "ID: " << this->ID << endl;
	for (int i = 0; i < bookList.size(); i++) {
		cout << i + 1 << ". " << bookList[i]->getTitle() << endl;
	}
}
