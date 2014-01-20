/* 
 * File:   log_helper.cpp
 * Author: mexus
 * 
 * Created on January 15, 2014, 3:02 PM
 */

#include <string>
#include <memory>

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
Log::LogLevel Log::globalLogLevel = Log::debug;

Log::Log(const std::string& label) : label(label) {
        
}

Log::Log(const std::string& label, LogLevel level) : label(label) {
        OverrideLogLevel(level);
}


Log::Log(const Log& old, const std::string& label) : label(old.label), overrideLogLevel(old.overrideLogLevel) {
        AddLabel(label);
}

Log::Log(const Log& old, const std::string& label, LogLevel level) : label(old.label) {
        OverrideLogLevel(level);
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
        globalLogLevel = l;
}

Log::LogLevel Log::GetLogLevel() const {
        if (overrideLogLevel)
                return *(overrideLogLevel.get());
        else
                globalLogLevel;
}

void Log::OverrideLogLevel(){
        overrideLogLevel.reset();
}

void Log::OverrideLogLevel(Log::LogLevel l) {
        overrideLogLevel = std::shared_ptr<LogLevel>(new LogLevel(l));
}



