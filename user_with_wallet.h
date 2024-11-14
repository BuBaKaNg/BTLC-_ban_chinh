#ifndef _USER_WITH_WALLET_
#define _USER_WITH_WALLET_
#include "user.h"
#include "transaction.h"
#include <vector>
#include <fstream>


using namespace std;
class UserWithWallet : public User{
	private:
    //THUỘC TÍNH ========
    string walletId;
    int balance;
    //__________________
    public:
    //CONSTRUCTOR ======
    UserWithWallet();
    UserWithWallet(string userId, string account, size_t password,string name, string email, string phoneNumber, string walletId, int balance);
    //______
    
    
    //GETTER, SETTER ========
    string getWalletId();
    void setWalletId(string _walletId);
    int getBalance();
    void setBalance(int _balance);
    //________________
    
    //ĐỌC FILE =============
    void readFromFile(ifstream& ifs);
    //_______________
    
    
     //GHI FILE ==========
    void writeToFile(ofstream& ofs);
    //_______________
    
    // PRINT ======
    void print();
    //_______
    
    //OVERRIDE SHOW INFOR
    void showInfor();
    //______
    
    //TRADE ======
    void trade(vector<UserWithWallet> &users, vector<Transaction> &transactions);
	//_______
	
	// SHOW TRANSACTIONS ======
	void showTransactions(vector<Transaction> &transactions, string userId);
	//______

};

#endif