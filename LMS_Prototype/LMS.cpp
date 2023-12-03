#include "LMS.h"

LMS::LMS()
{
    bookList.clear();
    collectionList.clear();
    adminList.clear();
    memberList.clear();
}

LMS::~LMS()
{
    if (sampleList) delete[] sampleList;
}


vector<Book*> LMS::getBookL()
{
    return bookList;
}


vector<BookCollection*> LMS::getCollectionL()
{
    return collectionList;
}

void LMS::setSample(BookCollection* bC)
{
    this->sampleList = bC;
}

BookCollection* LMS::getSample()
{
    return sampleList;
}

void LMS::displaySampleList()
{
    sampleList->displayBooks();
}

vector<Member*> LMS::getMemberL()
{
    return memberList;
}

vector<Admin*> LMS::getAdminL()
{
    return adminList;
}