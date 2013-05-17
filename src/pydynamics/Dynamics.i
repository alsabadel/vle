/* Module Dynamics */
%module(directors="1") testDynamics
%ignore vle::devs::operator<<;
%{
 /**** includes ****/ 
#include <vle/DllDefines.hpp>
#include <vle/devs/Time.hpp>
#include <vle/devs/InitEventList.hpp>
#include <vle/devs/ObservationEvent.hpp>
#include <vle/vpz/AtomicModel.hpp>
#include <vle/value/Value.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Integer.hpp>
#include <vle/value/Boolean.hpp>
#include <vle/value/String.hpp>
#include <vle/value/Map.hpp>
#include <vle/value/Set.hpp>
#include <vle/utils/PackageTable.hpp>
#include <vle/version.hpp>
#include <vle/devs/ExternalEvent.hpp>
#include <vle/devs/ExternalEventList.hpp>
//#include <vle/devs/Dynamics.hpp>
#include "testDynamics.hpp"
#include <Python.h>
%}

%{
using namespace vle;
using namespace vle::devs;
using namespace vle::value;
using namespace vle::vpz;
using namespace vle::utils;
using namespace std;
%}

%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>
%include <std_set.i>
%include <stdint.i> 
%include <stl.i>

%template(ExternalEventList) std::vector < vle::devs::ExternalEvent* >;
//%typemap(out) const string& { $result = PyString_FromString($1.c_str()); }
//%apply const string& {std::string*};
//%apply const map& {std::map*};

%template(VectorValue) std::vector < vle::value::Value* >;
%template(MapValue) std::map < std::string, vle::value::Value* >;

#define VLE_API


/**** includes ****/ 
%include "testDynamics.hpp"
//%include <vle/devs/Dynamics.hpp>
%include <vle/DllDefines.hpp>
%include <vle/devs/Time.hpp>
%include <vle/devs/InitEventList.hpp>
%include <vle/devs/ObservationEvent.hpp>
%include <vle/vpz/AtomicModel.hpp>
%include <vle/value/Value.hpp>
%include <vle/value/Double.hpp>
%include <vle/value/Integer.hpp>
%include <vle/value/Boolean.hpp>
%include <vle/value/String.hpp>
%include <vle/value/Map.hpp>
%include <vle/value/Set.hpp>
%include <vle/devs/ExternalEvent.hpp>
%include <vle/devs/ExternalEventList.hpp>
%include <vle/utils/PackageTable.hpp>
%include <vle/version.hpp>
