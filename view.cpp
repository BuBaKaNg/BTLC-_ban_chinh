#include <iostream>
#include "view.h"
#include <iomanip>
using namespace std;

void startScreen(){
	
	showMenuHeader("REWARD WALLET APP", 50);
    cout << "1. Logging" << endl;
    cout << "2. Sign up" << endl;
    cout << "3. Clear" << endl;
    cout << "0. Exit" << endl;
    cout << setfill('_') << setw(50) << '_' << endl;
    setfill(' ');
    cout << endl;
    cout << "Please choose one option (0-3): ";
}

void showMenuHeader(const std::string& title, int width_s) {
    int width = width_s; // Chiều rộng của tiêu đề menu
    int padding = (width - title.size()) / 2; // Tính toán khoảng trống cho căn giữa

    // Dòng trên cùng
    std::cout << std::setfill('=') << std::setw(width) << "=" << std::endl;

    // Căn giữa tiêu đề
    std::cout << std::setfill(' ') << std::setw(padding + title.size()) << title 
              << std::setw(padding) << " " << std::endl;

    // Dòng dưới cùng
    std::cout << std::setfill('=') << std::setw(width) << "=" << std::endl;

    // Trả lại ký tự điền mặc định
    std::cout << std::setfill(' ');
}