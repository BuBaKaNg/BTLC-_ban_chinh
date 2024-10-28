#include "user.h"
#include <iostream>
#include <functional>

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
        std::cout << "______________________________________" << std::endl;
        std::cout << "User ID: " << getUserId() << std::endl;
        std::cout << "Name: " << getName() << std::endl;
        std::cout << "Email: " << getEmail() << std::endl;
        std::cout << "Phone Number: " <<  getPhoneNumber() << std::endl;
}
//_________



//UPDATE INFOR ======
void User::updateInfor(){
        /*Hàm này dùng để update infor người dùng và admin*/
    while(1){
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
            if(option == 1){
                std::cout << "Please enter your new name:";
                std::getline(std::cin, new_infor);
                setName(new_infor);
            }
            else if(option == 2){
                std::cout << "Please enter your new email:";   
                std::getline(std::cin, new_infor);         
                setEmail(new_infor);
            }
            else if(option == 3){
                std::cout << "Please enter your new phone number:"; 
                std::getline(std::cin, new_infor);
                setPhoneNumber(new_infor);
            }
            else if(option == 4){
                std::cout << "Please enter your new password:"; 
                std::getline(std::cin, new_infor);
                std::hash<std::string> hashString;
                setPassword(hashString(new_infor));
            }
            else if(option == 0){
                return;
        }
    }
}
//__________


//PRINT ======
void User::print(){
	std::cout << getUserId() + " " + getName() + " " + getEmail() + " " + getPhoneNumber() +
        " " + getAccount() + " " + std::to_string(getPassword());
}

//_________