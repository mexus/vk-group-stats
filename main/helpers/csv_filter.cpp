/* 
 * File:   Filter.cpp
 * Author: mexus
 * 
 * Created on January 14, 2014, 11:12 PM
 */

#include "csv_filter.h"
#include <algorithm>
#include <iostream>

namespace csv {

        Filter::Filter() {

        }

        Filter::~Filter() {
        }

        void Filter::AddPossibleValue(const std::string& field, const std::string& value) {
                values[field].push_back(value);
        }

        void Filter::AddPossibleValues(const std::string& field, const std::vector<std::string>& passedValues) {
                std::vector<std::string> & vals = values[field];
                vals.insert(vals.end(), passedValues.begin(), passedValues.end());
        }

        bool Filter::CheckValue(const std::string& key, const std::string& value) const {
                auto fieldIt = values.find(key);
                if (fieldIt == values.end() || fieldIt->second.empty())
                        return true;
                else {
                        auto &possibleValues = fieldIt->second;
                        auto valueIt = std::find(possibleValues.begin(), possibleValues.end(), value);
                        return valueIt != possibleValues.end();
                }
        }

        bool Filter::CheckFields(const std::vector<std::string>& line) const {
                for (auto &pair : values) {
                        auto& lookupField = pair.first;
                        if (std::find(line.begin(), line.end(), lookupField) == line.end()) {
                                std::cout << "[Filter::CheckFields] Not found field {" << lookupField << "}" << std::endl;
                                return false;
                        }
                }
                return true;
        }

        void Filter::AddRequiredField(const std::string& field) {
                values[field];
        }

        void Filter::AddRequiredFields(const std::vector<std::string>& fields) {
                for (auto &field : fields)
                        AddRequiredField(field);
        }

}
