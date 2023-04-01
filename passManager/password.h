#include <openssl/rsa.h>
#include <openssl/pem.h>
class password {
public:
    std::string generate_salt(int length);
    void hash_rsa(RSA* rsa, const std::string& salt);
    bool verify_rsa(RSA* rsa, const std::string& filename);
    void clearSha(const std::string& filename);
};

