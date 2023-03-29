#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <sstream>
#include <fstream>
#include "key.h"
#include <bitset>
#include <iomanip>

std::string key::encodeRSA(std::string message, RSA* rsa) {
    int keySize = RSA_size(rsa);
    int blockLength = keySize - 11; 
    int messageLength = message.length();
    int numBlocks = messageLength / blockLength + (messageLength % blockLength ? 1 : 0);
    std::string encodedMessage;
    encodedMessage.reserve(numBlocks * keySize);
    for (int i = 0; i < numBlocks; i++) {
        std::string block = message.substr(i * blockLength, blockLength);
        unsigned char* encryptedBlock = new unsigned char[keySize];
        int result = RSA_public_encrypt(block.length(), (const unsigned char*)block.c_str(), encryptedBlock, rsa, RSA_PKCS1_PADDING);
        if (result != -1) {
            encodedMessage.append((char*)encryptedBlock, keySize);
        }
        delete[] encryptedBlock;
    }
    
    return encodedMessage;
}


std::string key::decodeRSA(std::string encoded, RSA* rsa) {
    int keySize = RSA_size(rsa);
    int blockLength = keySize;
    int encodedLength = encoded.length();
    int numBlocks = encodedLength / blockLength;
    std::string decodedMessage;
    decodedMessage.reserve(numBlocks * (keySize - 11));
    for (int i = 0; i < numBlocks; i++) {
        std::string block = encoded.substr(i * blockLength, blockLength);
        unsigned char* decryptedBlock = new unsigned char[keySize];
        int result = RSA_private_decrypt(block.length(), (const unsigned char*)block.c_str(), decryptedBlock, rsa, RSA_PKCS1_PADDING);
        if (result != -1) {
            decodedMessage.append((char*)decryptedBlock, result);
        }
        delete[] decryptedBlock;
    }
    return decodedMessage;
}



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
    key::accessKey =  key;
}
bool key::isKeyInserted() {
    if (key::accessKey == NULL)
        return false;
    else return true;
    
}

