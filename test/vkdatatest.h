#ifndef VKDATATEST_H
#define VKDATATEST_H

#define protected public
#include "../main/vk/vk_data.h"
#undef protected
#include "../main/logging/log.h"

class VkDataTest {
public:
        VkDataTest();
        bool TestLoad();
        bool TestValues() const;

        bool AllTests();
private:
        VkData vkData;
        static Log cLog;

        static const std::string cvsFile;
};

#endif // VKDATATEST_H
