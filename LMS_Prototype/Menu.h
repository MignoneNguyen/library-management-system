#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Menu
{
private:
	string name;
	string description;
	vector <Menu*> subMenu;
	int action;

public:
	Menu();
	Menu(string name, string description, int action = -1);
	~Menu();

	void setName(string s);
	string getName();

	void setDescription(string d);
	string getDescription();
	void setAction(int a);
	int getAction();

	void addSubMenu(Menu* m);
	Menu* getSubMenu(int index);

	void addSpecialSubMenu(Menu* m); //<7:15pm- 29/4> add specialsubmenu that doesnot create another menu

	void displayMenu();

	int pickOption();

};

