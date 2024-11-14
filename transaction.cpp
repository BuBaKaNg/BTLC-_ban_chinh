#include "transaction.h"

#include <iostream>

using namespace std;

//CONSTRUCTOR ==========
Transaction::Transaction(){}
Transaction::Transaction(std::string id, std::string userId, std::string message) : transactionId(id), userId(userId), message(message){};
//__________

//GETTER SETTER =======
std::string Transaction::getTransactionId(){return transactionId;};
std::string Transaction::getUserId(){return userId;};
std::string Transaction::getMessage(){return message;};
void Transaction::setTransactionId(std::string _id){transactionId = _id;};
void Transaction::setUserId(std::string _userId){userId = _userId;};
void Transaction::setMessage(std::string _message){message = _message;};
//__________


//ĐỌC FILE =========
void Transaction::readFromFile(std::ifstream& ifs){
    std::string line;
    std::getline(ifs, line);
    Transaction::setUserId(line);
    std::getline(ifs, line);
    Transaction::setTransactionId(line);
    std::getline(ifs, line);
    Transaction::setMessage(line);
}
//__________


//GHI FILE =========
void Transaction::writeToFile(std::ofstream& ofs){
    ofs << Transaction::getUserId() << "\n";
    ofs << Transaction::getTransactionId() << "\n";
    ofs << Transaction::getMessage() << "\n";
}
//__________

//PRINT ======
void Transaction::print(){
	cout << "____________________________________________________________________________________________________" << endl;
	cout << "USER ID" << " : " << getUserId() << endl;
	cout << "TRANSACTION ID" << " : " << getTransactionId() << endl;
	cout << "MESSAGE" << " : " << getMessage() << endl;
}
//______


