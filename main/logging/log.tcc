#include <iostream>

#include "log.h"

template<class ...Args>
std::ostream& Log::operator()(Log::LogLevel level, Args... args){
        if (level >= GetLogLevel()){
                lock.lock();
                if (label.empty())
                        return Print(*cdefault, levelMessages.at(level), args...);
                else
                        return Print(*cdefault, levelMessages.at(level), label, args...);
        } else
                return cnull;
}

template<class T, class ...Args>
std::ostream& Log::Print(std::ostream& s, T t, Args... args) const{
        s << "[" << t << "] ";
        return Print(s, args...);
}
