#ifndef _ADMIN_
#define _ADMIN_
#include <string>
#include <vector>
#include "user_with_wallet.h"
#include "user.h"
#include <fstream>

class Admin : public User{
	public:
    //CONSTRUCTOR ======
    Admin();
    Admin(string id, string account, size_t password, string name, string email, string phoneNumber);
    //______
    
    //ĐỌC FILE ===============
    void readFromFile(ifstream& ifs);
    //___________________
    
    
    //GHI FILE ==========
    void writeToFile(ofstream& ofs);
    //______
    
    
    //SHOW LIST USER ======
    void showList(vector<UserWithWallet> &users);
    //_____
    
    
	//UPDATE INFOR OF USER ======
	void updateInforOfUser(vector<UserWithWallet> &users, string userId);
	//_______
	
	//CREATE ACCOUNT ======
	void createAccount(vector<UserWithWallet> &users);
	//______
	
	//PRINT ============
    void print();
    //_______________
    
    //SINH WALLET ID
    string generateWalletId();
    //_______
    
    
    //SINH USER ID =======
    string generateUserId();
    //______


};

#endif