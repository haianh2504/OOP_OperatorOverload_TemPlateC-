// Mã số sinh viên: 25520093
// Họ và tên: Phan Hải Anh
// Ngày Sinh: 25/04/2007
// Lớp: IT002.Q25
// BTTuan4

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <numeric>
using namespace std;

template <typename T>
class PhanSo
{
    private:
    T tuSo;
    T mauSo;
    
    // Hàm rút gọn tối ưu
    void RutGon() {
        if (tuSo == 0) {
            mauSo = 1; // đưa về dạng chuẩn 0/1
            return;
        }

        // Tìm UCLN của giá trị tuyệt đối
        T common = gcd(std::abs(tuSo), std::abs(mauSo));

        tuSo /= common;
        mauSo /= common;

        // Chuẩn hóa dấu: Luôn để dấu ở tử số hoặc số dương
        if (mauSo < 0) {
            tuSo = -tuSo;
            mauSo = -mauSo;
        }
    };


    public:
    // constructor
    PhanSo(T tuso = 0, T mauso = 1) : tuSo(tuso)
    {
        if(mauso != 0)
        {
            mauSo = mauso;
            RutGon();
        }
        else
        {
            throw invalid_argument("Error: Mau so phai khac 0!");
            // xu ly loi
        }
    };
    
    // setter
    void setPhanSo(T tuso, T mauso)
    {
        tuSo = tuso;
        if(mauso != 0)
        {
            mauSo = mauso;
            RutGon();
        }
        else{
            throw invalid_argument("Error: Mau so phai khac 0!");
        }
    }
    // getter
    T getTuSo()
    {
        return tuSo;
    }

    T getMauSo()
    {
        return mauSo;
    }

    double giaTri()
    {
        return static_cast<double>(tuSo) / mauSo;
    }


    // operator overloading

    // phép cộng: ( phân số + phân số ) hay (phân số + một số) ( do bên trái là đối tượng phân số)
    PhanSo operator+(const PhanSo &ps2)
    {
        return PhanSo<T>(tuSo*(ps2.mauSo) + (ps2.tuSo)*mauSo, mauSo*(ps2.mauSo));
    }
    
    // Phép trừ: ( phân số - phân số ) hay (phân số - một số) ( do bên trái là đối tượng phân số)
    PhanSo operator-(const PhanSo &ps2)
    {
        return PhanSo<T>(tuSo*(ps2.mauSo) - (ps2.tuSo)*mauSo, mauSo*(ps2.mauSo));
    }
    
    // Phép nhân: ( phân số với phân số ) _ (phân số với số)
    PhanSo operator*(const PhanSo &ps2)
    {
        return PhanSo<T>(tuSo*(ps2.tuSo), mauSo*(ps2.mauSo));
    }

    // Phép chia:
    PhanSo operator/(const PhanSo &ps2)
    {
        return PhanSo<T>(tuSo*(ps2.mauSo), mauSo*(ps2.tuSo));
    }
    // Phép bằng:
    bool operator==(const PhanSo &ps2) const 
    {
        if(tuSo == ps2.tuSo && mauSo == ps2.mauSo) return true;
        return false;
    }
    // Phép lớn hơn hoặc bằng
    bool operator>=(const PhanSo &ps2) const
    {
        if(giaTri() >= ps2.giaTri()) return true;
        // else
        return false;
    }
    // Phép lớn hơn
    bool operator>(const PhanSo &ps2) const
    {
        if(giaTri() > ps2.giaTri()) return true;
        // else
        return false;
    }
    // Phép nhỏ hơn
    bool operator<(const PhanSo &ps2) const
    {
        if(giaTri() < ps2.giaTri()) return true;
        // else
        return false;
    }
    // Phép nhỏ hơn hoặc bằng
    bool operator<=(const PhanSo &ps2) const
    {
        if(giaTri() <= ps2.giaTri()) return true;
        // else
        return false;
    }
    // Phép khác nhau
    bool operator!=(const PhanSo &ps2) const
    {
        if(tuSo != ps2.tuSo || mauSo != ps2.mauSo) return true;
        return false;
    }

    // Hiển thị phân số - truyền thống
    void display() const
    {
        if(mauSo == 1)
        {
            cout << tuSo << endl;
        }
        else
        {
            cout << tuSo << "/" << mauSo << endl;
        }
    }
    // khai báo Hiển thị phân số overload
    friend ostream& operator<<(ostream& out, const PhanSo<T> &ps2);
    friend istream& operator>>(istream& in, PhanSo<T> &ps);
};

// Hiển thị phân số - overload 
template <typename T>
ostream& operator<<(ostream& out,const PhanSo<T> &ps2)
    {
        if(ps2.mauSo == 1)
        {
            out << ps2.tuSo;
        }
        else
        {
            out << ps2.tuSo << "/" << ps2.mauSo;
        }
        // trả lại công cụ
        return out;
    }
// Nhập phân số - overload
template <typename T>
istream& operator>>(istream& in, PhanSo<T> &ps)
    {
       T tu, mau;
       in >> tu >> mau;
       // checking 
       if(mau != 0)
       {
        ps.tuSo = tu;
        ps.mauSo = mau;
       }
       else
       {
        throw invalid_argument("Error: Mau so phai khac 0!");
       }
       // trả lại công cụ
       return in;
    }

int main()
{
    // testing code
    
}