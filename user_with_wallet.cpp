#include "user_with_wallet.h"
#include <iostream>
#include "global_functions.h"


//CONSTRUCTOR ======
UserWithWallet::UserWithWallet(){}
UserWithWallet::UserWithWallet(string userId, string account, size_t password,string name, string phoneNumber, string email, string walletId, int balance) :
	User(userId, account, password, name, email, phoneNumber), walletId(walletId), balance(balance){}
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
        size_t password;
        ifs >> password;
        ifs.ignore();
        setPassword(password);
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
void UserWithWallet::trade(vector<UserWithWallet> &users, vector<Transaction> &transactions){
	        cout << "========== TRADE ==========" << endl;
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
            	if(walletId == getWalletId()){
            		cout << "Wallet id is not valid!!" << endl;
            		return;
				}
                if(getBalance() >= amount){
                	if(!checkOTP()){
                		cout << "OTP is wrong !!" << endl;
                		return;
					}
                	for(UserWithWallet &us : users){
                		if(us.getUserId() == getUserId()){
                  			us.setBalance(getBalance() - amount);
                  			break;
						}
					}
                    user.setBalance(user.getBalance() + amount);     
                    string message = getCurrentDateTime() + " " + toUpperAndTrimSpaces(getName()) + " transferred " + to_string(amount) + " to " + toUpperAndTrimSpaces(user.getName());
                    string transactionId = generateTransactionId();
					Transaction transAToB(transactionId, getUserId(), message);
					transactions.push_back(transAToB);
					message = getCurrentDateTime() + " " + toUpperAndTrimSpaces(user.getName()) + " received " + to_string(amount) + " from " + toUpperAndTrimSpaces(getName());
					Transaction transBFromA(transactionId, user.getUserId(), message);
					transactions.push_back(transBFromA);
                }
                else{
                    cout << "Balance not enough" << endl;
                    return;
                }
                cout << "TRADE SUCCESSFULLY!!!" << endl;
                return;
            }
        }
        cout << "Wallet ID not found" << endl;
}
//_______


//SHOW TRANSACTIONS ======
void UserWithWallet::showTransactions(vector<Transaction> &transactions, string userId){
	cout << "========== TRANSACTION HISTORY ==========" << endl;
	for(Transaction trans : transactions){
		if(trans.getUserId() == userId){
			trans.print();
		}
	}
}
//______