#include "csvparsertest.h"
#include <iostream>
#include "../main/helpers/csv_filter.h"

using namespace csv;

CSVParserTest::CSVParserTest()
{
}

void CSVParserTest::PrintLine(const Parser::Line & line){
    std::cout << line.size() << " fields: ";
    for (auto &f : line)
        std::cout << "[" << f << "] ";
    std::cout << std::endl;
}

bool CSVParserTest::AllTests(){
    bool res(true);
#define RunTest(function) \
        std::cout << "Running test " #function << std::endl; \
        if (function()) \
                std::cout << "CSVParserTest " #function << " PASSED" << std::endl; \
        else { \
                std::cout << "CSVParserTest " #function << " FAILED" << std::endl; \
                res = false; \
        }

    RunTest(TestParseLine);
    RunTest(TestParseFileFiltered);
    RunTest(TestParseFile);
    if (res){
        RunTest(TestGetters);
    }

    if (res)
        std::cout << "CSVParserTest: ALL TESTS PASSED" << std::endl;
    else
        std::cout << "CSVParserTest: SOME TESTS FAILED" << std::endl;
    return res;
}

bool CSVParserTest::TestParseLine() const{
    std::vector<std::string> testStrings {
        "",
        " ",
        ",",
        "Ahaha,\"In quotes\",,",
        "\"Quotes\",No quotes,\"Last quoted\"",
        "1,2,3,",
        "1,2,3,4,\"5\",",
        "one,two,\"quoted..\"...,three"
    };

    std::vector<Parser::Line> testResults {
        {""},
        {" "},
        {"", ""},
        {"Ahaha", "In quotes", "", ""},
        {"Quotes", "No quotes", "Last quoted"},
        {"1", "2", "3"},
        {"1", "2", "3", "4", "5"},
        {"one", "two", "quoted..", "three"}
    };

    auto n = testStrings.size();
    if (n != testResults.size()){
        std::cerr << "Bad test CSVParserTest::TestParseLine: testStrings.size() != testResults.size(): " <<
                  n << " != " << testResults.size() << std::endl;
        return false;
    } else {
        for (decltype(n) i = 0; i < n; ++i){
            Parser::Line res;
            if (!Parser::ParseLine(testStrings[i], res, i))
                return false;
            else if (res != testResults[i]){
                std::cerr << "Failed test CSVParserTest::TestParseLine, line " << i << std::endl <<
                             "\t{" << testStrings[i] << "}" << std::endl <<
                             "\t";
                PrintLine(res);
                return false;
            }
        }
        return true;
    }
}

bool CSVParserTest::TestParseFileFiltered() {
        Filter filter;
        filter.AddPossibleValues("Field one", std::vector<std::string>({"1", "5", "not"}));
        filter.AddPossibleValues("Field two", std::vector<std::string>({"2", "last"}));
        parser.SetFilter(&filter);
        bool res = TestParseFile({
                {"1", "2", "3"},
                {"5", "last", "string"}
            });
        parser.SetFilter();
        return res;
}

bool CSVParserTest::TestParseFile() {
        return TestParseFile({
                {"1", "2", "3"},
                {"too", "many", "fields"},
                {"not", "enough", ""},
                {"5", "last", "string"}
            });
}

bool CSVParserTest::TestParseFile(const std::vector<Parser::Line> & lines){
    if (parser.Load(fileName)){
        if (parser.headFields != Parser::Line{"Field one", "Field two", "Field three"}){
            std::cerr << "Wrong fields" << std::endl;
            return false;
        } else {
            auto linesCount = lines.size();
            if (linesCount != parser.lines.size()){
                std::cerr << "Wrong number of lines: " << parser.lines.size() << "/" << linesCount << std::endl;
                return false;
            } else {
                for (decltype(linesCount) i =0; i < linesCount; ++i){
                    if (parser.lines[i] != lines[i]) {
                        std::cerr << "Wrong line " << i << std::endl << "\t";
                        PrintLine(lines[i]);
                        std::cerr << "\t";
                        PrintLine(parser.lines[i]);
                        return false;
                    }
                }
            }
        }
        return true;
    } else
        return false;
}

bool CSVParserTest::TestGetters() const{
    if (
            parser.GetFieldId("Field one") != 0 ||
            parser.GetFieldId("Field two") != 1 ||
            parser.GetFieldId("Field three") != 2 ||
            !parser.CheckFields({"Field one", "Field two", "Field three"}) ||
            !parser.FindFields({"Field three", "Field two", "Field one"})
            ){
        std::cerr << "Wrong fields (header)" << std::endl;
        return false;
    } else {
        if (
                parser.GetLinesCount() != 4 ||
                parser.GetValue(0, 1) != "2" ||
                parser.GetValue(0, "Field three") != "3" ||
                parser.GetValue(1, 2) != "fields" ||
                parser.GetValue(3, 2) != "string"
                ){
            std::cerr << "Get values failed" << std::endl;
            return false;
        } else {
            try {
                parser.GetValue(100, 0);
                std::cerr << "Not received an exception for non-existent line" << std::endl;
                return false;
            } catch (const std::range_error&){
                ;
            }
            try {
                parser.GetValue(0, 100);
                std::cerr << "Not received an exception for non-existent field" << std::endl;
                return false;
            } catch (const std::range_error&){
                ;
            }
            return true;
        }
    }
}
