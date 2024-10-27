#include "user_with_wallet.h"
#include <iostream>


//CONSTRUCTOR ======
UserWithWallet::UserWithWallet(){}
UserWithWallet::UserWithWallet(string userId, string account, string password,string name, string phoneNumber, string email, string walletId, int balance) :
	User(userId, account, password, name, phoneNumber, email), walletId(walletId), balance(balance){}
//______

//GETTER, SETTER ========
string UserWithWallet::getWalletId(){return walletId;}
void UserWithWallet::setWalletId(string _walletId){walletId = _walletId;}
int UserWithWallet::getBalance(){return balance;}
void UserWithWallet::setBalance(int _balance){balance = _balance;}
//________________

 //ĐỌC FILE =================================================
void UserWithWallet::readFromFile(ifstream& ifs){
        string line;
        getline(ifs, line);
        setUserId(line);
        getline(ifs, line);
        setAccount(line);
        getline(ifs, line);
        setPassword(line);
        getline(ifs, line);
        setName(line);
        getline(ifs, line);
        setEmail(line);
        getline(ifs, line);
        setPhoneNumber(line);
        getline(ifs, line);
        setWalletId(line);
        int balance;	
        ifs >> balance;
        ifs.ignore();
        setBalance(balance);
}
//________________________________________________________________


 //GHI FILE ================
void UserWithWallet::writeToFile(ofstream& ofs){
    ofs << getUserId();
    ofs << '\n' << getAccount();
    ofs << '\n' << getPassword();
    ofs << '\n' << getName();
    ofs << '\n' << getEmail();
    ofs << '\n' << getPhoneNumber();
    ofs << '\n' << getWalletId();
    ofs << '\n' << to_string(getBalance());
    ofs << '\n';
}
//_________________


//PRINT ==========
void UserWithWallet::print(){
       User::print();
	   cout << " " +  getWalletId() + " " + to_string(getBalance());
    }
//___________

//OVERRIDE SHOW INFOR
void UserWithWallet::showInfor(){
    User::showInfor();
    cout << "Wallet ID: " << getWalletId() << endl;
    cout << "Balance: " << getBalance() << endl;
}
//______


//TRADE ======
void UserWithWallet::trade(vector<UserWithWallet> &users){
	        cout << "________________________________________________" << endl;
        string walletId;
        int amount;
        cout << "Enter wallet ID you want to trade: ";
        cin >> walletId;
        cin.ignore();
        cout << "Enter amount to trade: ";
        cin >> amount;
        cin.ignore();
        for(UserWithWallet &user : users){
            if(user.getWalletId() == walletId){
                if(user.getBalance() >= amount){
                    setBalance(user.getBalance() - amount);
                    user.setBalance(user.getBalance() + amount);                    
                }
                else{
                    cout << "Balance not enough" << endl;
                }
                return;
            }
        }
        cout << "Wallet ID not found" << endl;
}
//_______