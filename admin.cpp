#include "admin.h"
#include "user.h"
#include <iostream>
#include "global_functions.h"

//CONSTRUCTOR ============
Admin::Admin(){}
Admin::Admin(string id, string account, string password, string name, string email, string phoneNumber) :
    User(id, account, password, name, email, phoneNumber){}
//______     


//ĐỌC FILE ============
void Admin::readFromFile(ifstream& ifs){
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
}
//_______________


//GHI FILE ============
void Admin::writeToFile(ofstream& ofs){
    ofs << getUserId() << "\n";
    ofs << getAccount() << "\n";
    ofs << getPassword() << "\n";
    ofs << getName() << "\n";
    ofs << getEmail() << "\n";
    ofs << getPhoneNumber() << "\n";
}
//_______


//SHOW LIST ==========
void Admin::showList(vector<UserWithWallet> &users){
    cout << "====================== LIST USERS ======================" << endl;
    cout << endl;
    for(UserWithWallet& user : users){
        cout << "*****************************************" << endl;
        cout << "User id : " << user.getUserId() << endl;
        cout << "Name : " << user.getName() << endl;
        cout << "Email : " << user.getEmail() << endl;
        cout << "Phone number : " << user.getPhoneNumber() << endl; 
        cout << "Wallet id : " << user.getWalletId() << endl;
        cout << "Balance : " << user.getBalance() << endl;
        cout << "******************************************" << endl;
        cout << endl;
    }
}
//_________


//SINH WALLET ID ======
string Admin::generateWalletId(){
    // Hàm này sinh ra wallet id mới
    maxWalletId++;
    string walletId = to_string(maxWalletId);
    while(walletId.length() < 9){
        walletId = "0" + walletId;
    }

    return "WALLET" + walletId;
}
//______


//SINH USER ID
string Admin::generateUserId(){
    // Hàm này sinh ra user id mới
    maxUserId++;
    string userId = to_string(maxUserId);
    while(userId.length() < 9){
        userId = "0" + userId;
    }

    return "USER" + userId;
}
//______



//UPDATE INFOR ======
void Admin::updateInforOfUser(vector<UserWithWallet> &users, string userId){
    for(auto &user : users){
        if(user.getUserId() == userId){
            user.updateInfor();
            return;
        }
    }
}
//______





//CREATE ACCOUNT ======
void Admin::createAccount(vector<UserWithWallet> &users, string account, string name, string password, string email, string phoneNumber, int amount){
    string userId = generateUserId();
    string walletId = generateWalletId();
    UserWithWallet user(userId, account, name, password, email, phoneNumber, walletId, amount);
    users.push_back(user);
    
}
//______

void Admin::print(){
	User::print();
}