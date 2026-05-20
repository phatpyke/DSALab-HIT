MSSV: 2125110168 Phạm Tấn Phát
# Tuần 1: Tổng Quan C++ & Big-O — Bài tập

## 🎯 Mục tiêu tuần này
Hiểu Big-O, phân tích độ phức tạp, ôn tập C++ cơ bản.

---

### Bài 1: Phân tích Big-O ⭐
Xác định Big-O của 10 đoạn code C++ cho trước. Giải thích tại sao.
1.Truy cập mảng
int getElement(int arr[], int i) {
    return arr[i];
}
Tại sao O(1)? Chỉ thực hiện một thao tác duy nhất: đọc địa chỉ bộ nhớ tại vị trí i. Không phụ thuộc vào kích thước mảng n.
2. Tìm kiếm nhị phân
int binarySearch(int arr[], int n, int x) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}
Tại sao O(log n)? Mỗi vòng lặp chia đôi không gian tìm kiếm. Với n = 1.000.000, chỉ cần ~20 bước.
3. Duyệt tuyến tính
int findMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx) mx = arr[i];
    return mx;
}
Tại sao O(n)? Vòng lặp chạy đúng n-1 lần — mỗi phần tử được xét một lần duy nhất.
4. Merge sort
void mergeSort(int arr[], int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid+1, r);
    merge(arr, l, mid, r); // O(n)
}
Tại sao O(n log n)? Cây đệ quy có log n tầng; mỗi tầng thực hiện tổng cộng n thao tác gộp → n × log n.
5. Bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}
Tại sao O(n²)? Vòng ngoài chạy n lần, vòng trong chạy ~n lần → tổng cộng ~n²/2 phép so sánh.
6. Nhân ma trận
void matMul(int A[][N], int B[][N],
            int C[][N], int n) {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        C[i][j] = 0;
        for (int k = 0; k < n; k++)
          C[i][j] += A[i][k] * B[k][j];
      }
}
Tại sao O(n³)? Ba vòng lặp lồng nhau, mỗi vòng chạy n lần → n × n × n = n³ phép tính.
7. Fibonacci đệ quy
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
Tại sao O(2ⁿ)? Mỗi lời gọi sinh ra 2 lời gọi con → cây đệ quy có ~2ⁿ nút. Tính fib(50) mà không nhớ hóa là thảm họa!
8. Hai mảng độc lập
void printBoth(int a[], int n,
               int b[], int m) {
    for (int i = 0; i < n; i++)
        cout << a[i];
    for (int j = 0; j < m; j++)
        cout << b[j];
}
Tại sao O(n + m)? Hai vòng lặp chạy tuần tự (không lồng nhau) nên cộng số bước: n + m. Nếu m ≈ n thì cũng là O(n).
9. In tất cả cặp
void printPairs(int arr[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            cout << arr[i] << "," 
                 << arr[j] << "\n";
}
Tại sao O(n²)? Số cặp (i, j) với i < j là n(n−1)/2 ≈ n²/2. Hằng số 1/2 bị bỏ qua → O(n²).
10. Đếm bit
int countBits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // xóa bit 1 thấp nhất
        count++;
    }
    return count;
}
Tại sao O(log n)? Số bit của n là ⌊log₂n⌋ + 1. Mỗi vòng lặp xóa đúng một bit 1 → số vòng lặp ≤ số bit = O(log n).
### Bài 2: Đo thời gian thực tế ⭐⭐
Dùng `chrono` đo thời gian chạy của O(n), O(n²), O(log n) với n = 1.000 → 100.000. In bảng kết quả.

╔════════════╦══════════════════╦══════════════════╦══════════════════╗
║     n      ║   O(log n)       ║     O(n)         ║     O(n²)        ║
╠════════════╬══════════════════╬══════════════════╬══════════════════╣
║      1.000 ║        18.30 μs  ║        17.40 μs  ║        24.17 ms  ║
║      5.000 ║        59.90 μs  ║        87.40 μs  ║       712.91 ms  ║
║     10.000 ║       109.10 μs  ║       163.50 μs  ║      2856.70 ms  ║
║     25.000 ║       237.10 μs  ║       430.30 μs  ║     17680.48 ms  ║
║     50.000 ║       493.40 μs  ║       805.70 μs  ║     70155.93 ms  ║
║     75.000 ║       704.00 μs  ║      1313.40 μs  ║    157344.62 ms  ║
║    100.000 ║      1080.50 μs  ║      1834.60 μs  ║    279348.20 ms  ║ 
╚════════════╩══════════════════╩══════════════════╩══════════════════╝

📊 Phân tích:
  • O(log n): Tăng rất chậm - gần như không đổi khi n tăng
  • O(n):     Tăng tuyến tính - gấp đôi n thì thời gian gấp đôi
  • O(n²):    Tăng bậc hai - gấp đôi n thì thời gian tăng gấp 4 lần

💡 Lưu ý: Với n > 10.000, thời gian O(n²) được ước tính để tránh chạy quá lâu.

### Bài 3: Tối ưu hàm ⭐⭐
Cho 3 hàm O(n²) — tối ưu xuống O(n) hoặc O(n log n). Chứng minh bằng cách đo thời gian.

Các hàm O(n²) thường gặp và cách tối ưu:
Hàm 1: Tìm cặp số có tổng bằng target
Phiên bản O(n²):

python
def find_pair_bruteforce(arr, target):
    n = len(arr)
    for i in range(n):
        for j in range(i+1, n):
            if arr[i] + arr[j] == target:
                return (arr[i], arr[j])
    return None
Phiên bản tối ưu O(n):

python
def find_pair_optimized(arr, target):
    seen = set()
    for num in arr:
        complement = target - num
        if complement in seen:
            return (complement, num)
        seen.add(num)
    return None
Hàm 2: Tìm phần tử trùng lặp đầu tiên
Phiên bản O(n²):

python
def first_duplicate_bruteforce(arr):
    n = len(arr)
    min_index = n
    for i in range(n):
        for j in range(i+1, n):
            if arr[i] == arr[j]:
                min_index = min(min_index, j)
    return arr[min_index] if min_index < n else None
Phiên bản tối ưu O(n):

python
def first_duplicate_optimized(arr):
    seen = {}
    for i, num in enumerate(arr):
        if num in seen:
            return num
        seen[num] = i
    return None
Hàm 3: Tìm dãy con tăng dài nhất (LIS)
Phiên bản O(n²):

python
def lis_bruteforce(arr):
    n = len(arr)
    dp = [1] * n
    for i in range(n):
        for j in range(i):
            if arr[i] > arr[j]:
                dp[i] = max(dp[i], dp[j] + 1)
    return max(dp) if arr else 0
Phiên bản tối ưu O(n log n):

python
import bisect

def lis_optimized(arr):
    if not arr:
        return 0
    tails = []
    for num in arr:
        pos = bisect.bisect_left(tails, num)
        if pos == len(tails):
            tails.append(num)
        else:
            tails[pos] = num
    return len(tails)
Code đo thời gian và so sánh:
python
import time
import random
import matplotlib.pyplot as plt
import numpy as np

def measure_time(func, *args, num_trials=5):
    """Đo thời gian thực thi trung bình"""
    times = []
    for _ in range(num_trials):
        start = time.perf_counter()
        func(*args)
        end = time.perf_counter()
        times.append(end - start)
    return np.mean(times)

def test_pair_sum():
    """Test hàm tìm cặp số có tổng bằng target"""
    sizes = [100, 500, 1000, 2000, 5000, 10000]
    times_brute = []
    times_opt = []
    
    for n in sizes:
        arr = list(range(n))
        target = n - 1 + (n - 2)  # Đảm bảo có cặp cuối cùng
        
        # Đo phiên bản brute force (chỉ test với size nhỏ)
        if n <= 2000:
            t_brute = measure_time(find_pair_bruteforce, arr, target)
            times_brute.append(t_brute)
        else:
            times_brute.append(None)
        
        # Đo phiên bản tối ưu
        t_opt = measure_time(find_pair_optimized, arr, target)
        times_opt.append(t_opt)
    
    return sizes, times_brute, times_opt

def test_duplicate():
    """Test hàm tìm phần tử trùng lặp đầu tiên"""
    sizes = [100, 500, 1000, 2000, 5000, 10000]
    times_brute = []
    times_opt = []
    
    for n in sizes:
        # Tạo mảng có duplicate ở cuối để worst case
        arr = list(range(n-1)) + [n-2]
        
        # Đo phiên bản brute force
        if n <= 2000:
            t_brute = measure_time(first_duplicate_bruteforce, arr)
            times_brute.append(t_brute)
        else:
            times_brute.append(None)
        
        # Đo phiên bản tối ưu
        t_opt = measure_time(first_duplicate_optimized, arr)
        times_opt.append(t_opt)
    
    return sizes, times_brute, times_opt

def test_lis():
    """Test hàm tìm dãy con tăng dài nhất"""
    sizes = [100, 500, 1000, 2000, 5000, 10000]
    times_brute = []
    times_opt = []
    
    for n in sizes:
        arr = list(range(n))  # Dãy đã sắp xếp (best case)
        
        # Đo phiên bản brute force
        if n <= 2000:
            t_brute = measure_time(lis_bruteforce, arr)
            times_brute.append(t_brute)
        else:
            times_brute.append(None)
        
        # Đo phiên bản tối ưu
        t_opt = measure_time(lis_optimized, arr)
        times_opt.append(t_opt)
    
    return sizes, times_brute, times_opt

def plot_results():
    """Vẽ biểu đồ so sánh"""
    fig, axes = plt.subplots(1, 3, figsize=(18, 5))
    
    # Test 1: Pair Sum
    sizes1, brute1, opt1 = test_pair_sum()
    ax = axes[0]
    ax.plot(sizes1[:len(brute1)], brute1, 'r-o', label='O(n²) Brute Force')
    ax.plot(sizes1, opt1, 'b-o', label='O(n) Optimized')
    ax.set_xlabel('Input Size (n)')
    ax.set_ylabel('Time (seconds)')
    ax.set_title('Pair Sum Performance')
    ax.legend()
    ax.grid(True)
    
    # Test 2: First Duplicate
    sizes2, brute2, opt2 = test_duplicate()
    ax = axes[1]
    ax.plot(sizes2[:len(brute2)], brute2, 'r-o', label='O(n²) Brute Force')
    ax.plot(sizes2, opt2, 'b-o', label='O(n) Optimized')
    ax.set_xlabel('Input Size (n)')
    ax.set_ylabel('Time (seconds)')
    ax.set_title('First Duplicate Performance')
    ax.legend()
    ax.grid(True)
    
    # Test 3: LIS
    sizes3, brute3, opt3 = test_lis()
    ax = axes[2]
    ax.plot(sizes3[:len(brute3)], brute3, 'r-o', label='O(n²) DP')
    ax.plot(sizes3, opt3, 'b-o', label='O(n log n) Optimized')
    ax.set_xlabel('Input Size (n)')
    ax.set_ylabel('Time (seconds)')
    ax.set_title('LIS Performance')
    ax.legend()
    ax.grid(True)
    
    plt.tight_layout()
    plt.show()

def print_comparison_table():
    """In bảng so sánh chi tiết"""
    print("\n=== PAIR SUM ===")
    print(f"{'Size':<10} {'Brute Force':<15} {'Optimized':<15} {'Speedup':<10}")
    print("-" * 50)
    
    sizes, brute, opt = test_pair_sum()
    for i in range(len(sizes)):
        if brute[i] and opt[i]:
            speedup = brute[i] / opt[i] if opt[i] > 0 else float('inf')
            print(f"{sizes[i]:<10} {brute[i]:.6f}s{'':8} {opt[i]:.6f}s{'':8} {speedup:.1f}x")
    
    print("\n=== FIRST DUPLICATE ===")
    print(f"{'Size':<10} {'Brute Force':<15} {'Optimized':<15} {'Speedup':<10}")
    print("-" * 50)
    
    sizes, brute, opt = test_duplicate()
    for i in range(len(sizes)):
        if brute[i] and opt[i]:
            speedup = brute[i] / opt[i] if opt[i] > 0 else float('inf')
            print(f"{sizes[i]:<10} {brute[i]:.6f}s{'':8} {opt[i]:.6f}s{'':8} {speedup:.1f}x")
    
    print("\n=== LONGEST INCREASING SUBSEQUENCE ===")
    print(f"{'Size':<10} {'O(n²) DP':<15} {'O(n log n)':<15} {'Speedup':<10}")
    print("-" * 50)
    
    sizes, brute, opt = test_lis()
    for i in range(len(sizes)):
        if brute[i] and opt[i]:
            speedup = brute[i] / opt[i] if opt[i] > 0 else float('inf')
            print(f"{sizes[i]:<10} {brute[i]:.6f}s{'':8} {opt[i]:.6f}s{'':8} {speedup:.1f}x")

# Chạy chương trình
if __name__ == "__main__":
    print_comparison_table()
    plot_results()
Phân tích kết quả:
1. Độ phức tạp lý thuyết:
Brute Force: O(n²) - Thời gian tăng gấp 4 lần khi input tăng gấp đôi

Optimized: O(n) hoặc O(n log n) - Thời gian tăng tuyến tính hoặc log-linear

2. Kết quả thực nghiệm (dự kiến):
text
PAIR SUM:
Size 1000: Brute Force ~0.05s, Optimized ~0.0001s → Speedup: 500x
Size 2000: Brute Force ~0.2s,  Optimized ~0.0002s → Speedup: 1000x

LIS:
Size 1000: O(n²) ~0.08s,    O(n log n) ~0.0005s → Speedup: 160x
Size 2000: O(n²) ~0.32s,    O(n log n) ~0.001s  → Speedup: 320x
3. Chứng minh qua thực nghiệm:
Độ dốc của đường cong: Phiên bản brute force có dạng parabol (đặc trưng của O(n²))

Tỷ lệ speedup: Tăng tuyến tính với n, chứng tỏ độ phức tạp đã giảm thành công

Khả năng mở rộng: Phiên bản optimized xử lý được input 10,000+ phần tử trong khi brute force không thể
### Bài 4: 🔥 Dự Án Mini — Big-O Benchmark Tool ⭐⭐⭐
> **Cảm hứng:** [algorithm-visualizer.org](https://algorithm-visualizer.org)

Viết chương trình **BenchmarkTool** hiển thị bảng so sánh tốc độ các thuật toán:
```
╔══════════════╦══════════╦══════════╦══════════╗
║   Thuật toán ║  n=1000  ║  n=10000 ║ n=100000 ║
╠══════════════╬══════════╬══════════╬══════════╣
║    O(1)      ║  0.001ms ║  0.001ms ║  0.001ms ║
║    O(log n)  ║  0.003ms ║  0.004ms ║  0.005ms ║
║    O(n)      ║  0.12ms  ║  1.2ms   ║  12ms    ║
║    O(n²)     ║  8ms     ║  800ms   ║  80000ms ║
╚══════════════╩══════════╩══════════╩══════════╝
```

**Yêu cầu:** dùng `std::chrono`, hiển thị bảng căn chỉnh đẹp, xuất ra file `benchmark.txt`.

---
📁 Tham khảo: `Chuong1_TongQuan/Chuong1_TongQuan.cpp`
