// Mã số sinh viên: 25520093
// Họ và tên: Phan Hải Anh
// Ngày Sinh: 25/04/2007
// Lớp: IT002.Q25
// BTTuan4
#include <iostream>
#include <string>
#include <stdexcept>
#include <windows.h> // thư viện chứa các APIs cần thiết về hệ điều hành window
using namespace std;

// Logic hợp lệ 
template <typename T>
bool isValid(T value, T startPoint, T endPoint, const string &THONGBAO){
    if(value >= startPoint && value <= endPoint)
    {
        return true;
    }
    
    // throw error
    throw invalid_argument(THONGBAO);
};
// CTime
class CTime
{
    private:
    int hour, minute, second;

    public:
    // constructor
    CTime(int h = 0, int m = 0, int s = 0) : hour(h), minute(m), second(s){
        // kiểm tra tính hợp lệ
        isValid(hour, 0, 23,"Lỗi: Thông tin giờ không hợp lệ.");
        isValid(minute, 0, 59,"Lỗi: Thông tin phút không hợp lệ.");
        isValid(second, 0, 59,"Lỗi: Thông tin giây không hợp lệ.");  
    };

    // Cập nhật thời gian
    void timeUpdate(int h, int m, int s)
    {
        isValid(h, 0, 23,"Lỗi: Thông tin giờ không hợp lệ.");
        isValid(m, 0, 59,"Lỗi: Thông tin phút không hợp lệ.");
        isValid(s, 0, 59,"Lỗi: Thông tin giây không hợp lệ."); 
        // nếu thành công
        hour = h;
        minute = m;
        second = s;
    };

    // OVERLOAD OPERATOR
    // +
    friend CTime operator+(const CTime &TIME1, int second)
    {
        // guard clause
        if(second < 0)
        {
            return TIME1 - second;
            // nếu tôi muốn đưa về phép trừ thì sao?
        }
        // logic start
        int newSecond = TIME1.second + second;
        int newMinute = TIME1.minute;
        int newHour = TIME1.hour;
        while(newSecond > 59)
        {
            newSecond = newSecond - 60;
            newMinute += 1;
            if(newMinute > 59)
            {
                newMinute = 0;
                newHour += 1;
                if(newHour > 23)
                {
                    newHour = 0;
                }
            }
        };

        // trả về
        return CTime(newHour, newMinute, newSecond);
    }
    // -
    friend CTime operator-(const CTime &TIME1, int second)
    {
        // guard clause
        if(second < 0)
        {
            return TIME1 + second;
        }
        // logic start
        int newSecond = TIME1.second - second;
        int newMinute = TIME1.minute;
        int newHour = TIME1.hour;
        while(newSecond < 0)
        {
            newSecond = newSecond + 60;
            newMinute -= 1;
            if(newMinute < 0)
            {
                newMinute = 59;
                newHour -= 1;
                if(newHour < 0)
                {
                    newHour = 23;
                }
            }
        };

        // trả về
        return CTime(newHour, newMinute, newSecond);
    };
    // (postfix): t++
    CTime operator++(int)
    {
        CTime temp = *this;
        this->second += 1;
        if(this->second > 59)
        {
            this->second = 0;
            this->minute += 1;
            if(this->minute > 59)
            {
                this->minute = 0;
                this->hour += 1;
                if(this->hour > 23) this->hour = 0;
            }
        };
        return temp;
    }
    // (prefix): ++t
    CTime& operator++()
    {
        this->second += 1;
        if(this->second > 59)
        {
            this->second = 0;
            this->minute += 1;
            if(this->minute > 59)
            {
                this->minute = 0;
                this->hour += 1;
                if(this->hour > 23) this->hour = 0;
            }
        };
        return *this;
    };
    // Nhập >>
    friend istream& operator>>(istream& in, CTime &TIME)
    {
        int h, m, s;
        
            if(!(in >> h >> m >> s))
            {
                throw invalid_argument("Lỗi: Sai kiểu dữ liệu.");
            }
            
            // else
            isValid(h, 0, 23,"Lỗi: Thông tin giờ không hợp lệ.");
            isValid(m, 0, 23,"Lỗi: Thông tin phút không hợp lệ.");
            isValid(s, 0, 23,"Lỗi: Thông tin giây không hợp lệ."); 
            // nếu hợp lệ
            TIME.hour = h;
            TIME.minute = m;
            TIME.second = s;
        return in;
    }
    // Xuất <<
    friend ostream& operator<<(ostream &out, const CTime &TIME)
    {
        out << TIME.hour << " giờ " << TIME.minute << " phút " << TIME.second << " giây ";
        return out;
    }

    // destructor
    ~CTime(){};
};


// lấy kích thước màn hình console từ hàm windows
void getConsoleSize()
{
    // Lấy giấy phép để điều khiển màn hình output.
    HANDLE giayPhep = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy tờ phiếu để chứa thông tin màn hình.
    CONSOLE_SCREEN_BUFFER_INFO toPhieu;

    // Yêu cầu windows điền thông tin vào tờ phiếu
    if(GetConsoleScreenBufferInfo(giayPhep, &toPhieu))
    {
        // trích xuất chiều rộng và chiều dài của màn hình console.
        int width = toPhieu.srWindow.Right - toPhieu.srWindow.Left + 1;
        int height = toPhieu.srWindow.Bottom - toPhieu.srWindow.Top + 1;

        cout << "Chiều rộng Console: " << width << " cột." << endl;
        cout << "Chiều cao Console: " << height << " hàng." << endl;
    };
    
};
// Hàm dịch chuyển con trỏ dựa trên cấu trúc COORD ( tọa độ )
void gotoXY(int x, int y){
    HANDLE giayPhep = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y }; // Ép kiểu về SHORT vì cấu trúc COORD yêu cầu vậy 
    SetConsoleCursorPosition(giayPhep, pos); // SHORT 
};
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    // testing code
    CTime currTime(5,56,59);
    cout << currTime << endl;

    // + 
    CTime nextTime = currTime + 70;
    cout << nextTime << endl;
    
    // -
    CTime previousTime = currTime - 70;
    cout << previousTime << endl;

    // ++ (postfix)
    cout << currTime++ << endl;
    cout << currTime << endl;

    // ++ (prefix)
    cout << ++currTime << endl;

    // reset time
    currTime.timeUpdate(23,59,30);
    cout << currTime << endl;
    
    


    // hứng lỗi
    try
    {
        // Nhập time
    CTime newTime;
    cout << "Nhập dữ liệu newTime: ";
    cin >> newTime;
    cout << newTime << endl;
        currTime.timeUpdate(23,59,30);
    }
    catch(const invalid_argument& e)
    {
        cerr << e.what() << '\n';
    }
    
    
    // Thiết kế đồng hồ
    string time = "23 giờ 59 phút 59 giây"; // giả sử để tính độ dài max của ký tự cout
    // cout << time.length() << endl; -> 26 ký tự
    CTime curr(23,59,59);
    // 1. xác định kích thước màn console
    getConsoleSize(); // 123 cột - 11 hàng ( 1 hàng hay 1 cột tương đương 1 ký tự )
    int width = 123;
    
    // vòng lặp để đồng hồ chạy
    while(true)
    {
        gotoXY(width - 30, 5); // góc trên bên trái

        cout << curr;
        // tăng 1 giây liên tục
        ++curr;

        // dừng 1 giây
        Sleep(1000); // tính theo đơn vị miligiay
    };
    
    return 0;

}