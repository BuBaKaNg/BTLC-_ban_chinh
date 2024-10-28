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
void saveTransaction();
//______

//SINH USER ID =====
string generateUserId();
//_____

//SINH WALLET ID ======
string generateWalletId();
//____


#endif
