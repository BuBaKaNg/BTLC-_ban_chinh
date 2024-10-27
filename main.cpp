/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include <iostream>
#include "global_functions.h"
#include "admin.h"
#include "user_with_wallet.h"
#include "view.h"
#include "user.h"

using namespace std;



int main(int argc, char** argv) {
//LOAD TỪ DATA BASE ====
	vector<UserWithWallet> users = loadUserWithWallet();
	vector<Admin> admins = loadAdmin();
//	vector<Transaction> transactions = loadTransaction();
//	admins = loadAdmin();
//	loadConfig();
//	transactions = loadTransaction();
//	logging();
	
//___	
//	while(1){
//		startScreen();
//		bool success;
//		int option; cin >> option; cin.ignore();
//		if(option == 1){
//			success = logging();
//		}
//		else if(option == 2){
//			success = signUp();
//		}
//		else if(option == 3){
//			cout << "********************************************"
//			cout << "==== CẢM ƠN BẠN ĐÃ SỬ DỤNG CHƯƠNG TRÌNH ====" << endl;
//			return 0;	
//		}
//		if(!succcess){
//			continue;
//		}
//		operate();
//	}
return 0;
}

