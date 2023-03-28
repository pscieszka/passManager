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
			/*rsa key  -> sha256, i potem hasla - > rsa i pozniej otwierasz sha256 sprawdza key i jak jest git
			to jest git
			rsa cout -> string, string-> sha256?
			*/
			bool acces = key.isKeyInserted();
			if (acces) {
				record.id = record.trackId();
				record.insertRecord();
				break;
			}
			else cout << "nie dla psa\n";

		
			break;
		case 3:
			bool acces = key.isKeyInserted();
			if (acces) {
				cout << "input id: ";
				cin >> record.id;
				record.removeRecord(record.id);
				menu.fixIds();
				break;
			}
			else cout << "nie dla psa\n";

			break;
		case 4:

			rsa = key.generateRSAKey();
			key.insertKeyToFile(rsa);

			//cout << "Give pass";
			//cin >> test;
			//encryptedData = key.encryptData(test, rsa);

			//decryptedData = key.decryptData(encryptedData, rsa);
			
			RSA_free(rsa);
			break;
		case 5:
			key.deleteKeyFile();
			exit(0);
			break;
		case 6: // read from file test
			cout << "path:";
			cin >> key.filePath;
			rsa = key.loadKeyFromFile(key.filePath);
			key.insertKey(rsa);
			break;

		default:
			cout << "Wrong number. Try again.\nInsert number: ";
			break;
		}
	}
    return 0;
}


