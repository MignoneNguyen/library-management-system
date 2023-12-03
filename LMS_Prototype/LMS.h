#pragma once
#include <iostream>
#include <vector>

#include "Book.h"
#include "User.h"
#include "RegisteredUser.h"
#include "BookCollection.h"
#include "Member.h"
#include "Admin.h"

using namespace std;

class LMS
{
private:
	vector<Book*> bookList; 

	vector<Admin*> adminList;
	vector<Member*> memberList;

	vector<BookCollection*> collectionList;
	BookCollection* sampleList;

public:
	LMS();
	~LMS();

	vector<Book*> getBookL();
	vector<BookCollection*> getCollectionL();

	void setSample(BookCollection*);
	BookCollection* getSample();
	void displaySampleList();

	vector<Member*> getMemberL();
	vector<Admin*> getAdminL();

	void addnewMember(Member* newAcc) {
		memberList.push_back(newAcc);
	}

	void addNewBook(Book* newBook) {
		bookList.push_back(newBook);
	}

	void addNewCol(BookCollection* newCol) {
		collectionList.push_back(newCol);
	}

	void removeBook(Book* B) {
		for (int i = 0; i < bookList.size(); i++) {
			if (B->getSerialNumber() == bookList[i]->getSerialNumber()) {
				delete bookList[i];
				bookList.erase(bookList.begin() + (i - 1));
				break;
			}
		}
	}

	//Test
	void defaultFunc() {

		Book* book1 = new Book("Book 1", "Author A", 10, 2, "Culture", true);
		Book* book2 = new Book("Book 2", "Author B", 20, 5, "Science", false);
		Book* book3 = new Book("Book 3", "Author C", 15, 2, "Fiction", true);
		
		addNewBook(book1);
		addNewBook(book2);
		addNewBook(book3);

		Admin* newBoi = new Admin(ADMIN, "Bob", "123456");
		adminList.push_back(newBoi);

		BookCollection* SAMPLE = new BookCollection("Sample Collection");
		SAMPLE->addBookList(book1);
		setSample(SAMPLE);
		collectionList.push_back(SAMPLE);

		BookCollection* coll1 = new BookCollection("Collection 1");
		coll1->addBookList(book1);
		coll1->addBookList(book2);
		addNewCol(coll1);

		
	}
};