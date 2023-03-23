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
    /*for (int i = 1; i < listSize * 4;i += 4) {
        getline(file, text);
        cout << text << "\t\t\t";
        getline(file, text);
        getline(file, text);
        getline(file, text);
    }
    cout << "\n";
    file.close();
    file.open("data.txt");
    for (int i = 1; i < listSize * 4;i += 4) {
        getline(file, text);
        getline(file, text);
        cout << text << "\t\t\t";
        getline(file, text);
        getline(file, text);
    }
    file.close();
    file.open("data.txt");
    cout << "\n";
    for (int i = 1; i < listSize * 4;i += 4) {
        getline(file, text);
        getline(file, text);
        getline(file, text);
        cout << text << "\t\t\t";
        getline(file, text);
    }
    file.close();
    file.open("data.txt");
    cout << "\n";
    for (int i = 1; i < listSize * 4;i += 4) {
        getline(file, text);
        getline(file, text);
        getline(file, text);
        getline(file, text);
        cout << text << "\t\t\t";
    }
    file.close();
    file.open("data.txt");
    cout << "\n";
 
    cout << "\n\n";
    file.close();*/
    std::vector<std::string> lines;
    for (int i = 0; i < 4; i++) {
        file.clear();
        file.seekg(0, std::ios::beg);
        for (int j = 1; j <= listSize; j++) {
            for (int k = 0; k < 4; k++) {
                getline(file, text);
                if (k == i) {
                    lines.push_back(text);
                }
            }
        }
        for (int j = 0; j < lines.size(); j++) {
            std::cout << lines[j] << "\t\t\t";
        }
        std::cout << std::endl;
        lines.clear();
    }
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
