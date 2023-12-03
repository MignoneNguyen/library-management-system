#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book/*: public Library*/
{
private:

	string bookTitle;
	string author;
	int serialNumber;
	int pageCount;
	int freePage;
	string category;
	bool visibility;
	static int lastestID;

public:
	Book();
	Book(string t, string au, int pC, int fP, string c, bool vB);

	void setTitle(string t);
	string getTitle();

	void setSerialNumber(int sN);
	int getSerialNumber();

	void setAuthor(string au);
	string getAuthor();

	void setPageCount(int pC);
	int getPageCount();

	void setFreePage(int fP);
	int getFreePage();

	void setCategory(string c);
	string getCategory();

	void setVisibility(bool vB);
	bool getVisibility();
};

