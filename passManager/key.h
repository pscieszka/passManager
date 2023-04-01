#include <openssl/rsa.h>
#include <openssl/pem.h>
class key
{
private:
	RSA* accessKey; // user key to decrypt/encrypt
public:
	key() {
		accessKey = nullptr;
	}

	std::string filePath; // path to file with key

	RSA* generateRSAKey(); //generate RSA key

	RSA* loadKeyFromFile(std::string filePath); // returns RSA* type variable extracted from .PEM file

	std::string encryptRSA(std::string message, RSA* rsa);

	std::string decryptRSA(std::string encoded, RSA* rsa);


	std::string loadEncryptedMessageFromFile(std::string fileName, int id);

	void saveEncryptedMessageToFile(std::string fileName, std::string encryptedMessage,int ID);

	void insertKeyToFile(RSA* key); //saving key to file after generating

	void insertKey(RSA* key); //input for private variable RSA* accesKey

	void deleteKeyFile(); // deleting key file before closing program
	
	bool isKeyInserted();

	


	//std::string rsaToString(RSA* key);
};

