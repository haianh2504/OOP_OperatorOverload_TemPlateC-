// Mã số sinh viên: 25520093
// Họ và tên: Phan Hải Anh
// Ngày Sinh: 25/04/2007
// Lớp: IT002.Q25
// BTTuan6
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <vector>
using namespace std;
// Hàm xóa khoảng trắng ở đầu chuỗi (Left Trim)
string ltrim(const string &s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    return (start == string::npos) ? "" : s.substr(start);
}
// Hàm xóa khoảng trắng ở cuối chuỗi (Right Trim)
string rtrim(const string &s) {
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}
// Hàm xóa khoảng trắng ở cả hai đầu (Trim)
string trim(const string &s) {
    return rtrim(ltrim(s));
}
// composition DATE
class Date
{
    private:
    int day;
    int month;
    int year;
    public:
    // constructor
    Date(int ngay, int thang, int nam) : day(ngay), month(thang), year(nam)
    {
        if(!isValidDate(ngay, thang, nam))
        {
            throw invalid_argument("Lỗi: ngày tháng năm không hợp lệ.");
        }
    }
    // isValidDate
    static bool isValidDate(int ngay, int thang, int nam)
    {
        // overall
        if(0 >= nam || 0 >= thang || thang > 12 || 0 >= ngay || ngay > 31) return false;
        // detail
        if(thang == 2)
        {
            if(isLeapYear(nam))
            {
                return (1 <= ngay && ngay <= 29) ? true : false;
            }
            return (1 <= ngay && ngay <= 28) ? true : false;
        }
        else if(thang == 1 || thang == 3 || thang == 5 || thang == 7 || thang == 8 || thang == 10 || thang == 12)
        {
            return (1 <= ngay && ngay <= 31) ? true : false;
        }
        return (1 <= ngay && ngay <= 30) ? true : false;
    }
    // isLeapYear
    static bool isLeapYear(int nam)
    {
        return (nam % 400 == 0 || (nam % 4 == 0 && nam % 100 != 0)) ? true : false;
    }
    // Date 
    bool SetDate(int ngay, int thang, int nam)
    {
        if(!isValidDate(ngay, thang, nam)) return false;
        day = ngay;
        month = thang;
        year = nam;
        return true;
    };
    // day
    bool SetDay(int ngay)
    {
        if(!isValidDate(ngay, month, year)) return false;
        day = ngay;
        return true;
    }
    int GetDay()const{return day;}
    // month
    bool SetMonth(int thang)
    {
        if(!isValidDate(day, thang, year)) return false;
        month = thang;
        return true;
    }
    int GetMonth()const{return month;}
    // year
    bool SetYear(int nam)
    {
        if(!isValidDate(day, month, nam)) return false;
        year = nam;
        return true;
    }
    int GetYear()const{return year;}
    // Khoảng cách giữa 1-1-1 tới Date cụ thể ( d/m/y)
    static int YearGap(Date &D)
    {
        // Khai báo
        Date Origin(1,1,1);
        int tongNgay = 0;
        int Ngay;
        // năm 1 -> năm hiện tại
        int year = Origin.GetYear();
        while(year < D.GetYear())
        {
            Ngay = (isLeapYear(year)) ? 366 : 365;
            tongNgay += Ngay;
            year++;
        };
        // Cộng số ngày còn lại từ tháng
        int thang = D.GetMonth();
        while(Origin.GetMonth() < thang)
        {
            if(Origin.GetMonth() == 2){
                if(isLeapYear(D.GetYear())){tongNgay += 29;}
                else tongNgay += 28;
            }
            else if(Origin.GetMonth() == 1 || Origin.GetMonth() == 3 || Origin.GetMonth() == 5 || Origin.GetMonth() == 7 || Origin.GetMonth() == 8 || Origin.GetMonth() == 10 || Origin.GetMonth() == 12)
            {
                tongNgay += 31;
            }
            else tongNgay += 30;
            //
            Origin.SetMonth(Origin.GetMonth() + 1);
        }
        // Cộng ngày còn lại
        tongNgay += D.GetDay();
        // trả về
        return tongNgay;
    }
    // Khoảng cách giữa hai DATES ( ngày )
    static int YearGapBetween(Date &D1, Date &D2)
    {
        // Quy ước: D1 là currentDate
        int tongNgayD1 = YearGap(D1);
        int tongNgayD2 = YearGap(D2);
        if(tongNgayD1 < tongNgayD2) return -abs(tongNgayD1 - tongNgayD2);
        return abs(tongNgayD1 - tongNgayD2);

    }
    // destructor
    ~Date(){};
};
// ABSTRACT CLASS
class NhanVien
{
    protected:
    string HoTen = "Không xác định";
    Date ngaySinh;
    long long luong = 0;
    public:
    // constructor
    NhanVien(const string &ho_ten, const Date &ngay_sinh) : HoTen(ho_ten), ngaySinh(ngay_sinh){};
    // Ngày sinh
    Date GetNgaySinh()const{return ngaySinh;}
    // Họ tên 
    bool isValidHoTen(string ho_ten)
    {
        string newHoTen = trim(ho_ten);
        if(newHoTen.empty())return false;
        for(int i = 0; i < newHoTen.length(); i++)
        {
            if(newHoTen[i] >= '0' && newHoTen[i] <= '9') return false;
            if(newHoTen[i] == '~' || newHoTen[i] == '!' || newHoTen[i] == '@' || newHoTen[i] == '#' || newHoTen[i] == '$' || newHoTen[i] == '%' || newHoTen[i] == '^' || newHoTen[i] == '&' || newHoTen[i] == '*' || newHoTen[i] == '(' || newHoTen[i] == ')' || newHoTen[i] == '-' || newHoTen[i] == '+' || newHoTen[i] == '=' || newHoTen[i] == '{' || newHoTen[i] == '}' || newHoTen[i] == '[' || newHoTen[i] == ']' || newHoTen[i] == '|' || newHoTen[i] == '\\' || newHoTen[i] == ':' || newHoTen[i] == ';' || newHoTen[i] == '"' || newHoTen[i] == '\'' || newHoTen[i] == '<' || newHoTen[i] == '>' || newHoTen[i] == ',' || newHoTen[i] == '.' || newHoTen[i] == '?' || newHoTen[i] == '/') return false;    
        }
        return true;
    }
    bool SetHoTen(string ho_ten)
    {
        if(isValidHoTen(ho_ten))
        {
            HoTen = trim(ho_ten);
            return true;
        }
        return false;
    };
    string GetHoTen()const{return HoTen;}
    // pure virtual function
    // Tính lương
    virtual void TinhLuong() = 0;
    // Get lương
    virtual long long GetLuong()const = 0;
    // Nhập thông tin
    virtual void nhapThongTin() = 0;
    // Xuất thông tin
    virtual void xuatThongTin() = 0;
    // Destructor
    virtual ~NhanVien() = 0;
};
// SẢN XUẤT
class SanXuat : public NhanVien
{
    private:
    long long luongCanBan = 0;
    int soSanPham = 0;
    int donGiaSP = 0;
    // static
    // Lương căn bản
    static const long long MIN_LuongCanBan = 5000000;
    static const long long MAX_LuongCanBan = 8000000;
    // Số sản phẩm
    static const int MIN_SoSanPham = 0;
    static const int MAX_SoSanPham = 100;
    // Đơn giá sản phẩm
    static const int MIN_DonGiaSP = 50000;
    static const int MAX_DonGiaSP = 2000000;
    // Hàm kiểm tra logic
    static bool isValidInfo(long long luong_CanBan, int so_SanPham, int donGia_SanPham)
    {
        if(luong_CanBan < MIN_LuongCanBan || luong_CanBan > MAX_LuongCanBan) return false;
        if(so_SanPham < MIN_SoSanPham || so_SanPham > MAX_SoSanPham) return false;
        if(donGia_SanPham < MIN_DonGiaSP || donGia_SanPham > MAX_DonGiaSP) return false;
        return true;
    }
    public:
    // constructor
    SanXuat(const string &ho_ten,const Date &ngay_sinh, long long luong_canBan, int so_SanPham, int donGia_SanPham) : NhanVien(ho_ten,ngay_sinh), luongCanBan(luong_canBan), soSanPham(so_SanPham), donGiaSP(donGia_SanPham){
        // kiểm tra logic ở đây
        if(!isValidInfo(luong_canBan, so_SanPham, donGia_SanPham))
        {
            throw invalid_argument("Lỗi: thông tin không hợp lệ.");
        }
        // Tính lương
        TinhLuong();
    }
    // Lương căn bản
    bool SetLuongCanBan(long long luong_canBan)
    {
        if(MIN_LuongCanBan <= luong_canBan && luong_canBan <= MAX_LuongCanBan) 
        {
            luongCanBan = luong_canBan;
            TinhLuong();
            return true;
        }
        return false;
    }
    long long GetLuongCanBan()const{return luongCanBan;}
    // Số sản phẩm
    bool SetSoSanPham(int so_SanPham)
    {
        if(MIN_SoSanPham <= so_SanPham && so_SanPham <= MAX_SoSanPham) 
        {
            soSanPham = so_SanPham;
            TinhLuong();
            return true;
        }
        return false;
    }
    int GetSoSanPham()const{return soSanPham;}
    // Đơn giá sản phẩm
    bool SetDonGiaSP(int donGia_SanPham)
    {
        if(MIN_DonGiaSP <= donGia_SanPham && donGia_SanPham <= MAX_DonGiaSP) 
        {
            donGiaSP = donGia_SanPham;
            TinhLuong();
            return true;
        }
        return false;
    }
    int GetDonGiaSP()const{return donGiaSP;}
    // Tính Lương
    void TinhLuong()override
    {
        luong = luongCanBan + soSanPham*donGiaSP;
    }
    long long GetLuong()const override{
        if(luongCanBan == 0) throw runtime_error("Lỗi: Lương chưa cập nhật");
        else return luong;
    }
    // Nhập thông tin
    void nhapThongTin()override
    {
        string ho_ten;
        int ngay, thang, nam;
        long long luong_canBan;
        int so_sanPham;
        int donGia_sanPham;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Họ tên: "; getline(cin, ho_ten);
        cout << "Ngày tháng năm sinh: " << endl;
        cout << "Ngày: "; cin >> ngay;
        cout << "Tháng: "; cin >> thang;
        cout << "Năm: "; cin >> nam;
        cout << "Số sản phẩm làm được: "; cin >> so_sanPham;
        cout << "Đơn giá 1 sản phẩm: "; cin >> donGia_sanPham;
        // kiểm tra tính hợp lệ
        if(!isValidHoTen(ho_ten) || !ngaySinh.isValidDate(ngay, thang, nam) || !isValidInfo(luong_canBan, so_sanPham, donGia_sanPham))
        {
            throw invalid_argument("Lỗi: thông tin không hợp lệ.");
        }
        // gán giá trị
        SetHoTen(ho_ten);
        ngaySinh.SetDate(ngay, thang, nam);
        SetSoSanPham(so_sanPham);
        SetDonGiaSP(donGia_sanPham);
        // Tính lương
        TinhLuong();
    };
    // Xuất thông tin
    void xuatThongTin()override
    {
        cout << "Họ tên: " << GetHoTen() << endl;
        cout << "Ngày tháng năm sinh: " << ngaySinh.GetDay() << "/" << ngaySinh.GetMonth() << "/" << ngaySinh.GetYear() << endl;
        cout << "Số sản phẩm làm được: " << GetSoSanPham() << endl;
        cout << "Đơn giá 1 sản phẩm: " << GetDonGiaSP() << endl;
        cout << "Lương: " << GetLuong() << endl;
    };

    ~SanXuat(){};
    // destructor
};
// VĂN PHÒNG
class VanPhong : public NhanVien
{
    private:
    int soNgayLamViec = 0;
    int luongNgay = 0;
    // static
    // Số ngày làm việc
    static const int MIN_SoNgayLamViec = 0;
    static const int MAX_SoNgayLamViec = 31;
    // Lương ngày
    static const int MIN_LuongNgay = 0;
    static const int MAX_LuongNgay = 1000000;
    // Hàm kiểm tra logic
    static bool isValidInfo(int so_NgayLamViec, int luong_Ngay)
    {
        if(so_NgayLamViec < MIN_SoNgayLamViec || so_NgayLamViec > MAX_SoNgayLamViec) return false;
        if(luong_Ngay < MIN_LuongNgay || luong_Ngay > MAX_LuongNgay) return false;
        return true;
    }
    public:
    // constructor
    VanPhong(const string &ho_ten,const Date &ngay_sinh, int so_NgayLamViec, int luong_Ngay) : NhanVien(ho_ten,ngay_sinh), soNgayLamViec(so_NgayLamViec), luongNgay(luong_Ngay){
        // kiểm tra logic ở đây
        if(!isValidInfo(so_NgayLamViec, luong_Ngay))
        {
            throw invalid_argument("Lỗi: thông tin không hợp lệ.");
        }
        // Tính lương
        TinhLuong();
    }
    // Số ngày làm việc
    bool SetSoNgayLamViec(int so_NgayLamViec)
    {
        if(MIN_SoNgayLamViec <= so_NgayLamViec && so_NgayLamViec <= MAX_SoNgayLamViec) 
        {
            soNgayLamViec = so_NgayLamViec;
            TinhLuong();
            return true;
        }
        return false;
    }
    int GetSoNgayLamViec()const{return soNgayLamViec;}
    // Lương ngày
    bool SetLuongNgay(int luong_Ngay)
    {
        if(MIN_LuongNgay <= luong_Ngay && luong_Ngay <= MAX_LuongNgay) 
        {
            luongNgay = luong_Ngay;
            TinhLuong();
            return true;
        }
        return false;
    }
    int GetLuongNgay()const{return luongNgay;}
    // Tính Lương
    void TinhLuong()override
    {
        luong = soNgayLamViec*luongNgay;
    }
    long long GetLuong()const override{
        if(luongNgay == 0) throw runtime_error("Lỗi: Lương chưa cập nhật");
        else return luong;
    }
    // Nhập thông tin
    void nhapThongTin()override
    {
        string ho_ten;
        int ngay, thang, nam;
        int so_NgayLamViec;
        int luong_Ngay;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Họ tên: "; getline(cin, ho_ten);
        cout << "Ngày tháng năm sinh: " << endl;
        cout << "Ngày: "; cin >> ngay;
        cout << "Tháng: "; cin >> thang;
        cout << "Năm: "; cin >> nam;
        cout << "Số ngày làm việc: "; cin >> so_NgayLamViec;
        cout << "Lương ngày: "; cin >> luong_Ngay;
        // kiểm tra tính hợp lệ
        if(!isValidHoTen(ho_ten) || !ngaySinh.isValidDate(ngay, thang, nam) || !isValidInfo(so_NgayLamViec, luong_Ngay))
        {
            throw invalid_argument("Lỗi: thông tin không hợp lệ.");
        }
        // gán giá trị
        SetHoTen(ho_ten);
        ngaySinh.SetDate(ngay, thang, nam);
        SetSoNgayLamViec(so_NgayLamViec);
        SetLuongNgay(luong_Ngay);
        // Tính lương
        TinhLuong();
    }
    // Xuất thông tin
    void xuatThongTin()override
    {
        cout << "Họ tên: " << GetHoTen() << endl;
        cout << "Ngày tháng năm sinh: " << ngaySinh.GetDay() << "/" << ngaySinh.GetMonth() << "/" << ngaySinh.GetYear() << endl;
        cout << "Số ngày làm việc: " << GetSoNgayLamViec() << endl;
        cout << "Lương ngày: " << GetLuongNgay() << endl;
        cout << "Lương: " << GetLuong() << endl;
    }
    // destructor
    ~VanPhong(){};
};

int main()
{
    vector<NhanVien*> danhSachNhanVienVanPhong;
    vector<NhanVien*> danhSachNhanVienSanXuat;
    int soNhanVienVanPhong, soNhanVienSanXuat;
    cout << "Nhập số nhân viên văn phòng: "; cin >> soNhanVienVanPhong;
    for(size_t i = 0; i < soNhanVienVanPhong; i++)
    {
        cout << "Nhập thông tin nhân viên văn phòng thứ " << i + 1 << ":" << endl;
        NhanVien* nvvp = new VanPhong("Không xác định", Date(1,1,2000),0,0);
        try
        {
            nvvp->nhapThongTin();
            danhSachNhanVienVanPhong.push_back(nvvp);
        }
        catch(const exception& e)
        {
            cerr << e.what() << endl;
            delete nvvp; // Giải phóng bộ nhớ nếu có lỗi
            i--;
        }
    }
    cout << "Nhập số nhân viên sản xuất: "; cin >> soNhanVienSanXuat;
    for(size_t i = 0; i < soNhanVienSanXuat; i++)
    {
        cout << "Nhập thông tin nhân viên sản xuất thứ " << i + 1 << ":" << endl;
        NhanVien* nvsp = new SanXuat("Không xác định", Date(1,1,2000),0,0,0);
        try
        {
            nvsp->nhapThongTin();
            danhSachNhanVienSanXuat.push_back(nvsp);
        }
        catch(const exception& e)
        {
            cerr << e.what() << endl;
            delete nvsp; // Giải phóng bộ nhớ nếu có lỗi
            i--;
        }
    };
    // Xuất thông tin nhân viên văn phòng
    cout << "\nThông tin nhân viên văn phòng:" << endl;
    for(size_t i = 0; i < danhSachNhanVienVanPhong.size(); i++)
    {
        cout << "Nhân viên văn phòng thứ " << i + 1 << ":" << endl;
        danhSachNhanVienVanPhong[i]->xuatThongTin();
    }
    // Xuất thông tin nhân viên sản xuất
    cout << "\nThông tin nhân viên sản xuất:" << endl;
    for(size_t i = 0; i < danhSachNhanVienSanXuat.size(); i++)
    {
        cout << "Nhân viên sản xuất thứ " << i + 1 << ":" << endl;
        danhSachNhanVienSanXuat[i]->xuatThongTin();
    }
    // tính tổng lương phải trả cho nhân viên văn phòng
    long long tongLuongVanPhong = 0;
    for(size_t i = 0; i < danhSachNhanVienVanPhong.size(); i++)
    {
        tongLuongVanPhong += danhSachNhanVienVanPhong[i]->GetLuong();
    }
    cout << "\nTổng lương phải trả cho nhân viên văn phòng: " << tongLuongVanPhong << endl;
    // Nhân viên sản xuất có lương thấp nhất
    NhanVien* nvLuongThapNhat = danhSachNhanVienSanXuat[0];
    for(size_t i = 0; i < danhSachNhanVienSanXuat.size(); i++)
    {
        if(danhSachNhanVienSanXuat[i]->GetLuong() < nvLuongThapNhat->GetLuong())
        {
            nvLuongThapNhat = danhSachNhanVienSanXuat[i];
        }
    }
    cout << "\nNhân viên sản xuất có lương thấp nhất:" << endl;
    nvLuongThapNhat->xuatThongTin();
    // Nhân viên văn phòng cao tuổi nhất
    Date currDate(4,5,2026);
    // guard clause
    if(danhSachNhanVienVanPhong.empty())
    {
        cout << "\nKhông có nhân viên văn phòng nào để xác định tuổi." << endl;
        return 0;
    }
    // NẾU CÓ NHÂN VIÊN VĂN PHÒNG, TIẾP TỤC XÁC ĐỊNH NHÂN VIÊN CAO TUỔI NHẤT
    NhanVien* nvCaoTuoiNhat = danhSachNhanVienVanPhong[0];
    for(size_t i = 1; i < danhSachNhanVienVanPhong.size(); i++)
    {
        Date theOldest = nvCaoTuoiNhat->GetNgaySinh();
        int oldestAge = theOldest.YearGapBetween(theOldest, currDate);
        Date current = danhSachNhanVienVanPhong[i]->GetNgaySinh();
        int currentAge = current.YearGapBetween(current, currDate);
        if(currentAge > oldestAge)
        {
            nvCaoTuoiNhat = danhSachNhanVienVanPhong[i];
        }
    }
    cout << "\nNhân viên văn phòng cao tuổi nhất:" << endl;
    nvCaoTuoiNhat->xuatThongTin();
    // giải phóng bộ nhớ
    for(int i = 0; i < soNhanVienVanPhong; i++)
    {
        delete danhSachNhanVienVanPhong[i];
    }
    danhSachNhanVienVanPhong.clear();
    for(int i = 0; i < soNhanVienSanXuat; i++)
    {
        delete danhSachNhanVienSanXuat[i];
    }
    danhSachNhanVienSanXuat.clear();

    return 0;
}
