/*
 * BAI 1: MANG CO BAN
 * Nhap mang n phan tu. Tinh min, max, trung binh, tong.
 * Khong dung STL.
 */

#include <iostream>
using namespace std;

// --- Cac ham xu ly mang ---

int timMin(int arr[], int n) {
    int min = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] < min) min = arr[i];
    return min;
}

int timMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

long long tinhTong(int arr[], int n) {
    long long tong = 0;
    for (int i = 0; i < n; i++) tong += arr[i];
    return tong;
}

double tinhTrungBinh(int arr[], int n) {
    return (double)tinhTong(arr, n) / n;
}

void inMang(int arr[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " ]" << endl;
}

// --- Ham main ---

int main() {
    int n;
    cout << "=== BAI 1: MANG CO BAN ===" << endl;
    cout << "Nhap so phan tu n: ";
    cin >> n;

    if (n <= 0) {
        cout << "n phai lon hon 0!" << endl;
        return 1;
    }

    // Cap phat mang tren stack (n <= 1000 de an toan)
    int arr[1000];
    cout << "Nhap " << n << " phan tu:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  arr[" << i << "] = ";
        cin >> arr[i];
    }

    cout << "\nMang vua nhap: ";
    inMang(arr, n);
    cout << "----------------------------" << endl;
    cout << "Min       : " << timMin(arr, n)       << endl;
    cout << "Max       : " << timMax(arr, n)       << endl;
    cout << "Tong      : " << tinhTong(arr, n)     << endl;
    cout << "Trung binh: " << tinhTrungBinh(arr, n) << endl;

    return 0;
}

/*
 * BAI 2: MANG 2D
 * Nhan 2 ma tran n×n.
 * Tinh dinh thuc ma tran 3x3.
 * Hien thi dep.
 */

#include <iostream>
#include <iomanip>   // setw
using namespace std;

const int MAXN = 10;

// --- Hien thi ma tran ---
void inMaTran(int a[][MAXN], int n, const char* tenMaTran) {
    cout << tenMaTran << ":" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  |";
        for (int j = 0; j < n; j++)
            cout << setw(5) << a[i][j];
        cout << "  |" << endl;
    }
}

// --- Nhap ma tran ---
void nhapMaTran(int a[][MAXN], int n, const char* ten) {
    cout << "Nhap ma tran " << ten << " (" << n << "x" << n << "):" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cout << "  " << ten << "[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
}

// --- Nhan 2 ma tran n×n => result = a * b ---
void nhanMaTran(int a[][MAXN], int b[][MAXN], int result[][MAXN], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n; k++)
                result[i][j] += a[i][k] * b[k][j];
        }
}

// --- Dinh thuc 3x3 theo quy tac Sarrus ---
int dinhThuc3x3(int a[][MAXN]) {
    return  a[0][0] * (a[1][1]*a[2][2] - a[1][2]*a[2][1])
          - a[0][1] * (a[1][0]*a[2][2] - a[1][2]*a[2][0])
          + a[0][2] * (a[1][0]*a[2][1] - a[1][1]*a[2][0]);
}

// --- Ham main ---
int main() {
    cout << "=== BAI 2: MANG 2D ===" << endl;

    // ---- PHAN 1: Nhan ma tran ----
    cout << "\n--- PHAN 1: NHAN MA TRAN n x n ---" << endl;
    int n;
    cout << "Nhap kich thuoc n (1-" << MAXN << "): ";
    cin >> n;

    if (n < 1 || n > MAXN) {
        cout << "n phai trong khoang [1, " << MAXN << "]!" << endl;
        return 1;
    }

    int A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN];

    nhapMaTran(A, n, "A");
    nhapMaTran(B, n, "B");
    nhanMaTran(A, B, C, n);

    cout << "\nKet qua phep nhan A x B:" << endl;
    cout << string(30, '-') << endl;
    inMaTran(A, n, "  Ma tran A");
    cout << endl;
    inMaTran(B, n, "  Ma tran B");
    cout << "\n  A x B =" << endl;
    inMaTran(C, n, "  Ket qua C");

    // ---- PHAN 2: Dinh thuc 3x3 ----
    cout << "\n--- PHAN 2: DINH THUC MA TRAN 3x3 ---" << endl;
    int D[MAXN][MAXN];
    nhapMaTran(D, 3, "D");
    inMaTran(D, 3, "\n  Ma tran D");
    cout << "  det(D) = " << dinhThuc3x3(D) << endl;

    return 0;
}

/*
 * BAI 3: CON TRO & CAP PHAT DONG
 * Cai dat mang dong tu resize (nhu std::vector don gian).
 * Ho tro: push_back, pop_back, at(i), size(), capacity().
 */

#include <iostream>
#include <stdexcept>   // std::out_of_range
using namespace std;

// ============================================================
//  CLASS MyVector — Mang dong don gian
// ============================================================
class MyVector {
private:
    int*   data;       // con tro vung nho heap
    int    sz;         // so phan tu hien tai
    int    cap;        // suc chua hien tai

    // Noi bo: cap phat lai vung nho gap doi
    void resize(int newCap) {
        int* newData = new int[newCap];          // cap phat vung moi
        for (int i = 0; i < sz; i++)
            newData[i] = data[i];               // copy du lieu cu
        delete[] data;                           // giai phong vung cu
        data = newData;
        cap  = newCap;
        cout << "  [resize] cap do: " << cap << " -> " << newCap << endl;
    }

public:
    // Constructor: cap phat vung nho ban dau
    MyVector(int initCap = 2) : sz(0), cap(initCap) {
        data = new int[cap];
        cout << "  [MyVector] Khoi tao, capacity = " << cap << endl;
    }

    // Destructor: giai phong bo nho
    ~MyVector() {
        delete[] data;
        cout << "  [MyVector] Bo nho da duoc giai phong." << endl;
    }

    // Them phan tu vao cuoi
    void push_back(int val) {
        if (sz == cap)
            resize(cap * 2);           // gap doi khi day
        data[sz++] = val;
    }

    // Xoa phan tu cuoi
    void pop_back() {
        if (sz == 0) {
            cout << "  [pop_back] Mang da rong!" << endl;
            return;
        }
        sz--;
        // Thu hep neu dang dung < 1/4 suc chua (tranh resize lien tuc)
        if (sz > 0 && sz <= cap / 4)
            resize(cap / 2);
    }

    // Truy cap phan tu tai vi tri i (co kiem tra bien)
    int& at(int i) {
        if (i < 0 || i >= sz)
            throw out_of_range("Chi so ngoai pham vi!");
        return data[i];
    }

    // Truy cap chi-doc
    const int& at(int i) const {
        if (i < 0 || i >= sz)
            throw out_of_range("Chi so ngoai pham vi!");
        return data[i];
    }

    int  size()     const { return sz;  }
    int  capacity() const { return cap; }
    bool empty()    const { return sz == 0; }

    // In noi dung mang
    void print() const {
        cout << "  MyVector [size=" << sz << ", cap=" << cap << "]: [ ";
        for (int i = 0; i < sz; i++) {
            cout << data[i];
            if (i < sz - 1) cout << ", ";
        }
        cout << " ]" << endl;
    }
};

// ============================================================
//  Ham main — Demo MyVector
// ============================================================
int main() {
    cout << "=== BAI 3: CON TRO & CAP PHAT DONG ===" << endl;
    cout << "\n--- Tao MyVector capacity ban dau = 2 ---" << endl;

    MyVector v(2);

    // push_back
    cout << "\n--- push_back 6 phan tu ---" << endl;
    for (int i = 1; i <= 6; i++) {
        cout << "Push " << i * 10 << "  => ";
        v.push_back(i * 10);
        v.print();
    }

    // at()
    cout << "\n--- Truy cap phan tu voi at() ---" << endl;
    cout << "  at(0) = " << v.at(0) << endl;
    cout << "  at(3) = " << v.at(3) << endl;

    // Sua gia tri
    cout << "\n--- Sua at(2) = 999 ---" << endl;
    v.at(2) = 999;
    v.print();

    // pop_back
    cout << "\n--- pop_back 4 lan ---" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Pop  => ";
        v.pop_back();
        v.print();
    }

    // out_of_range
    cout << "\n--- Thu truy cap chi so sai ---" << endl;
    try {
        cout << v.at(100) << endl;
    } catch (const out_of_range& e) {
        cout << "  [Ngoai le bat duoc] " << e.what() << endl;
    }

    cout << "\n--- Ket thuc, Destructor se chay ---" << endl;
    // v tu dong bi huy khi ra khoi scope

    return 0;
}

/*
 * BAI 4: DU AN MINI — QUAN LY DIEM SINH VIEN
 * Dung mang dong (tu quan ly bo nho) de luu sinh vien.
 * Chuc nang: Them / Xoa / Sua / Tim kiem / Sap xep / Thong ke / Xuat file.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

// ============================================================
//  Struct SinhVien
// ============================================================
struct SinhVien {
    char mssv[12];   // Ma so sinh vien
    char ten[50];    // Ho va ten
    float diem;      // Diem trung binh
};

// ============================================================
//  Class DanhSachSV — Mang dong tu quan ly
// ============================================================
class DanhSachSV {
private:
    SinhVien* ds;
    int       sz;
    int       cap;

    void moRong() {
        int newCap = (cap == 0) ? 2 : cap * 2;
        SinhVien* newDs = new SinhVien[newCap];
        for (int i = 0; i < sz; i++)
            newDs[i] = ds[i];
        delete[] ds;
        ds  = newDs;
        cap = newCap;
    }

    // Xep loai theo diem
    const char* xepLoai(float d) const {
        if (d >= 9.0f) return "Xuat sac";
        if (d >= 8.0f) return "Gioi";
        if (d >= 7.0f) return "Kha";
        if (d >= 5.0f) return "Trung binh";
        return "Yeu";
    }

public:
    DanhSachSV() : ds(nullptr), sz(0), cap(0) {}

    ~DanhSachSV() { delete[] ds; }

    int soLuong() const { return sz; }

    // ----- THEM SINH VIEN -----
    void them(const char* mssv, const char* ten, float diem) {
        // Kiem tra trung MSSV
        for (int i = 0; i < sz; i++) {
            if (strcmp(ds[i].mssv, mssv) == 0) {
                cout << "  [!] MSSV " << mssv << " da ton tai!" << endl;
                return;
            }
        }
        if (sz == cap) moRong();
        strncpy(ds[sz].mssv, mssv, 11);  ds[sz].mssv[11] = '\0';
        strncpy(ds[sz].ten,  ten,  49);  ds[sz].ten[49]  = '\0';
        ds[sz].diem = diem;
        sz++;
        cout << "  [+] Da them sinh vien: " << ten << endl;
    }

    // ----- XOA SINH VIEN THEO MSSV -----
    bool xoa(const char* mssv) {
        for (int i = 0; i < sz; i++) {
            if (strcmp(ds[i].mssv, mssv) == 0) {
                cout << "  [-] Da xoa: " << ds[i].ten << endl;
                for (int j = i; j < sz - 1; j++)
                    ds[j] = ds[j + 1];
                sz--;
                return true;
            }
        }
        cout << "  [!] Khong tim thay MSSV: " << mssv << endl;
        return false;
    }

    // ----- SUA DIEM SINH VIEN -----
    bool sua(const char* mssv, float diemMoi) {
        for (int i = 0; i < sz; i++) {
            if (strcmp(ds[i].mssv, mssv) == 0) {
                float cu = ds[i].diem;
                ds[i].diem = diemMoi;
                cout << "  [*] Cap nhat diem " << ds[i].ten
                     << ": " << cu << " -> " << diemMoi << endl;
                return true;
            }
        }
        cout << "  [!] Khong tim thay MSSV: " << mssv << endl;
        return false;
    }

    // ----- TIM KIEM THEO TEN (co chua chuoi) -----
    void timTheoTen(const char* chuoi) const {
        cout << "\n  Ket qua tim kiem \"" << chuoi << "\":" << endl;
        bool found = false;
        for (int i = 0; i < sz; i++) {
            // Tim chuoi con thu cong (khong dung strstr de minh bach)
            int lenDs = strlen(ds[i].ten);
            int lenKw = strlen(chuoi);
            for (int j = 0; j <= lenDs - lenKw; j++) {
                bool match = true;
                for (int k = 0; k < lenKw; k++) {
                    // So sanh khong phan biet hoa/thuong
                    char c1 = ds[i].ten[j+k];
                    char c2 = chuoi[k];
                    if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
                    if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
                    if (c1 != c2) { match = false; break; }
                }
                if (match) {
                    inMot(i);
                    found = true;
                    break;
                }
            }
        }
        if (!found) cout << "  Khong tim thay ket qua." << endl;
    }

    // ----- TIM KIEM THEO MSSV -----
    void timTheoMSSV(const char* mssv) const {
        for (int i = 0; i < sz; i++) {
            if (strcmp(ds[i].mssv, mssv) == 0) {
                cout << "\n  Tim thay:" << endl;
                inMot(i);
                return;
            }
        }
        cout << "  [!] Khong tim thay MSSV: " << mssv << endl;
    }

    // ----- SAP XEP BUBBLE SORT THEO DIEM GIAM DAN -----
    void sapXep() {
        for (int i = 0; i < sz - 1; i++)
            for (int j = 0; j < sz - 1 - i; j++)
                if (ds[j].diem < ds[j+1].diem) {
                    SinhVien tmp = ds[j];
                    ds[j]        = ds[j+1];
                    ds[j+1]      = tmp;
                }
        cout << "  [OK] Da sap xep theo diem giam dan." << endl;
    }

    // ----- THONG KE -----
    void thongKe() const {
        if (sz == 0) { cout << "  Danh sach trong!" << endl; return; }
        float tong = 0, maxD = ds[0].diem, minD = ds[0].diem;
        int   idxMax = 0, idxMin = 0;
        for (int i = 0; i < sz; i++) {
            tong += ds[i].diem;
            if (ds[i].diem > maxD) { maxD = ds[i].diem; idxMax = i; }
            if (ds[i].diem < minD) { minD = ds[i].diem; idxMin = i; }
        }
        cout << fixed << setprecision(2);
        cout << "\n  === THONG KE ===" << endl;
        cout << "  Tong so SV    : " << sz << endl;
        cout << "  Diem TB lop   : " << tong / sz << endl;
        cout << "  Diem cao nhat : " << maxD << "  (" << ds[idxMax].ten << " - " << ds[idxMax].mssv << ")" << endl;
        cout << "  Diem thap nhat: " << minD << "  (" << ds[idxMin].ten << " - " << ds[idxMin].mssv << ")" << endl;

        // Phan phoi xep loai
        int xsac=0, gioi=0, kha=0, tb=0, yeu=0;
        for (int i=0; i<sz; i++) {
            float d = ds[i].diem;
            if (d >= 9.0f) xsac++;
            else if (d >= 8.0f) gioi++;
            else if (d >= 7.0f) kha++;
            else if (d >= 5.0f) tb++;
            else yeu++;
        }
        cout << "  Phan loai     : Xuat sac=" << xsac << "  Gioi=" << gioi
             << "  Kha=" << kha << "  TB=" << tb << "  Yeu=" << yeu << endl;
    }

    // ----- IN TOAN BO (dang bang) -----
    void inDanhSach() const {
        if (sz == 0) { cout << "  Danh sach trong!" << endl; return; }
        cout << fixed << setprecision(2);
        cout << "\n  " << string(65, '-') << endl;
        cout << "  " << left  << setw(5) << "STT"
                     << setw(12) << "MSSV"
                     << setw(28) << "Ho va ten"
                     << setw(8)  << "Diem"
                     << "Xep loai" << endl;
        cout << "  " << string(65, '-') << endl;
        for (int i = 0; i < sz; i++) {
            cout << "  " << left  << setw(5)  << (i + 1)
                         << setw(12) << ds[i].mssv
                         << setw(28) << ds[i].ten
                         << setw(8)  << ds[i].diem
                         << xepLoai(ds[i].diem) << endl;
        }
        cout << "  " << string(65, '-') << endl;
    }

    // ----- XUAT FILE TXT -----
    void xuatFile(const char* tenFile) const {
        ofstream f(tenFile);
        if (!f) {
            cout << "  [!] Khong mo duoc file: " << tenFile << endl;
            return;
        }
        f << "=== DANH SACH DIEM SINH VIEN ===" << endl;
        f << left  << setw(5)  << "STT"
               << setw(12) << "MSSV"
               << setw(28) << "Ho va ten"
               << setw(8)  << "Diem"
               << "Xep loai" << endl;
        f << string(65, '-') << endl;
        for (int i = 0; i < sz; i++) {
            f << fixed << setprecision(2)
              << left  << setw(5)  << (i + 1)
              << setw(12) << ds[i].mssv
              << setw(28) << ds[i].ten
              << setw(8)  << ds[i].diem
              << xepLoai(ds[i].diem) << endl;
        }
        f << string(65, '-') << endl;
        // Thong ke cuoi file
        if (sz > 0) {
            float tong = 0;
            for (int i = 0; i < sz; i++) tong += ds[i].diem;
            f << "\nTong so sinh vien: " << sz << endl;
            f << "Diem trung binh  : " << fixed << setprecision(2) << tong / sz << endl;
        }
        f.close();
        cout << "  [OK] Da xuat ra file: " << tenFile << endl;
    }

private:
    // In mot hang sinh vien
    void inMot(int i) const {
        cout << fixed << setprecision(2);
        cout << "  MSSV: " << ds[i].mssv
             << "  | Ten: " << ds[i].ten
             << "  | Diem: " << ds[i].diem
             << "  | " << xepLoai(ds[i].diem) << endl;
    }
};

// ============================================================
//  Menu & giao dien chinh
// ============================================================
void inMenu() {
    cout << "\n========================================" << endl;
    cout << "    QUAN LY DIEM SINH VIEN" << endl;
    cout << "========================================" << endl;
    cout << "  1. Them sinh vien" << endl;
    cout << "  2. Xoa sinh vien" << endl;
    cout << "  3. Sua diem sinh vien" << endl;
    cout << "  4. Xem danh sach" << endl;
    cout << "  5. Tim kiem" << endl;
    cout << "  6. Xep hang lop (sap xep theo diem)" << endl;
    cout << "  7. Thong ke" << endl;
    cout << "  8. Xuat bao cao ra file" << endl;
    cout << "  0. Thoat" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Chon chuc nang: ";
}

// Doc chuoi co khoang trang sau khi dung cin >> truoc do
void docChuoi(char* buf, int maxLen) {
    cin.ignore();
    cin.getline(buf, maxLen);
}

int main() {
    DanhSachSV ds;
    char mssv[12], ten[50];
    float diem;
    int luaChon;

    // Them san du lieu mau de demo
    ds.them("SV001", "Nguyen Van An",   8.5f);
    ds.them("SV002", "Tran Thi Bich",   9.2f);
    ds.them("SV003", "Le Hoang Nam",    6.8f);
    ds.them("SV004", "Pham Minh Duc",   4.5f);
    ds.them("SV005", "Vo Thi Lan",      7.3f);

    do {
        inMenu();
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                cout << "  MSSV     : "; cin >> mssv;
                cout << "  Ho ten   : "; docChuoi(ten, 50);
                cout << "  Diem     : "; cin >> diem;
                if (diem < 0 || diem > 10)
                    cout << "  [!] Diem phai trong khoang [0, 10]!" << endl;
                else
                    ds.them(mssv, ten, diem);
                break;

            case 2:
                cout << "  Nhap MSSV can xoa: "; cin >> mssv;
                ds.xoa(mssv);
                break;

            case 3:
                cout << "  Nhap MSSV can sua: "; cin >> mssv;
                cout << "  Diem moi         : "; cin >> diem;
                ds.sua(mssv, diem);
                break;

            case 4:
                ds.inDanhSach();
                break;

            case 5: {
                int loai;
                cout << "  Tim theo: (1) Ten   (2) MSSV   => ";
                cin >> loai;
                if (loai == 1) {
                    cout << "  Nhap ten (co the nhap mot phan): "; docChuoi(ten, 50);
                    ds.timTheoTen(ten);
                } else {
                    cout << "  Nhap MSSV: "; cin >> mssv;
                    ds.timTheoMSSV(mssv);
                }
                break;
            }

            case 6:
                ds.sapXep();
                ds.inDanhSach();
                break;

            case 7:
                ds.thongKe();
                break;

            case 8:
                ds.xuatFile("diem_sinhvien.txt");
                break;

            case 0:
                cout << "  Tam biet! Hen gap lai." << endl;
                break;

            default:
                cout << "  [!] Lua chon khong hop le!" << endl;
        }
    } while (luaChon != 0);

    return 0;
}
