#include <iostream>
#include "list.h"
#include "record.h"


using namespace std;


int main()
{	
    List menu;
	Record record;
	while (1) {
		menu.printMenu();
		cin >> menu.input;
		switch (menu.input) {
		case 1:
			menu.listing();
			break;
		case 2:
			record.id = record.trackId();
			record.insertRecord();
			break;
		case 3:
			cout << "input id: ";
			cin >> record.id;
			record.removeRecord(record.id);
			menu.fixIds();
			break;
		case 4:
			exit(0);
			break;
		default:
			cout << "Wrong number. Try again.\nInsert number: ";
		}
	}
    return 0;
}


