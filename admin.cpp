#include "admin.h"
#include "user.h"
#include <iostream>
#include "global_functions.h"
#include <functional>
#include "user_with_wallet.h"
#include <iomanip>
#include "view.h"

//CONSTRUCTOR ============
Admin::Admin(){}
Admin::Admin(string id, string account, size_t password, string name, string email, string phoneNumber) :
    User(id, account, password, name, email, phoneNumber){}
//______     

//OK
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
    setPhoneNumber(line);
    getline(ifs, line);
    setEmail(line);
}
//_______________


//GHI FILE ============
void Admin::writeToFile(ofstream& ofs){
    ofs << getUserId() << "\n";
    ofs << getAccount() << "\n";
    ofs << getPassword() << "\n";
    ofs << getName() << "\n";
    ofs << getPhoneNumber() << "\n";
    ofs << getEmail() << "\n";
}
//_______


//SHOW LIST ==========
void Admin::showList(vector<UserWithWallet> &users){
    int widthUser = 20;
    int widthAccount = 20;
    int widthName = 25;
    int widthEmail = 30;
    int widthPhoneNumber = 15;
    int widthWalletId = 25;
    int widthBalance = 10;
    
    
    showMenuHeader("LIST USER", 145);
    //IN TIEU DE COT
    cout << left << setw(widthUser) << "USER ID"
  		  << setw(widthAccount) << "ACCOUNT" 
  		  << setw(widthName) << "NAME"
  		  << setw(widthEmail) << "EMAIL"
  		  << setw(widthPhoneNumber) << "PHONE NUMBER"
  		  << setw(widthWalletId) << "WALLET ID" 
  		  << setw(widthBalance) << "BALANCE" << endl;
  	//IN DÒNG NGĂN CÁCH
  	cout << setfill('-') << setw(widthUser + widthAccount + widthName + widthEmail + widthPhoneNumber + widthWalletId + widthBalance) << "-" << endl;
  	cout << std::setfill(' ') << endl; // trả về mặc định
  	
    for(UserWithWallet& user : users){
	    // Kiểm tra và xử lý chuỗi USER ID
	    string userId = user.getUserId();
	    if (userId.size() > widthUser - 3) {
	        userId = userId.substr(0, widthUser - 3) + "...";
	    }
	
	    // Kiểm tra và xử lý chuỗi ACCOUNT
	    string account = user.getAccount();
	    if (account.size() > widthAccount - 3) {
	        account = account.substr(0, widthAccount - 3) + "...";
	    }
	
	    // Kiểm tra và xử lý chuỗi NAME
	    string name = toUpperAndTrimSpaces(user.getName());
	    if (name.size() > widthName - 3) {
	        name = name.substr(0, widthName - 3) + "...";
	    }
	
	    // Kiểm tra và xử lý chuỗi EMAIL
	    string email = user.getEmail();
	    if (email.size() > widthEmail - 3) {
	        email = email.substr(0, widthEmail - 3) + "...";
	    }
	
	    // Kiểm tra và xử lý chuỗi PHONE NUMBER
	    string phoneNumber = user.getPhoneNumber();
	    if (phoneNumber.size() > widthPhoneNumber - 3) {
	        phoneNumber = phoneNumber.substr(0, widthPhoneNumber - 3) + "...";
	    }
	
	    // Kiểm tra và xử lý chuỗi WALLET ID
	    string walletId = user.getWalletId();
	    if (walletId.size() > widthWalletId - 3) {
	        walletId = walletId.substr(0, widthWalletId - 3) + "...";
	    }
	
	    // Kiểm tra và xử lý chuỗi BALANCE (có thể là một số, nên bạn chỉ cần kiểm tra độ dài chuỗi số này)
	    string balance = to_string(user.getBalance());
	    if (balance.size() > widthBalance - 3) {
	        balance = balance.substr(0, widthBalance - 3) + "...";
	    }
	
	    // In các giá trị với chiều rộng đã được điều chỉnh
	    cout << left << setw(widthUser) << userId
	         << setw(widthAccount) << account
	         << setw(widthName) << name
	         << setw(widthEmail) << email
	         << setw(widthPhoneNumber) << phoneNumber
	         << setw(widthWalletId) << walletId
	         << setw(widthBalance) << balance << endl;
	}
    cout << setfill('-') << setw(widthUser + widthAccount + widthName + widthEmail + widthPhoneNumber + widthWalletId + widthBalance) << '-';
    cout << endl;
  	cout << setfill(' '); // trả về mặc định
  	cout << endl;
  	cout << right;
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
	//Hàm này update infor của user
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
		//Hàm này tạo tài khoản mới bằng admin
		showMenuHeader("CREATE ACCOUNT", 50);
	    string account, name, password, email, phoneNumber;
	    string amount;
	    cout << "NOTE: account not include special digit , can include '_' and '.'" << endl;
	    cout << "Please enter your account: " << endl;
		getline(cin, account);

		for(int i = 0; i < account.length(); i++){
			if(account[i] == ' '){
				cout << "Create an account is failed, your account is not valid!!" << endl;
				return;
			}
			if(!isalnum(account[i]) && !isalpha(account[i]) && account[i] != '_' && account[i] != '.' && account.length() > 256){
				cout << "Create an account is failed, your account is not valid!!" << endl;
				return;
			}
		}
		if(account.length() == 0){
			cout << "Create an account is failed, your account is not valid!!" << endl;
			return;
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
		if(!checkValidStr(name)){
			cout << "Create an account is failed, your name is not valid" << endl;
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
		getline(cin, amount);
		if(amount.length() > 8){
			cout << "Create an account is failed, point of total wallet is not enough" << endl;
				return;
		}
		if(!checkStrNum(amount)){
			cout << "Create an account is failed, this is not a number" << endl;
			return;
		}
		remainPoint -= stoi(amount);
		cin.ignore();
	    string userId = generateUserId();
	    string walletId = generateWalletId();
	    hash<string> hashString;
	    UserWithWallet user(userId, account,hashString(password), name, email, phoneNumber, walletId, stoi(amount));
	    users.push_back(user);
	    cout << "Account of user is: " << account << endl;
		cout << "Password of user is: " << password << endl;
	    cout << "CREATE SUCCESS !!" << endl;
		return;   
}
//______

//Hàm này dùng để debug bằng cách in thông tin 
void Admin::print(){
	User::print();
}