/** 
 * @file vpz/Condition.hpp
 * @brief 
 * @author The vle Development Team
 * @date mar, 31 jan 2006 17:19:48 +0100
 */

/*
 * Copyright (C) 2006 - The vle Development Team
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef VLE_VPZ_CONDITION_HPP
#define VLE_VPZ_CONDITION_HPP

#include <string>
#include <map>
#include <vle/vpz/Base.hpp>
#include <vle/value/Map.hpp>
#include <vle/value/Set.hpp>

namespace vle { namespace vpz {

    /** 
     * @brief Define the ConditionValues like a dictionnary, (portname, values).
     */
    typedef std::map < std::string, value::Set > ConditionValues;

    /** 
     * @brief Define the ValueList to a vle::value::MapValue.
     */
    class ValueList : public std::map < std::string, value::Value >
    {
    public:
        value::Value get(const std::string& name);

        const value::Value& get(const std::string& name) const;
    };

    /** 
     * @brief A condition define a couple model name, port name and a Value.
     * This class allow loading and writing a condition.
     */
    class Condition : public Base
    {
    public:
        Condition(const std::string& name);

        virtual ~Condition() 
        { }

        /** 
         * @brief Add Condition informations to the stream.
         * @code
         * <condition name="">
         *  <port name="">
         *   <!-- vle::value XML representation. -->
         *  </port>
         * </condition>
         * @endcode
         * 
         * @param out 
         */
        virtual void write(std::ostream& out) const;

        inline virtual Base::type getType() const
        { return CONDITION; }

        ////
        //// Manage the ConditionValues
        ////

        /** 
         * @brief Get a reference to the ConditionValues.
         * @return A constant reference to the ConditionValues.
         */
        inline const ConditionValues& conditionvalues() const
        { return m_list; }

        /** 
         * @brief Add a port to the value list.
         * @param portname name of the port.
         */
        void add(const std::string& portname);

        /** 
         * @brief Remove a port of the value list.
         * @param portname name of the port.
         */
        void del(const std::string& portname);

        /** 
         * @brief Add a value to a specified port. If port does not exist, it
         * will be create.
         * @param portname name of the port to add value. 
         * @param value the value to push.
         */
        void addValueToPort(const std::string& portname,
                            const value::Value& value);

        ////
        //// Get/Set function
        ////

        /** 
         * @brief Return the name of the condition.
         * @return 
         */
        inline const std::string& name() const
        { return m_name; }

        /** 
         * @brief Build a new ValueList based on the SetList with only the
         * first value for each Set.
         * @return A cloned ValueList based on the SetList.
         */
        ValueList firstValues() const;

        /** 
         * @brief Get the value::Set attached to a port.
         * @param portname The name of the port.
         * @return A reference to a value::Set.
         * @throw Exception::Internal if portname not exist.
         */
        const value::Set& getSetValues(const std::string& portname) const;

        /** 
         * @brief Return a reference to the first value::Value of the specified
         * port.
         * @param portname the name of the port to test.
         * @return A reference to a value::Value.
         * @throw Exception::Internal if portname not exist.
         */
        const value::Value& firstValue(const std::string& portname) const;

        /** 
         * @brief Return a reference to the nth value::Value of the specified
         * port.
         * @param portname the name of the specified port.
         * @param i the value of the port.
         * @return A reference to a value::Value.
         * @throw Exception::Internal if portname not exist or if value list
         * have no nth value.
         */
        const value::Value& nValue(const std::string& portname, size_t i) const;

        /** 
         * @brief Return a reference to the value::Set of the latest added port.
         * This function is principaly used in Sax parser.
         * @return A reference to the value::Set of the port.
         * @throw Exception::Internal if port does not exist.
         */
        value::Set& lastAddedPort();

        /** 
         * @brief Return true if this condition is a permanent data for the
         * devs::ModelFactory.
         * @return True if this condition is a permanent value.
         */
        inline bool isPermanent() const
        { return m_ispermanent; }

        /** 
         * @brief Set the permanent value of this condition.
         * @param value True to conserve this condition in devs::ModelFactory.
         */
        inline void permanent(bool value = true)
        { m_ispermanent = value; }

        /** 
         * @brief This function initialise every, to each port, a new
         * value::Set.
         */
        void rebuildValueSet();

    private:
        Condition();

        ConditionValues         m_list;         /* list of port, values. */
        std::string             m_name;         /* name of the condition. */
        std::string             m_last_port;    /* latest added port. */
        bool                    m_ispermanent;
    };

}} // namespace vle vpz

#endif
