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

    std::cout << "Klucz RSA zapisano do pliku: " << "yourkey.PEM" << std::endl;
}

/*RSA* load_rsa_key_from_file(std::string file_path) {
    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Nie mo¿na otworzyæ pliku do odczytu klucza RSA: " << file_path << std::endl;
        return nullptr;
    }

    RSA* rsa_key = PEM_read_RSAPrivateKey(file, NULL, NULL, NULL);
    if (!rsa_key) {
        std::cerr << "Nie mo¿na odczytaæ klucza RSA z pliku: " << file_path << std::endl;
        file.close();
        return nullptr;
    }

    file.close();

    std::cout << "Klucz RSA odczytano z pliku: " << file_path << std::endl;

    return rsa_key;
}*/