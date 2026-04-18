// Mã số sinh viên: 25520093
// Họ và tên: Phan Hải Anh
// Ngày Sinh: 25/04/2007
// Lớp: IT002.Q25
// BTTuan5
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

// 1.Công ty du lịch X có nhu cầu quản lý thông tin các chuyến xe. 
// Hiện tại công ty có 2 loại chuyến xe:
// -Chuyến xe nội thành có các thông tin sau: Mã số chuyến, Họ tên tài xế, số xe, số tuyến, số km đi được, doanh thu.
// -Chuyến xe ngoại thành có các thông tin sau: Mã số chuyến, Họ tên tài xế, số xe, nơi đến, số ngày đi được, doanh thu.
// Áp dụng tính kế thừa, cài đặt các lớp cho phép thực hiện các chức năng sau:
// -Nhập thông tin chuyến xe nội thành
// -Nhập thông tin chuyến xe ngoại thành
// -Xuất thông tin chuyến xe nội thành
// -Xuất thông tin chuyến xe ngoại thành
// Viết chương trình minh họa, cho phép nhập mỗi loại 2 chuyến xe. Xuất tổng doanh thu cho tất cả các chuyến xe và tổng doanh thu của từng loại chuyến xe.


// ABSTRACT CLASS CHUYEN XE
class CHUYENXE
{
    private:
    string maSo;
    string taiXe;
    string soXe;
    
    public:
    // constructor
    CHUYENXE(string ms = "Không xác định.", string tx = "Không xác định.", string sx = "Không xác định." ) : maSo(ms), taiXe(tx), soXe(sx){};
    
    // Mã số chuyến
    void setMaSoChuyen(string maSoChuyen)
    {
        // logic kiểm tra
        // gán
        maSo = maSoChuyen;
    };
    string getMaSoChuyen() const
    {
        return maSo;
    }
    
    // Tài xế
    void setTaiXe(string tenTaiXe)
    {
        // logic kiểm tra
        // gán
        taiXe = tenTaiXe;
    }
    string getTaiXe() const
    {
        return taiXe;
    }
    
    // số xe
    void setSoXe(string bienSoXe)
    {
        // logic kiểm tra
        // gán
        soXe = bienSoXe;
    }
    string getSoXe() const
    {
        return soXe;
    }

    // Nhập thông tin.
    virtual void nhapThongTin() = 0;

    // Xuất thông tin.
    virtual void xuatThongTin() = 0;

    // Tính doanh thu
    virtual void tinhDoanhThu() = 0;

    // Xuất doanh thu
    virtual long long getDoanhThu() = 0;

    // destructor
    virtual ~CHUYENXE() = 0;

};

CHUYENXE::~CHUYENXE() {}

// XE NỘI THÀNH
class NOITHANH : public CHUYENXE
{
    private:
    int soTuyen;
    int Km;
    long long doanhThu;
    static int donGiaMoiKm;

    public:
    // constructor
    NOITHANH(int st = 0, int km = 0, long long dt = 0) : CHUYENXE(), soTuyen(st), Km(km), doanhThu(dt){};

    // Số Tuyến
    void setSoTuyen(int st)
    {
        // logic kiểm tra
        // gán
        soTuyen = st;
    }
    int getSoTuyen() const{
        return soTuyen;
    }

    // Số km đi được
    void setKM(int km)
    {
        // logic kiểm tra
        // gán
        Km = km;
    }
    int getKM()const{
        return Km;
    }

    // Đơn giá mỗi 1 km
    static void setDonGiaMotKm(int newNumber)
    {
        // check logic...
        
        // gán
        donGiaMoiKm = newNumber;
    };

    // Tính doanh Thu = số KM x đơn giá mỗi KM
    void tinhDoanhThu() override
    {
        doanhThu = Km * donGiaMoiKm;
    }
    // Doanh Thu
    long long getDoanhThu() override 
    {
        return doanhThu;
    }

    // Nhập thông tin
    void nhapThongTin() override
    {
        string ms;
        string tx;
        string sx;
        int st;
        int km;

        // input
        cout << "Mã số chuyến: "; cin >> ms;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Tên tài xế: "; getline(cin, tx);
        cout << "Biển số xe: "; cin >> sx;
        cout << "Số tuyến: "; cin >> st;
        cout << "Số kilomet đi được: "; cin >> km;

        // kiểm tra và gán
        setMaSoChuyen(ms);
        setTaiXe(tx);
        setSoXe(sx);
        setSoTuyen(st);
        setKM(km);
    };
    
    // Xuất thông tin
    void xuatThongTin() override
    {
        cout << "Mã số chuyến: " << getMaSoChuyen() << endl;
        cout << "Tên tài xế: " << getTaiXe() << endl;
        cout << "Biển số xe: " << getSoXe() << endl;
        cout << "Số tuyến: " << getSoTuyen() << endl;
        cout << "Số kilomet đi được: " << getKM() << endl;
        cout << "-------> Doanh Thu trong tháng: " << getDoanhThu() << endl;
    }
};

// XE NGOẠI THÀNH
class NGOAITHANH : public CHUYENXE
{
    private:
    string noiDen;
    int soNgay;
    static int donGiaMotNgay;
    long long doanhThu;

    public:
    // constructor
    NGOAITHANH(string nd = "Không xác định.", int sn = 0) : CHUYENXE(), noiDen(nd), soNgay(sn){};

    // Nơi đến
    void setNoiDen(string nd)
    {
        // logic kiểm tra
        // gán
        noiDen = nd;
    }
    string getNoiDen() const
    {
        return noiDen;
    }

    // Số ngày đi được
    void setSoNgay(int sn)
    {
        // logic kiểm tra
        // gán
        soNgay = sn;
    }
    int getSoNgay() const
    {
        return soNgay;
    }

    // đơn giá 1 ngày đi
    static void setDonGiaMotNgay(int newNumber)
    {
        // logic kiểm tra
        // gán
        donGiaMotNgay = newNumber;
    };

    // tính Doanh Thu = số ngày * đơn giá 1 ngày
    void tinhDoanhThu() override
    {
        doanhThu = soNgay * donGiaMotNgay;
    }
    
    // Doanh thu
    long long getDoanhThu() override
    {
        return doanhThu;
    }

    // Nhập thông tin
    void nhapThongTin() override
    {
        string ms;
        string tx;
        string sx;
        string nd;
        int sn;

        // input
        cout << "Mã số chuyến: "; cin >> ms;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Tên tài xế: "; getline(cin, tx);
        cout << "Biển số xe: "; cin >> sx;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nơi đến: "; getline(cin, nd);
        cout << "Số ngày đi được: "; cin >> sn;

        // kiểm tra và gán
        setMaSoChuyen(ms);
        setTaiXe(tx);
        setSoXe(sx);
        setNoiDen(nd);
        setSoNgay(sn);
    };

    // Xuất thông tin
    void xuatThongTin() override
    {
        cout << "Mã số chuyến: " << getMaSoChuyen() << endl;
        cout << "Tên tài xế: " << getTaiXe() << endl;
        cout << "Biển số xe: " << getSoXe() << endl;
        cout << "Nơi đến: " << getNoiDen() << endl;
        cout << "Số ngày đi được: " << getSoNgay() << endl;
        cout << "-------> Doanh Thu trong tháng: " << getDoanhThu() << endl;
    }
};

// Hàm tính tổng doanh thu của chuyến NỘI THÀNH
long long tongDoanhThuNoiThanh(const vector<CHUYENXE*> &NoiThanh)
{
    long long tongDoanhThu = 0;
    for(size_t i = 0; i < NoiThanh.size(); i++)
    {
        tongDoanhThu += NoiThanh[i]->getDoanhThu();
    };
    return tongDoanhThu;
}

// hàm tính tổng doanh thu của chuyến NGOẠI THÀNH
long long tongDoanhThuNgoaiThanh(const vector<CHUYENXE*> &NgoaiThanh)
{
    long long tongDoanhThu = 0;
    for(size_t i = 0; i < NgoaiThanh.size(); i++)
    {
        tongDoanhThu += NgoaiThanh[i]->getDoanhThu();
    };
    return tongDoanhThu;
};

// Hàm tính tổng doanh thu của cả hai loại chuyến
long long tongDoanhThu(const vector<CHUYENXE*> &NoiThanh, const vector<CHUYENXE*> &NgoaiThanh)
{
    return tongDoanhThuNoiThanh(NoiThanh) + tongDoanhThuNgoaiThanh(NgoaiThanh);
}

// Khởi tạo giá trị cho các biến static
int NOITHANH::donGiaMoiKm = 0;
int NGOAITHANH::donGiaMotNgay = 0;

int main()
{
    // Hiển thị tiếng việt ở console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    NOITHANH::setDonGiaMotKm(10000);
    NGOAITHANH::setDonGiaMotNgay(500000);

    vector<CHUYENXE*> NoiThanh;
    vector<CHUYENXE*> NgoaiThanh;

    int xeNoiThanh = 0;
    int xeNgoaiThanh = 0;

    if(cin >> xeNoiThanh && xeNoiThanh > 0){
        // Nhập nội thành
        for(int i = 0; i < xeNoiThanh; i++)
        {
            cout << "Xe nội thành số " << i + 1 << endl;
            CHUYENXE* noiThanh = new NOITHANH();
            noiThanh->nhapThongTin();
            NoiThanh.push_back(noiThanh);
        }
    }
    
    if(cin >> xeNgoaiThanh && xeNgoaiThanh > 0){
        // Nhập ngoại thành
        for(int i = 0; i < xeNgoaiThanh; i++)
        {
            cout << "Xe ngoại thành số " << i + 1 << endl;
            CHUYENXE* ngoaiThanh = new NGOAITHANH();
            ngoaiThanh->nhapThongTin();
            NgoaiThanh.push_back(ngoaiThanh);
        }
    };
    
    // tính doanh thu cho từng chuyến xe
    for(size_t i = 0; i < NoiThanh.size(); i++)
    {
        NoiThanh[i]->tinhDoanhThu();
    };
    for(size_t i = 0; i < NgoaiThanh.size(); i++)
    {
        NgoaiThanh[i]->tinhDoanhThu();
    }
    // In doanh thu
    cout << "Tổng doanh thu cho tất cả các chuyến xe: " << tongDoanhThu(NoiThanh, NgoaiThanh) << "vnd" << endl;
    cout << "Tổng doanh thu của chuyến nội thành: " << tongDoanhThuNoiThanh(NoiThanh) << "vnd" << endl;
    cout << "Tổng doanh thu của chuyến ngoại thành: " << tongDoanhThuNgoaiThanh(NgoaiThanh) << "vnd" << endl;

    // nhớ delete
    for(size_t i = 0; i < NoiThanh.size(); i++)
    {
        delete NoiThanh[i];
    };
    NoiThanh.clear();
    for(size_t i = 0; i < NgoaiThanh.size(); i++)
    {
        delete NgoaiThanh[i];
    };
    NgoaiThanh.clear();
};