/* Module Dynamics */
%module(directors="1") PyDynamics

%ignore operator<<;

%{
 /**** includes ****/ 
#include <vle/DllDefines.hpp>
#include <vle/devs/Time.hpp>

#include <vle/value/Value.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Integer.hpp>
#include <vle/value/Boolean.hpp>
#include <vle/value/String.hpp>

#include <vle/value/Null.hpp> /* +++ */
#include <vle/value/Table.hpp> /* +++ */
#include <vle/value/Tuple.hpp> /* +++ */
#include <vle/value/XML.hpp> /* +++ */

#include <vle/value/Map.hpp>
#include <vle/value/Set.hpp>

#include <vle/devs/InitEventList.hpp>
#include <vle/devs/ExternalEvent.hpp>
#include <vle/devs/ExternalEventList.hpp>
#include <vle/devs/ObservationEvent.hpp>
#include <vle/vpz/AtomicModel.hpp>

#include <vle/utils/PackageTable.hpp>
#include <vle/version.hpp>
#include <vle/devs/Dynamics.hpp>
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

%template(VectorValue) std::vector < vle::value::Value* >;
%template(MapValue) std::map < std::string, vle::value::Value* >;

/**** includes ****/ 

%include <vle/DllDefines.hpp> /* #define VLE_API */

%include <vle/devs/Dynamics.hpp>
%include <vle/DllDefines.hpp>

%include <vle/value/Value.hpp>
%include <vle/value/Double.hpp>
%include <vle/value/Integer.hpp>
%include <vle/value/Boolean.hpp>
%include <vle/value/String.hpp>
%include <vle/value/Map.hpp>
%include <vle/value/Set.hpp>
%include <vle/value/Null.hpp>

%include <vle/devs/Time.hpp>
%include <vle/devs/InitEventList.hpp>
%include <vle/devs/ExternalEvent.hpp>
%include <vle/devs/ExternalEventList.hpp>

%include <vle/devs/ObservationEvent.hpp>
%include <vle/vpz/AtomicModel.hpp>
%include <vle/utils/PackageTable.hpp>
%include <vle/version.hpp>


/* typedef vle::value::Map InitEventList; */
%pythoncode %{
    class InitEventList(Map) : pass
%}

