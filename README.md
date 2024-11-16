- DỰ ÁN VÍ ĐIỂM THƯỞNG BÀI TẬP LỚN C++

+ BÀI TẬP CHẠY TRÊN HỆ ĐIỀU HÀNH WINDOW
+ chạy trên IDE DEVC++ bằng chức năng project
+ LƯU Ý:
  Bài tập mô phỏng một ví điểm thưởng gồm 2 đối tượng chính: admin, user_with_wallet tương tác với nhau
  Do mô phỏng không có chức năng để sử dụng và nạp điểm thưởng, nên trong khuôn khổ điểm thưởng sẽ tạm do admin cung cấp
+ VÍ TỔNG:
  Chức năng này được chạy ngầm trong chương trình và không thể tương tác trực tiếp 
+ DATABASE:
  gồm có 2 bản là một bản chính và một bản backup : chương trình sẽ lưu lại bản backup khi vừa bắt đầu sau khi chạy chương trình
  Ngoài ra bản chính bao gồm các database sau : db_admin, db_transaction, db_config, db_user
+ SƠ ĐỒ UML CÁC ĐỐI TƯỢNG CƠ BẢN :
  ![image](https://github.com/user-attachments/assets/49bdc9ce-384b-4719-b838-289986986505)
+ LƯU ĐỒ THỰC HIỆN CỦA CHƯƠNG TRÌNH :
  ![image](https://github.com/user-attachments/assets/91655c0d-a719-4e1b-b2e1-af854b65b8d6)

+ Khi clone code về nếu ở dev c thì mở file .dev còn nếu không có trình IDE devC thì có thể mở file.exe để chạy chương trình

+ Phân công nhiệm vụ :
  - Ba Ka : thiết kế cơ sở dữ liệu, quản lý , sửa lỗi và tích hợp code của các thành viên và mã hash
  - Tô Hoàng Phi : chịu trách nhiệm phần viết mã OTP , thời gian và các chức năng khác của phần đăng ký.
  - Nguyễn Trọng Nhân : Viết các chức năng liên quan tới đăng nhập và các tính năng của User
  - Trần Minh Khôi : Viết các mã xử lí gmail, và xử lí chuỗi và viết code UI
  - Lê Hoài Tâm : Chịu trách nhiệm các hàm xử lí chuỗi và chuẩn hóa chuỗi. 
+ Mô tả chương trình :
  Chương trình gồm 2 phần chính : 1 là của user, 2 là của admin
    User có thể : xem thông tin cá nhân, chuyển khoản, xem lịch sử giao dịch, thay đổi thông tin cá nhân
    Admin có thể : xem thông tin cá nhân, chỉnh sửa thông tin cá nhân, chính sửa thông tin người dùng, tạo tài khoản hộ người dùng, xem danh sách các user


+ Chương trình có thể còn một số buggg !! :>>> không gì là chắc chắn cả
