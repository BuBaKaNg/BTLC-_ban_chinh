#include "user.h"
#include <iostream>
#include <functional>
#include "global_functions.h"
//CONSTRUCTOR ======
User::User(){}

User::User(std::string userId, std::string account, std::size_t password,
	 std::string name, std::string email, std::string phoneNumber) :userId(userId), account(account), password(password), name(name),email(email), phoneNumber(phoneNumber){}
//______

//GETTER SETTER ======
std::string User::getUserId() { return userId; }
std::string User::getAccount() { return account; }
std::size_t User::getPassword() { return password; }
std::string User::getName() { return name; }
std::string User::getEmail() { return email; }
std::string User::getPhoneNumber() { return phoneNumber; }
void User::setUserId(std::string _userId) { userId = _userId; }
void User::setAccount(std::string _account) { account = _account; }
void User::setPassword(std::size_t _password) { password = _password; }
void User::setName(std::string _name) { name = _name; }
void User::setEmail(std::string _email) { email = _email; }
void User::setPhoneNumber(std::string _phoneNumber) { phoneNumber = _phoneNumber; }
//______

//SHOW INFOR ======
void User::showInfor(){
        /*Hàm này dùng để đưa ra màn hình thông tin người dùng*/
        std::cout << "========== INFOR ==========" << '\n';
        std::cout << "User ID: " << getUserId() << '\n';
        std::cout << "Account: " << getAccount() << '\n';
        std::cout << "Name: " << toUpperAndTrimSpaces(getName()) << '\n';
        std::cout << "Email: " << getEmail() << '\n';
        std::cout << "Phone Number: " <<  getPhoneNumber() << '\n';
}
//_________



//UPDATE INFOR ======
void User::updateInfor(){
        /*Hàm này dùng để update infor người dùng và admin*/
    while(1){
    		//IN RA MÀN HÌNH UPDATE ==========
            std::cout << "======= UPDATE ========" << std::endl;
            int option;
            std::cout << "1. Update Name" << std::endl;
            std::cout << "2. Update Email" << std::endl;
            std::cout << "3. Update Phone Number" << std::endl;
            std::cout << "4. Update Password" << std::endl;
            std::cout << "0. Exit" << std::endl;
            std::cout << "Choose option:";
            std::cin >> option;
            std::cin.ignore();
            std::string new_infor;
            //______
            
            //UPDATE NAME =========
            if(option == 1){
                std::cout << "Please enter your new name:";
                std::getline(std::cin, new_infor);
            	if(!checkName(new_infor)){ // check tên có hợp lệ không ?
            		cout << "UPDATE IS FAILED, NEW INFORMATION IS NOT VALID!!" << endl;
            		continue;
				}
				else if(checkOTP()){ // check OTP
                	setName(new_infor);
                	cout << "NAME UPDATED SUCCESSFULY !!" << endl;
				}
				else{
					cout << "UPDATE IS FAILED, WRONG OTP !!!" << endl;
					continue;
				}
            }
            //_____
            
            //UPDATE EMAIL ==========
            else if(option == 2){
                std::cout << "Please enter your new email:";   
                std::getline(std::cin, new_infor);  
                if(!isValidEmail(new_infor)){ // check email có hợp lệ không
                	cout << "UPDATE IS FAILED, NEW INFORMATION IS NOT VALID!!" << endl;
            		continue;
				}
				else if(checkOTP()){ // check otp
                	setEmail(new_infor);
                	cout << "EMAIL UPDATED SUCCESSFULY !!" << endl;
				}       
				else{
					cout << "UPDATE IS FAILED, WRONG OTP!!!" << endl;
					continue;
				}
            }
            //_____
            
            //UPDATE SỐ ĐIỆN THOẠI ==========
            else if(option == 3){
                std::cout << "Please enter your new phone number:"; 
                std::getline(std::cin, new_infor);
                if(!checkPhone(new_infor)){ // check phone có hợp lệ không
                	cout << "UPDATE IS FAILED, NEW INFORMATION IS NOT VALID!!" << endl;
            		continue;
				}
                if(checkOTP()){ // check otp
                	setPhoneNumber(new_infor);
                	cout << "PHONE NUMBER UPDATED SUCCESSFULY !!" << endl;
				}
				else{
					cout << "UPDATE IS FAILED, OTP WRONG!!!" << endl;
					continue;
				}
            }
            //______
            
            //UPDATE PASSWORD ==========
            else if(option == 4){
                std::cout << "Please enter your new password:"; 
                std::getline(std::cin, new_infor);
                std::hash<std::string> hashString;
                if(!checkPassword(new_infor)){ // check mật khẩu hợp lệ không ?
                	cout << "UPDATE IS FAILED, NEW INFORMATION IS NOT VALID!!" << endl;
            		continue;
				}
                if(checkOTP()){ // check OTP
                	setPassword(hashString(new_infor));
                	cout << "PASSWORD UPDATED SUCCESSFULY !!" << endl;
				}
				else{
					cout << "UPDATE IS FAILED, OTP IS WRONG!!!" << endl;
					continue;
				}
            }
            else if(option == 0){
                return;
        }
        //____
    }
}
//__________


//PRINT ======
void User::print(){
	std::cout << getUserId() + " " + getName() + " " + getEmail() + " " + getPhoneNumber() +
        " " + getAccount() + " " + std::to_string(getPassword());
}

//_________