#ifndef _USER_
#define _USER_

#include <string>
#include <vector>

class User {
	protected:
    //THUỘC TÍNH ========
    std::string userId;
    std::string account;
    std::size_t password;
    std::string name;
    std::string email;
    std::string phoneNumber;
    //_________________
    public:
	
	//CONSTRUCTOR ===============
    User();
    User(std::string userId, std::string account, std::size_t password, std::string name, std::string email, std::string phoneNumber);
    //__________________________
    
    
    //GETTER, SETTER ========
    std::string getUserId();
    std::string getAccount();
    std::size_t getPassword();
    std::string getName();
    std::string getEmail();
    std::string getPhoneNumber();
    void setUserId(std::string _userId);
    void setAccount(std::string _account);
    void setPassword(std::size_t _password);
    void setName(std::string _name);
    void setEmail(std::string _email);
    void setPhoneNumber(std::string _phoneNumber);
    //____________
    
    //SHOW INFOR ======
    void showInfor(); // in ra thông tin của người dùng hoặc admin
    //_________
    
    //UPDATE INFOR ======
    void updateInfor(); // thay đổi thông tin của người dùng hoặc admin
    //________
    
    //PRINT ======
    void print(); // in để debug
    //_________
    
    
    
};
#endif