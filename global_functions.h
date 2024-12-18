#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "user_with_wallet.h"
#include "admin.h"
#include "transaction.h"

//BIẾN TOÀN CỤC ======
//LƯU CÁC THÔNG TIN CỦA VÍ TỔNG
extern int originPoint;
extern int remainPoint;
extern int maxWalletId;
extern int maxUserId;
extern int maxTransactionId;
//_____

//DÙNG ĐỂ TẢI DỮ LIỆU USER LÊN ====
vector<UserWithWallet> loadUserWithWallet();
//_____


//DÙNG ĐỂ TẢI DỮ LIỆU ADMIN LÊN ===
vector<Admin> loadAdmin();
//______

//DÙNG ĐỂ LƯU DỮ LIỆU USER XUỐNG ===
void saveUserWithWallet(vector<UserWithWallet> &users);
//______

//TÍNH SỐ ĐIỂM CÒN LẠI TRONG VÍ TỔNG
int caculateRemain(vector<UserWithWallet> &users);
//____


//TẢI THÔNG TIN NỀN TẢNG
void loadConfig();
//____

//LƯU LẠI CÁC THÔNG TIN CHO LẦN CHẠY SAU ====
void saveConfig();
//____


//LOAD TRANSACTION =====
vector<Transaction> loadTransaction();
//_____

//SAVE TRANSACTION =====
void saveTransaction(vector<Transaction> &transactions);
//______

//SINH USER ID =====
string generateUserId();
//_____

//SINH WALLET ID ======
string generateWalletId();
//____


//SINH TRANSACTION ID ====
string generateTransactionId();
//____

//CHECK USER TỒN TẠI ====
bool isAvailableUser(vector<UserWithWallet> &users, string account);
//____

//CHECK EMAIL ====
bool isValidEmail(string email);
//____


//SINH OTP
string generateOTP(int length, int extra_seed);
//____

//CHECK OTP
bool checkOTP();
//____

//SINH MAT KHAU
string generatePassword(int length);
//____

//CHECK TEN HOP LE
bool checkName(string name);
//____

//CHECK SĐT HOP LE 
bool checkPhone(string phoneNumber);
//___


//CHECK PASS
bool checkPassword(string password);
//___

//SAVE ADMIN
void saveAdmin(vector<Admin> &admins);
//____


//CHUAN HOA XAU IN HOA VA KHONG CO KHOANG TRANG 2 BEN
string toUpperAndTrimSpaces(const string &input);
//_____

//HÀM LẤY NGÀY THÁNG NĂM HIỆN TẠI
string getCurrentDateTime();
//____


//HÀM CHECK PHONE TỒN TẠI
bool checkPhoneAvailable(vector<UserWithWallet> &user, string phoneNumber);
//____

//HÀM BACKUP
void backUp(vector<UserWithWallet> &users, vector<Transaction> &transactions, vector<Admin> &admins);
//___

//HÀM CHECK KHOẢN TRẮNG
bool checkValidStr(string str);
//___

//CHECK XAU CO PHAI SO KHONG ?
bool checkStrNum(string str);
//___

bool checkLengthName(string name);
#endif
