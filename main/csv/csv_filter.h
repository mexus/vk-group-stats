/* 
 * File:   Filter.h
 * Author: mexus
 *
 * Created on January 14, 2014, 11:12 PM
 */

#ifndef FILTER_H
#define	FILTER_H

#include <map>
#include <vector>
#include <string>
#include "../logging/log.h"

namespace csv {

        class Filter {
        public:
                Filter();
                virtual ~Filter();

                void AddPossibleValue(const std::string& field, const std::string& value);
                void AddPossibleValues(const std::string& field, const std::vector<std::string>& value);
                void AddRequiredField(const std::string& field);
                void AddRequiredFields(const std::vector<std::string>& fields);

                bool CheckValue(const std::string &key, const std::string &value) const;
                bool CheckFields(const std::vector<std::string> &line) const;
        protected:
                static Log cLog;
        private:
                std::map<std::string, std::vector<std::string> > values;
        };

}

#endif	/* FILTER_H */

