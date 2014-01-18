#include "date.h"
#include <cstdio>
#include <iostream>

DateHelper::DateHelper(const std::string &s) : day(0), month(0), year(0), isValid(false) {
        isValid = Parse(s);
}

DateHelper::DateHelper(int day, int month, int year) : day(day), month(month), year(year), isValid(true) {
        ;
}

bool DateHelper::Parse(const std::string & s) {
        if (std::sscanf(s.c_str(), "%2d.%2d.%4d", &day, &month, &year) != 3) {
                std::cerr << "DateHelper::Parse " << "Can't parse date {" << s << "}" << std::endl;
                return false;
        } else
                return true;
}

bool operator<(const DateHelper& lhs, const DateHelper& rhs) {
        if (lhs.year == rhs.year) {
                if (lhs.month == rhs.month) {
                        return lhs.day < rhs.day;
                } else
                        return lhs.month < rhs.month;
        } else
                return lhs.year < rhs.year;
}

bool operator==(const DateHelper& lhs, const DateHelper& rhs) {
        return
        lhs.year == rhs.year &&
                lhs.month == rhs.month &&
                lhs.day == rhs.day;
}

bool DateHelper::IsValid() const {
        return isValid;
}
