class password {
public:
    std::string generate_salt(int length);
    std::string hash_password(std::string password, std::string salt);

};

