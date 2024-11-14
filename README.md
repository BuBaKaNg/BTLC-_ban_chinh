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

+ CHúng em vừa phát hiện bài tập vẫn còn một số bug chưa fix xong !!
  
  Ví dụ như nhập vào option bằng chữ số hoặc trade khi nhập vào chữ số
  Khi mới tạo nick mới chưa có transaction history nên bổ sung thêm từ empty
  Khi tạo tài khoản nhập nhiều kí tự rõng vẫn tạo được tương tự với các ràng buộc kí tự khác 

