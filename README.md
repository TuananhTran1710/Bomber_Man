
# GIỚI THIỆU GAME
* Video Demo game: https://s.net.vn/m6yq
* BomberMan là một game chiến thuật 2 người chơi lấy ý tưởng chính từ tựa game Bom IT, với những nhân vật hoạt hình vui nhộn, bạn sẽ nhập vai vào một nhân vật và đi ăn các item bằng cách đặt bom để phá các ô chứa nó, sau đó dùng sẽ khéo léo và nhanh nhạy của mình để hạ gục đối thủ.
# MỤC LỤC
* [0. CÁCH TẢI GAME](#0-cách-tải-game)
* [1. CẤU TRÚC GAME](#1-cấu-trúc-game)
* [2. HƯỚNG DẪN CÁCH CHƠI](#2-hướng-dẫn-cách-chơi)
* [3. GIỚI THIỆU GAMEPLAY](#3-giới-thiệu-gameplay)
* [4. CÁCH TỔ CHỨC FILE .CPP VÀ .H](#4-cách-tổ-chức-file-cpp-và-h)
* [5. NGUỒN THAM KHẢO](#5-nguồn-tham-khảo)
# 0. CÁCH TẢI GAME
* Tải game được nén thành file .zip tại link sau: https://github.com/TuananhTran1710/Bomber_Man/releases
* Giải nén game vào một thư mục và bật Bomber_Man.exe lên và chơi
# 1. CẤU TRÚC GAME
 ![t](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/menu.png?raw=true)
 
* Ban đầu vào giao diện của game sẽ có 3 mục menu: BẮT ĐẦU, HƯỚNG DẪN và GAME KHÁC.
  - Ấn vào BẮT ĐẦU để chơi game  
  - Ấn vào HƯỚNG DẪN để xem cách chơi
  - Ấn vào GAME KHÁC để thoát game

# 2. HƯỚNG DẪN CÁCH CHƠI
![tt](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/huongdan.png?raw=true)
## 1. Cách di chuyển và sử dụng item
* Game Bomber_Man sử dụng chế độ 2 người chơi.
* Đối với người chơi thứ nhất (P1): Sử dụng các phím W,A,S,D để di chuyển nhân vật kết hợp với phím Spacebar để sử dụng các tính năng của item.
* Đối với người chơi thứ hai (P2): Sử dụng phím mũi tên để di chuyển, kết hợp với phím Enter (ở bàn phím NumPad)

## 2. Giới thiệu về tính năng các item

### I. Đặc điểm của các ô trên bản đồ
| Hình ảnh | Tính năng của ô |
| ------------- |:-------------:|
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/3.png?raw=true)| Ô này là ô cố định, không thể phá  |
|     ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/7.png?raw=true)  | Đây cũng là ô cố định trong map, không thế phá    |
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/2.png?raw=true)     | Đây là ô để xây mép trên và mép dưới của bản đồ, luôn cố định trong map, không thể phá    |
|   ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/4.png?raw=true)                   |             Ô này chứa các item, khi bị phá sẽ sinh ra các item ngẫu nhiên          |
|  ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/5.png?raw=true)            |         Ô này chứa các item, khi bị phá sẽ sinh ra các item ngẫu nhiên     |
|  ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/6.png?raw=true)  |  Ô này chứa các item, khi bị phá sẽ sinh ra các item ngẫu nhiên    |

### II. Tính năng của các item
| Item  | Tính năng |
| ------------- |:-------------:|
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/bom.png?raw=true)    |Sau khi được ấn để đặt, phát nổ sau khoảng 2 giây.<br> Gây hiệu ứng với 4 ô xung quanh     |
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/9.png?raw=true)      | Sau khi nhân vật ăn được item này sẽ sở hữu 2 lần phun lửa gây hiệu ứng trong 1 ô    |
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/12.png?raw=true)      | Sau khi nhân vật ăn được item này sẽ sở hữu 1 lần bắn tên lửa, <br> khi tên lửa va chạm sẽ phát nổ như bom gây hiệu ứng 4 ô xung quanh  |
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/13.png?raw=true) |       Nhân vật sẽ bất tử khi có khiên, khiên mất khi va chạm với vụ nổ hoặc đạn của nhân vật khác |
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/14.png?raw=true)| Nhân vật khi sở hữu súng điện sẽ bắn ra đạn lazer có tầm bắn rất xa và chính xác            |
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/10.png?raw=true)| Súng bắn ra đạn thường với tầm bắn gần|
| ![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/15.png?raw=true)|Khi nhận được item này thì số lần đặt bom liên tiếp sẽ tăng thêm 1|
|![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/11.png?raw=true) | Sau khi đặt, mìn chưa phát nổ ngay, chỉ khi nào ta nhấn thêm một lần nút đặt nữa thì mìn sẽ phát nổ, hiệu ứng nổ giống như bom 

* CHÚ Ý: Nhân vật trong một thời điểm chỉ có thể có một item duy nhất để dùng, khi ăn một item mới thì sẽ được chuyển đổi sang item đó.

# 3. GIỚI THIỆU GAMEPLAY
* Khi vào game, giao diện sẽ như sau với map được sinh ngẫu nhiên nhờ thuật toán DFS

![1](https://github.com/TuananhTran1710/Bomber_Man/blob/main/map1/mappppppp.png?raw=true)
* Vũ khí mặc định của mỗi nhân vật là bom thường, ta sẽ dùng nó đặt vào các ô trống để phá các ô chứa item, sau đó lấy item sử dụng.
* Chú ý: Nếu các vụ nổ trúng nhân vật mà vụ nổ ấy gây ra từ vũ khí của chính nhân vật đó thì só mạng sẽ không được tính cho người chơi nào. Chỉ khi nhân vật này bị kill bởi vũ khí (đạn, vụ nổ) của nhân vật kia thì mới tính số mạng hạ gục
* Chúng ta sẽ chỉ chơi trong thời gian giới hạn là 5 phút. 
* Nếu chưa hết thời gian, người chơi nào hạ gục đối thủ 7 mạng trước sẽ chiến thắng và game kết thúc
* Nếu hết thời gian mà chưa ai đạt được số mạng hạ gục tối đa thì so sánh xem ai hạ gục được đối thủ nhiều hơn sẽ chiến thắng, nếu bằng nhau thì hòa.


# 4. CÁCH TỔ CHỨC FILE .CPP VÀ .H
* BaseObject.h và BaseObject.cpp: quản lý về vấn đề hình ảnh, mỗi một hình ảnh là một kiểu class BaseObject.
* game_map.h và game_map.cpp: quản lý về map (load map và xây dựng map)
* ImpTimer.h và ImpTimer.cpp: quản lý về vấn đề FPS
* MainObject.h và MainObject.cpp: xây dựng nhân vật chính của game.
* BulletObject.h và BulletObject.cpp: quản lý các tính năng của đạn, di chuyển của đạn
* Nobom.h và Nobom.cpp: quản lý hình ảnh vụ nổ
* TextObject quản lý về text trong game
# 5. GHI CHÚ VỀ CÁC SỐ LIỆU TRONG MÃ NGUỒN
* Trong code có những số liệu dùng nhiều khi tính toán. Sau đây là bảng chú thích rõ ý nghĩa của các số liệu đó:
| Số liệu | Ý nghĩa |
|--------------|-------|
| 185 | Vị trí rect.x của ô [1][0] trong bản đồ |
| 185 + 14*45   | Vị trí rect.x của ô [1][14] trên bản đồ |
| 60 | Vị trí rect.y của các ô thuộc dòng 1 trong bản đồ | 
| 45 | Độ cao, rộng của 1 ô trong map |

* CHÚ Ý: Bản đồ như một ma trận 15x15 gồm 15 dòng và 15 cột, mỗi một giá trị [i][j] tương ứng với một ô trên bản đồ
# 6. NGUỒN THAM KHẢO
[Phát Triển Phần Mềm 123A-Z](https://www.youtube.com/@PhatTrienPhanMem123AZ)
* Toàn bộ file : ImpTimer.cpp, ImpTimer.h, BaseObject.h, BaseObject.cpp, TextObject.h, TextObject.cpp, game_map.h
* Một số hình ảnh trong file map1 và một số đoạn code khác sẽ được nói rõ trong video trình bày game

[SDL2_Download](https://github.com/libsdl-org/SDL/releases)
* Các file thư viện SDL2 ở link trên

[Bom IT2](https://gamevui.vn/bom-it2/game)
* Lấy một số hình ảnh item và map

Ngoài ra còn một số hình ảnh khác được copy trên các trang web của google
