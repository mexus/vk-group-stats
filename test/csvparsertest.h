#ifndef CSVPARSERTEST_H
#define CSVPARSERTEST_H

#define protected public
#include "../main/csv/csv_parser.h"
#undef protected
#include "../main/logging/log.h"

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
        static Log sLog;

        static const std::string fileName;
        static void PrintLine(const csv::Parser::Line&);

        bool TestParseFile(const std::vector<csv::Parser::Line> &);
};

#endif // CSVPARSERTEST_H
