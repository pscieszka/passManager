class Record
{
private:
    std::string password;
    std::string url;
    std::string login;
 
public:
    
    int id;
    int trackId();
    void insertRecord();
    void removeRecord(int id);
    

};

