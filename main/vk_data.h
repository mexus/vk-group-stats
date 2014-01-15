#ifndef VKDATA_H
#define VKDATA_H

#include <string>
#include <map>
#include "helpers/date_helper.h"

namespace csv {
        class Parser;
}

class VkData {
public:
        VkData();
        bool LoadCSV(const std::string &file);

protected:
        std::map<DateHelper, unsigned long int> membersIn;
        std::map<DateHelper, unsigned long int> membersOut;

        void ParseCSV(const csv::Parser& p);
};

#endif // VKDATA_H
