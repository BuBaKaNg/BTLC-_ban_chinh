/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include <iostream>
#include "global_functions.h"
#include "admin.h"
#include "user_with_wallet.h"
#include "view.h"
#include "user.h"

using namespace std;
//Biến này dùng để sinh giá trị hash
hash<string> hashString;
//____


void refresh(vector<UserWithWallet> users, vector<Transaction> transactions){
	saveUserWithWallet(users);
	saveTransaction(transactions);
	saveConfig();
}

//ĐĂNG NhẬP
string logging(vector<UserWithWallet> &users, vector<Admin> &admins){
	cout << "====== LOGGING ========" << endl;
	cout << "Please enter your account: " << endl;
	string account;
	getline(cin, account);
	cout << "Please enter your password: " << endl;
	string password; 
	getline(cin, password);
	for(Admin admin : admins){
		if(admin.getPassword() == hashString(password) && admin.getAccount() == account){
			return admin.getUserId();
		}
	}
	for(UserWithWallet user : users){
		if(user.getPassword() == hashString(password) && user.getAccount() == account){
			return user.getUserId();
		}
	}
	return "fail";
}


//ĐĂNG KÝ
int signUp(vector<UserWithWallet> &users){
	int control;
	while(1){
		string account, password, name, email, phoneNumber;
		cout << "======= SIGN UP ==========" << endl;	
		cout << "Please enter your account: " << endl;
		getline(cin, account);
		cout << "Please enter your password: " << endl;
		getline(cin, password);
		cout << "Please enter your name: " << endl;
		getline(cin, name);
		cout << "Please enter your email: " << endl;
		getline(cin, email);
		cout << "Please enter your phone number: " << endl;
		getline(cin, phoneNumber);
		UserWithWallet user(generateUserId(), account, hashString(password), name, email, phoneNumber, generateWalletId(), 0);
		users.push_back(user);
		return 1;
	}
	return 0;
}

//HOẠT ĐỘNG
void operate(string userId, vector<UserWithWallet> &users, vector<Admin> &admins, vector<Transaction> &transactions){
	while(1){	
		if(userId.substr(0,4) != "USER"){
			Admin admin;
			for(Admin ad : admins){
				if(ad.getUserId() == userId){
					admin = ad;
					break;
				}
			}
			cout << "========= ADMIN ==========" << endl;
			cout << "1. Show list user" << endl;
			cout << "2. Create an account" << endl;
			cout << "3. Update information of user" << endl;
			cout << "4. Show your information" << endl;
			cout << "5. Update your information" << endl;
			cout << "0. Exit" << endl;
			int choose; cin >> choose;
			cin.ignore();
			if(choose == 1){
				admin.showList(users);
			}
			else if(choose == 2){
				admin.createAccount(users);
				refresh(users, transactions);
			}
			else if(choose == 3){
				cout << "Please enter your user id need to update: " << endl;
				string userId_update; getline(cin, userId_update);
				admin.updateInforOfUser(users, userId_update);
				refresh(users, transactions);
			}
			else if(choose == 4){
				admin.showInfor();
			}
			else if(choose == 5){
				admin.updateInfor();
				ofstream ofs("data\\db_admin.txt", std::ios::trunc);
				admin.writeToFile(ofs);
				ofs.close();
				refresh(users, transactions);
			}
			else if(choose == 0){
				return;
			}
		}
		else{
			UserWithWallet user;
			for(UserWithWallet us : users){
				if(us.getUserId() == userId){
					user = us;
					break;
				}
			}
			cout << "========== USER ==========" << endl;
			cout << "1. Show your information" << endl;
			cout << "2. Update your information" << endl;
			cout << "3. Trade" << endl;
			cout << "4. Show history of trade" << endl;
			cout << "0. Exit" << endl;
			int choose; cin >> choose;
			if(choose == 1){
				user.showInfor();
			}
			else if(choose == 2){
				user.updateInfor();
				refresh(users, transactions);
			}
			else if(choose == 3){
				user.trade(users, transactions);
				refresh(users, transactions);
			}
			else if(choose == 4){
				user.showTransactions(transactions, user.getUserId());
			}
			else if(choose == 0){
				return;
			}
		}
	}
}
//____

int main(int argc, char** argv) {
//LOAD TỪ DATA BASE ====
	vector<UserWithWallet> users = loadUserWithWallet();
	vector<Admin> admins = loadAdmin();
	vector<Transaction> transactions = loadTransaction();
	loadConfig(); 
	while(1){
		startScreen();
		string userId = "fail";
		int option; cin >> option; cin.ignore();
		if(option == 1){
			userId = logging(users, admins);
		}
		else if(option == 2){
			int success;
			success = signUp(users);
			if(success == 1){
				refresh(users, transactions);
				userId = logging(users, admins);
			}
		}
		else if(option == 3){
			system("CLS");
		}
		else if(option == 0){
			refresh(users, transactions);
			cout << "***********************************" << endl;
			cout << "==== THANK FOR USE THE PROGRAM ====" << endl;
			return 0;	
		}
		if(userId == "fail"){
			continue;
		}
		operate(userId, users, admins, transactions);
		refresh(users, transactions);
	}
return 0;
}

