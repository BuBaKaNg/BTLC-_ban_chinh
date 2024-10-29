#include "global_functions.h"
#include <random>     // Thư viện sinh số ngẫu nhiên
#include <string>     // Thư viện chuỗi
#include <ctime>   
#include <iostream>  
#include <cstdlib> 
#include <sstream>
#include <cctype>
#include <algorithm>
int originPoint = 1;
int remainPoint = 1;
int maxWalletId = 1;
int maxUserId = 1;
int maxTransactionId = 1;
int otpLength = 6;



vector<UserWithWallet> loadUserWithWallet(){
	vector<UserWithWallet> users;
	ifstream ifs("data\\db_user.txt");
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
	ofstream ofs("data\\db_user.txt", ios::trunc);
	for(auto user : users){
            user.writeToFile(ofs);
        }
    ofs.close();
}

vector<Admin> loadAdmin(){
	vector<Admin> admins;
	ifstream ifs("data\\db_admin.txt");
	 while (ifs.good()) {
        Admin admin;
        admin.readFromFile(ifs);
        admins.push_back(admin);
    }
    ifs.close();
    return admins;
}


void loadConfig(){
	ifstream ifs("data\\db_config.txt");
	ifs >> originPoint; ifs.ignore();
	ifs >> remainPoint; ifs.ignore();
	ifs >> maxWalletId; ifs.ignore();
	ifs >> maxUserId; ifs.ignore();
	ifs >> maxTransactionId; ifs.ignore();
	ifs.close();
}

void saveConfig(){
	ofstream ofs("data\\db_config.txt", ios::trunc);
	ofs << originPoint << '\n';
	ofs << remainPoint << '\n';
	ofs << maxWalletId << '\n';
	ofs << maxUserId << '\n';
	ofs << maxTransactionId << '\n';
}

vector<Transaction> loadTransaction(){
	vector<Transaction> transactions;
	ifstream ifs("data\\db_transaction.txt");
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
	ofstream ofs("data\\db_transaction.txt", ios::trunc);
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

string generateTransactionId(){
	// Hàm này sinh ra wallet id mới
    maxTransactionId++;
    string transactionId = to_string(maxTransactionId);
    while(transactionId.length() < 9){
        transactionId = "0" + transactionId;
    }
    return "TRANS" + transactionId;
}

bool isAvailableUser(vector<UserWithWallet> &users, string account){
	for(UserWithWallet user : users){
		if(user.getAccount() == account) return true;
	}
	return false;
}


bool isValidEmail(string s)
{
    bool flag = 0;
    int dem = 0,i,ch=0;
    for (int i = 0; i < s.length(); i++)
    {
        if (!isalnum(s[i]) && !isalpha(s[i]) && s[i] != '.' && s[i] != '_' && s[i] != '@')
        {
            return 0;
        }
        if (s[i] == '@')
            dem++;
        if (dem > 1)
            return 0;
    }
    for (i = 0; s[i] != '@'; i++)
    {
        if (isalpha(s[i]) && isalnum(s[i]))
            ch = 1;
        if (i > 64)
            return 0;
    }
    if (ch == 0)
        return 0;
    dem = 0;
    for (int j = i + 1; j < s.length(); j++)
    {
        if (s[j] == '.')
            flag = 1;
        dem++;
        if (dem > 254)
            return 0;
    }
    if (flag == 0)
        return 0;
    if (s[s.length() - 1] == '.')
        return 0;
    return 1;
}


string generateOTP(int length, int extra_seed) {
    string otp = "";

    // Seed kết hợp giữa giây hiện tại và một giá trị bổ sung (extra_seed)
    time_t current_time = std::time(nullptr);
    mt19937 rng(current_time + extra_seed); // Seed khác nhau cho mỗi lần gọi

    uniform_int_distribution<int> dist(0, 9); // Sinh số từ 0 đến 9

    for (int i = 0; i < length; ++i) {
        otp += to_string(dist(rng)); // Ghép các số thành chuỗi OTP
    }

    return otp;
}

bool checkOTP(){
	cout << "===== CHECK OTP ======" << endl;
	string otp = generateOTP(otpLength, 1);
	cout << "Your OTP is :" << otp << endl;
	string new_otp;
	cout << "Please enter your otp to verify: ";
	getline(cin, new_otp);
	if(new_otp == otp){		
		return true;
	} 
	return false;
}

string generatePassword(int length) {
    const string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string digits = "0123456789";
    const string special = "!@#$%^&*()";
    
    // Kết hợp các ký tự từ các loại khác nhau
    const string all_chars = lowercase + uppercase + digits + special;
    string password;
    password.reserve(length); // Đặt trước dung lượng cho mật khẩu

    srand(static_cast<unsigned int>(time(0))); // Khởi tạo seed cho số ngẫu nhiên

    for (int i = 0; i < length; ++i) {
        password += all_chars[rand() % all_chars.size()];
    }

    return password;
}

bool checkName(string name){
	return name.length() >= 8 && name.length() <= 256;
}

bool checkPassword(string password){
	return password != "";
}

bool checkPhone(string phoneNumber){
	return phoneNumber.length() == 10;
}

string toUpperAndTrimSpaces(const string& input) {
    // Tạo một bản sao của chuỗi gốc để xử lý
    string result;
    stringstream stream(input);
    string word;

    // Đọc từng từ, chuyển thành chữ hoa và thêm vào result với một khoảng trắng giữa các từ
    while (stream >> word) {
        // Chuyển từng từ thành chữ hoa
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (!result.empty()) {
            result += " "; // Thêm khoảng trắng giữa các từ
        }
        result += word;
    }

    return result;
}