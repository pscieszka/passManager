#include <openssl/rsa.h>
#include <openssl/pem.h>
class key
{
public:
	RSA* generateRSAKey();
	std::string encryptData(const std::string& data, RSA* publicKey);
	std::string decryptData(const std::string& encryptedData, RSA* privateKey);
	
};

