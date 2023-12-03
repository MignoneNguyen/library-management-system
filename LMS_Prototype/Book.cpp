
#include "Book.h"

int Book::lastestID = 0;

Book::Book()
{
	bookTitle = "";
	author = "";
	serialNumber = 0;
	pageCount = 0;
	freePage = 0;
	category = "";
	visibility = false;
}


Book::Book(string t, string au, int pC, int fP, string c, bool vB)
{
	bookTitle = t;
	author = au;
	serialNumber = lastestID++;
	pageCount = pC;
	freePage = fP;
	category = c;
	visibility = vB;
}

void Book::setTitle(string t)
{
	bookTitle = t;
}

string Book::getTitle()
{
	return bookTitle;
}

void Book::setSerialNumber(int sN)
{
	serialNumber = sN;

}

int Book::getSerialNumber()
{
	return serialNumber;
}

void Book::setAuthor(string au)
{
	author = au;
}

string Book::getAuthor()
{
	return author;
}

void Book::setPageCount(int pC)
{
	pageCount = pC;
}

int Book::getPageCount()
{
	return pageCount;
}

void Book::setFreePage(int fP)
{
	freePage = fP;
}

int Book::getFreePage()
{
	return freePage;
}

void Book::setCategory(string c)
{
	category = c;
}

string Book::getCategory()
{
	return category;
}

void Book::setVisibility(bool vB)
{
	visibility = vB;
}

bool Book::getVisibility()
{
	return visibility;
}
