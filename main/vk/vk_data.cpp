#include "vk_data.h"
#include "../csv/csv_parser.h"
#include <iostream>

Log VkData::sLog("VkData");

VkData::VkData() {
}

bool VkData::LoadCSV(const std::string & f) {
        S_LOG("LoadCSV");
        using namespace csv;
        Parser parser;
        Filter filter;
        parser.SetFilter(&filter);

        static const Parser::Line fields{"Date", "Criterion", "Parameter 1", "Parameter 2", "Value"};
        filter.AddRequiredFields(fields);
        filter.AddPossibleValue("Criterion", "members");
        filter.AddPossibleValues("Parameter 1",{"New members", "Members lost"});

        if (!parser.Load(f)) {
                log(Log::error) << "VkData::LoadCSV " << "Failed to load file" << Log::endl;
                return false;
        } else {
                if (!parser.FindFields(fields)) {
                        auto &s = log(Log::error) << "Wrong fields, should be: ";
                        Parser::PrintFields(fields, s);
                        s << Log::endl;
                        return false;
                } else {
                        ParseCSV(parser);
                        return true;
                }
        }
}

void VkData::ParseCSV(const csv::Parser &p) {
        S_LOG("ParseCSV");
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
                                        log(Log::warning) << "Unknown mode {" << modeString << "}" << Log::endl;
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
