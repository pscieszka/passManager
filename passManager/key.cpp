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

std::string key::encryptRSA(std::string message, RSA* key) {
    std::string result;
    int keySize = RSA_size(key);
    char* encrypted = new char[keySize];
    int length = RSA_public_encrypt(message.size() + 1, (unsigned char*)message.c_str(), (unsigned char*)encrypted, key, RSA_PKCS1_OAEP_PADDING);
    if (length != -1) {
        result = std::string(encrypted, length);
    }
    else {
        std::cerr << "Error encrypting message with RSA.\n";
    }
    delete[] encrypted;
    return result;
}


std::string key::decryptRSA(std::string message, RSA* key) {
    std::string result;
    int keySize = RSA_size(key);
    char* decrypted = new char[keySize];
    int length = RSA_private_decrypt(keySize, (unsigned char*)message.c_str(), (unsigned char*)decrypted, key, RSA_PKCS1_OAEP_PADDING);
    if (length != -1) {
        result = std::string(decrypted, length);
    }
    else {
        std::cerr << "Error decrypting message with RSA.\n";
    }
    delete[] decrypted;
    return result;
}

void key::saveEncryptedMessageToFile(std::string fileName, std::string encryptedMessage, int id) {
    std::ofstream outFile(fileName, std::ios::out | std::ios::app | std::ios::binary);
    if (outFile) {
        outFile << "ID NUMBER = " << id << "\n" << encryptedMessage << std::endl;
        outFile << "END OF MESSAGE WITH ID = " << id << "\n\n";
        std::cout << "Encrypted message with ID " << id << " saved to file: " << fileName << std::endl;
    }
    else {
        std::cerr << "Error saving encrypted message with ID " << id << " to file: " << fileName << std::endl;
    }
    outFile.close();
}
std::string key::loadEncryptedMessageFromFile(std::string fileName, int id) {
    std::ifstream inFile(fileName, std::ios::in | std::ios::binary);
    std::string encryptedMessage;
    if (inFile) {
        std::string line;
        int currentId = -1;
        bool found = false;
        while (std::getline(inFile, line)) {
            if (line.find("ID NUMBER = ") != std::string::npos) {
                currentId = std::stoi(line.substr(line.find("=") + 1));
                if (currentId == id) {
                    found = true;
                }
            }
            else {
                if (found && line.find("END OF MESSAGE WITH ID = ") == std::string::npos) {
                    encryptedMessage += line;
                    encryptedMessage += "\n";
                }
            }
        }
        if (found) {
            std::cout << "Encrypted message with ID " << id << " read from file: " << fileName << std::endl;
        }
        else {
            std::cerr << "Could not find encrypted message with ID " << id << " in file: " << fileName << std::endl;
        }
    }
    else {
        std::cerr << "Error loading encrypted message from file: " << fileName << std::endl;
    }
    inFile.close();
    return encryptedMessage;
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

