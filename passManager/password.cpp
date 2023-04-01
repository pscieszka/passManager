#include <openssl/evp.h>
#include <openssl/sha.h>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <random>
#include <sstream>
#include <fstream>
#include "password.h"


    std::string password::generate_salt(int length)
    {
        std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> dist(0, chars.size() - 1);
        std::string salt;
        for (int i = 0; i < length; ++i)
            salt += chars[dist(generator)];
        return salt;
    }

    void password::hash_rsa(RSA* rsa, const std::string& salt)
    {
        const int hash_length = 32;
        unsigned char hash[hash_length];

        BIO* bio = BIO_new(BIO_s_mem());
        PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
        char* key_buffer;
        long key_length = BIO_get_mem_data(bio, &key_buffer);

        std::string salted_key(key_buffer, key_length);
        salted_key += salt;

        EVP_MD_CTX* context = EVP_MD_CTX_new();
        EVP_DigestInit_ex(context, EVP_sha256(), NULL);
        EVP_DigestUpdate(context, salted_key.c_str(), salted_key.length());
        EVP_DigestFinal_ex(context, hash, NULL);
        EVP_MD_CTX_free(context);

        std::ofstream outfile("sha.dat", std::ios::out | std::ios::binary);
        outfile.write(reinterpret_cast<const char*>(&hash_length), sizeof(hash_length));
        outfile.write(salted_key.c_str(), salted_key.length());
        outfile.write(reinterpret_cast<const char*>(hash), hash_length);
        outfile.close();
    }

    bool password::verify_rsa(RSA* rsa, const std::string& filename)
    {
        const int hash_length = 32;
        unsigned char hash[hash_length];

        BIO* bio = BIO_new(BIO_s_mem());
        PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
        char* key_buffer;
        long key_length = BIO_get_mem_data(bio, &key_buffer);

        EVP_MD_CTX* context = EVP_MD_CTX_new();
        EVP_DigestInit_ex(context, EVP_sha256(), NULL);
        EVP_DigestUpdate(context, key_buffer, key_length);
        EVP_MD_CTX_free(context);

        std::ifstream infile(filename, std::ios::binary);
        if (!infile) {
            return false;
        }
        int stored_hash_length;
        infile.read(reinterpret_cast<char*>(&stored_hash_length), sizeof(stored_hash_length));
        if (stored_hash_length != hash_length) {
            return false;
        }
        std::string stored_data(key_length + 32, '\0');
        infile.read(&stored_data[0], stored_data.size());
        infile.close();

        context = EVP_MD_CTX_new();
        EVP_DigestInit_ex(context, EVP_sha256(), NULL);
        EVP_DigestUpdate(context, stored_data.c_str(), key_length + 32);
        EVP_DigestFinal_ex(context, hash, NULL);
        EVP_MD_CTX_free(context);

        if (memcmp(key_buffer, stored_data.c_str(), key_length) != 0 ||
            memcmp(hash, stored_data.c_str() + key_length, hash_length) != 0) {
            return false;
        }

        return true;
    }


    void password::clearSha(const std::string& filename) {
        std::ofstream outfile(filename, std::ios::out | std::ios::trunc);
        outfile.close();
    }




   
