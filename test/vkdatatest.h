#ifndef VKDATATEST_H
#define VKDATATEST_H

#define protected public
#include "../main/vk_data.h"
#undef protected
#include "../main/helpers/log_helper.h"

class VkDataTest {
public:
        VkDataTest();
        bool TestLoad();
        bool TestValues() const;

        bool AllTests();
private:
        VkData vkData;
        Log log;

        static const std::string cvsFile;
};

#endif // VKDATATEST_H
