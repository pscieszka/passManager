#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "list.h"
#include "record.h"
#include "key.h"
#include "password.h"


using namespace std;


int main()
{
	cout << "\t\tGenerate private key before adding accounts. It will be required to decrypt passwords.\n\n";
		key key;
		std:string test;
		std::string decryptedData;
		RSA* rsa;
		std::string encryptedData;
    List menu;
	Record record;
	while (1) {
		menu.printMenu();
		cin >> menu.input;
		switch (menu.input) {

		case 1:
			menu.listSize = record.trackId();
			menu.listing(menu.listSize);
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
		case 5:
			exit(0);
			break;
		case 4:
			
			rsa = key.generateRSAKey();
			key.insertKeyToFile(rsa);

			//cout << "Give pass";
			//cin >> test;
			//encryptedData = key.encryptData(test, rsa);
			//cout << "Zaszyfrowany ci¹g znaków: " << encryptedData << endl;

			//decryptedData = key.decryptData(encryptedData, rsa);
			//cout << "Odszyfrowany ci¹g znaków: " << decryptedData << endl;
			RSA_free(rsa);
			break;
		default:
			cout << "Wrong number. Try again.\nInsert number: ";
			break;
		}
	}
    return 0;
}


