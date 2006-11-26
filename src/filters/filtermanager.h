/* This file is part of Strigi Desktop Search
 *
 * Copyright (C) 2006 Flavio Castelli <flavio.castelli@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
#ifndef FILTERMANAGER_H
#define FILTERMANAGER_H

#include <map>
#include <string>
#include "strigi_thread.h"
#include <vector>

class Filter;

/**
* @class FilterManager
* @brief Class used for managing filters
*
* Manage all filtering rules, taking care of load, save, check operations
* @sa Filter
*/

class FilterManager
{
    public:
        FilterManager();
        ~FilterManager();

        /**
        * check if text matches a filtering rules
        * @return true if text matches a filtering rule, false otherwise
        */
        bool findMatch(const std::string& text);

        /**
         * convenience method, same as above
         * @param text message
         * @param len length of message
         */
        bool findMatch(const char* text, uint len);

        /**
         * @return a multimap with filtering RTTI as key, and m_rule as value
         */
        std::multimap<int,std::string> getFilteringRules();
        void setFilteringRules(const std::multimap<int,std::string>& rules);

    private:
        void clearRules();

        std::vector<Filter*> m_rules;
        std::string m_strigidir;
        StrigiMutex m_rulesMutex;
};

#endif

