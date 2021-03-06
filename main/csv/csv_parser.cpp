#include "csv_parser.h"
#include <exception>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace csv {

        Log Parser::cLog("csv::Parser");
        const char Parser::separator;

        void Parser::SetFilter(const Filter* f) {
                filter = f;
        }

        const std::string& Parser::GetValue(size_t line, size_t fieldId) const {
                if (line >= lines.size())
                        throw std::range_error("Requested non-existent line " + std::to_string(line));
                else if (fieldId >= headFields.size())
                        throw std::range_error("Requested non-existent field " + std::to_string(fieldId));
                else
                        return lines[line][fieldId];
        }

        const std::string& Parser::GetValue(size_t line, const std::string& field) const {
                return GetValue(line, GetFieldId(field));
        }

        size_t Parser::GetLinesCount() const {
                return lines.size();
        }

        size_t Parser::GetFieldId(const std::string &field) const {
                auto it = std::find(headFields.cbegin(), headFields.cend(), field);
                if (it == headFields.end())
                        throw std::range_error("Requested non-existent field");
                else
                        return it - headFields.cbegin();
        }

        bool Parser::CheckFields(const Line &fields) const {
                return fields == this->headFields;
        }

        bool Parser::FindFields(const Line &testFields) const {
                for (auto &field : testFields) {
                        if (std::find(headFields.cbegin(), headFields.cend(), field) ==
                                headFields.cend())
                                return false;
                }
                return true;
        }

        bool Parser::FilterLine(const Line& l) const {
                S_LOG("FilterLine");
                if (filter) {
                        size_t fieldsCount = headFields.size();
                        for (size_t i = 0; i < fieldsCount; ++i) {
                                auto &field = headFields[i];
                                auto &val = l[i];
                                if (!filter->CheckValue(field, val)) {
                                        log(Log::error) << "Value {" << val << "} of field {" << field << "} is not allowed" << Log::endl;
                                        return false;
                                }
                        }
                }
                return true;
        }

        bool Parser::Load(const std::string &fileName) {
                S_LOG("Load");
                headFields.clear();
                lines.clear();
                std::ifstream cvs(fileName);
                size_t cnt(0);
                size_t fieldsCount(0);
                if (cvs.is_open()) {
                        while (cvs.good()) {
                                std::string str;
                                std::getline(cvs, str);
                                ++cnt;
                                if (cvs.good()) {
                                        if (str.empty())
                                                log(Log::notice, cnt) << "Empty line" << Log::endl;
                                        else if (fieldsCount == 0) {
                                                if (
                                                        !ParseLine(str, headFields, cnt) ||
                                                        (!headFields.empty() && filter && !filter->CheckFields(headFields))
                                                        )
                                                        return false;
                                                else
                                                        fieldsCount = headFields.size();
                                        } else {
                                                Line line;
                                                if (!ParseLine(str, line, cnt))
                                                        return false;
                                                else {
                                                        if (line.size() != fieldsCount) {
                                                                if (line.size() < headFields.size())
                                                                        log(Log::warning, cnt) <<
                                                                                "Not enough fields (" << line.size() << "/" <<
                                                                                fieldsCount <<
                                                                                ") in a line, adding blank fields" << Log::endl;
                                                                else if (line.size() > headFields.size())
                                                                        log(Log::warning, cnt) << "Too many fields (" <<
                                                                                line.size() << "/" << fieldsCount <<
                                                                                ") in a line, ignoring extra fields" << Log::endl;
                                                                line.resize(fieldsCount);
                                                        }
                                                        if (FilterLine(line))
                                                                lines.push_back(line);
                                                }
                                        }
                                } else
                                        break;
                        }
                        return true;
                } else
                        return false;
        }

        std::string::const_iterator Parser::FindSeparator(const std::string &s,
                const std::string::const_iterator &it, size_t lineNumber) {
                S_LOG("FindSeparator");
                auto res = it;
                if (res != s.end()) {
                        ++res;
                        if (res != s.end() && *res != separator) {
                                log(Log::warning, lineNumber, res - s.begin() + 2) << "Here should be a separator" << Log::endl;
                                res = std::find(res + 1, s.end(), separator);
                        }
                }
                return (res == s.end()) ? res : (res + 1);
        }

        bool Parser::ParseLine(const std::string& s, Line & l, size_t lineNumber) {
                S_LOG("ParseLine");
                auto it = s.begin();
                if (it == s.end())
                        l.emplace_back();
                else {
                        while (it != s.end()) {
                                char c = *it;
                                if (c == '"' || c == '\'') {
                                        auto closingQuote = (it + 1 == s.end()) ? s.end() : std::find(it + 1, s.end(), c);
                                        if (closingQuote == s.end()) {
                                                log(Log::error, lineNumber, it - s.begin()) << "Close quote not found" << Log::endl;
                                                l.emplace_back();
                                                break;
                                        } else {
                                                l.emplace_back(it + 1, closingQuote);

                                                it = FindSeparator(s, closingQuote, lineNumber);
                                        }
                                } else if (c == separator) {
                                        log(Log::warning, lineNumber, it - s.begin()) << "Empty field" << Log::endl;
                                        l.emplace_back();
                                        ++it;
                                        if (it == s.end())
                                                l.emplace_back();
                                } else {
                                        auto fieldEnd = std::find(it, s.end(), separator);
                                        l.emplace_back(it, fieldEnd);

                                        it = (fieldEnd == s.end()) ? fieldEnd : (fieldEnd + 1);
                                }
                        }
                }
                return true;
        }

        void Parser::PrintFields(const Line &fields, std::ostream &s) {
                for (auto it = fields.cbegin(); it != fields.cend(); ++it) {
                        s << "\"" << *it << "\"";
                        if (it + 1 != fields.cend())
                                s << ", ";
                }
        }

}
