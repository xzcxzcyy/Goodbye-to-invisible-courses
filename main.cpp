#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

bool ckRun(int year)
{
    if (year % 100 == 0)
    {
        return year % 400 == 0;
    }
    else
    {
        return year % 4 == 0;
    }
}

class Date
{
public:
    int year, month, day;
    Date(int yyyy, int mm, int dd)
    {
        year = yyyy;
        month = mm;
        day = dd;
    }

    string toString()
    {
        string res;
        res.clear();
        if (year < 2000)
        {
            return res;
        }

        res += to_string(year);
        if (month < 10)
        {
            res += "0";
        }
        res += to_string(month);
        if (day < 10)
        {
            res += "0";
        }
        res += to_string(day);

        return res;
    }

    void nextWeek()
    {
        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
            if (day + 7 <= 31)
            {
                day += 7;
            }
            else
            {
                day = 7 - (31 - day);
                month += 1;
            }
            break;

        case 12:
            if (day + 7 <= 31)
            {
                day += 7;
            }
            else
            {
                day = 7 - (31 - day);
                month = 1;
                year += 1;
            }
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            if (day + 7 <= 30)
            {
                day += 7;
            }
            else
            {
                day = 7 - (30 - day);
                month += 1;
            }
            break;

        case 2:
            if (ckRun(year))
            {
                if (day + 7 <= 29)
                {
                    day += 7;
                }
                else
                {
                    day = 7 - (29 - day);
                    month += 1;
                }
            }
            else
            {
                if (day + 7 <= 28)
                {
                    day += 7;
                }
                else
                {
                    day = 7 - (28 - day);
                    month += 1;
                }
            }
            break;
        }
    }
};

int main()
{
    ofstream fout("result.ics");
    fout << "BEGIN:VCALENDAR" << endl
         << "PRODID:-//github/xzcxzcyy" << endl;

    Date today(2020, 3, 17);

    for (int i = 1; i <= 6; ++i)
    {
        //uid不可重复. 代码复用的时候记得个性化
        string uid = to_string(i) + "hust" + "junshililun" + "@banson20200316";
        fout << "BEGIN:VEVENT" << endl
             << "SUMMARY:军事理论" << endl
             << "UID:" << uid << endl
             << "DESCRIPTION: 计卓1901" << endl
             << "DTSTART:"
             << today.toString() + "T080000" << endl
             << "DTEND:"
             << today.toString() + "T094000" << endl
             << "LOCATION:西十二楼N101" << endl
             << "BEGIN:VALARM" << endl
             // 提前多少分钟提醒
             << "TRIGGER:-PT20M" << endl
             //alarm duration
             << "DURATION:PT05M" << endl
             << "ACTION:AUDIO" << endl
             << "REAPEAT;VALUE=TEXT:1" << endl
             << "END:VALARM" << endl
             << "END:VEVENT" << endl;
        today.nextWeek();
    }

    fout << "END:VCALENDAR";
}
