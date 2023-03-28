#include <openssl/rsa.h>
#include <openssl/pem.h>
class key
{
private:
	RSA* accesKey=NULL; // user key to decrypt/encrypt
public:

	std::string filePath; // path to file with key

	RSA* generateRSAKey(); //generate RSA key

	RSA* loadKeyFromFile(std::string filePath); // returns RSA* type variable extracted from .PEM file

	std::string encryptData(const std::string& data, RSA* publicKey); //encrypt

	std::string decryptData(const std::string& encryptedData, RSA* privateKey); //decrypt

	void insertKeyToFile(RSA* key); //saving key to file after generating

	void insertKey(RSA* key); //input for private variable RSA* accesKey

	void deleteKeyFile(); // deleting key file before closing program
	
	bool isKeyInserted();

	std::string rsaToString(RSA* key);
};

