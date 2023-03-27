#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <sstream>
#include <fstream>
#include "key.h"


RSA* key::generateRSAKey() {
    RSA* rsa = RSA_new();
    BIGNUM* bn = BN_new();

    BN_set_word(bn, RSA_F4);

    if (RSA_generate_key_ex(rsa, 2048, bn, nullptr) != 1) {
        
        RSA_free(rsa);
        BN_free(bn);
        return nullptr;
    }

    BN_free(bn);
    return rsa;
}

std::string key::encryptData(const std::string& data, RSA* publicKey) {
    
    int keyLength = RSA_size(publicKey);
    char* encrypted = new char[keyLength];
    memset(encrypted, 0, keyLength);

    
    int result = RSA_public_encrypt(data.length(), reinterpret_cast<const unsigned char*>(data.c_str()), reinterpret_cast<unsigned char*>(encrypted), publicKey, RSA_PKCS1_PADDING);
    if (result == -1) {
        
        RSA_free(publicKey);
        delete[] encrypted;
        return "";
    }

    
    std::string encryptedData(encrypted, result);

    delete[] encrypted;

    
    return encryptedData;
}

std::string key::decryptData(const std::string& encryptedData, RSA* privateKey) {
    
    int keyLength = RSA_size(privateKey);
    char* decrypted = new char[keyLength];
    memset(decrypted, 0, keyLength);

    
    int result = RSA_private_decrypt(encryptedData.length(), reinterpret_cast<const unsigned char*>(encryptedData.c_str()), reinterpret_cast<unsigned char*>(decrypted), privateKey, RSA_PKCS1_PADDING);
    if (result == -1) {
        
        RSA_free(privateKey);
        delete[] decrypted;
        return "";
    }

    
    std::string decryptedData(decrypted, result);

   
    delete[] decrypted;

    
    return decryptedData;
}



void key::insertKeyToFile(RSA* key) {
    FILE* file;
    fopen_s(&file,"yourkey.PEM", "w");
    PEM_write_RSAPrivateKey(file, key, NULL, NULL, 0, NULL, NULL);
    fclose(file);

    std::cout << "RSA key saved to file: " << "yourkey.PEM" << "\nThe key has been set as default, but it will be deleted when you exit the program.\nIf you want to access data saved during this session, save your key in a directory separate from the program.\n";
}

RSA* key::loadKeyFromFile(std::string filePath) {
    static char filePathChar[64];
    strncpy_s(filePathChar, sizeof(filePathChar), filePath.c_str(), _TRUNCATE);
    const char* filePathPtr = filePathChar;
    FILE* file;
    fopen_s(&file, filePathPtr, "r");

    if (!file) {
        std::cerr << "Cannot open key file from: " << filePath << "\n";
        return nullptr;
    }

    RSA* rsaKey = PEM_read_RSAPrivateKey(file, NULL, NULL, NULL);
    if (!rsaKey) {
        std::cerr << "Cannot read key from file: " << filePath << "\n";
        fclose(file);
        return nullptr;
    }

    fclose(file);

    std::cout << "RSA key read from file: " << filePath << "\n";

    return rsaKey;
}

void key::deleteKeyFile() {
    int result = remove("yourkey.PEM");
    if (!result) 
        std::cout << "key file deleted successfully.\n";
    
    else
        std::cout << "Error deleting key file.\n";
    
}
void key::insertKey(RSA* key) {
    key = key::accesKey;
}