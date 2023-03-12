class Record
{
private:
    std::string password;
 
public:
    std::string url;
    std::string login;

    int id;
    int trackId();
    void insertRecord();
    void removeRecord(int id);
    

};

