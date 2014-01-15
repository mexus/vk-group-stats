#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "log_helper.h"
#include "csv_filter.h"

namespace csv {

        class Parser {
        public:
                typedef std::vector<std::string> Line;

                void SetFilter(const Filter * = nullptr);
                bool Load(const std::string &file);

                const std::string& GetValue(size_t Line, size_t fieldId) const;
                const std::string& GetValue(size_t Line, const std::string&) const;
                size_t GetFieldId(const std::string &) const;
                size_t GetLinesCount() const;
                bool CheckFields(const Line& fields) const;
                bool FindFields(const Line& fields) const;

                static void PrintFields(const Line& fields, std::ostream& = std::cout);
        protected:
                Line headFields;
                std::vector<Line> lines;
                const Filter *filter = nullptr;
                static Log log;

                bool FilterLine(const Line&) const;

                static std::string::const_iterator FindSeparator(const std::string& str,
                        const std::string::const_iterator &it, size_t lineNumber);
                static bool ParseLine(const std::string& str, Line &, size_t lineNumber);

//                static std::ostream& Log(const std::string &type, size_t Line);
//                static std::ostream& Log(const std::string &type, size_t Line, size_t pos);

                static const char separator = ',';
        };
}
