#include <iostream>
#include "list.h"
#include "record.h"
#include <fstream>
#include <string>
using namespace std;

void List::listing() {
    ifstream file("data.txt");
    string text;
    
    cout << "\n";
    while (getline(file, text)){
        
        cout << "\t\t\t\t\t\t"<< text <<"\n";
      
    }
    cout << "\n\n";
    file.close();
}

void List::printMenu() {
	cout << "\t\t\t\t\t\tMenu\n\n";
	cout << "\t\t\t\t\t\t1.List account\n\t\t\t\t\t\t2.Add account\n\t\t\t\t\t\t3.Remove\n\t\t\t\t\t\t4.Exit\n\t\t\t\t\t\tInsert number: ";
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
        else if (i%4==0 && i!=0) {
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
