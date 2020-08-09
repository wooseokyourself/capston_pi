#include "date.hpp"

Date::Date() {
    this->isValid = true;

    time_t timeObj = time(NULL);
	struct tm* tm = localtime(&timeObj);
    this->year = tm->tm_year + 1900;
    this->month = tm->tm_mon + 1;
    this->day = tm->tm_mday;
    this->hour = tm->tm_hour;
    this->minute = tm->tm_min;
    this->second = tm->tm_sec;
    
    string temp;
    this->form += to_string (this->year);
    this->form += "-";

    temp = to_string (this->month);
    if (temp.length() == 1) temp = "0" + temp;
	this->form += temp;
    this->form += "-";

    temp = to_string (this->day);
    if (temp.length() == 1) temp = "0" + temp;
    this->form += temp;

    this->form += " ";

	temp = to_string (this->hour);
    if (temp.length() == 1) temp = "0" + temp;
	this->form += temp;
    this->form += ":";

	temp = to_string (this->minute);
    if (temp.length() == 1) temp = "0" + temp;
	this->form += temp;
    this->form += ":";

	temp = to_string (this->second);
    if (temp.length() == 1) temp = "0" + temp;
	this->form += temp;
}

Date::Date(string form) {
    this->isValid = true;

    this->form = form;
    string temp;

    temp = form.substr(0, 4);
    this->year = stoi(temp);

    temp = form.substr(5, 2);
    this->month = stoi(temp);

    temp = form.substr(8, 2);
    this->day = stoi(temp);

    temp = form.substr(11, 2);
    this->hour = stoi(temp);

    temp = form.substr(14, 2);
    this->minute = stoi(temp);

    temp = form.substr(17, 2);
    this->second = stoi(temp);
}

Date::Date(int __notValid) {
    this->isValid = false;
}

/**
 * return true if LValue is earlier or same
*/
bool Date::operator <= (const Date& opponent) {
    if (this->year < opponent.year) {
        return true;
    }
    else if (this->year == opponent.year) {
        if (this->month < opponent.month) {
            return true;
        }
        else if (this->month == opponent.month) {
            if (this->day < opponent.day) {
                return true;
            }
            else if (this->day == opponent.day) {
                if (this->hour < opponent.hour) {
                    return true;
                } else if (this->hour == opponent.hour) {
                    if (this->minute < opponent.minute) {
                        return true;
                    }
                    else if (this->minute == opponent.minute) {
                        if (this->second <= opponent.second) {
                            return true;
                        }
                        else {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else{
        return false;
    }
}