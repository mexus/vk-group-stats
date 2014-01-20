/* 
 * File:   log_helper.cpp
 * Author: mexus
 * 
 * Created on January 15, 2014, 3:02 PM
 */

#include <string>

#include "log.h"

std::mutex Log::lock;
const std::map<Log::LogLevel, std::string> Log::levelMessages {
        {Log::debug,    " Debug "},
        {Log::notice,   "Notice "},
        {Log::warning,  "Warning"},
        {Log::info,     " Info  "},
        {Log::error,    " Error "},
        {Log::nothing,  "Nothing"}
};
std::ostream Log::cnull(0);
std::ostream* Log::cdefault(&std::cout);

Log::Log(const std::string& label) : label(label) {
        
}

Log::Log(const Log& old, const std::string& label) : label(old.label) {
        AddLabel(label);
}

Log::~Log() {
}

void Log::AddLabel(const std::string& newLabel) {
        if (!newLabel.empty()) {
                if (!label.empty())
                        label += "::";
                label += newLabel;
        }
}

std::ostream& Log::endl(std::ostream& s) {
        s << std::endl;
        lock.unlock();
        return s;
}

std::ostream& Log::Print(std::ostream& s) const {
        return s;
}

void Log::SetLogLevel(Log::LogLevel l) {
        logLevel = l;
}


