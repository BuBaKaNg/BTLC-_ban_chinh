/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include <iostream>
#include "global_functions.h"
#include "admin.h"
#include "user_with_wallet.h"
#include "view.h"
#include "user.h"
#include <iomanip>
//CMT
using namespace std;
//Biến này dùng để sinh giá trị hash
hash<string> hashString;
//____

/*HÀM LÀM MỚI CSDL =======
	-Giúp CSDL không bị mất khi chương trình đột nhiên bị tắt
*/
void refresh(vector<UserWithWallet> &users, vector<Transaction> &transactions, vector<Admin> &admins){
	saveUserWithWallet(users);
	saveTransaction(transactions);
	saveAdmin(admins);
	saveConfig();
}
//______

//ĐĂNG NhẬP ==========
string logging(vector<UserWithWallet> &users, vector<Admin> &admins){
	//NHẬP THÔNG TIN ==========
	showMenuHeader("LOGGING", 50);
	cout << "Please enter your account: " << endl;
	string account;
	getline(cin, account);
	cout << "Please enter your password: " << endl;
	string password; 
	getline(cin, password);
	//_____
	
	//TÌM THÔNG TIN TRONG CSDL
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
	//_____
	return "not_found"; // Trả về xâu "not_found" khi không tìm thấy tài khoản
}
//______

//ĐĂNG KÝ ==========
int signUp(vector<UserWithWallet> &users){
	while(1){
		// YÊU CẦU NHẬP CÁC THÔNG TIN CƠ BẢN ==========
		string account, password, name, email, phoneNumber;
		showMenuHeader("SIGN UP", 50);
		cout << "Please enter your account: " << endl;
		getline(cin, account);
		if(account.length() < 8 || account.length() > 256 || !checkValidStr(account)){ // check độ dài tên tài khoản hợp lệ không ?
			cout << "Account is so long or short or not valid !!" << endl;
			break;
		}
		else if(isAvailableUser(users, account)){
			cout << "User is available !!!" << endl;
			break;
		}
		cout << "Please enter your password: " << endl;
		getline(cin, password);
		if(!checkPassword(password)){ // check người dùng có nhập mật khẩu không
			cout << "Password is empty or not valid !!" << endl;
			break;
		}
		cout << "Please enter your name: " << endl;
		getline(cin, name);
		if(!checkLengthName(name)){ // check tên người dùng có hợp lệ không
			cout << "Name is not valid!!" << endl;
			break;
		}
		cout << "Please enter your email: " << endl;
		getline(cin, email);
		if(!isValidEmail(email)){ // check email có hợp lệ không
			cout << "Email is not valid!!" << endl;
			break;
		}
		cout << "Please enter your phone number: " << endl;
		getline(cin, phoneNumber);
		if(!checkPhone(phoneNumber)){ // check số điện thoại có hợp lệ không
			cout << "Phone number is not valid" << endl;
			break;
		}
		//_____
		
		//TẠO TÀI KHOẢN ĐƯA VÀO CSDL =========
		UserWithWallet user(generateUserId(), account, hashString(password), name, email, phoneNumber, generateWalletId(), 0);
		users.push_back(user);
		cout << "SIGN UP SUCCESSFULLY !!!" << endl;
		//____
		return 1;
	}
	return 0;
}
//______


//HOẠT ĐỘNG ==========
void operate(string userId, vector<UserWithWallet> &users, vector<Admin> &admins, vector<Transaction> &transactions){
	while(1){	
		if(userId.substr(0,4) != "USER"){ // Kiểm tra loại tài khoản không dành cho user
			//KHỞI TẠO 1 ADMIN
			Admin admin;
			for(Admin &ad : admins){
				if(ad.getUserId() == userId){
					admin = ad;
					break;
				}
			}
			//____
			
			
			//IN RA MÀN HÌNH MENU CỦA ADMIN
			showMenuHeader("ADMIN", 50);
			cout << "1. Show list user" << endl;
			cout << "2. Create an account" << endl;
			cout << "3. Update information of user" << endl;
			cout << "4. Show your information" << endl;
			cout << "5. Update your information" << endl;
			cout << "0. Exit" << endl;
			cout << setfill('-') << setw(50) << '-' << endl;
			cout << setfill(' ') << endl;
			cout << "Please choose one option (0-5): ";

			//____
			
			
			string choose; getline(cin, choose);
			cout << endl;
			//SHOW LIST ==========
			if(choose == "1"){
				admin.showList(users);
			}
			//______
			
			//TẠO TÀI KHOẢN ==========
			else if(choose == "2"){
				admin.createAccount(users);
				refresh(users, transactions, admins);
			}
			//______
			
			//THAY ĐỔI THÔNG TIN CHO 1 USER
			else if(choose == "3"){
				cout << "Please enter your user id need to update: " << endl;
				string userId_update; getline(cin, userId_update);
				admin.updateInforOfUser(users, userId_update);
				refresh(users, transactions, admins);
			}
			//_____
			
			//IN RA THÔNG TIN CỦA ADMIN ==========
			else if(choose == "4"){
				admin.showInfor();
				cout << endl;
			}
			//_____
			
			//THAY ĐỔI THÔNG TIN ADMIN ==========
			else if(choose == "5"){
				admin.updateInfor();
				for(Admin &ad : admins){
					if(ad.getUserId() == admin.getUserId()){
						ad = admin;
						break;
					}
				} 
				refresh(users, transactions, admins);
			}
			//______
			
			//ĐĂNG XUẤT KHỎI TK ADMIN
			else if(choose == "0"){
				return;
			}
			//____
			else{
				cout << "Option entered not valid !!!" << endl;
			}
		}
		/*USER
			-nếu không phải admin => user
		*/
		else{
			//KHỞI TẠO 1 TÀI KHOẢN USER ========
			UserWithWallet user;
			for(UserWithWallet &us : users){
				if(us.getUserId() == userId){
					user = us;
					break;
				}
			}
			//______
			
			//IN RA MÀN HÌNH MENU USER ==========
			showMenuHeader("USER", 50);
			cout << "1. Show your information" << endl;
			cout << "2. Update your information" << endl;
			cout << "3. Trade" << endl;
			cout << "4. Show history of trade" << endl;
			cout << "0. Exit" << endl;
			cout << setfill('-') << setw(50) << '-' << endl;
			cout << setfill(' ') << endl;
			cout << "Please choose one option (0-4): ";
			//_____
			
			
			string choose; getline(cin, choose);
			
			//SHOW INFOR CỦA USER ==========
			if(choose == "1"){
				user.showInfor();
			}
			//______
			
			//UPDATE INFOR CỦA USER ==========
			else if(choose == "2"){
				user.updateInfor();
				for(UserWithWallet &us : users){
					if(user.getUserId() == us.getUserId()){
						us = user;
						break;
					}
				}
				refresh(users, transactions, admins);
			}
			//______
			
			//CHỨC NĂNG GIAO DỊCH CỦA USER ==========
			else if(choose == "3"){
				user.trade(users, transactions);
				refresh(users, transactions, admins);
			}
			//_____
			
			//CHỨC NĂNG SHOW LỊCH SỬ GIAO DỊCH ==========
			else if(choose == "4"){
				user.showTransactions(transactions, user.getUserId());
			}
			//_____
			
			//ĐĂNG XUẤT KHỎI TÀI KHOẢN USER ==========
			else if(choose == "0"){
				return;
			}
			else{
				cout << "Option entered not valid !!!" << endl;
			}
			//_____
		}
	}
}
//_____

int main(int argc, char** argv) {
//LOAD TỪ DATA BASE ====
	vector<UserWithWallet> users = loadUserWithWallet(); // Load list user
	vector<Admin> admins = loadAdmin(); // Load list admin
	vector<Transaction> transactions = loadTransaction(); // Load list transaction
	loadConfig(); // Load các thông tin cơ bản bao gồm ví tổng
//___
//BACKUP
	backUp(users, transactions, admins);
//___
	while(1){
		startScreen(); // Màn hình bắt đầu
		string userId = "fail";
		string option; getline(cin, option);
		// lựa chọn 1 là đăng nhập
		cout << endl;
		if(option == "1"){
			userId = logging(users, admins); // Nếu logging thành công thì trả về 1 user id 
		} 
		// lựa chọn 2 là đăng kí
		else if(option == "2"){
			int success;
			success = signUp(users); // Đăng kí trả về thành công hoặc không 
			if(success == 1){
				//Đăng ký thành công thì chuyển sang màn hình đăng nhập
				refresh(users, transactions, admins);
				userId = logging(users, admins);
			}
		}
		// Lựa chọn 3 là reset lại màn hình
		else if(option == "3"){
			system("CLS");
		}
		//Lựa chọn 0 là kết thúc chương trình
		else if(option == "0"){
			refresh(users, transactions, admins);

			showMenuHeader("THANKS FOR USE THE APP !!!", 140);
			return 0;	
		}
		else{
			cout << "Option entered not valid !!" << endl;
		}
		//Nếu user id là fail thì đăng nhập hoặc đăng kí thất bại
		if(userId == "fail"){
			continue;
		}
		//Không tìm thấy user id này trong CSDL
		else if(userId == "not_found"){
			cout << "Wrong account or password!!" << endl;
			continue;
		}
		
		//HÀM VẬN HÀNH CHÍNH ==========
		operate(userId, users, admins, transactions);
		//______
		
		//HÀM LÀM MỚI CSDL KHI KẾT THÚC CHƯƠNG TRÌNH ==========
		refresh(users, transactions, admins);
		//______
	}
return 0;
}

