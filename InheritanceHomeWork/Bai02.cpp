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
using namespace std;

// Kiểm tra tính hợp lệ vùng
// true / false
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
    friend ostream& operator<<(ostream& out, const Date &D)
    {
        out << "Ngày " << D.ngay << " tháng " << D.thang << " năm " << D.nam << endl;
        
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

// ABSTRACT CLASS SACH
class SACH
{
    private:
    string maSach;
    Date ngayNhap;
    long donGia;
    int soLuong;
    string nhaXuatBan;


    protected:
    // constructor
    SACH(string ms = "Không xác định.", int day = 1, int month = 1, int year = 1970, long dg = 0, int sl = 0, string nxb = "Không xác định.") : maSach(ms), ngayNhap(day, month, year), donGia(dg), soLuong(sl), nhaXuatBan(nxb){};

    public:
    // Nhập thông tin
    virtual void NhapThongTin() = 0;
    virtual void cinOverload(istream& in){ // overload
        // thuộc tính chung
        string ms;
        long dg;
        int sl;
        string nxb;
        cout << "Mã sách: "; in >> ms;
        cout << "Ngày nhập: "; in >> ngayNhap;
        cout << "Đơn giá: "; in >> dg;
        cout << "Số lượng(1 - 300): "; in >> sl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhà xuất bản: "; getline(in, nxb);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        setMaSach(ms);
        setDonGia(dg);
        setSoLuong(sl);
        setNXB(nxb);
    };
    friend istream& operator>>(istream& in, SACH &s)
    {
    s.cinOverload(in);
    return in;
    }

    // Xuất thông tin
    virtual void XuatThongTin() = 0;
    virtual void coutOverload(ostream& out)
    {
        out << "Mã sách: " << maSach << endl;
        out << "Ngày nhập: " << ngayNhap << endl;
        out << "Đơn giá: " << donGia << endl;
        out << "Số lượng: " << soLuong << endl;
        out << "Nhà xuất bản: " << nhaXuatBan << endl;
    };
    friend ostream& operator<<(ostream& out, SACH &s)
    {
        s.coutOverload(out);
        return out;
    }

    // Tính thành tiền
    virtual void tinhThanhTien() = 0;
    // Thành tiền
    virtual long long getThanhTien() = 0;


    // Mã sách
    void setMaSach(string ms)
    {
        maSach = ms;
    }
    string getMaSach() const
    {
        return maSach;
    }

    // Ngày nhập sách
    void setNgayNhap(int day, int month, int year)
    {
        ngayNhap.dateValid(day,month,year);
    };
    Date getNgayNhap()
    {
        return ngayNhap;
    };

    // Đơn giá
    void setDonGia(long dg)
    {
        if(dg < 0)
        {
            throw invalid_argument("Lỗi: Đơn giá không được dưới 0 đồng");
        }
        
        if(dg > 2000000)
        {
            throw invalid_argument("Lỗi: Đơn giá không được vượt quá 2 triệu đồng");
        }

        donGia = dg;
    };
    long getDonGia() const
    {
        return donGia;
    }

    // Số lượng
    void setSoLuong(int sl)
    {
        if(sl < 0 || sl > 300)
        {
            throw invalid_argument("Lỗi: Số lượng không cho phép.");
        }
        soLuong = sl;
    }
    int getSoLuong() const
    {
        return soLuong;
    };

    // Nhà xuất bản
    void setNXB(string nxb)
    {
        nhaXuatBan = nxb;
    }
    string getNXB()
    {
        return nhaXuatBan;
    }

    // destructor
    virtual ~SACH(){};
};
// Khai báo biến static
int Date::currentYear = 2026;



// SÁCH GIÁO KHOA
class GIAOKHOA : public SACH
{
    private:
    string tinhTrang;
    long thanhTien;
    
    public:
    // constructor
    GIAOKHOA(string tt = "Không xác định.") : SACH(), tinhTrang(tt), thanhTien(0){
        tinhThanhTien();
    };

    // tình trạng
    void setTinhTrang(string tt)
    {
        while(tt != "mới" && tt != "cũ" && tt != "MỚI" && tt != "CŨ")
        {
            cout << "Vui lòng nhập lại tình trạng ( chỉ được *mới* hay *cũ* ): ";
            cin >> tt;
        }

        tinhTrang = tt;
    };
    string getTinhTrang() const
    {
        return tinhTrang;
    };

    // Tính thành tiền
    void tinhThanhTien() override
    {
        thanhTien = (tinhTrang == "MỚI" || tinhTrang == "mới") ? (getSoLuong()*getDonGia()) : (getSoLuong()*getDonGia()*50)/100;
    }

    // Thành tiền
    long long getThanhTien() override
    {
        return thanhTien;
    }

    // Nhập thông tin
    void NhapThongTin() override
    {
        string ms;
        int day, month, year;
        long dg;
        int sl;
        string nxb;
        string tt;
        
        cout << "Mã sách: "; cin >> ms;
        cout << "Ngày nhập (ngày tháng năm): "; cin >> day >> month >> year;
        cout << "Đơn giá: "; cin >> dg;
        cout << "Số lượng(1 - 300): "; cin >> sl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Tên nhà xuất bản: "; getline(cin, nxb);
        cout << "Tình trạng sách: "; getline(cin, tt);

        setMaSach(ms);
        setNgayNhap(day,month,year);
        setDonGia(dg);
        setSoLuong(sl);
        setNXB(nxb);
        setTinhTrang(tt);
    };
    // Nhập thông tin - overload operator - overide
    void cinOverload(istream& in) override
    {
        // Tái sử dụng lớp cha
        SACH::cinOverload(in);

        // thuộc tính riêng lớp con
        string tt;
        cout << "Tình trạng sách (mới hoặc cũ): "; cin >> tt;
        setTinhTrang(tt);
    }
    
    // Xuất thông tin 
    void XuatThongTin() override
    {
        cout << "Mã sách: " << getMaSach() << endl;
        cout << "Ngày nhập: " << getNgayNhap() << endl;
        cout << "Đơn giá: " << getDonGia() << "vnd" << endl;
        cout << "Số lượng: " << getSoLuong() << " cuốn" << endl;
        cout << "Nhà xuất bản:  " << getNXB() << endl;
        cout << "----------> Thành tiền: " << getThanhTien() << "vnd" << endl;
    }
    // Xuất thông tin - overload operator - overide
    void coutOverload(ostream& out) override
    {
        // Tái sử dụng từ lớp cha
        SACH::coutOverload(out);

        // thuộc tính riêng lớp con
        out << "Tình trạng: " << tinhTrang << endl;
        out << "----------> Thành tiền: " << thanhTien << "vnd" << endl;

    }
};

class THAMKHAO : public SACH
{
    private:
    static int phanTramThue;
    long long thanhTien;

    public:
    THAMKHAO(int pt = 0) : SACH(), thanhTien(0)
    {
        setPhanTramThue(pt);
    };

    static void setPhanTramThue(int pt)
    {
        if(pt < 0 || pt > 100)
        {
            throw invalid_argument("Lỗi: Phần trăm thuế không hợp lệ.");
        }
        phanTramThue = pt;
    }
    static int getPhanTramThue()
    {
        return phanTramThue;
    }

    // Tính thành tiền
    void tinhThanhTien() override
    {
        thanhTien = getSoLuong()*getDonGia() + (getSoLuong()*getDonGia()*phanTramThue)/100;
    }

    // Thành tiền
    long long getThanhTien() override
    {
        return thanhTien;
    }

    // Nhập thông tin
    void NhapThongTin() override
    {
        string ms;
        int day, month, year;
        long dg;
        int sl;
        string nxb;
        int pt;

        cout << "Mã sách: "; cin >> ms;
        cout << "Ngày nhập (ngày tháng năm): "; cin >> day >> month >> year;
        cout << "Đơn giá: "; cin >> dg;
        cout << "Số lượng(1 - 300): "; cin >> sl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Tên nhà xuất bản: "; getline(cin, nxb);
        cout << "Phần trăm thuế: "; cin >> pt;

        setMaSach(ms);
        setNgayNhap(day,month,year);
        setDonGia(dg);
        setSoLuong(sl);
        setNXB(nxb);
        setPhanTramThue(pt);
    };

    void cinOverload(istream& in) override
    {
        SACH::cinOverload(in);

        int pt;
        cout << "Phần trăm thuế: "; in >> pt;
        setPhanTramThue(pt);
    }

    void XuatThongTin() override
    {
        cout << "Mã sách: " << getMaSach() << endl;
        cout << "Ngày nhập: " << getNgayNhap() << endl;
        cout << "Đơn giá: " << getDonGia() << "vnd" << endl;
        cout << "Số lượng: " << getSoLuong() << " cuốn" << endl;
        cout << "Nhà xuất bản:  " << getNXB() << endl;
        cout << "Phần trăm thuế: " << getPhanTramThue() << "%" << endl;
        cout << "----------> Thành tiền: " << getThanhTien() << "vnd" << endl;
    }

    void coutOverload(ostream& out) override
    {
        SACH::coutOverload(out);
        out << "Phần trăm thuế: " << phanTramThue << "%" << endl;
        out << "----------> Thành tiền: " << thanhTien << "vnd" << endl;
    }
};

int THAMKHAO::phanTramThue = 3;

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    vector<GIAOKHOA> dsGiaoKhoa(3);
    vector<THAMKHAO> dsThamKhao(3);

    cout << "=== Nhap thong tin 3 sach giao khoa ===" << endl;
    for(size_t i = 0; i < 3; ++i)
    {
        cout << "\nSach giao khoa " << (i + 1) << ":" << endl;
        dsGiaoKhoa[i].NhapThongTin();
        dsGiaoKhoa[i].tinhThanhTien();
    }

    cout << "\n=== Nhap thong tin 3 sach tham khao ===" << endl;
    for(size_t i = 0; i < 3; ++i)
    {
        cout << "\nSach tham khao " << (i + 1) << ":" << endl;
        dsThamKhao[i].NhapThongTin();
        dsThamKhao[i].tinhThanhTien();
    }

    long long tongThanhTienGiaoKhoa = 0;
    for(size_t i = 0; i < 3; ++i)
    {
        tongThanhTienGiaoKhoa += dsGiaoKhoa[i].getThanhTien();
    }

    long long tongThanhTienThamKhao = 0;
    long long tongDonGiaThamKhao = 0;
    for(size_t i = 0; i < 3; ++i)
    {
        tongThanhTienThamKhao += dsThamKhao[i].getThanhTien();
        tongDonGiaThamKhao += dsThamKhao[i].getDonGia();
    }

    long long trungBinhDonGiaThamKhao = (tongDonGiaThamKhao + 1) / 3;

    cout << "\n=== Ket qua ===" << endl;
    cout << "Tong thanh tien sach giao khoa: " << tongThanhTienGiaoKhoa << " vnd" << endl;
    cout << "Tong thanh tien sach tham khao: " << tongThanhTienThamKhao << " vnd" << endl;
    cout << "Trung binh cong don gia sach tham khao: " << trungBinhDonGiaThamKhao << " vnd" << endl;


    // Xuất ra các sách giáo khoa của nhà xuất bản K (cho nhập K)
    // đi qua vector sách giáo khoa - getNhaSachBan nào 
    string NXB;
    getline(cin, NXB);
    cout << "Các loại sách giáo khoa của NXB " << NXB << " là: ";
    for(size_t i = 0; i < dsGiaoKhoa.size(); i++)
    {
        if(dsGiaoKhoa[i].getNXB() == NXB)
        {
            cout << dsGiaoKhoa[i].getMaSach() << ", ";
        }
    };
    return 0;
}