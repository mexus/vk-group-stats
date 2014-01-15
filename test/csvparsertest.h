#ifndef CSVPARSERTEST_H
#define CSVPARSERTEST_H

#define protected public
#include "../main/helpers/csv_parser.h"
#undef protected
#include "../main/helpers/log_helper.h"

class CSVParserTest {
public:
        CSVParserTest();

        bool AllTests();

        bool TestParseLine() const;
        bool TestParseFileFiltered();
        bool TestParseFile();
        bool TestGetters() const;

protected:
        csv::Parser parser;
        Log log;

        static const std::string fileName;
        static void PrintLine(const csv::Parser::Line&);

        bool TestParseFile(const std::vector<csv::Parser::Line> &);
};

#endif // CSVPARSERTEST_H
