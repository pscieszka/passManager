#include <openssl/evp.h>
#include <openssl/sha.h>
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <random>
#include <sstream>
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

    std::string password::hash_password(std::string password, std::string salt)
    {
        const int hash_length = 32;
        unsigned char hash[hash_length];
        const char* salted_password = (password + salt).c_str();
        EVP_MD_CTX* context = EVP_MD_CTX_new();
        EVP_DigestInit_ex(context, EVP_sha256(), NULL);
        EVP_DigestUpdate(context, salted_password, strlen(salted_password));
        EVP_DigestUpdate(context, salted_password, strlen(salted_password));
        EVP_DigestFinal_ex(context, hash, NULL);
        EVP_MD_CTX_free(context);

        std::stringstream ss;
        for (int i = 0; i < hash_length; ++i)
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);

       return ss.str();
    }

