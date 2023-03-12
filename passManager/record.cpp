#include <iostream>
#include "record.h"
#include <fstream>
#include <string>
using namespace std;

void Record::insert() {
    fstream file;
    file.open("data.txt", ios::app);
    cout << "Enter url:" << endl;
    cin >> url;
    cout << "Enter login:" << endl;
    cin >> login;
    cout << "Enter password:" << endl;
    cin >> password;
    file << id << endl << url << endl << login << endl << password << endl; // ignorowanie spacji
    file.close();
}

int Record::trackId() {
    fstream file("data.txt");
    string line;
    int numLines = 0;
    while (getline(file, line))
        ++numLines;
    if (numLines == 0)
        return 0;
    return numLines / 4;
}
