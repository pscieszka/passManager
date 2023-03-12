#include <iostream>
#include "list.h"
#include <fstream>
using namespace std;

void List::listing() {
	cout << "temp";
}

void List::printMenu() {
	cout << "Menu" << endl;
	cout << "1.List account.\n2.Add account\n3.Exit\nInsert number: ";
	int input;
	cin >> input;
	switch (input) {
	case 1:
		List::listing();
		break;
	case 2:
		//Record::insert();
		cout << "insert temp";
		break;
	case 3:
		exit(0);
		break;
	default:
		cout << "Wrong number. Try again.\nInsert number: ";
	}
}
