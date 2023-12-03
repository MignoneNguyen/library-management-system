#include "Admin.h"


Admin::~Admin()
{
}

Book* Admin::search(vector<Book*> bookList)
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
					if (title == bookList[i]->getTitle()) {
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
					if (serialNum == bookList[i]->getSerialNumber()) {
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
				accessBook(foundBook, bookList);
			}
			return foundBook;
		}
		else {
			cout << "Cannot find the book." << endl << endl;
			return nullptr;
		}
	}
}

void Admin::accessBook(Book* B, vector<Book*> bookList)
{
	cout << "Accessing book as ADMIN " << this->getID() << endl << endl;
	cout << "Book title: " << B->getTitle() << endl;
	cout << "Serial number: " << B->getSerialNumber() << endl;
	cout << "Author: " << B->getAuthor() << endl;
	cout << "Category: " << B->getCategory() << endl;
	cout << "Total of Pages: " << B->getPageCount() << endl;
	cout << "Free Pages: " << B->getFreePage() << endl;

	Menu* bookSetting = new Menu("Book Settings", "Modify book's settings");
	Menu* showhide = new Menu("Hide/Show", "Hide the book from the library", SHOW_OR_HIDE);
	Menu* editSetting = new Menu("Edit", "Edit book's information");
	Menu* title = new Menu("Title", "Change book's title", EDIT_TITLE);
	Menu* author = new Menu("Author", "Change book's author", EDIT_AUTHOR);
	Menu* totalPage = new Menu("Total Page", "Change book's total pages", EDIT_TOTAL_PAGES);
	Menu* freePage = new Menu("Free Page", "Change book's free pages", EDIT_FREE_PAGES);
	Menu* editCategory = new Menu("Category", "Change book's category", EDIT_CATEGORY);
	Menu* remove = new Menu("Delete", "Delete current book", REMOVE_BOOK);
	Menu* exitBookSetting = new Menu("Exit", "Exit the Book Settings", EXIT_BOOK_SETTING);

	bookSetting->addSpecialSubMenu(showhide);
	bookSetting->addSubMenu(editSetting);
	bookSetting->addSpecialSubMenu(remove);
	bookSetting->addSpecialSubMenu(exitBookSetting);

	editSetting->addSpecialSubMenu(title);
	editSetting->addSpecialSubMenu(author);
	editSetting->addSpecialSubMenu(totalPage);
	editSetting->addSpecialSubMenu(freePage);
	editSetting->addSpecialSubMenu(editCategory);

	Menu* currentMenu = bookSetting;

	bool cont = true;
	while (cont)
	{
		currentMenu->displayMenu();
		int opt = currentMenu->pickOption();
		currentMenu = currentMenu->getSubMenu(opt - 1);
		cout << endl;

		switch (currentMenu->getAction()) {
		case -1: break;
		case EXIT_BOOK_SETTING: cont = false;
			break;
		case SHOW_OR_HIDE: this->showOrHide(B);
			if (B->getVisibility() == true) { cout << "Book is now shown.\n"; }
			else { cout << "Book is now hidden.\n"; }
			currentMenu = bookSetting;
			break;
		case REMOVE_BOOK:
			removeBook(B, bookList);
			cout << "Book deleted successfully.\n";
			currentMenu = bookSetting;
			break;
		case EDIT_TITLE: editBook(B, EDIT_TITLE);
			cout << "Title changed successfully.\n";
			currentMenu = editSetting;
			break;
		case EDIT_AUTHOR: editBook(B, EDIT_AUTHOR);
			cout << "Author changed successfully.\n";
			currentMenu = editSetting;
			break;
		case EDIT_TOTAL_PAGES: editBook(B, EDIT_TOTAL_PAGES);
			cout << "Total pages changed successfully.\n";
			currentMenu = editSetting;
			break;
		case EDIT_FREE_PAGES: editBook(B, EDIT_FREE_PAGES);
			cout << "Free pages changed successfully.\n";
			currentMenu = editSetting;
			break;
		case EDIT_CATEGORY: editBook(B, EDIT_CATEGORY);
			cout << "Category changed successfully.\n";
			currentMenu = editSetting;
			break;
		}
	}

}

Book* Admin::addBooks(vector <Book*> bookList)
{
	string name;
	cout << "Book name: ";
	cin.clear();
	cin.ignore();
	getline(cin, name);

	string author;
	cout << "Author name: ";
	cin.clear();
	cin.ignore();
	getline(cin, author);

	int pageCount;
	cout << "Page Number: ";
	cin >> pageCount;

	int freePage;
	cout << "Number of free pages:: ";
	cin >> freePage;

	string category;
	string categoryList[3] = { "Culture", "Science", "Fiction" };
	for (int i = 0; i < 3; i++) {
		cout << i + 1 << ". " << categoryList[i] << endl;
	}
	int opt;
	do {
		cout << "Category option:" << endl;
		cin >> opt;
		if (opt != 1 && opt != 2 && opt != 3) {
			cout << "ERROR: Invalid option." << endl;
		}
	} while (opt != 1 && opt != 2 && opt != 3);
	category = categoryList[opt - 1];

	bool visibility;
	char opt2;
	cout << "Visibility. T or F: ";
	cin >> opt2;
	try {
		if (opt2 == 'T' || opt2 == 'F') {
			if (opt2 == 'T') visibility = true;
			else visibility = false;
		}
		else {
			throw "Invalid Input";
		}
	}
	catch (const char* mess) {
		cout << mess << endl;
	}
	Book* newBook = new Book(name, author, pageCount, freePage, category, visibility);

	return newBook;
}

void Admin::showOrHide(Book* B)
{
	if (B->getVisibility() == false) {
		B->setVisibility(true);
	}
	else {
		B->setVisibility(false);
	}
}

Book* Admin::removeBook(Book* B, vector<Book*> bL)
{
	for (int i = 0; i < bL.size(); i++) {
		if (B->getSerialNumber() == bL[i]->getSerialNumber()) {
			return B;
		}
	}
}

void Admin::editBook(Book* book, int action)
{
	//Let user first search the book before the sub-menu of Edit Book shows up
	//The book needed to edit is variable 'book'
	switch (action) {
	case EDIT_TITLE: {
		cout << "New name: ";
		string newTitle;
		cin.ignore();
		getline(cin, newTitle);
		book->setTitle(newTitle);
		break;
	}
	case EDIT_AUTHOR: {
		cout << "New author: ";
		string newAuthor;
		cin.ignore();
		getline(cin, newAuthor);
		book->setAuthor(newAuthor);
		break;
	}
	case EDIT_TOTAL_PAGES: cout << "Set total of pages: ";
		int newPages;
		cin >> newPages;
		book->setPageCount(newPages);
		break;
	case EDIT_FREE_PAGES: cout << "Set number of free pages: ";
		int newFreePages;
		cin >> newFreePages;
		book->setFreePage(newFreePages);
		break;
	case EDIT_CATEGORY: {
		string categoryList[3] = { "Culture", "Science", "Fiction" };
		for (int i = 0; i < 3; i++) {
			cout << i + 1 << ". " << categoryList[i] << endl;
		}
		int opt;
		cout << "Category option:" << endl;
		cin >> opt;
		book->setCategory(categoryList[opt - 1]);
		break; }
	}

}

void Admin::addCollection(vector<BookCollection*>& cL, vector<Book*> bookLib)
{
	cout << "Collection's name: ";
	string newName;
	cin.ignore();
	getline(cin, newName);
	BookCollection* newCollection = new BookCollection(newName);
	bool cont = true;
	while (cont == true) {	// Add book to the collection
		Book* wantedBook = this->search(bookLib);
		newCollection->addBookList(wantedBook);
		cout << "Add another book? Type 1 for 'y' and other keys for 'no': ";
		string opt;
		cin >> opt;
		if (opt != "1") { cont = false; }
	}
	cL.push_back(newCollection);	//Add this collection to collection list

}


void Admin::manageCollection(vector<BookCollection*> cL, vector<Book*> bookLib)
{
	Menu* collectionSetting = new Menu("Collection Settings", "Add and edit collections");
	Menu* addCollection = new Menu("Add Collection", "Add new collection to the library", ADD_COLLECTION);
	Menu* editCollection = new Menu("Edit Collection", "Edit collection's information");
	Menu* editCollName = new Menu("Change name", "Change the name of this collection", EDIT_COLLECTION_NAME);
	Menu* addBtoC = new Menu("Add book", "Add a new book to this collection", ADD_BOOK_TO_COLLECTION);
	Menu* removeBfC = new Menu("Remove book", "Remove a book from this collection", REMOVE_BOOK_FROM_COLLECTION);
	Menu* exitCollectionSetting = new Menu("Exit", "Exit Collection Settings", EXIT_COLLECTION_SETTING);

	vector<Menu*> collectionMenus;

	collectionSetting->addSpecialSubMenu(exitCollectionSetting);
	collectionSetting->addSpecialSubMenu(addCollection);
	collectionSetting->addSubMenu(editCollection);

	for (int i = 0; i < cL.size(); i++) {	//In edit collection, names of all collections appear and admin can choose 1 to edit
		collectionMenus.push_back(new Menu(cL[i]->getCollectionName(), "Edit this collection's info"));
		collectionMenus[i]->addSpecialSubMenu(editCollName);
		collectionMenus[i]->addSpecialSubMenu(addBtoC);
		collectionMenus[i]->addSpecialSubMenu(removeBfC);
		editCollection->addSubMenu(collectionMenus[i]);
	}
	
	Menu* currentMenu = collectionSetting;

	bool cont = true;
	int currentCol;
	while (cont)
	{
		currentMenu->displayMenu();
		int opt = currentMenu->pickOption();
		if (currentMenu == editCollection) currentCol = opt;
		currentMenu = currentMenu->getSubMenu(opt - 1);
		cout << endl;

		switch (currentMenu->getAction()) {
		case -1: break;
		case EXIT_COLLECTION_SETTING: cont = false;
			break;
		case ADD_COLLECTION: this->addCollection(cL, bookLib);
			collectionMenus.push_back(new Menu(cL[cL.size()-1]->getCollectionName(), "Edit this collection's info"));
			collectionMenus[cL.size()-1]->addSpecialSubMenu(editCollName);
			collectionMenus[cL.size()-1]->addSpecialSubMenu(addBtoC);
			editCollection->addSubMenu(collectionMenus[cL.size()-1]);
			currentMenu = collectionSetting;
			break;
		case EDIT_COLLECTION_NAME: {
			string newName;
			cout << "New collection's name: ";
			cin.ignore();
			getline(cin, newName);
			cL[currentCol-2]->setCollectionName(newName);
			collectionMenus[currentCol - 2]->setName(newName);
			currentMenu = editCollection;
			break;
		}
		case ADD_BOOK_TO_COLLECTION: {
			while (true) {	// Add book to the collection
				Book* wantedBook = this->search(bookLib);
				cL[currentCol-2]->addBookList(wantedBook);
				cout << "Add another book? Type 1 for 'yes' and other keys for 'no': ";
				string decision;
				cin >> decision;
				if (decision != "1") { break; }
			}
			currentMenu = editCollection;
			break;
		}
		case REMOVE_BOOK_FROM_COLLECTION: {
			while (true) {
				Book* wantedBook = this->search(bookLib);
				cL[currentCol-2]->removeBook(wantedBook);
				cout << "Remove another book? Type 1 for 'yes' and other keys for 'no': ";
				string decision;
				cin >> decision;
				if (decision != "1") { break; }
			}
			currentMenu = editCollection;
			break;
		}
		}
	}
	//1. Add collection
		//a. ID
		//b. Name
		//c. Add books to collection
			//Search book
			//Push to bookList
			//Repeat til "No"
	//2. Edit collection
		//Name
		//Add books (1.c)
		//Remove book
			//Print books in collection
			//Let admin choose number
			//Pop from bookList
}

Admin* Admin::login(vector<Admin*> uL) {
	int loginStatus;
	string username, password;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	Admin* logInAcc = new Admin();
	bool accFound = false;

	for (int i = 0; i < uL.size(); i++) {
		if (username == uL[i]->getUsername() && password == uL[i]->getPassword()) {
			accFound = true;
			logInAcc = uL[i];
			break;
		}
	}

	if (accFound == true) {
		return logInAcc;
	}
	else {
		cout << "Username or Password is Incorrect" << endl;
		return nullptr;
	}
}