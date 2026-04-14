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

    // phép cộng: ( phân số + phân số ) hay (phân số + một số ) hay (một số + phân số) 
       // Hàm thành viên sẽ mặc định bên trái là "chính", bên phải là "phụ" - khách
       // Sử dụng hàm friend để đối xử với hai tham chiếu công bằng (cả hai đều là khách) / để truy cập vào tuSo, mauSo;
    friend PhanSo operator+(const PhanSo &ps1, const PhanSo &ps2)
    {
        return PhanSo<T>((ps1.tuSo)*(ps2.mauSo) + (ps2.tuSo)*(ps1.mauSo), (ps1.mauSo)*(ps2.mauSo));
    }
    
    // Phép trừ: ( phân số - phân số ) hay (phân số - một số) hay (một số - phân số)
    friend PhanSo operator-(const PhanSo &ps1,const PhanSo &ps2)
    {
        return PhanSo<T>((ps1.tuSo)*(ps2.mauSo) - (ps2.tuSo)*(ps1.mauSo), (ps1.mauSo)*(ps2.mauSo));
    }
    
    // Phép nhân: ( phân số với phân số ) _ (phân số với số)
    friend PhanSo operator*(const PhanSo &ps1, const PhanSo &ps2)
    {
        return PhanSo<T>((ps1.tuSo)*(ps2.tuSo), (ps1.mauSo)*(ps2.mauSo));
    }

    // Phép chia:
    friend PhanSo operator/(const PhanSo &ps1, const PhanSo &ps2)
    {
        return PhanSo<T>((ps1.tuSo)*(ps2.mauSo), (ps1.mauSo)*(ps2.tuSo));
    }
    // Phép bằng:
    friend bool operator==(const PhanSo &ps1, const PhanSo &ps2)
    {
        if(ps1.tuSo == ps2.tuSo && ps1.mauSo == ps2.mauSo) return true;
        return false;
    }
    // Phép lớn hơn hoặc bằng
    friend bool operator>=(const PhanSo &ps1, const PhanSo &ps2)
    {
        if(ps1.giaTri() >= ps2.giaTri()) return true;
        // else
        return false;
    }
    // Phép lớn hơn
    friend bool operator>(const PhanSo &ps1, const PhanSo &ps2)
    {
        if(ps1.giaTri() > ps2.giaTri()) return true;
        // else
        return false;
    }
    // Phép nhỏ hơn
    friend bool operator<(const PhanSo &ps1, const PhanSo &ps2)
    {
        if(ps1.giaTri() < ps2.giaTri()) return true;
        // else
        return false;
    }
    // Phép nhỏ hơn hoặc bằng
    friend bool operator<=(const PhanSo &ps1, const PhanSo &ps2)
    {
        if(ps1.giaTri() <= ps2.giaTri()) return true;
        // else
        return false;
    }
    // Phép khác nhau
    friend bool operator!=(const PhanSo &ps1, const PhanSo &ps2)
    {
        if(ps1.tuSo != ps2.tuSo || ps1.mauSo != ps2.mauSo) return true;
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
    friend ostream& operator<<(ostream& out,const PhanSo<T> &ps2)
    {
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
    }
    // Nhập phân số - overload
    friend istream& operator>>(istream& in, PhanSo<T> &ps)
    {
       T tu, mau;
       in >> tu >> mau;
       // checking 
       if(mau != 0)
       {
        ps.tuSo = tu;
        ps.mauSo = mau;
        ps.RutGon();
       }
       else
       {
        throw invalid_argument("Error: Mau so phai khac 0!");
       }
       // trả lại công cụ
       return in;
    }
};


int main()
{
    // testing code
    PhanSo<int> ps1(1, 2); // 1/2
    PhanSo<int> ps2(3, 4); // 3/4
    PhanSo<int> ps3 = ps1 + ps2; // 1/2 + 3/4 = 5/4
    PhanSo<int> ps4 = ps1 - ps2; // 1/2 - 3/4 = -1/4
    PhanSo<int> ps5 = ps1 * ps2; // 1/2 * 3/4 = 3/8
    PhanSo<int> ps6 = ps1 / ps2; // 1/2 / 3/4 = 2/3
    cout << "ps1: " << ps1 << endl;
    cout << "ps2: " << ps2 << endl;
    cout << "ps1 + ps2: " << ps3 << endl;
    cout << "ps1 - ps2: " << ps4 << endl;
    cout << "ps1 * ps2: " << ps5 << endl;
    cout << "ps1 / ps2: " << ps6 << endl;
    
}