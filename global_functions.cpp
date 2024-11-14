#include "global_functions.h"
#include <random>     // Thư viện sinh số ngẫu nhiên
#include <string>     // Thư viện chuỗi
#include <ctime>   //Thời gian
#include <iostream>  // nhập xuất
#include <cstdlib> //Quản lí bộ nhớ
#include <sstream> // string stream
#include <cctype> //kiểm tra kí tự
#include <algorithm> //thuật toán

//Các cấu hình cần thiết cho các lần chạy chương trình
int originPoint = 1;
int remainPoint = 1;
int maxWalletId = 1;
int maxUserId = 1;
int maxTransactionId = 1;
int otpLength = 6;
//____



/*Tải các user lên từ csdl*/

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


/*Tính toán số điểm còn lại trong ví tổng*/

int caculateRemain(vector<UserWithWallet> &users){
	int sum = 0;
	for(UserWithWallet &user : users){
		sum += user.getBalance();
	}
	return originPoint - sum;
}

/*Lưu các user xuống csdl*/

void saveUserWithWallet(vector<UserWithWallet> &users){
	ofstream ofs("data\\db_user.txt", ios::trunc);
	for(auto user : users){
            user.writeToFile(ofs);
        }
    ofs.close();
}

/*Tải dữ liệu admin lên chương trình*/

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


/*Tải các cấu hình cần thiết từ các lần chạy trước lên chương trình*/

void loadConfig(){
	ifstream ifs("data\\db_config.txt");
	ifs >> originPoint; ifs.ignore();
	ifs >> remainPoint; ifs.ignore();
	ifs >> maxWalletId; ifs.ignore();
	ifs >> maxUserId; ifs.ignore();
	ifs >> maxTransactionId; ifs.ignore();
	ifs.close();
}

/*Lưu lại các cấu hình cần thiết
	Bao gồm ví tổng, max wallet, max user id...
*/

void saveConfig(){
	ofstream ofs("data\\db_config.txt", ios::trunc);
	ofs << originPoint << '\n';
	ofs << remainPoint << '\n';
	ofs << maxWalletId << '\n';
	ofs << maxUserId << '\n';
	ofs << maxTransactionId << '\n';
}

/*Tải transaction từ csdl lên chương trình chính*/

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

/*Lưu lại các transaction vào csdl*/

void saveTransaction(vector<Transaction> &transactions){
	ofstream ofs("data\\db_transaction.txt", ios::trunc);
	for(auto &transaction : transactions){
            transaction.writeToFile(ofs);
    }
    ofs.close();
}

/*Tạo ra user id*/

string generateUserId(){
	// Hàm này sinh ra user id mới
    maxUserId++;
    string userId = to_string(maxUserId);
    while(userId.length() < 9){
        userId = "0" + userId;
    }

    return "USER" + userId;
}

/*Tạo ra wallet id*/

string generateWalletId(){
	// Hàm này sinh ra wallet id mới
    maxWalletId++;
    string walletId = to_string(maxWalletId);
    while(walletId.length() < 9){
        walletId = "0" + walletId;
    }

    return "WALLET" + walletId;
}

/*Tạo ra transaction id*/

string generateTransactionId(){
	// Hàm này sinh ra wallet id mới
    maxTransactionId++;
    string transactionId = to_string(maxTransactionId);
    while(transactionId.length() < 9){
        transactionId = "0" + transactionId;
    }
    return "TRANS" + transactionId;
}

/*
	check xem user có tồn tại tròn csdl không?
*/

bool isAvailableUser(vector<UserWithWallet> &users, string account){
	for(UserWithWallet user : users){
		if(user.getAccount() == account) return true;
	}
	return false;
}

/*
	Check 1 email có hợp lệ không 
	Hợp lệ khi trước '@' không được có kí tự đặc biệt và không nhiều hơn 1 @
	trước @ chỉ được là kí tự và độ dài bé hơn 64 
	sau @ phải có dấu chấm và độ dài email sau @ <= 254 kí tự
	dấu chấm không được ở cuối email
	
*/

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


/*Hàm này sinh ra 1 string OTP*/

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

/*
	hàm này tạo ra 1 số OTP và check người dùng nhập OTP đó có đúng không
*/

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

/*
	Hàm này tạo mật khẩu tự động bằng các kí tự số , kí tự đặc biệt, và kí tự alpha
*/

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

/*
	Kiểm tra 1 tên hợp lệ là có độ dài từ 8 đến 256 kí tự
*/

bool checkName(string name){
	return name.length() >= 8 && name.length() <= 256;
}

/*Password hợp lệ là password không bị rỗng*/

bool checkPassword(string password){
	return password != "";
}

/*
	Hàm này check số điện thoại hợp lệ không , nếu nó tồn tại trong csdl và 
	độ dài của số điện thoại đúng bằng 10
*/

bool checkPhone(string phoneNumber){
	vector<UserWithWallet> users = loadUserWithWallet();
	for(UserWithWallet user : users){
		if(user.getPhoneNumber() == phoneNumber){
			return false;
		}
	}
	return phoneNumber.length() == 10;
}

/*
	Hàm này chuẩn hóa 1 xâu thành in hoa và xóa các khoảng cách dư thừa
*/

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


/*
	Hàm này dùng lưu Admin vào cơ sở dữ liệu
*/
void saveAdmin(vector<Admin> &admins){
	ofstream ofs("data\\db_admin.txt", ios::trunc);
	for(Admin admin : admins){
		admin.writeToFile(ofs);
	}
	ofs.close();
}

/*
	Hàm này trả về 1 string thời gian giờ phút giây và ngày tháng năm hiện tại
*/

std::string getCurrentDateTime() {
    // Lấy thời gian hiện tại
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);  // Chuyển đổi sang thời gian cục bộ

    // Sử dụng stringstream để tạo chuỗi định dạng giờ ngày
    std::stringstream ss;
    ss << localTime->tm_hour << ":"
       << localTime->tm_min << ":"
       << localTime->tm_sec << "-"
       << localTime->tm_mday << "/"
       << localTime->tm_mon + 1 << "/"  // Tháng +1 vì bắt đầu từ 0
       << localTime->tm_year + 1900;  // Năm +1900
       

    return ss.str();  // Trả về chuỗi kết quả
}


/*
	hàm check phone hợp lệ trả về true khi số điện thoại có trong cơ sở dữ liệu
*/
bool checkPhoneIsAvailable(vector<UserWithWallet> &users, string phoneNumber){
	for(UserWithWallet user : users){
		if(user.getPhoneNumber() == phoneNumber){
			return false;
		}
	}
	return true;
}

/*
	LƯU LẠI DỮ LIỆU BACKUP KHI CHẠY CHƯƠNG TRÌNH
*/

void backUp(vector<UserWithWallet> &users, vector<Transaction> &transactions, vector<Admin> &admins){
	ofstream ofs("backup\\db_config.txt", ios::trunc);
	ofs << originPoint << '\n';
	ofs << remainPoint << '\n';
	ofs << maxWalletId << '\n';
	ofs << maxUserId << '\n';
	ofs << maxTransactionId << '\n';
	ofs.close();
	ofstream ofs1("backup\\db_admin.txt", ios::trunc);
	for(Admin admin : admins){
		admin.writeToFile(ofs1);
	}
	ofs1.close();
	ofstream ofs2("backup\db_user.txt", ios::trunc);
	for(auto user : users){
            user.writeToFile(ofs2);
        }
    ofs2.close();
    ofstream ofs3("backup\\db_transaction.txt", ios::trunc);
	for(auto &transaction : transactions){
            transaction.writeToFile(ofs3);
    }
    ofs3.close();
}

