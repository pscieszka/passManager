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
		string password1;
		password hash;
		string path;
		int id;
		string test2,sum2;
		string line;
		string sum ="";
		string decryptedData;
		RSA* rsa=NULL;
		RSA* rsa2;
		std::string encryptedData;
		string loadedEncryptedMessage;
		List menu;
		
		Record record;
		bool acces;
		fstream file;
		string decryptedMessage;
		string salt;
		
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
				cin >> password1;
				string encryptedMessage = key.encryptRSA(password1, rsa);
				key.saveEncryptedMessageToFile("encrypted_message.dat", encryptedMessage, record.id);
				password1 = "";
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
			hash.clearSha("sha.dat");
			rsa = key.generateRSAKey();
			rsa2 = rsa;
			key.insertKey(rsa);
			key.insertKeyToFile(rsa);

			//salt = hash.generate_salt(32);
			//hash.hash_rsa(rsa, salt);

			break;
		case 5:
			cout << "path:";
			cin >> key.filePath;
			rsa = key.loadKeyFromFile(key.filePath);
			key.insertKey(rsa);
			//if (hash.verify_rsa(rsa, "shat.dat"))
				//cout << "\nCorrect key!\n";
			//else {
				//cout << "\nWrong key!\n";
				//rsa = nullptr;
			//}
			break;

		case 6:
			cout << "Insert ID to show:";
			cin >> id;
			loadedEncryptedMessage = key.loadEncryptedMessageFromFile("encrypted_message.dat", id);
			decryptedMessage = key.decryptRSA(loadedEncryptedMessage, rsa);
			cout << "password:" << decryptedMessage << "\n";
			decryptedMessage = "";
			break;
		case 7:
			key.deleteKeyFile();
			exit(0);
			break;
		//case 8:// test case

			//rsa = key.generateRSAKey();
			//if (!rsa) {
			//	std::cerr << "Cannot generate RSA key\n";
			//	return -1;
			//}
			//key.insertKeyToFile(rsa);
			//rsa = nullptr;
			//cin >> path;
			//rsa2 = key.loadKeyFromFile(path);

			//std::string message = "test";
			//std::string encryptedMessage = key.encryptRSA(message, rsa2);

			//key.saveEncryptedMessageToFile("encrypted_message.dat", encryptedMessage);

			//std::string loadedEncryptedMessage = key.loadEncryptedMessageFromFile("encrypted_message.dat");

			//std::string decryptedMessage = key.decryptRSA(loadedEncryptedMessage, rsa2);

			//cout << "Original message: " << message << endl;
			//cout << "Encrypted message: " << encryptedMessage << endl;
			//cout << "Loaded encrypted message: " << loadedEncryptedMessage << endl;
			//cout << "Decrypted message: " << decryptedMessage << endl;
			//break;
		//default:
			//cout << "Wrong number. Try again.\nInsert number: ";
			//break;
		}
	}
    return 0;
}


