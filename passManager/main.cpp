#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "list.h"
#include "record.h"
#include "key.h"
#include "password.h"
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>


using namespace std;


int main()
{
	cout << "\t\tGenerate private key before adding accounts. It will be required to decrypt passwords.\n\n";
		key key;
	    string test;
		string test2,sum2;
		string line;
		string sum ="";
		string decryptedData;
		RSA* rsa=NULL;
		RSA* rsa2;
		std::string encryptedData;
		List menu;
		Record record;
		bool acces;
		fstream file;
		
	while (1) {
		menu.printMenu();
		cin >> menu.input;
		switch (menu.input) {

		case 1:
			menu.listSize = record.trackId();
			menu.listing(menu.listSize);
			break;
		case 2: 
			acces = key.isKeyInserted();
			if (acces) {
				record.id = record.trackId();
				record.insertRecord();
				cout << "Pasword:\n";
				cin >> test;
				//test2 = key.encodeRSA(test, rsa);
				
				//file.open("pass.txt", std::ios::app);
				//file << test2;
				//file.close();
				break;
			}
			else cout << "Please insert key\n";

		
			break;
		case 3:
			acces = key.isKeyInserted();
			if (acces) {
				cout << "input id: ";
				cin >> record.id;
				record.removeRecord(record.id);
				menu.fixIds();
				break;
			}
			else cout << "Please insert key\n";

			break;
		case 4:

			rsa = key.generateRSAKey();
			rsa2 = rsa;
			key.insertKey(rsa);
			key.insertKeyToFile(rsa);
			//cout << "Give pass";
			//cin >> test;
			//encryptedData = key.encryptData(test, rsa);

			//decryptedData = key.decryptData(encryptedData, rsa);
			
			
			break;
		case 5: // read from file test
			cout << "path:";
			cin >> key.filePath;
			rsa = key.loadKeyFromFile(key.filePath);
			key.insertKey(rsa);
			break;
		case 6:
			key.deleteKeyFile();
			exit(0);
			break;
		case 7:
			rsa = key.generateRSAKey();
			if (!rsa) {
				std::cerr << "Cannot generate RSA key\n";
				return -1;
			}

			
			std::string message = "dupa";
			std::string encryptedMessage = key.encryptRSA(message, rsa);

			
			key.saveEncryptedMessageToFile("encrypted_message.dat", encryptedMessage);

			
			std::string loadedEncryptedMessage = key.loadEncryptedMessageFromFile("encrypted_message.dat");

			
			std::string decryptedMessage = key.decryptRSA(loadedEncryptedMessage, rsa);

			
			std::cout << "Original message: " << message << std::endl;
			std::cout << "Encrypted message: " << encryptedMessage << std::endl;
			std::cout << "Loaded encrypted message: " << loadedEncryptedMessage << std::endl;
			std::cout << "Decrypted message: " << decryptedMessage << std::endl;
			break;
		//default:
			//cout << "Wrong number. Try again.\nInsert number: ";
			//break;
		}
	}
    return 0;
}


