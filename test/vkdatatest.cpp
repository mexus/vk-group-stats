#include "vkdatatest.h"
#include <vector>
#include <map>
#include <iostream>

VkDataTest::VkDataTest() {
}

bool VkDataTest::TestLoad() {
        return vkData.LoadCSV(cvsFile);
}

bool VkDataTest::TestValues() const {
        std::vector<DateHelper> dates;
        for (int i = 1; i <= 7; ++i)
                dates.emplace_back(i, 1, 2014);
        std::map<DateHelper, unsigned long int> ins{
                {dates[0], 32},
                {dates[1], 40},
                {dates[2], 43},
                {dates[3], 43},
                {dates[4], 35},
                {dates[5], 49},
                {dates[6], 11}
        };

        decltype(ins) outs {
                {
                        dates[0], 11
                },
                {
                        dates[1], 10
                },
                {
                        dates[2], 5
                },
                {
                        dates[3], 13
                },
                {
                        dates[4], 10
                },
                {
                        dates[5], 15
                },
                {
                        dates[6], 1
                }
        };
        if (vkData.membersIn != ins) {
                std::cerr << "VkDataTest::TestValues " << "Wrong members 'in'" << std::endl;
                return false;
        } else if (vkData.membersOut != outs) {
                std::cerr << "VkDataTest::TestValues " << "Wrong members 'out'" << std::endl;
                return false;
        } else
                return true;
}

bool VkDataTest::AllTests() {
#define RunTest(function) \
    if (function()) \
        std::cout << "VkDataTest" #function << " passed" << std::endl; \
    else { \
        std::cout << "VkDataTest" #function << " failed" << std::endl; \
        res = false; \
    }

        bool res(true);
        RunTest(TestLoad);
        if (res) {
                RunTest(TestValues);
        }

        if (res)
                std::cout << "VkDataTest: ALL TESTS PASSED" << std::endl;
        else
                std::cout << "VkDataTest: SOME TESTS FAILED" << std::endl;
        return res;

}
