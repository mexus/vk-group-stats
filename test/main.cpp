#include <iostream>
#include "csvparsertest.h"
#include "vkdatatest.h"

using namespace std;

int main()
{
    CSVParserTest parserTest;
    VkDataTest vkDataTest;
    return parserTest.AllTests() && vkDataTest.AllTests() ? 0 : 1;
}

