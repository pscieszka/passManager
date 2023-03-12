#include <iostream>
#include "list.h"
#include "record.h"


using namespace std;

int main()
{
    List menu;
	Record record;
    menu.printMenu();
	cin >> menu.input;
	switch (menu.input) {
	case 1:
		menu.listing();
		break;
	case 2:
		record.id = record.trackId();
		record.insert();
		break;
	case 3:
		exit(0);
		break;
	default:
		cout << "Wrong number. Try again.\nInsert number: ";
	}
    return 0;
}


