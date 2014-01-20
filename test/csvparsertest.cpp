#include "csvparsertest.h"
#include <iostream>
#include <stdexcept>

using namespace csv;

Log CSVParserTest::sLog("CSVParserTest");

CSVParserTest::CSVParserTest() {
}

void CSVParserTest::PrintLine(const Parser::Line & line) {
        std::cout << line.size() << " fields: ";
        for (auto &f : line)
                std::cout << "[" << f << "] ";
}

bool CSVParserTest::AllTests() {
        S_LOG("AllTests");
        bool res(true);
#define RunTest(function) \
        log(Log::info) << "Running test " #function << Log::endl; \
        if (function()) \
                log(Log::info) << #function << " PASSED" << Log::endl; \
        else { \
                log(Log::info) << #function << " FAILED" << Log::endl; \
                res = false; \
        }

        RunTest(TestParseLine);
        RunTest(TestParseFileFiltered);
        RunTest(TestParseFile);
        if (res) {
                RunTest(TestGetters);
        }

        if (res)
                log(Log::info) << "ALL TESTS PASSED" << Log::endl;
        else
                log(Log::info) << "SOME TESTS FAILED" << Log::endl;
        return res;
}

bool CSVParserTest::TestParseLine() const {
        S_LOG("TestParseLine");
        std::vector<std::string> testStrings{
                "",
                " ",
                ",",
                "Ahaha,\"In quotes\",,",
                "\"Quotes\",No quotes,\"Last quoted\"",
                "1,2,3,",
                "1,2,3,4,\"5\",",
                "one,two,\"quoted..\"...,three"
        };

        std::vector<Parser::Line> testResults{
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
        if (n != testResults.size()) {
                log(Log::error) << "Bad test CSVParserTest::TestParseLine: testStrings.size() != testResults.size(): " <<
                        n << " != " << testResults.size() << Log::endl;
                return false;
        } else {
                for (decltype(n) i = 0; i < n; ++i) {
                        Parser::Line res;
                        if (!Parser::ParseLine(testStrings[i], res, i))
                                return false;
                        else if (res != testResults[i]) {
                                auto &s = log(Log::error) << "Failed test CSVParserTest::TestParseLine, line " << i << std::endl <<
                                        "\t{" << testStrings[i] << "}" << std::endl <<
                                        "\t";
                                PrintLine(res);
                                s << Log::endl;
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

bool CSVParserTest::TestParseFile(const std::vector<Parser::Line> & lines) {
        S_LOG("TestParseFile");
        if (parser.Load(fileName)) {
                if (parser.headFields != Parser::Line{"Field one", "Field two", "Field three"}) {
                log(Log::error) << "Wrong fields" << Log::endl;
                return false;
        } else {
                        auto linesCount = lines.size();
                        if (linesCount != parser.lines.size()) {
                                log(Log::error) << "Wrong number of lines: " << parser.lines.size() << "/" << linesCount << Log::endl;
                                return false;
                        } else {
                                for (decltype(linesCount) i = 0; i < linesCount; ++i) {
                                        if (parser.lines[i] != lines[i]) {
                                                auto &s = log(Log::error) << "Wrong line " << i << std::endl << "\t";
                                                PrintLine(lines[i]);
                                                s << "\n\t";
                                                PrintLine(parser.lines[i]);
                                                s << Log::endl;
                                                return false;
                                        }
                                }
                        }
                }
                return true;
        } else
                return false;
}

bool CSVParserTest::TestGetters() const {
        S_LOG("TestParseFile");
        if (
                parser.GetFieldId("Field one") != 0 ||
                parser.GetFieldId("Field two") != 1 ||
                parser.GetFieldId("Field three") != 2 ||
                !parser.CheckFields({"Field one", "Field two", "Field three"}) ||
        !parser.FindFields({"Field three", "Field two", "Field one"})
        ) {
        log(Log::error) << "Wrong fields (header)" << Log::endl;
        return false;
} else {
                if (
                        parser.GetLinesCount() != 4 ||
                        parser.GetValue(0, 1) != "2" ||
                        parser.GetValue(0, "Field three") != "3" ||
                        parser.GetValue(1, 2) != "fields" ||
                        parser.GetValue(3, 2) != "string"
                        ) {
                        log(Log::error) << "Get values failed" << Log::endl;
                        return false;
                } else {
                        try {
                                parser.GetValue(100, 0);
                                log(Log::error) << "Not received an exception for non-existent line" << Log::endl;
                                return false;
                        } catch (const std::range_error& e) {
                                log(Log::info) << "Received an exception: " << e.what() << Log::endl;
                        }
                        try {
                                parser.GetValue(0, 300);
                                log(Log::error) << "Not received an exception for non-existent field" << Log::endl;
                                return false;
                        } catch (const std::range_error& e) {
                                log(Log::info) << "Received an exception: " << e.what() << Log::endl;
                        }
                        return true;
                }
        }
}
