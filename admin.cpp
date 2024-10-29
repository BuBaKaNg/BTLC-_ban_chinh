#include "admin.h"
#include "user.h"
#include <iostream>
#include "global_functions.h"
#include <functional>
#include "user_with_wallet.h"

//CONSTRUCTOR ============
Admin::Admin(){}
Admin::Admin(string id, string account, size_t password, string name, string email, string phoneNumber) :
    User(id, account, password, name, email, phoneNumber){}
//______     


//ĐỌC FILE ============
void Admin::readFromFile(ifstream& ifs){
    string line;
    getline(ifs, line);
    setUserId(line);
    getline(ifs, line);
    setAccount(line);
    size_t password;
    ifs >> password;
	setPassword(password);
	ifs.ignore();
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
        cout << "Account: " << user.getAccount() << endl;
        cout << "Name : " << toUpperAndTrimSpaces(user.getName()) << endl;
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
    cout << "USER DOES NOT EXIST!!!" << endl;
}
//______





//CREATE ACCOUNT ======
void Admin::createAccount(vector<UserWithWallet> &users){
		cout << "==== CREATE ACCOUNT ======" << endl;
	    string account, name, password, email, phoneNumber;
	    int amount;
	    cout << "NOTE: account not include special digit , can include '_' and '.'" << endl;
	    cout << "Please enter your account: " << endl;
		getline(cin, account);
		if(account.length() == 0){
			cout << "Create an account is failed, your account is empty!!" << endl;
			return;
		}
		for(int i = 0; i < account.length(); i++){
			if(!isalnum(account[i]) && !isalpha(account[i]) && account[i] != '_' && account[i] != '.' && account.length() > 256){
				cout << "Create an account is failed, your account is not valid!!" << endl;
				return;
			}
		}
		if(isAvailableUser(users, account)){
			cout << "Create an account is failed, your account is available" << endl;
			return;
		}
		password = generatePassword(8);
		cout << "Please enter your name: " << endl;
		getline(cin, name);
		if(name.length() > 256){
			cout << "Create an account is failed, your name is so long" << endl;
			return;
		}
		if(name.length() < 8){
			cout << "Create an account is failed, your name is so short" << endl;
			return;
		}
		cout << "Please enter your email: " << endl;
		getline(cin, email);
		if(!isValidEmail(email)){
			cout << "Create an account is failed, your email is not valid" << endl;
			return;
		}
		cout << "Please enter your phone number: " << endl;
		getline(cin, phoneNumber);
		if(phoneNumber.length() != 10){
			cout << "Create an account is failed, your phone number is not valid" << endl;
			return;
		}
		cout << "Please enter number of point user want to redeem: " << endl;
		cin >> amount;
		if(amount >= remainPoint){
			cout << "Create an account is failed, point of total wallet is not enough" << endl;
			return;
		}
		remainPoint -= amount;
		cin.ignore();
	    string userId = generateUserId();
	    string walletId = generateWalletId();
	    hash<string> hashString;
	    UserWithWallet user(userId, account,hashString(password), name, email, phoneNumber, walletId, amount);
	    users.push_back(user);
	    cout << "Account of user is: " << account << endl;
		cout << "Password of user is: " << password << endl;
	    cout << "CREATE SUCCESS !!" << endl;
		return;   
}
//______

void Admin::print(){
	User::print();
}