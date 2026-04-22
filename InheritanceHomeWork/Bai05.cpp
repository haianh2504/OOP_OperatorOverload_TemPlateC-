// Mã số sinh viên: 25520093
// Họ và tên: Phan Hải Anh
// Ngày Sinh: 25/04/2007
// Lớp: IT002.Q25
// BTTuan5

#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <string>
#include <limits>
#include <windows.h>
#include <iomanip>
using namespace std;


// COMPOSITION
// Ngày tháng năm sinh
template<typename T>
bool isValid(T value, T start, T end)
{
    if(value >= start && value <= end)
    {
        return true;
    }
    // 
    return false;
}

// composition Date
class Date
{
    private:
    int ngay;
    int thang;
    int nam;
    static int currentYear;

    public:
    // constructor
    Date(int day = 1, int month = 1, int year = 1970) : ngay(day), thang(month), nam(year){
        // logic kiểm tra
        dateValid(day, month, year);
    }; 

    // Hàm kiểm tra tính đúng đắn của dữ liệu
    void dateValid(int day, int month, int year)
    {
        // Kiểm tra cả 3 dữ liệu tổng quát
        if(isValid(day, 1, 31) && isValid(month, 1, 12) && isValid(year, 1970, 2026))
        {
            int ngayToiDa;
            // kiểm tra bước 2
            if(month == 2)
            {
                ngayToiDa = (namNhuan(year)) ? 29 : 28;
                if(isValid(day, 1, ngayToiDa))
                {
                    ngay = day;
                    thang = month;
                    nam = year;
                    return;
                }
                throw invalid_argument("Lỗi: Ngày không hợp lệ.");
            }
            else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
            {
                ngayToiDa = 31;
                if(isValid(day, 1, ngayToiDa))
                {
                    ngay = day;
                    thang = month;
                    nam = year;
                    return;
                }
                throw invalid_argument("Lỗi: Ngày không hợp lệ.");
            }
            else
            {
                ngayToiDa = 30;
                if(isValid(day, 1, ngayToiDa))
                {
                    ngay = day;
                    thang = month;
                    nam = year;
                    return;
                }
                throw invalid_argument("Lỗi: Ngày không hợp lệ.");
            }
        }
        else{
            throw invalid_argument("Lỗi: Thông tin ngày tháng năm không hợp lệ.");
        }
    }
    // Năm nhuận
    bool namNhuan(int year)
    {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? true : false;  
    };
    // display - truyền thống
    void dateDisplay()
    {
        cout << "Ngày " << ngay << " tháng " << thang << " năm " << nam << endl;
    }
    // display - overload
    friend ostream& operator<<(ostream& out, Date &D)
    {
        out << "Ngày " << D.ngay << " tháng " << D.thang << " năm " << D.nam;
        return out;
    }

    // Nhập thông tin - overload
    friend istream& operator>>(istream& in, Date &D)
    {
        int day, month, year;
        cout << "Ngày: "; in >> day;
        cout << "Tháng: "; in >> month;
        cout << "Năm: "; in >> year;

        // kiểm tra tính hợp lệ
        D.dateValid(day, month, year);

        return in;

    }
};

// NHÂN VIÊN - ABSTRACT CLASS
class NHANVIEN
{
    protected:
    string hoTen = "Không xác định";
    Date ngaySinh;

    public:
    // constructor
    NHANVIEN(string hoten, Date &ns) : hoTen(hoten), ngaySinh(ns){};
    // DEFAULT constructor
    NHANVIEN(){};
    // Nhập thông tin
    virtual void nhapThongTin(){
        string hoten;
        int day,month,year;
        cout << "Họ và tên: "; getline(cin, hoten);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ngày tháng năm sinh: "; cin >> day >> month >> year;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Xuất thông tin
    virtual void xuatThongTin(){
        cout << "Họ và tên: " << hoTen << endl;
        cout << "Ngày tháng năm sinh: "; ngaySinh.dateDisplay(); cout << endl;
    }
    // Họ tên
    void setHoTen(string newName)
    {
        hoTen = newName;
    };
    string getHoTen()
    {
        return hoTen;
    };
    // Ngày sinh
    void setNgaySinh(int day, int month, int year)
    {
        ngaySinh.dateValid(day, month, year);
        // có cần phải try catch ở đây luôn không
    }
    Date getNgaySinh()
    {
        return ngaySinh;
    }
    // tính lương
    virtual void tinhLuong() = 0;
    // get lương
    virtual long long getLuong() = 0;
    // destructor
    virtual ~NHANVIEN(){};
};

// NHÂN VIÊN SẢN XUẤT
class SANXUAT : public NHANVIEN
{
    private:
    long long luongCanBan = 0;
    int soSanPham = 0;
    static long donGiaSanPham;
    long long tongLuong = -1;

    public:
    // constructor
    SANXUAT(string &hoten, Date &ns, long long lcb, int ssp) : NHANVIEN(hoten, ns),luongCanBan(lcb), soSanPham(ssp)
    {
        // check logic
        duLieuHopLe(lcb, ssp);
        // tính lương
        tinhLuong();
    };
    // DEFAULT CONSTRUCTOR
    SANXUAT(){};
    // hàm logic xét tính hợp lệ của dữ liệu
    void duLieuHopLe(long long lcb, int ssp)
    {
        if((5000000 <= lcb && lcb <= 6000000) && (0 <= ssp && ssp <= 200) ) // 5 triệu -> 6 triệu vnd / 1 -> 200 sản phẩm tối đa trong thời gian cố định
        {
            luongCanBan = lcb;
            soSanPham = ssp;
        }
        else
        {
            if(lcb < 5000000 || lcb > 6000000)
            {
                throw invalid_argument("Lỗi: Dữ liệu nhân viên không hợp lệ. ( !lương cơ bản )");
            }
            
            if(ssp < 0 || ssp > 100)
            {
                throw invalid_argument("Lỗi: Dữ liệu nhân viên không hợp lệ. ( !số sản phẩm )");
            }
           
        }
    }
    // Đơn giá 1 sản phẩm ( chung )
    static void setDonGiaSanPham(int newNumber)
    {
        if(5000 <= newNumber && newNumber <= 10000)
        {
            donGiaSanPham = newNumber;
        }
        else
        {
            cout << "Cập nhật đơn giá sản phẩm không thành công." << endl;
            return;
        }
    };
    // Lương căn bản
    bool setLuongCanBan(long long lcb)
    {
        if((5000000 <= lcb && lcb <= 6000000)) // 5 triệu -> 6 triệu vnd
        {
            luongCanBan = lcb;
            return true;
        }
        else
        {
            cout << "Lỗi: Cập nhật lương căn bản không thành công ( chỉ được giao động 5 triệu -> 6 triệu )" << endl;
            return false;
        }
    }
    long long getLuongCanBan()
    {
        return luongCanBan;
    }
    // Số sản phẩm
    bool setSoSanPham(int ssp)
    {
        if(0 <= ssp && ssp <= 200) // 1 -> 200 sản phẩm tối đa trong thời gian cố định
        {
            soSanPham = ssp;
            return true;
        }
        else
        {
         cout << "Lỗi: Cập nhật số sản phẩm không thành công ( chỉ được giao động 0 -> 200 sản phẩm tối đa )" << endl;   
         return false;
        }
    }
    int getSoSanPham()
    {
        return soSanPham;
    }
    // Lương bổng
    void tinhLuong() override
    {
        tongLuong = luongCanBan + soSanPham*donGiaSanPham;
    }
    long long getLuong() override
    {
        if(tongLuong != -1) return tongLuong;
        return 0;
    }
    // Nhập thông tin
    void nhapThongTin() override
    {
        cout << "===== Nhân Viên SẢN XUẤT ==" << endl;
        NHANVIEN::nhapThongTin();
        long long lcb;
        int ssp;
        cout << "Lương căn bản: "; cin >> lcb;
        cout << "Số sản phẩm đóng góp: "; cin >> ssp;
        // kiểm tra tính đúng đắn dữ liệu
        if(setLuongCanBan(lcb) && setSoSanPham(ssp))
        {
            // tính lại lương
            tinhLuong();
        };
    };
    // Xuất thông tin
    void xuatThongTin() override
    {
        NHANVIEN::xuatThongTin();
        cout << "Lương căn bản: " << luongCanBan << endl;
        cout << "Số sản phẩm đóng góp được: " << soSanPham << endl;
        cout << "Đơn giá mỗi sản phẩm: " << donGiaSanPham << endl;
        cout << "---> Lương nhận được: " << tongLuong << endl;
    };

};
// khởi tạo giá trị cho đơn giá 1 sản phẩm
long SANXUAT::donGiaSanPham = 5000;

class VANPHONG : public NHANVIEN
{
    private:
    int soNgayLamViec = 0;
    static int donGiaMotNgayLamViec;
    long long tongLuong;

    public:
    // constructor
    VANPHONG(string &hoten, Date &ns, int snlv) : NHANVIEN(hoten, ns), soNgayLamViec(snlv){
        duLieuHopLe(snlv);
        tinhLuong(); 
    }
    // DEFAULT CONSTRUCTOR
    VANPHONG(){};
    // hàm logic xét tính hợp lệ của dữ liệu ( dành cho constructor )
    void duLieuHopLe(int snlv)
    {
        if(1 <= snlv && snlv <= 31)
        {
            soNgayLamViec = snlv;
        }
        else
        {
            throw invalid_argument("Lỗi: Dữ liệu nhân viên không hợp lệ. ( số ngày làm việc phải từ 0 -> 31 ngày )");
        }
    }
    // Công đi làm 1 ngày ( chung )
    static void setDonGiaSanPham(int newNumber)
    {
        if(100000 <= newNumber && newNumber <= 400000)
        {
            donGiaMotNgayLamViec = newNumber;
        }
        else
        {
            cout << "Lỗi: Cập nhật lương 1 ngày làm việc không thành công.( chỉ từ 100000 -> 400000/ ngày)" << endl;
        }
    };
    // Số ngày làm việc
    bool setSoNgayLamViec(int snlv)
    {
        if(1 <= snlv && snlv <= 31)
        {
            soNgayLamViec = snlv;
            return true;
        }
        cout << "Lỗi: Cập nhật số ngày làm việc không thành công ( từ 1 -> 31 ngày tối đa )" << endl; 
        return false;
    }
    int getSoNgayLamViec()
    {
        return soNgayLamViec;
    }
    // Lương bổng
    void tinhLuong() override
    {
        tongLuong = static_cast<long long>(donGiaMotNgayLamViec)*soNgayLamViec;
    }
    long long getLuong() override
    {
        if(tongLuong == -1)
        {
            return 0;
        }
        return tongLuong;
    }
    // Nhập thông tin
    void nhapThongTin() override
    {
        cout << "===== Nhân Viên VĂN PHÒNG ==" << endl;
        NHANVIEN::nhapThongTin();
        long long snlv;
        cout << "Số ngày làm việc: "; cin >> snlv;
        // kiểm tra tính đúng đắn dữ liệu
        if(setSoNgayLamViec(snlv))
        {
            // tính lại lương
            tinhLuong();
        };
    };
    // Xuất thông tin
    void xuatThongTin() override
    {
        NHANVIEN::xuatThongTin();
        cout << "Số ngày làm việc: " << soNgayLamViec << endl;
        cout << "Lương 1 ngày làm việc: " << donGiaMotNgayLamViec << endl;
        cout << "---> Lương nhận được: " << tongLuong << endl;
    }

};
// Khởi tạo lương 1 ngày di làm cho nhân viên văn phòng
int VANPHONG::donGiaMotNgayLamViec = 100000; 

int main()
{
    // hỗ trợ in,nhập ra tiếng việt
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    vector<NHANVIEN*> SanXuat;
    vector<NHANVIEN*> VanPhong;

    // NHÂN VIÊN SẢN XUẤT - NHẬP
    int sxSize;
    cout << "Số lượng nhân viên sản xuất: "; cin >> sxSize;
    if(sxSize > 0)
    {
        cout << "=== Nhân viên sản xuất ===" << endl;
        for(int i = 0; i < sxSize; i++)
        {
            NHANVIEN* nvsx = new SANXUAT();
            cout << "Nhân viên " << i + 1 << ":" << endl;
            nvsx->nhapThongTin();
            SanXuat.push_back(nvsx);
        };
    }
    else
    {
        cout << "Số lượng nhân viên không hợp lệ." << endl;
    }

    // NHÂN VIÊN VĂN PHÒNG - NHẬP
    int vpSize;
    cout << "Số lượng nhân viên văn phòng: "; cin >> vpSize;
    if(sxSize > 0)
    {
        cout << "=== Nhân viên văn phòng ===" << endl;
        for(int i = 0; i < vpSize; i++)
        {
            NHANVIEN* nvvp = new VANPHONG();
            cout << "Nhân viên " << i + 1 << ":" << endl;
            nvvp->nhapThongTin();
            VanPhong.push_back(nvvp);
        };
    }
    else
    {
        cout << "Số lượng nhân viên không hợp lệ." << endl;
    }

    // XUẤT THÔNG TIN DANH SÁCH CÁC NHÂN VIÊN
    cout << "=== DANH SÁCH nhân viên sản xuất ===" << endl;
    for(int i = 0; i < sxSize; i++)
    {
        cout << "Nhân viên " << i + 1 << ": " << endl;
        SanXuat[i]->xuatThongTin();
    };

    cout << "=== DANH SÁCH nhân viên văn phòng ===" << endl;
    for(int i = 0; i < vpSize; i++)
    {
        cout << "Nhân viên " << i + 1 << ": " << endl;
        VanPhong[i]->xuatThongTin();
    };

    // TÍNH TỔNG LƯƠNG MÀ CÔNG TY PHẢI CHI TRẢ
    long long tongluongctychitra = 0;
    for(int i = 0; i < sxSize; i++)
    {
        tongluongctychitra += SanXuat[i]->getLuong();
    };
    for(int i = 0; i < vpSize; i++)
    {
        tongluongctychitra += VanPhong[i]->getLuong();
    };
    // Hiển thị tổng lương
    if(tongluongctychitra <= 1000000)
    {
        cout << tongluongctychitra << endl;
    }
    else
    {
        long double tongluongrutgon = tongluongctychitra/1000000.0L;
        cout << fixed << setprecision(2) << tongluongrutgon << endl;
    }
    // delete hai danh sách
    



}

