// ============================================================
//  Chuong1_TongQuan_NangCao.cpp
//  Noi dung: Kieu du lieu, CTDL, Giai thuat va BigO
// ============================================================
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <chrono> // Thu vien ho tro do thoi gian thuc thi
using namespace std;

// ============================================================
//  BAI 1: Kieu du lieu - Tinh tong chu so cua n
// ============================================================
unsigned short TinhTongChuSo(unsigned int n) {
    unsigned short tong = 0;
    while (n > 0) {
        tong += n % 10;
        n /= 10;
    }
    return tong;
}

// Tinh nang nang cao: Xu ly so sieu lon bang chuoi
unsigned int TinhTongChuSo(const string& soLon) {
    unsigned int tong = 0;
    for (char kyTu : soLon) {
        if (isdigit(kyTu)) {
            tong += kyTu - '0';
        }
    }
    return tong;
}

// ============================================================
//  BAI 2: Minh hoa CTDL - Bang diem Sinh Vien
// ============================================================
#define SOMH 3
#define MAX_SV 100

void XuatBangDiem_2D(float danhSachDiem[][SOMH], int soSinhVien) {
    cout << "\n--- Bang diem (2D array) ---\n";
    for (int i = 0; i < soSinhVien; i++) {
        for (int j = 0; j < SOMH; j++) {
            cout << "  Sinh vien " << i + 1
                 << " hoc mon " << j + 1
                 << " diem: " << danhSachDiem[i][j] << "\n";
        }
    }
}

int TimMonHocDiemCaoNhat(float danhSachDiem[][SOMH], int tongSoMonHoc, int sinhVienCanTim) {
    // Tinh nang nang cao: Kiem tra tinh hop le cua du lieu dau vao
    if (sinhVienCanTim < 1 || sinhVienCanTim > MAX_SV) {
        return -1; // Tra ve -1 neu so thu tu sinh vien khong hop le
    }
    
    int monHocDiemCaoNhat = 0;
    int chiSoSinhVien = sinhVienCanTim - 1; 

    for (int i = 1; i < tongSoMonHoc; i++) {
        if (danhSachDiem[chiSoSinhVien][monHocDiemCaoNhat] < danhSachDiem[chiSoSinhVien][i]) {
            monHocDiemCaoNhat = i;
        }
    }
    return monHocDiemCaoNhat + 1;
}

// ============================================================
//  BAI 3: Do phuc tap BigO - Dem vong lap & Do thoi gian
// ============================================================
void MinhHoaBigO() {
    int N = 500; // Tang N de thay ro do tre cua thuat toan O(N^3)
    long long soBuocLap = 0;

    cout << "\n--- O(N^3): do thoi gian 3 vong lap long nhau ---\n";
    soBuocLap = 0;
    
    // Bat dau bam gio
    auto thoiGianBatDau = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                soBuocLap++;
            }
        }
    }
    
    // Ket thuc bam gio
    auto thoiGianKetThuc = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> thoiGianChay = thoiGianKetThuc - thoiGianBatDau;

    cout << "  N = " << N << ", so buoc: " << soBuocLap << "\n";
    cout << "  Thoi gian thuc thi: " << fixed << setprecision(2) << thoiGianChay.count() << " ms\n";
}

// ============================================================
//  BAI 4: Phuong trinh bac nhat (O(K))
// ============================================================
void GiaiPhuongTrinhBacNhat() {
    double heSoA, heSoB;
    cout << "\n--- Giai phuong trinh bac nhat: ax + b = 0 ---\n";
    cout << "  Nhap he so a: "; cin >> heSoA;
    cout << "  Nhap he so b: "; cin >> heSoB;
    
    if (heSoA == 0) {
        if (heSoB == 0) cout << "  => Phuong trinh co vo so nghiem\n";
        else            cout << "  => Phuong trinh vo nghiem\n";
    } else {
        cout << "  => x = " << -heSoB / heSoA << "\n";
    }
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    cout << "============================================================\n";
    cout << "  CHUONG 1: TONG QUAN VE CTDL VA GIAI THUAT (NANG CAO)\n";
    cout << "============================================================\n";

    // Bai 1
    cout << "\n[BAI 1] Tinh tong chu so\n";
    unsigned int n = 12345;
    cout << "  So int = " << n << " => Tong chu so = " << TinhTongChuSo(n) << "\n";
    string soKhongLo = "987654321987654321987654321";
    cout << "  So chuoi = " << soKhongLo << " => Tong chu so = " << TinhTongChuSo(soKhongLo) << "\n";

    // Bai 2
    cout << "\n[BAI 2] Bang diem sinh vien (CTDL mang 2 chieu)\n";
    float bangDiem[4][SOMH] = {
        {6.0f, 6.5f, 9.0f},
        {7.0f, 8.0f, 5.0f},
        {8.0f, 4.5f, 8.0f},
        {5.0f, 4.0f, 7.0f}
    };
    XuatBangDiem_2D(bangDiem, 4);
    int sinhVienCanKiemTra = 2;
    int ketQuaMon = TimMonHocDiemCaoNhat(bangDiem, SOMH, sinhVienCanKiemTra);
    if (ketQuaMon != -1) {
        cout << "\n  Mon hoc diem cao nhat cua SV thu " << sinhVienCanKiemTra
             << " la mon so: " << ketQuaMon << "\n";
    }

    // Bai 3
    cout << "\n[BAI 3] Minh hoa phan lop BigO thuc te\n";
    MinhHoaBigO();

    // Bai 4
    cout << "\n[BAI 4] Phuong trinh bac nhat (O(K))\n";
    // GiaiPhuongTrinhBacNhat(); // Ban co the bo comment dong nay de thu nhap tu ban phim

    cout << "\n============================================================\n";
    return 0;
}
