#include <openssl/rsa.h>
#include <openssl/pem.h>
class password {
public:
    std::string generate_salt(int length);
    std::string hash_password(std::string password, std::string salt);
    std::string hash_rsa(RSA* rsa, std::string salt);

};

