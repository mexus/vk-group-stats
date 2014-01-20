#ifndef VKDATA_H
#define VKDATA_H

#include <string>
#include <map>
#include "../date_helper/date.h"
#include "../logging/log.h"

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
        static Log sLog;

        void ParseCSV(const csv::Parser& p);
};

#endif // VKDATA_H
