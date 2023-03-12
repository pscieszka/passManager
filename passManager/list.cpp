#include <iostream>
#include "list.h"
#include "record.h"
#include <fstream>
#include <string>
using namespace std;

void List::listing() {
    ifstream file("data.txt");
    string text;
    while (!file.eof()) {
        getline(file, text);
        cout << text << endl;
    }
    file.close();
}

void List::printMenu() {
	cout << "Menu" << endl;
	cout << "1.List account.\n2.Add account\n3.Remove\n4.Exit\nInsert number: ";
}
