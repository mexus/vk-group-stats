#ifndef VKDATATEST_H
#define VKDATATEST_H

#define protected public
#include "../main/vk_data.h"
#undef protected

class VkDataTest
{
public:
    VkDataTest();
    bool TestLoad();
    bool TestValues() const;

    bool AllTests();
private:
    VkData vkData;

    static const std::string cvsFile;
};

#endif // VKDATATEST_H
