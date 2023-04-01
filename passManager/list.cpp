#include <iostream>
#include "list.h"
#include "record.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void List::listing(int listSize) {
    ifstream file("data.txt");
    string text;
    
    cout << "\n";
    for (int i = 1; i <= listSize*4; i++) {
        if (i % 4 == 1) {
            cout << "\n";
        }
        getline(file, text);
        cout << text<<"\n";
    }
    file.close();
    cout << "\n\n";
}

void List::printMenu() {
	cout << "\t\t\t\t\t\tMenu\n\n";
	cout << "\t\t\t\t\t\t1.List account\n\t\t\t\t\t\t2.Add account\n\t\t\t\t\t\t3.Remove\n\t\t\t\t\t\t4.Generate private key\n\t\t\t\t\t\t5.Read key from file\n\t\t\t\t\t\t6.Show password\n\t\t\t\t\t\t7.exit\n\t\t\t\t\t\tInsert number: ";
}

void List::fixIds() {
    ifstream file("data.txt");
    ofstream fixedFile("temp.txt");
    int i = -1;
    string line;
    
    while (getline(file, line) ) {
        i++;
        if (line == "\n") {
            break;
        }
        else if (i%4==0) {
            fixedFile << i/4 << endl;
        }
        else {
            fixedFile << line << endl;
        }
        
        
    }
    file.close();
    fixedFile.close();

    remove("data.txt");
    rename("temp.txt", "data.txt");
    remove("temp.txt");
}
