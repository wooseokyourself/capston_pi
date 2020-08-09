#ifndef DATE
#define DATE

#include <ctime>
#include <string>

using namespace std;

class Date {
public:
    bool isValid;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    string form; /** yyyy-mm-dd hh:mm:ss */

    Date();
    Date(string form);
    Date(int);

    bool operator <= (const Date& opponent);
};

#endif