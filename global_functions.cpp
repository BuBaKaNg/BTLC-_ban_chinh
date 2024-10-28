#include "global_functions.h"
int originPoint = 0;
int remainPoint = 0;
int maxWalletId = 0;
int maxUserId = 0;


vector<UserWithWallet> loadUserWithWallet(){
	vector<UserWithWallet> users;
	ifstream ifs("D:\\material\\C++\\NewProject\\BTLC++\\db_user.txt");
	 while (ifs.good()) {
        UserWithWallet user;
        user.readFromFile(ifs);
        
		if(ifs.fail()) break;
        users.push_back(user);
    }
    ifs.close();
    return users;
}


int caculateRemain(vector<UserWithWallet> &users){
	int sum = 0;
	for(UserWithWallet &user : users){
		sum += user.getBalance();
	}
	return originPoint - sum;
}

void saveUserWithWallet(vector<UserWithWallet> &users){
	ofstream ofs("D:\\material\\C++\\NewProject\\BTLC++\\db_user.txt", ios::trunc);
	for(auto user : users){
            user.writeToFile(ofs);
        }
    ofs.close();
}

vector<Admin> loadAdmin(){
	vector<Admin> admins;
	ifstream ifs("D:\\material\\C++\\NewProject\\BTLC++\\db_admin.txt");
	 while (ifs.good()) {
        Admin admin;
        admin.readFromFile(ifs);
        admins.push_back(admin);
    }
    ifs.close();
    return admins;
}


void loadConfig(){
	ifstream ifs("D:\\material\\C++\\NewProject\\BTLC++\\db_config.txt");
	ifs >> originPoint; ifs.ignore();
	ifs >> remainPoint; ifs.ignore();
	ifs >> maxWalletId; ifs.ignore();
	ifs >> maxUserId; ifs.ignore();
	ifs.close();
}

void saveConfig(){
	ofstream ofs("D:\\material\\C++\\NewProject\\BTLC++\\db_config.txt", ios::trunc);
	ofs << originPoint << '\n';
	ofs << remainPoint << '\n';
	ofs << maxWalletId << '\n';
	ofs << maxUserId << '\n';
}

vector<Transaction> loadTransaction(){
	vector<Transaction> transactions;
	ifstream ifs("D:\\material\\C++\\NewProject\\BTLC++\\db_transaction.txt");
	while (ifs.good()) {
        Transaction transaction;
        transaction.readFromFile(ifs);
        
        // Kiểm tra nếu đọc thành công thông tin user
        if (ifs.fail()) {
            break;  // Dừng nếu không còn dữ liệu hợp lệ
        }

        transactions.push_back(transaction);
    }
    ifs.close();
    return transactions;
}

void saveTransaction(vector<Transaction> &transactions){
	ofstream ofs("D:\\material\\C++\\NewProject\\BTLC++\\db_transaction.txt", ios::trunc);
	for(auto &transaction : transactions){
            transaction.writeToFile(ofs);
    }
    ofs.close();
}

string generateUserId(){
	// Hàm này sinh ra user id mới
    maxUserId++;
    string userId = to_string(maxUserId);
    while(userId.length() < 9){
        userId = "0" + userId;
    }

    return "USER" + userId;
}

string generateWalletId(){
	// Hàm này sinh ra wallet id mới
    maxWalletId++;
    string walletId = to_string(maxWalletId);
    while(walletId.length() < 9){
        walletId = "0" + walletId;
    }

    return "WALLET" + walletId;
}