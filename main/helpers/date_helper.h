#ifndef DATEHELPER_H
#define DATEHELPER_H

#include <string>

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

        bool Parse(const std::string&);
};

bool operator<(const DateHelper&, const DateHelper&);
bool operator==(const DateHelper&, const DateHelper&);

#endif // DATEHELPER_H
