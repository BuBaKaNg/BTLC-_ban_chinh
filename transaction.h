#ifndef _TRANSACTION_
#define _TRANSACTION_
#include <string>
#include <fstream>

//TRANSACTION ============================================================
class Transaction{
    private:
    //THUỘC TÍNH
    std::string transactionId;
    std::string userId;
    std::string message;
    public:
    //CONSTRUCTOR ============================================================
    Transaction();
    Transaction(std::string id, std::string userId, std::string message);
    //________________________________________________________________
    
	//GETTER, SETTER ========================================================
    std::string getTransactionId();
    std::string getUserId();
    std::string getMessage();
    void setTransactionId(std::string _id);
    void setUserId(std::string _userId);
    void setMessage(std::string _message);
    //________________________________________________________________


    //ĐỌC FILE =================================================
    void readFromFile(std::ifstream& ifs);
    //________________________________________________________________


    //GHI FILE =================================================
    void writeToFile(std::ofstream& ofs);
    //________________________________________________________________
    
    //PRINT ======
    void print();
    //______
};

#endif