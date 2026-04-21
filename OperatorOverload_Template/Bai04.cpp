// Mã số sinh viên: 25520093
// Họ và tên: Phan Hải Anh
// Ngày Sinh: 25/04/2007
// Lớp: IT002.Q25
// BTTuan4

/* 
Thầy ơi em xin phép chia sẻ vài thông tin về các bài làm của em.
Các bài tập em làm đều là em tự làm, tuy nhiên sau khi làm xong thì em có tự học hỏi và chỉnh sửa thêm
nhờ AI ( em không copy ), với mục đích cải thiện code tốt hơn và làm quen với tính chuyên nghiệp sớm.
Em cảm ơn thầy.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <numeric>

using namespace std;
// Công cụ kiểm tra tính hợp lệ
template<typename T>
bool HopLe(T value,T startPoint, T endPoint,const string &THONGBAO)
{
    if(startPoint <= endPoint && value >= startPoint && value <= endPoint)
    {
        // Hợp lệ
        return true;
    }
    
    // else
    throw invalid_argument(THONGBAO);
};
template<typename T>
bool HopLe2(T value,T startPoint, T endPoint)
{
    if(startPoint <= endPoint && value >= startPoint && value <= endPoint)
    {
        // Hợp lệ
        return true;
    }
    
    // else
    return false;
};
// .. Hàm logic tính hợp lê
bool DateHopLe(int d, int m, int y)
{
    if(m == 2)
    {
        if(y%400 == 0 || (y%4==0 && y%100 != 0))
        {
            if(HopLe2(d, 1, 29)) return true;
        }
        else{
            if(HopLe2(d, 1, 28)) return true;
        };
    }
    else if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
    {
         if(HopLe2(d, 1, 31)) return true;
    }
    else
    {
         if(HopLe2(d, 1, 30)) return true;
    };
    return false;
}
// CLASS CDATE
class CDate
{
    private:
    int day, month, year;

    public:
    // constructor
    CDate(int ngay = 1, int thang = 1, int nam = 1) : day(ngay), month(thang), year(nam){
        LogicThietLapThoiGian(ngay, thang, nam);
    };

    // setter ( logic )
    void LogicThietLapThoiGian(int nam, int thang, int ngay)
    {
        // kiểm tra tính hợp lệ của dữ liệu: ( ngày và tháng )
        bool namNhuan = (nam % 400 == 0) || (nam % 4 == 0 && nam % 100 != 0);
        // THÁNG
        if(HopLe(thang, 1, 12, "Lỗi: Tháng không hợp lệ."))
        {
            // NGÀY
            if(thang == 1 || thang == 3 || thang == 5 || thang == 7 || thang == 8 || thang == 10 || thang == 12)
            {
                if(HopLe(ngay, 1, 31, "Lỗi: Ngày không hợp lệ."))
                {
                    year = nam;
                    month = thang;
                    day = ngay;
                   
                    return;
                }
                // else: throw error.
            }
            else if(thang == 2)
            {
                // kiểm tra năm nhuận hay không nhuận
                int NgayToiDa = (namNhuan) ? 29 : 28;
                if(HopLe(ngay, 1, NgayToiDa, "Lỗi: Ngày không hợp lệ."))
                {
                    year = nam;
                    month = thang;
                    day = ngay;
                    
                    return;
                }
                // error: throw
            }
            else{
                if(HopLe(ngay, 1, 30, "Lỗi: Ngày không hợp lệ."))
                {
                    year = nam;
                    month = thang;
                    day = ngay;
                    
                    return;
                }
                // else: throw error.
            }
        }
        // else: throw error( tháng không hợp lệ. )
    };
    // setter ( xử lý thông tin người dùng nhập ) 
    void HamThietLapThoiGian()
    {
        int y, m, d;
        while(true)
        {
            cout << "Nhập ngày tháng năm: ";
            if(!cin >> d >> m >> y)
            {
                cin.clear(); //  đưa trạng thái cin về lại: ổn định 
                cin.ignore(1000, '\n');  // xóa dữ liệu sai từ input ( dừng tại nút enter ) - tối đa 1000 ký tự
                continue;
            }

            // nếu vượt qua:
            try{
                LogicThietLapThoiGian(y, m, d);
                break;
            }
            catch(const invalid_argument &THONGBAO)
            {
                cout << "Lỗi: " << THONGBAO.what() << ". Vui lòng thử lại!" << endl;
                // -> quay lại vòng lặp
            }

        }
    };

    // Hàm cộng 1 ngày ( hàm hỗ trợ logic )
    friend void ExcessingDayIncrement(CDate &Date)
    {
        // xác định ngày tối đa
        int ngayToiDa;
        if(Date.month == 2)
        {
            bool namNhuan = (Date.year % 400 == 0) || (Date.year % 4 == 0 && Date.year % 100 != 0);
            ngayToiDa = (namNhuan) ? 29 : 28;
        }
        else if(Date.month == 1 || Date.month == 3 || Date.month == 5 || Date.month == 7 || Date.month == 10 || Date.month == 12)
        {
            ngayToiDa = 31;
        }
        else
        {
            ngayToiDa = 30;
        };


        // Kiểm tra lại excession
        if(Date.day > ngayToiDa)
        {
            Date.day = 1;
            Date.month += 1;
        }
        
        if(Date.month > 12)
        {
            Date.month = 1;
            Date.year += 1;
        }
    };
    // Hàm trừ 1 ngày ( hàm hỗ trợ logic )
    friend void ExcessingDayDecrement(CDate &Date)
    {
        // xác định ngày tối đa
        int ngayToiDa;
        if(Date.month == 2)
        {
            bool namNhuan = (Date.year % 400 == 0) || (Date.year % 4 == 0 && Date.year % 100 != 0);
            ngayToiDa = (namNhuan) ? 29 : 28;
        }
        else if(Date.month == 1 || Date.month == 3 || Date.month == 5 || Date.month == 7 || Date.month == 10 || Date.month == 12)
        {
            ngayToiDa = 31;
        }
        else
        {
            ngayToiDa = 30;
        };

        if(Date.day < 0)
        {
            Date.day = ngayToiDa;
            if(Date.month == 1)
            {
                Date.month = 12;
                Date.year -= 1;
            };
        }
    }
    // Hàm cộng 1 ngày ( hàm chính overload - postfix) d++
    CDate operator++(int)
    {
        CDate temp = *this;
        this->day = this->day + 1;
        ExcessingDayIncrement(*this);
        return temp;
    }
    // Hàm cộng 1 ngày ( hàm chính overload - prefix ) ++d
    CDate& operator++()
    {
        this->day = this->day + 1;
        ExcessingDayIncrement(*this);
        return *this;
    } 
    // Hàm trừ 1 ngày ( postfix ) d--
    CDate operator--(int)
    {
        CDate temp = *this;
        this->day = this->day - 1;
        ExcessingDayDecrement(*this);
        return temp;
    }
    // Hàm trừ 1 ngày ( prefix ) --d
    CDate& operator--()
    {
        this->day = this->day - 1;
        ExcessingDayDecrement(*this);
        return *this; // giải tham chiếu
    };

    // HIỂN THỊ THÔNG TIN NGÀY - overload
    friend ostream& operator<<(ostream& out, const CDate &Date)
    {
        if(Date.month < 10)
        {
            out << Date.day << "/0" << Date.month << "/" << Date.year << endl;
        }
        else
        {
            out << Date.day << "/" << Date.month << "/" << Date.year << endl;
        }
        return out;
    }
    // NHẬP THÔNG TIN NGÀY - overload
    friend istream& operator>>(istream& in, CDate &Date)
    {
        int d, m, y;
        while(true)
        {
            try
            {
                cout << "Nhập thông tin ngày tháng năm(dd mm yy): ";
                if(!(in >> d >> m >> y))
                {
                    in.clear();
                    in.ignore(1000, '\n');
                    throw invalid_argument("Lỗi: Nhập thông tin sai kiểu dữ liệu.");
                }
                else
                {
                    if(DateHopLe(d,m,y)){
                        Date.day = d;
                        Date.month = m;
                        Date.year = y;
                        break;
                    }
                    else{
                        throw invalid_argument("Lỗi: Nhập ngày tháng không hợp lệ.");
                    }
                }
            }
            catch(const invalid_argument& error)
            {
                cout << error.what() << endl;
            }
            
        };

        return in;
        
    }

    // TÍNH KHOẢNG CÁCH NĂM
    // Hàm xác định nếu đó là năm nhuật
    static bool laNamNhuan(int year)
    {
        return ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) ? true : false;
    };
    // Hàm xác định số ngày tối đa
    static int ngayToiDa(int month, int year)
    {
        int ngayToiDa;
        if(month == 2)
        {
            return (laNamNhuan(year)) ? 29 : 28;
        }
        else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            ngayToiDa = 31;
            return ngayToiDa;
        }
        else
        {
            ngayToiDa = 30;
            return ngayToiDa;
        }
    }
    // Hàm xác định số ngày từ thời điểm hiện tại về -> 01/01/0001
    friend int DAYdistance(const CDate &Date)
    {
       int total = 0;
       // năm 1 -> năm cận end
       for(int i = 1; i < Date.year; i++)
       {
        total += (laNamNhuan(i)) ? 366 : 365;
       }
       // cộng số ngày còn lại của năm end
       for(int i = 1; i < Date.month; i++)
       {
        total += ngayToiDa(i, Date.year);
       }
       total += Date.day;

       return total;
    }
    friend float distanceCalculatedByDays(const CDate &start, const CDate &end)
    {
        // xác định ngày tối đa
        // Theo Quy ước tự đưa ra - khoảng cách ( tính theo năm ) được làm tròn chuẩn ở 3 số thập phân sau dấu phẩy
        float distanceByYear  = static_cast<float>(DAYdistance(end) - DAYdistance(start))/365.0f;
        // làm tròn
        distanceByYear = round(distanceByYear*1000)/1000.0f;
        return distanceByYear;
    };

    // destructor
    ~CDate(){};
};

int main()
{
    // testing code
   CDate sinhNhatToi(25,4,2007);
   // test Date++;
   cout << "(postfix)++ :";
   cout << sinhNhatToi << " -> " << sinhNhatToi++ << " -> " << sinhNhatToi << endl;

   CDate sinhNhatBRO1(19,12,1992);
   // test ++Date;
   cout << "++(prefix) :";
   cout << sinhNhatBRO1 << " -> " << ++sinhNhatBRO1 << " -> " << sinhNhatBRO1 << endl;

   CDate sinhNhatBRO2(1,3,1991);
   // test Date--;
   cout << "(postfix)-- :";
   cout << sinhNhatBRO2 << " -> " << sinhNhatBRO2-- << " -> " << sinhNhatBRO2 << endl;

    CDate sinhNhatBRO3(11,9,1991);
   // test --Date;
   cout << "--(prefix) :";
   cout << sinhNhatBRO3 << " -> " << --sinhNhatBRO3 << " -> " << sinhNhatBRO3 << endl;

   // BÀI TOÁN TÍNH TIỀN LÃI
   cout << "--------------Tính tiền lãi suất ngân hàng dựa vào CDate----------------" << endl;

   // Quy ước: lãi suất ngân hàng: 2,3% / năm
   const float laiSuatNganHang = 2.3;
   long long TongTien = 50000000; // 50 trieu
   cout << "Tổng tiền ban đầu: " << TongTien << "VND" << endl;
   // Deposit: 13/4/2026 -> withdraw: 25/12/2030
   CDate deposit(13,4,2026);
   CDate withdraw(25,12,2030);
   // logic
   float yearPassed = distanceCalculatedByDays(deposit, withdraw);
   long long tienLoi = (yearPassed*TongTien*laiSuatNganHang)/100;
   TongTien += tienLoi;
   // in ra
   cout << "Gửi tiền: 13/4/2026 -> Rút tiền: 25/12/2030" << endl;
   cout << "Tổng tiền sau đó: " << TongTien << " VND" << endl;
   cout << "Tiền lãi: " << tienLoi << " VND" << endl;

   
}

