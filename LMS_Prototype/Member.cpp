#include "Member.h"

Member::Member(int id, aType aL, string u, string pw, string n, string ph, int start, int end, BookCollection* sample) : RegisteredUser(id, aL = MEMBER, u, pw, n, ph)
{
    startOfMembership = start;
    endOfMembership = end;
    borrowedBook.clear();
    subcribedCollection.clear();
    subcribedCollection.push_back(sample);
}

Member::~Member()
{
}

void Member::displayBorrowedBooks()
{
    for (int i = 0; i < borrowedBook.size(); i++) {
        cout << i + 1 << ". " << borrowedBook[i]->getTitle() << "<Seri: " << borrowedBook[i]->getSerialNumber() << ">" << endl;
    }
}

vector<Book*> Member::getBorrowedBooks() {
    return borrowedBook;
}

Book* Member::getBookFromList(int index)
{
    return borrowedBook[index];
}

void Member::subcribe(vector<BookCollection*> colList)
{
    
    if(colList.empty() == false){
        int colID, subOpt;
        cout << "Do you want to subcribe to any collections? 1 for yes, other keys for no" << endl;
        cin >> subOpt;
        if (subOpt == 1) {
            cout << "Chooose a collection to subcribe: ";
            cin >> colID;

            for (int i = 0; i < colList.size(); i++) {
                if (colID == colList[i]->getCollectionID()) {
                    subcribedCollection.push_back(colList[i]);
                    colList[i]->addUserList(this);
                    cout << colList[i]->getCollectionID() << '\t' << ": SUBCRIBED" << endl;
                    break;
                }

            }
        }
        cin.ignore();
        cin.clear();
    }
    else { return; }
    
   
}

void Member::unsubcribe(BookCollection* col)
{
    for (int i = 0; i < subcribedCollection.size(); i++) {
        if (col->getCollectionID() == subcribedCollection[i]->getCollectionID()) {
            col->removeUser(this);
            subcribedCollection.erase(subcribedCollection.begin() + i);
            break;
        }
    }

}

void Member::setEndOfMembership(int e)
{
    endOfMembership = e;
}

int Member::getEndOfMembership()
{
    return endOfMembership;
}

void Member::setStartOfMembership(int s)
{
    startOfMembership = s;
}

int Member::getStartOfMembership()
{
    return startOfMembership;
}

void Member::borrowBook(Book* b)
{
    borrowedBook.push_back(b);
}

void Member::returnBook(Book* b)
{
    for (int i = 0; i < borrowedBook.size(); i++) {
        if (borrowedBook[i]->getSerialNumber() == b->getSerialNumber()) {
            borrowedBook.erase(borrowedBook.begin() + i);
            break;
        }
    }
}

Member* Member::login(vector<Member*> uL) {
    int loginStatus;
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    Member* logInAcc = new Member();
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

void Member::accessBook(Book* B)
{
    cout << "Accessing book as MEMBER " << this->getID() << endl << endl;
    cout << "Book title: " << B->getTitle() << endl;
    cout << "Serial number: " << B->getSerialNumber() << endl;
    cout << "Author: " << B->getAuthor() << endl;
    cout << "Category: " << B->getCategory() << endl;
    cout << "Total of Pages: " << B->getPageCount() << endl;
    cout << "Free Pages: " << B->getPageCount() << endl;

    cout << "Checking borrow status..." << endl;

    bool borrowed = false;
    for (int i = 0; i < borrowedBook.size(); i++) {
        if (B == borrowedBook[i]) {
            cout << "Book Status: BORROWED" << endl;
            borrowed = true;
        }
    }

    if (borrowed == false) {
        try {
            cout << "Do you want to borrow this book?" << endl;
            cout << "1 for yes or 2 for no" << endl;
            int opt;
            cin >> opt;
            if (cin.fail()) {
                throw "Invalid Input";
            }
            else if(opt != 1 && opt != 2){
                throw "Out of Bounds. Only 1 or 2";
            }
            else {
                if (opt == 1) {
                    borrowBook(B);
                    cout << "Book Status: BORROWED" << endl;
                }
            }
            
        }
        catch (const char* mess) {
            cout << "ERROR: " << mess << endl;
        }
       
    }
    else {
        try {
            cout << "Do you want to return this book?" << endl;
            cout << "1 for yes or 2 for no" << endl;
            int opt;
            cin >> opt;
            if (cin.fail()) {
                throw "Invalid Input";
            }
            else if (opt != 1 && opt != 2) {
                throw "Out of Bounds. Only 1 or 2";
            }
            else {
                if (opt == 1) {
                    returnBook(B);
                    cout << "Book Status: RETURNED" << endl;
                }
               
            }

        }
        catch (const char* mess) {
            cout << "ERROR: " << mess << endl;
        }
    }
    cout << endl;
}

Book* Member::search(vector<Book*> bookList)
{
    cout << "1. Search by title" << endl << "2. Search by serial number" << endl;
    while (true) {
        int userOption;
        cout << "Your option: ";
        cin >> userOption;

        // Test for valid user option to search
        try {
            if (cin.fail()) {
                throw "Invalid Input";
            }
            else if (userOption != 1 && userOption != 2) {
                throw "Invalid Option.";
            }
            else {		// If valid:
                try {
                    if (userOption == 1) {		//User chose to search by title
                        cout << "Enter title: ";
                        string title;
                        cin.ignore();
                        getline(cin, title);

                        bool bookFound = false;
                        Book* foundBook = new Book();

                        for (int i = 0; i < bookList.size(); i++) 
                        {
                            if (title == bookList[i]->getTitle())
                            {
                                bookFound = true;
                                foundBook = bookList[i];
                                break;
                            }
                            else {
                                throw "Cannot find the book";
                            }
                        }


                        if (bookFound == true) {
                            cout << "Access this book? Type 1 for 'yes' and other keys for 'no': ";
                            string gotoAccess;
                            cin >> gotoAccess;
                            if (gotoAccess == "1")
                            {
                                accessBook(foundBook);
                                break;
                          
                            }
                            else { 
                                return foundBook;}
                        }
                        
                    }
                    else {		//User chose to search by serial number
                        cout << "Enter serial number: ";
                        int serialNum;
                        cin >> serialNum;

                        bool bookFound = false;
                        Book* foundBook = new Book();

                        for (int i = 0; i < bookList.size(); i++)
                        {

                            if (serialNum == bookList[i]->getSerialNumber())
                            {
                                bookFound = true;
                                foundBook = bookList[i];
                                break;
                            }
                            else {
                                throw "Cannot find the book";
                            }
                        }


                        if (bookFound == true) {
                            cout << "Access this book? Type 1 for 'yes' and other keys for 'no': ";
                            string gotoAccess;
                            cin >> gotoAccess;
                            if (gotoAccess == "1")
                            {
                                accessBook(foundBook);
                                break;

                            }
                            else { return foundBook; }

                    
                            
                        }
                    }
                    cout << endl;
                    break;
                }
                catch (const char* message) {
                    cin.ignore();
                    cin.clear();
 
                    cout << "ERROR: " << message << endl;
                    return nullptr;
                }
            }
        }
        catch (const char* message) {		//If user option is invalid, output error message
            cout << "ERROR: " << message << endl;
        }
    }
}

//cout << "1. Search by title" << endl << "2. Search by serial number" << endl;
//while (true) {
//    int userOption;
//    cout << "Your option: ";
//    cin >> userOption;
//    // Test for valid user option to search
//    try {
//        if (userOption != 1 && userOption != 2) {
//            throw "Invalid option.";
//        }
//        //cin.fail()
//        else {		// If valid:
//            try {
//                if (userOption == 1) {		//User chose to search by title
//                    cout << "Enter title: ";
//                    string title;
//                    getline(cin, title);
//                    for (int i = 0; i < bookList.size(); i++) {
//                        if ((bookList[i]->getVisibility() == true) && (title == bookList[i]->getTitle())) {
//                            return bookList[i]; break;
//                        }
//                        else { throw "Cannot find the book."; break; }
//                    }
//                }
//                else {		//User chose to search by serial number
//                    cout << "Enter serial number: ";
//                    int serialNum;
//                    cin >> serialNum;
//                    for (int i = 0; i < bookList.size(); i++) {
//                        if ((bookList[i]->getVisibility() == true) && (serialNum == bookList[i]->getSerialNumber())) {
//                            return bookList[i]; break;
//                        }
//                        else { throw "Cannot find the book."; break; }
//                    }
//                }
//            }
//            catch (const char* message) {
//                cin.clear();
//                cin.ignore();
//                cout << "ERROR: " << message << endl;
//                return nullptr;
//            }
//        }
//    }
//    catch (const char* message) {		//If user option is invalid, output error message
//        cout << "ERROR: " << message << endl;
//    }
//}

void Member::accessCollection(vector<BookCollection*> colList)
{
    Menu* accessCollMenu = new Menu("Access Collections", "Access and explore collections");
    Menu* subscribedMenu = new Menu("Subcribed Collections", "View the subcribed collections", SUB_LIST);
    Menu* unsubcribedMenu = new Menu("Other Collections", "Explore other collections", UNSUB_LIST);
    Menu* unsubOpt = new Menu("Ubsubcribe", "Unsubscribe this collection", UNSUB);
    Menu* accessBookOpt = new Menu("Access books", "Access books inside this colection", ACCESS_BOOK);
    Menu* exitCollectionMenu = new Menu("Exit", "Exit Collection Settings", EXIT_COLLECTION_ACCESS);
    vector<Menu*> collectionMenus;

    accessCollMenu->addSubMenu(subscribedMenu);
    accessCollMenu->addSubMenu(unsubcribedMenu);
    accessCollMenu->addSubMenu(exitCollectionMenu);

    Menu* currentMenu = accessCollMenu;

    bool cont = true;
    
    BookCollection* currentCollection = new BookCollection();
    while (cont)
    {
       // Book* currentBook = new Book();
         
        int bookID = 0;

        currentMenu->displayMenu();
        int opt = currentMenu->pickOption();
        currentMenu = currentMenu->getSubMenu(opt - 1);

        for (int i = 0; i < subcribedCollection.size(); i++) {
            if (currentMenu->getName() == subcribedCollection[i]->getCollectionName()) {
                currentCollection = subcribedCollection[i];
                break;
            }
        }
        cout << endl;

        switch (currentMenu->getAction()) {
        case -1: break;
        case EXIT_COLLECTION_ACCESS: cont = false;
            break;
        case SUB_LIST:
            if (subcribedCollection.empty()) {
                cout << "There is no subcribed Collection AVAILABLE" << endl;
                currentMenu = accessCollMenu;
                break;
            }

            for (int i = 0; i < subcribedCollection.size(); i++) {
                collectionMenus.push_back(new Menu(subcribedCollection[i]->getCollectionName(), "Accessing collection " + subcribedCollection[i]->getCollectionName()));
                vector<Menu*> bookMenus;

                for (int o = 0; o < subcribedCollection[i]->getBooksFromCollection().size(); o++) {
                    bookMenus.push_back(new Menu(subcribedCollection[i]->getBooksFromCollection()[o]->getTitle(), "Accessing current book in the collection", ACCESS_BOOK));
                    accessBookOpt->addSpecialSubMenu(bookMenus[o]);
                }
                collectionMenus[i]->addSubMenu(accessBookOpt);
                collectionMenus[i]->addSubMenu(unsubOpt);
                subscribedMenu->addSpecialSubMenu(collectionMenus[i]);
                collectionMenus[i]->addSpecialSubMenu(exitCollectionMenu);
            }

            currentMenu = subscribedMenu;

            break;
        case UNSUB_LIST:
           
            if (colList.size() == subcribedCollection.size()) {
                cout << "NO COLLECTIONS TO SUBCRIBE" << endl;
                break;
            }

            cout << "===== " << "LIST OF UNSUBCRIBED LIST" << " =====" << endl;
            cout << "ID. " << '\t' << "NAME" << endl;
            if (subcribedCollection.empty() == false) {
                for (int i = 0; i < colList.size(); i++) {
                    bool exist = false;
                    for (int j = 0; j < subcribedCollection.size(); j++) {
                        if (subcribedCollection[j] == colList[i]) {
                            exist = true;
                            break;
                        }
                        
                    }

                    if(exist == false){ cout << colList[i]->getCollectionID() << '\t' << colList[i]->getCollectionName() << endl; }
                    
                }
                
            }
            else {
                for (int i = 0; i < colList.size(); i++) {
                    cout << colList[i]->getCollectionID() << '\t' << colList[i]->getCollectionName() << endl;
                }
            }
            

            subcribe(colList);
            break;
        case UNSUB:unsubcribe(currentCollection);
            currentMenu = accessCollMenu;
            break;
        case ACCESS_BOOK: 
            currentCollection->displayBooks();

            cout << "Enter a Book ID: ";
            cin >> bookID;
            for (int i = 0; i < currentCollection->getBooksFromCollection().size(); i++) {
                if (bookID == currentCollection->getBooksFromCollection()[i]->getSerialNumber()) {
                    accessBook(currentCollection->getBooksFromCollection()[i]);
                    break;
                }
            }
           
            currentMenu = subscribedMenu;
            break;
            }
        }
        
    
}
