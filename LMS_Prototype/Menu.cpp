#include "Menu.h"


Menu::Menu()
{
	name = "Default Name";
	description = "Default description";
	action = -1;
	subMenu.clear();
}

Menu::Menu(string n, string d, int a)
{
	this->name = n;
	this->description = d;
	this->action = a;
	
	subMenu.clear();
}

Menu::~Menu()
{
	if (subMenu.size() > 0) {
		for (int i = 0; i < subMenu.size(); i++) {
			if (subMenu[i]) delete subMenu[i];
		}
	}
}

void Menu::setName(string s)
{
	this->name = s;

}

string Menu::getName()
{
	return name;
}

void Menu::setDescription(string d)
{
	this->description = d;
}

string Menu::getDescription()
{
	return description;
}

void Menu::setAction(int a)
{
	this->action = a;
}

int Menu::getAction()
{
	return action;
}

void Menu::addSubMenu(Menu* m)
{
	this->subMenu.push_back(m);
	m->subMenu.push_back(this);
}

Menu* Menu::getSubMenu(int index)
{
	if (index >= 0 && index < subMenu.size()) {
		return subMenu[index];
	}
	else return nullptr;
}

void Menu::addSpecialSubMenu(Menu* m)
{
	this->subMenu.push_back(m);
}


void Menu::displayMenu()
{
	//system("cls");
	cout << " ====== " << this->name << " ===== " << endl;
	cout << this->description << endl;
	for (int i = 0; i < subMenu.size(); i++) {
		cout << i + 1 << ". " << subMenu[i]->getName() << endl;
	}

}

int Menu::pickOption()
{
	while (true) {
		cout << "Pick an option: ";
		int opt;
		cin >> opt;
		try {
			if (cin.fail()) {
				throw "Invalid Input";
			}
			else if (opt <= 0 || opt > subMenu.size()) {
				throw "Out Of Range";
			}
			else {
				return opt;
			}
		}
		catch (const char* message) {
			cin.clear();
			cin.ignore();
			cout << "Error: " << message << endl;
		}
	}
}
