/*
 * @file PyDynamics.hpp
 *
 * This file is part of VLE, a framework for multi-modeling, simulation
 * and analysis of complex dynamical systems
 * http://www.vle-project.org
 *
 * Copyright (c) 2003-2007 Gauthier Quesnel <quesnel@users.sourceforge.net>
 * Copyright (c) 2003-2011 ULCO http://www.univ-littoral.fr
 * Copyright (c) 2007-2011 INRA http://www.inra.fr
 *
 * See the AUTHORS or Authors.txt file for copyright owners and contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef PYDYNAMICS_HPP
#define PYDYNAMICS_HPP

#include <iostream>

#include <Python.h>

#include <vle/devs/Dynamics.hpp>

//!!!#define SWIGRUNTIME_DEBUG 1
#include <DynamicsPYTHON_wrap.cxx> // renommer-installer <swigpyrun.h> ? !!!

namespace pydynamics {

    class PyDynamics : public vle::devs::Dynamics {

    private:
        // Swig types !!! a completer
        static swig_type_info *swig_DynamicsInit;
        static swig_type_info *swig_InitEventList;
	static swig_type_info *swig_ExternalEventList;
        static swig_type_info *swig_ObservationEvent;
        static swig_type_info *swig_Value;

	PyObject *pSelf;	

        vle::devs::DynamicsInit m_init;
        vle::devs::InitEventList m_initevents;

        /// Nom du modele python (dont code python installe sous pythonsrc de son paquet)
        std::string m_modelname;
        /// Nom du paquet du modele python (dont code python installe sous pythonsrc de son paquet)
        std::string m_pkgname;

        // specific methods
        void _test(PyObject *obj, const char *name) const; 
        void _testTime(double d, const char *name) const; 
	void load_types();

    public:
        PyDynamics(const vle::devs::DynamicsInit& init,
                const vle::devs::InitEventList& events);
        virtual ~PyDynamics();

        // DEVS Methods
        virtual void finish();
        virtual vle::devs::Time init(const vle::devs::Time& /* time */);
        virtual void output(const vle::devs::Time& /* time */,
                     vle::devs::ExternalEventList& /* output */) const;
        virtual vle::devs::Time timeAdvance() const;
        virtual void internalTransition( const vle::devs::Time& /* time */);
        virtual void externalTransition(const vle::devs::ExternalEventList& /* event */,
                     const vle::devs::Time& /* time */);
        virtual void confluentTransitions( const vle::devs::Time& /* time */,
                     const vle::devs::ExternalEventList& /* extEventlist */) const;
        virtual vle::value::Value* observation(const vle::devs::ObservationEvent& /* event */) const;

    }; // class PyDynamics

} // namespace pydynamics

DECLARE_DYNAMICS(pydynamics::PyDynamics)

#endif

