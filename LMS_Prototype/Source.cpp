#include <iostream>
#include <string>
#include <time.h>

#include "LMS.h"
#include "Book.h"
#include "BookCollection.h"
#include "Menu.h"
#include "RegisteredUser.h"
#include "Guest.h"
#include "Admin.h"

using namespace std;


enum ACTIONS {
	EXIT = 3,
	REGISTER,
	LOGIN,
	COLLECTION,
	G_SEARCH_BOOK,
	M_SEARCH_BOOK,
	A_SEARCH_BOOK,
	ADD_BOOK,
	REMOVE_BOOK,
	ACCESS_BOOK,
	MANAGE_COLLECTION,
	GUEST_COLLECTION,
	M_BORROWED
};

void menu();

void menu() {

	LMS lib;
	lib.defaultFunc();

	Guest* guestMode = new Guest(lib.getSample());

	Menu* mainMenu = new Menu("Main Menu", "The Library Main Menu");
	Menu* logIn = new Menu("LogIn Menu", "The LogIn Menu", LOGIN);
	Menu* logOut = new Menu("Logout", "You have logged out");
	Menu* guest = new Menu("Guest", "The Guest Menu", GUEST);
	Menu* memberLogIn = new Menu("Member", "The Member LogIn Menu", MEMBER);
	Menu* adminLogIn = new Menu("Admin", "The Admin LogIn Menu", ADMIN);
	Menu* exitMenu = new Menu("Exit", "Exit the Library", EXIT);
	Menu* registerMenu = new Menu("Register", "Create new user", REGISTER);


	Menu* memberMenu = new Menu("Member Menu", "The Member Menu");
	Menu* adminMenu = new Menu("Admin Menu", "The Admin Menu");

	Menu* addBookMenu = new Menu("Add Book", "Add a book to the system", ADD_BOOK);
	Menu* collectionMenu = new Menu("Collection List", "Current Collections", COLLECTION);
	Menu* searchBookMenu = new Menu("Search Book", "Search Book as a GUEST", G_SEARCH_BOOK);
	Menu* searchBookMenu_M = new Menu("Search Book", "Search Book as a MEMBER", M_SEARCH_BOOK);
	Menu* searchBookMenu_A = new Menu("Search Book", "Search Book as a ADMIN", A_SEARCH_BOOK);
	Menu* manageColMenu = new Menu("Manage Collection", "Current Collections", MANAGE_COLLECTION);
	Menu* guestCollection = new Menu("Sample Collection", "Guess can only access sample collection", GUEST_COLLECTION);
	Menu* memberBorrowed = new Menu("Borrowed Books", "Access borrowed books", M_BORROWED);

	mainMenu->addSubMenu(logIn);
	mainMenu->addSubMenu(guest);
	mainMenu->addSubMenu(exitMenu);

	logIn->addSpecialSubMenu(adminLogIn);
	logIn->addSpecialSubMenu(memberLogIn);

	logOut->addSpecialSubMenu(mainMenu);

	guest->addSpecialSubMenu(registerMenu);
	guest->addSpecialSubMenu(searchBookMenu);
	guest->addSpecialSubMenu(guestCollection);

	adminMenu->addSpecialSubMenu(logOut);
	adminMenu->addSubMenu(searchBookMenu_A);
	adminMenu->addSubMenu(addBookMenu);
	adminMenu->addSubMenu(manageColMenu);


	memberMenu->addSpecialSubMenu(logOut);
	memberMenu->addSubMenu(searchBookMenu_M);
	memberMenu->addSpecialSubMenu(memberBorrowed);
	memberMenu->addSubMenu(collectionMenu);


	Menu* manageCollection = new Menu("Manage Collection", "Manage Collections", MANAGE_COLLECTION);

	adminLogIn->addSubMenu(manageCollection);

	Menu* currentMenu = mainMenu;

	Member* currentMem = new Member();
	Admin* currentAdmin = new Admin();

	while (true)
	{
		bool memNotFound = true;
		RegisteredUser* currentUser = new RegisteredUser();
		for (int i = 0; i < lib.getMemberL().size(); i++) {
			if (currentMem != lib.getMemberL()[i]) {
				memNotFound = false;
			}
		}
		if (memNotFound == false) {
			Member* currentMem = new Member();
		}

		bool logInSucceed = false;

		currentMenu->displayMenu();
		int opt = currentMenu->pickOption();
		currentMenu = currentMenu->getSubMenu(opt - 1);
		std::cout << endl;

		switch (currentMenu->getAction()) { //checking accessibility
		case -1: break;
		case EXIT: exit(0);
			break;
		case REGISTER: 
			lib.addnewMember(guestMode->Register(lib.getMemberL(), lib.getSample()));
			currentMenu = mainMenu;
			break;
		case G_SEARCH_BOOK: currentUser->search(lib.getBookL());
			currentMenu = guest;
			break;
		case GUEST_COLLECTION: {
			cout << "Sample Collection:\n";
			guestMode->getCollection()->displayBooks();
			cout << "Type in book's order number to access it: ";
			int bookNo;
			cin >> bookNo;
			guestMode->accessBook(guestMode->getCollection()->getBooksFromCollection()[bookNo - 1]);
			currentMenu = guest;
			break;
		}
		case ADMIN: currentAdmin = currentAdmin->login(lib.getAdminL());
			if (currentAdmin == nullptr) { currentMenu = logIn; }
			else { currentMenu = adminMenu; }
			break;
		case MEMBER: currentMem = currentMem->login(lib.getMemberL());
			if (currentMem == nullptr) { currentMenu = logIn; }
			else {
				lib.getSample()->addUserList(currentMem);
				currentMenu = memberMenu; }
			break;
		}

		if (currentMem != nullptr && currentAdmin != nullptr) {
	
			switch (currentMenu->getAction()) { //checking accessibility
			case -1: break;
			case M_SEARCH_BOOK: currentMem->search(lib.getBookL());
				break;
			case COLLECTION: currentMem->accessCollection(lib.getCollectionL());
				break;
			case M_BORROWED: currentMem->displayBorrowedBooks();
				cout << "Do you want to access any book? Type 1 for 'yes' and other keys for 'no': ";
				string decision;
				cin.clear();
				cin.ignore();
				cin >> decision;
				if (decision == "1") {
					if (currentMem->getBorrowedBooks().size() > 0) {
						cout << "Type in the book's order number to access: ";
						int bOrder;
						cin >> bOrder;
						currentMem->accessBook(currentMem->getBookFromList(bOrder - 1));
					}
				}
				currentMenu = memberMenu;
				break;
			}

			Book* newBook = new Book();
			Book* removeBook = new Book();
			switch (currentMenu->getAction()) {
			case -1: break;
			case A_SEARCH_BOOK: currentAdmin->search(lib.getBookL());
				break;
			case ADD_BOOK: 
				newBook = currentAdmin->addBooks(lib.getBookL());
				lib.addNewBook(newBook);
				break;
			
			case MANAGE_COLLECTION:
				currentAdmin->manageCollection(lib.getCollectionL(), lib.getBookL());
				break;
			}
		}
	}
}


int main() {
	menu();


}

