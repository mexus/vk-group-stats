#include "vk_data.h"
#include "helpers/csv_parser.h"
#include "helpers/csv_filter.h"
#include <iostream>

VkData::VkData() {
}

bool VkData::LoadCSV(const std::string & f) {
        using namespace csv;
        Parser parser;
        Filter filter;
        parser.SetFilter(&filter);

        static const Parser::Line fields{"Date", "Criterion", "Parameter 1", "Parameter 2", "Value"};
        filter.AddRequiredFields(fields);
        filter.AddPossibleValue("Criterion", "members");
        filter.AddPossibleValues("Parameter 1",{"New members", "Members lost"});

        if (!parser.Load(f)) {
                std::cerr << "VkData::LoadCSV " << "Failed to load file" << std::endl;
                return false;
        } else {
                if (!parser.FindFields(fields)) {
                        std::cerr << "Wrong fields, should be: ";
                        Parser::PrintFields(fields, std::cerr);
                        std::cerr << std::endl;
                        return false;
                } else {
                        ParseCSV(parser);
                        return true;
                }
        }
}

void VkData::ParseCSV(const csv::Parser &p) {
        using namespace csv;
        size_t dateField = p.GetFieldId("Date");
        size_t criterionField = p.GetFieldId("Criterion");
        size_t parameterField = p.GetFieldId("Parameter 1");
        size_t valueField = p.GetFieldId("Value");

        size_t n = p.GetLinesCount();
        for (size_t i = 0; i < n; ++i) {
                DateHelper date(p.GetValue(i, dateField));
                if (date.IsValid()) {
                        if (p.GetValue(i, criterionField) == "members") {

                                enum {
                                        modeNew,
                                        modeLost
                                } mode;
                                auto modeString = p.GetValue(i, parameterField);
                                if (modeString == "New members")
                                        mode = modeNew;
                                else if (modeString == "Members lost")
                                        mode = modeLost;
                                else {
                                        std::cout << "VkData::ParseCSV " << "Unknown mode {" << modeString << "}" << std::endl;
                                        continue;
                                }
                                unsigned long int visitors = std::stoul(p.GetValue(i, valueField));
                                switch (mode) {
                                        case modeNew:
                                                membersIn[date] = visitors;
                                                break;
                                        case modeLost:
                                                membersOut[date] = visitors;
                                }

                        }
                }
        }
}
