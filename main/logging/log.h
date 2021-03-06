/* 
 * File:   log_helper.h
 * Author: mexus
 *
 * Created on January 15, 2014, 3:02 PM
 */

#ifndef LOG_HELPER_H
#define	LOG_HELPER_H

#include <mutex>
#include <string>
#include <ostream>
#include <map>
#include <memory>

class Log {
public:
        enum LogLevel {
                debug,
                notice,
                warning,
                info,
                error,
                nothing
        };
        
        Log(const std::string& label = std::string());
        Log(const std::string& label, LogLevel level);
        Log(const Log&, const std::string& label);
        Log(const Log&, const std::string& label, LogLevel level);
        virtual ~Log();
        
        void OverrideLogLevel();
        void OverrideLogLevel(Log::LogLevel);
        static void SetLogLevel(Log::LogLevel);
        
        template<class ...Args>
        std::ostream& operator()(Log::LogLevel, Args... args);
        
        static std::ostream& endl(std::ostream&);
private:
        static std::mutex lock;
        static const std::map<LogLevel, std::string> levelMessages;
        
        static std::ostream cnull, *cdefault;
        
        std::string label;
        static LogLevel globalLogLevel;
        std::shared_ptr<LogLevel> overrideLogLevel;
        
        void AddLabel(const std::string &newLabel);
        LogLevel GetLogLevel() const;
        template<class T, class ...Args>
        std::ostream& Print(std::ostream&, T t, Args... args) const;
        std::ostream& Print(std::ostream&) const;

};

#define S_LOG(label) \
        static Log log(cLog, label)

#define D_LOG(label) \
        Log log(cLog, label)

#include "log.tcc"

#endif	/* LOG_HELPER_H */

