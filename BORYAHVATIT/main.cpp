#include <iostream>
#include <string>

using namespace std;

class Date
{
public:
    int second, minute, hour, day, month, year;
    bool isOurEra = 1;
    Date(int s = 0, int m = 0, int h = 0, int d = 1, int mo = 1, int y = 1960)
    {
        second = s;
        minute = m;
        hour = h;
        day = d;
        month = mo;
        year = y;
    }

    void normalizeSeconds()
    {
        if (second >= 60)
        {
            int extraMinutes = second / 60;
            second %= 60;
            if (isOurEra == 0) minute += extraMinutes;
            else minute += extraMinutes;
            //minute += extraMinutes;
            normalizeMinutes();
        }
        else if (second < 0)
        {
            int missingMinutes = (-second + 59) / 60;
            second = (second + missingMinutes * 60) % 60;
            minute -= missingMinutes;
            normalizeMinutes();
        }
    }

    void normalizeMinutes()
    {
        if (minute >= 60)
        {
            int extraHours = minute / 60;
            minute %= 60;
            if (isOurEra == 0) hour -= extraHours;
            else hour += extraHours;
            //hour += extraHours;
            normalizeHours();
        }
        else if (minute < 0)
        {
            int missingHours = (-minute + 59) / 60;
            minute = (minute + missingHours * 60) % 60;
            hour -= missingHours;
            normalizeHours();
        }
    }

    void normalizeHours()
    {
        if (hour >= 24)
        {
            int extraDays = hour / 24;
            hour %= 24;
            if (isOurEra == 0) day -= extraDays;
            else day += extraDays;
            //day += extraDays;
            normalizeDays();
        }
        else if (hour < 0)
        {
            int missingDays = (-hour + 23) / 24;
            hour = (hour + missingDays * 24) % 24;
            day -= missingDays;
            normalizeDays();
        }
    }

    void normalizeDays()
    {
        while (day < 1)
        {
            month--;
            if (month < 1)
            {
                month = 12;
                year--;
            }
            day += daysInMonth(month, year);
        }

        while (day > daysInMonth(month, year))
        {
            day -= daysInMonth(month, year);
            month++;
            if (month > 12)
            {
                month = 1;
                if (isOurEra == 0) year--;///
                else year++;///
                //year++;
            }
        }
    }

    void normalizeERA(){
        if (year<0 && isOurEra == 1) {year = -year; isOurEra = 0;}
        else if (year < 0 && isOurEra == 0) {year = -year; isOurEra = 1;}
        else if (year == 0) {year += 1; isOurEra = 1;}

    }

    void normalizeMonths()
    {
        if (month > 12)
        {
            int extraYears = (month - 1) / 12;
            month = (month - 1) % 12 + 1;
            if (isOurEra == 0) year -= extraYears;
            else year += extraYears;
            //year += extraYears;
        }
        else if (month < 1)
        {
            int missingYears = (-month + 11) / 12;
            month = (month + missingYears * 12) % 12 + 1;
            year -= missingYears;
        }
    }

    bool VESOKO(int year)
    {
        return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
    }

    int daysInMonth(int month, int year)
    {
        switch (month)
        {
            case 2:
                return VESOKO(year) ? 29 : 28;
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            default:
                return 31;
        }
    }

    bool operator<(const Date& other) const
    {
        if (isOurEra != other.isOurEra)
        {
            return isOurEra<other.isOurEra;
        }
        if (year != other.year)
        {
            return year < other.year;
        }
        if (month != other.month)
        {
            return month < other.month;
        }
        if (day != other.day)
        {
            return day < other.day;
        }
        if (hour != other.hour)
        {
            return hour < other.hour;
        }
        if (minute != other.minute)
        {
            return minute < other.minute;
        }
        if (second != other.second)
        {
            return second < other.second;
        }
        return false;
    }
    bool operator>(const Date& other) const
    {
        return other < *this;
    }

    Date operator+(const Date& other) const
    {

        Date result = *this;
        bool fla = result.isOurEra;

        if (isOurEra == 0) result.second -= other.second;///
        else result.second += other.second;///
       // result.second += other.second;
        if (isOurEra == 0) result.minute -= other.minute;///
        else result.minute += other.minute;///
        //result.minute += other.minute;
        if (isOurEra == 0) result.hour -= other.hour;///
        else result.hour += other.hour;///
        //result.hour += other.hour;
        if (isOurEra == 0) result.day -= other.day;///
        else result.day += other.day;///
        //result.day += other.day;
        if (isOurEra == 0) result.month -= other.month;///
        else result.month += other.month;///
        //result.month += other.month;
        if (isOurEra == 0) {if (result.year < other.year) {result.isOurEra = 1; fla = 1;} result.year -= other.year;}///
        else {  result.year += other.year;}///
        //result.year += other.year;
        result.normalize();

        result.normalizeERA();

        if (result.month == 12 && result.day == 31 && result.year == 1 && isOurEra ==1){
            result.day = 1; result.month = 1; result.year =1;
        }
        result.isOurEra = fla;
        return result;
    }
    Date operator-(const Date& other) const
    {
        Date result = *this;


        result.second -= other.second;
        result.minute -= other.minute;
        result.hour -= other.hour;
        result.day -= other.day;
        result.month -= other.month;
        if (isOurEra == 0) result.year += other.year;///!!!
        else result.year -= other.year;///
        result.normalize();

        result.normalizeERA();
        //cout<<result.day<<" "<<result.month<<" "<<result.year<<endl;
        if (result.month == 12 && result.day == 31 && result.year == 1 && isOurEra ==1){
            result.day = 1; result.month = 1; result.year =1; result.isOurEra = 1;
        }

        return result;
    }
    Date& operator+=(const Date& other)
    {
        second += other.second;
        minute += other.minute;
        hour += other.hour;
        day += other.day;
        month += other.month;
        if (isOurEra == 0) year -= other.year;///
        else year += other.year;///
        //year += other.year;
        normalize();

        normalizeERA();
        return *this;
    }

    Date& operator-=(const Date& other)
    {
        if ((isOurEra == 0) || (day==1 && month == 1 && year == 1 && isOurEra==1)) {isOurEra = 0; second += other.second;}///
        else {second -= other.second;}///
        //second -= other.second;
        if ((isOurEra == 0) || (day==1 && month == 1 && year == 1 && isOurEra==1)) {isOurEra = 0; minute += other.minute;}///
        else {minute -= other.minute;}///
        //minute -= other.minute;
        if ((isOurEra == 0) || (day==1 && month == 1 && year == 1 && isOurEra==1)) {isOurEra = 0; hour += other.hour;}///
        else {hour -= other.hour;}///
       // hour -= other.hour;
        if ((isOurEra == 0) || (day==1 && month == 1 && year == 1 && isOurEra==1)) {isOurEra = 0; day += other.day;}///
        else {day -= other.day;}///
        //day -= other.day;
        if ((isOurEra == 0) || (day==1 && month == 1 && year == 1 && isOurEra==1)) {isOurEra = 0; month += other.month;}///
        else {month -= other.month;}///
        //month -= other.month;
        if ((isOurEra == 0) || (day==1 && month == 1 && year == 1 && isOurEra==1)) {isOurEra = 0; year += other.year;}///
        else {year -= other.year;}///
        //year -= other.year;
        normalize();

        normalizeERA();
        return *this;
    }

    bool operator==(const Date& other) const
    {
        return second == other.second &&
               minute == other.minute &&
               hour == other.hour &&
               day == other.day &&
               month == other.month &&
               year == other.year &&
               isOurEra == other.isOurEra;
    }
    Date& operator=(const Date& other)
    {
        if (this == &other)
            return *this;
        if (other.year > year) {isOurEra = 1;}
        second = other.second;
        minute = other.minute;
        hour = other.hour;
        day = other.day;
        month = other.month;
        year = other.year;
        isOurEra = other.isOurEra;
        if (month == 12 && day == 31 && year == 1 && isOurEra ==0){
            day = 1; month = 1; year =1; isOurEra = 1;
            return *this;
        }
        else return *this;
    }

//СТАБИЛЬНОННООНООСТЬсу
    void normalize()
    {
        normalizeSeconds();
        normalizeMinutes();
        normalizeHours();
        normalizeDays();
        normalizeMonths();
    }

    friend ostream& operator<<(ostream& os, const Date& date);

};
ostream& operator<<(ostream& os, const Date& date)
{
    bool f = date.isOurEra;
    if (f == 1)
    os <<date.second<<"/"<<date.minute<<"/"<<date.hour<<"/"<< date.day << "/" << date.month << "/" << date.year<<" AC";
    else os <<date.second<<"/"<<date.minute<<"/"<<date.hour<<"/"<< date.day << "/" << date.month << "/" << date.year<<" BC";
    return os;
}

int main()
{
    Date date4(0,0,0,1,1,2500);
    Date date1;
    Date date2(0, 0, 0, 1, 1, 2000); date2.isOurEra = 1;
    date2 = date2 - date4;
    cout<<date1<<endl;
    cout<<date2<<"  "<<date2.isOurEra;

    //cout << "date 1 " << date1 << endl;
    //cout << "date 2 " << date2 << endl;
    //cout<<date3.era;


    return 0;
}
