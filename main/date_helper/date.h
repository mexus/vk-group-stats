#ifndef DATE_H
#define DATE_H

#include <string>
#include "../logging/log.h"

class DateHelper {
public:
        DateHelper(const std::string&);
        DateHelper(int day, int month, int year);
        bool IsValid() const;

        friend bool operator<(const DateHelper&, const DateHelper&);
        friend bool operator==(const DateHelper&, const DateHelper&);

protected:
        int day, month, year;
        bool isValid;
        static Log cLog;

        bool Parse(const std::string&);
};

bool operator<(const DateHelper&, const DateHelper&);
bool operator==(const DateHelper&, const DateHelper&);

#endif // DATE_H
