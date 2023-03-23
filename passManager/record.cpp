#include <iostream>
#include "record.h"
#include <fstream>
#include <string>
using namespace std;

void Record::insertRecord() {
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

void Record::removeRecord(int id) {
    ifstream inputFile("data.txt");
    ofstream outputFile("temp.txt");
    string line;

    bool removed = false;
 
    while (getline(inputFile,line)) {
        if (line == to_string(id)) {
            removed = true;
            for (int i = 0; i < 4; i++) {
                if (!getline(inputFile, line)) {
                    break;
                }
            } 
        }
        if (outputFile.tellp() != 0 || line != "")
            outputFile <<line <<endl;
    }
    inputFile.close();
    outputFile.close();
    if (!removed) {
        cout << "ID not found." << endl;
        remove("temp.txt");
    }
    else {
        remove("data.txt");
        rename("temp.txt", "data.txt");
        

    }
}