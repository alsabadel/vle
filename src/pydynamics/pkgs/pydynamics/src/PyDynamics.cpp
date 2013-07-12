/*
 * @file PyDynamics.cpp
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

#include <iostream>

#include <vle/utils/Path.hpp>
#include <vle/utils/Package.hpp>

#include "PyDynamics.hpp"

namespace pydynamics {

swig_type_info *PyDynamics::swig_DynamicsInit = 0;
swig_type_info *PyDynamics::swig_InitEventList = 0;
swig_type_info *PyDynamics::swig_ExternalEventList = 0;
swig_type_info *PyDynamics::swig_ObservationEvent = 0;
swig_type_info *PyDynamics::swig_Value = 0;

#define test(x) _test(x,#x)
#define testTime(x) _testTime(x,#x)

void PyDynamics::_test(PyObject *obj, const char *name) const {
    if (!obj) {
        std::cout << "\n\n... _test : ERROR !!!!!!!!!!!!!!!!!!!!!\n\n";
	    if (PyErr_Occurred()){
            std::cout << "... PyErr_Print() : ";
            PyErr_Print();
        } 
	    throw vle::utils::InternalError(string("on ")+name);
    } 
    //std::cout << name << " _test : no error \n";
}

void PyDynamics::_testTime(double d, const char *name) const {
    if(d == -1)
    {
        std::cout << "--- _testTime ERROR !!!! Value not a double ! \n"; 
	throw vle::utils::InternalError(string("on ")+"Time");
    }
    //std::cout << name << " _testTime : no error \n";
}

PyDynamics::PyDynamics(const vle::devs::DynamicsInit& init,
                       const vle::devs::InitEventList& events) :
            vle::devs::Dynamics(init, events),
            m_init(init),
            m_initevents(events),
            m_modelname("MyModelPy"), // par defaut
            m_pkgname("pydynamics") // par defaut
{ 
    //std::cout << "PyDynamics constructeur \n";
        
    //.......

}

PyDynamics::~PyDynamics() 
{ 
    //std::cout << "PyDynamics destructeur \n";

    Py_DECREF(pSelf);
    //!!!Py_DECREF(pModule);
    //!!!Py_DECREF(pDict);
    //!!!Py_DECREF(pClass);
    //!!!Py_Finalize(); //!!! if (--load == 0) 
    // Finish the Python Interpreter
    Py_Finalize();

    //std::cout << "HHHHHHH \n";
}


void PyDynamics::finish() {
    //std::cout << "PyDynamics::finish \n";

    //.......
};

void PyDynamics::load_types()
{
    // Load types !!!!
    swig_DynamicsInit = SWIG_TypeQuery("vle::devs::DynamicsInit *");
    swig_InitEventList = SWIG_TypeQuery("vle::devs::InitEventList *");
    swig_ExternalEventList = SWIG_TypeQuery("vle::devs::ExternalEventList *");
    swig_ObservationEvent = SWIG_TypeQuery("vle::devs::ObservationEvent *");
    swig_Value = SWIG_TypeQuery("vle::value::Value *");
}

vle::devs::Time PyDynamics::init( const vle::devs::Time& time )
{
    //std::cout << "PyDynamics::init \n";

    // Parameters

    if ( m_initevents.exist("modelname") ){
	    m_modelname = vle::value::toString( m_initevents.get( "modelname" ));
    }
    if ( m_initevents.exist("pkgname") ){
	    m_pkgname = vle::value::toString( m_initevents.get( "pkgname" ));
    }

    //std::cout << "\n";
    //std::cout << "nom du modele python : " << m_modelname << ", ";
    //std::cout << "nom du paquet du modele python : " << m_pkgname << ", ";
    //std::cout << "le code python " << m_modelname << ".py doit etre installe sous " << m_pkgname << "/pythonsrc." << "\n";
    std::cout << "\n";

/* debut essai *******************************************/

    /* CODE TEMPORAIRE essai OK d'appel du code python */

    PyObject *pName, *pModule, *pDict;
    PyTypeObject *pClass;
    PyObject *pTuple;


    // Initialize the Python Interpreter
    Py_Initialize();

    SWIG_init(); //!!!

    //std::cout << "000000000 \n";

    // Add pydynamics_wrapper and model path to pythonpath
    //!!! revoir le codage des path relativement aux path de paquets

    // wrapper : "...vle-1.1/pkgs-1.1/pydynamics_wrapper/wrapping"
    std::string pydynamics_wrapper_library_path = utils::Path::buildDirname( vle::utils::Path::path().getHomeDir(), "pkgs-1.1" );
    pydynamics_wrapper_library_path = utils::Path::buildDirname( pydynamics_wrapper_library_path, "pydynamics_wrapper" );
    pydynamics_wrapper_library_path = utils::Path::buildDirname( pydynamics_wrapper_library_path, "wrapping" );

    // modele python : pythonsrc de son paquet "....vle-1.1/pkgs-1.1/pydynamics/pythonsrc"
    std::string model_library_path = utils::Path::buildDirname( vle::utils::Path::path().getHomeDir(), "pkgs-1.1" );
    model_library_path = utils::Path::buildDirname( model_library_path, m_pkgname );
    model_library_path = utils::Path::buildDirname( model_library_path, "pythonsrc" );
    // /!\ hack pour avoir le python path sous ubuntu (voir a débuger avec Py_GetPath() ) traiter le cas des eggs 
    // /!\ /usr
    std::string debian_python_package_path = utils::Path::buildDirname("/usr", "lib", "python2.7", "dist-packages");  
    std::string local_debian_python_package_path = utils::Path::buildDirname("/usr", "local","lib", "python2.7", "dist-packages");  

    std::string total_path = std::string(Py_GetPath()) + ":" + pydynamics_wrapper_library_path + ":" + model_library_path + ":" + debian_python_package_path + ":" + local_debian_python_package_path;
    PySys_SetPath((char *)total_path.c_str());

    std::cout << "total_path vaut : " << total_path << "\n";
    std::cout << "000000001 \n";

    // Build the name object
    std::string model_library = m_modelname;
    pName = PyString_FromString(model_library.c_str());
    test(pName);

    // Load the module object
    pModule = PyImport_Import(pName);
    test(pModule);
    Py_DECREF(pName); // clean up

    // Load types !!!!
    load_types();

    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    test(pDict);

    pClass = (PyTypeObject*)PyDict_GetItemString(pDict, model_library.c_str());
    Py_DECREF(pDict); // clean up
    if (pClass != NULL) {
        std::cout << "pClass 'ok' \n";
    } else {
        std::cout << "pClass NOT OK \n";
    }

    pTuple = PyTuple_New(2);
    test(pTuple);

    //std::cout << "AAAAAAAAAAAA_1003 \n";
  
    PyObject *pInit = SWIG_NewPointerObj((void*)(&m_init), swig_DynamicsInit, 0);
    test(pInit);

    PyObject *pEvents = SWIG_NewPointerObj((void*)(&m_initevents), swig_InitEventList, 0);
    test(pEvents);

    PyTuple_SetItem(pTuple, 0, pInit);
    PyTuple_SetItem(pTuple, 1, pEvents);

    pSelf = PyType_GenericNew(pClass, pTuple, 0);
    test(pSelf);

    //std::cout << "AAAAAAAAAAAA_1008 \n";

    PyObject* pConstructor = PyObject_GetAttrString(pSelf, "__init__");
    test( pConstructor );

    //std::cout << "AAAAAAAAAAAA_1010 \n";

    PyObject *pResult = PyObject_Call(pConstructor, pTuple, 0);
    test(pResult);
 
    Py_DECREF(pTuple); // clean up
   

    // *** Appel fonction python init *** //
    PyObject *pObject = PyObject_CallMethod(pSelf, (char*)"init", (char*) "d", time, 0);
    test(pObject); 
    std::cout << "Initialisation ok \n";
    double p_Time = PyFloat_AsDouble(pObject);
    Py_DECREF(pObject); // clean up
    testTime(p_Time);

    //std::cout << "Mon double Py : " << p_Time << " \n";
    //std::cout << "AAAAAAAAAAAA_1011 \n";

    //-----
    
    // clean up
    Py_DECREF(pModule); 

    
    //std::cout << "GGGGGGG \n";
/* fin essai *********************************************/
    if(p_Time == vle::devs::infinity)
        return vle::devs::infinity;
    else if (p_Time == vle::devs::negativeInfinity)
        return vle::devs::negativeInfinity;  
    else
        return vle::devs::Time(p_Time);

    //return vle::devs::infinity; //!!!
    //return vle::devs::negativeInfinity; //!!!
}


void PyDynamics::output(const vle::devs::Time& time,
                     vle::devs::ExternalEventList& output) const
{
    //std::cout << "PyDynamics::output \n";

    PyObject *pEvent = SWIG_NewPointerObj((void*)(&output), swig_ExternalEventList, 0);
    test(pEvent);

    PyObject *pObject = PyObject_CallMethod(pSelf, (char*)"output", (char*)"dO", time, pEvent, 0);
    test(pObject);

    Py_DECREF(pEvent); // clean up
    Py_DECREF(pObject); // clean up
}

vle::devs::Time PyDynamics::timeAdvance() const
{
    //std::cout << "PyDynamics::timeAdvance \n";
    
    PyObject *pTime = PyObject_CallMethod(pSelf, (char*)"timeAdvance", 0);
    test(pTime);

    double c_ptr = PyFloat_AsDouble(pTime);
    testTime(c_ptr);
    //std::cout << "Mon double Py : " << c_ptr << " \n";
    
    Py_DECREF(pTime); // clean up

    if(c_ptr == vle::devs::infinity)
        return vle::devs::infinity;
    else if (c_ptr == vle::devs::negativeInfinity)
        return vle::devs::negativeInfinity;  
    else
        return vle::devs::Time(c_ptr);
}


void PyDynamics::internalTransition(
        const vle::devs::Time& time)
{
    //std::cout << "PyDynamics::internalTransition \n";
    
    PyObject *pObject = PyObject_CallMethod(pSelf, (char*)"internalTransition", (char*)"d", time, 0);
    test(pObject);  

    Py_DECREF(pObject); // clean up  
}

void PyDynamics::externalTransition(
        const vle::devs::ExternalEventList& event,
        const vle::devs::Time& time)
{
    //std::cout << "PyDynamics::externalTransition \n";

    PyObject *pEvent = SWIG_NewPointerObj((void*)(&event), swig_ExternalEventList, 0);
    test(pEvent);


    PyObject *pObject = PyObject_CallMethod(pSelf, (char*)"externalTransition", (char*)"Od", pEvent, time, 0);
    test(pObject); 

    Py_DECREF(pEvent); // clean up 
    Py_DECREF(pObject); // clean up 
}

void PyDynamics::confluentTransitions( 
        const vle::devs::Time& time,
        const vle::devs::ExternalEventList& extEventlist) const
{
    //std::cout << "PyDynamics::confluentTransition \n";

    PyObject *pExternal = SWIG_NewPointerObj((void*)(&extEventlist), swig_ExternalEventList, 0);
    test(pExternal);

    PyObject *pObject = PyObject_CallMethod(pSelf, (char*)"confluentTransition", (char*)"dO", time, pExternal, 0);
    test(pObject);

    Py_DECREF(pExternal); // clean up 
    Py_DECREF(pObject); // clean up 
    //return (Event::EventType)PyInt_AsLong(pObject);  
}


vle::value::Value* PyDynamics::observation(const vle::devs::ObservationEvent& event) const
{
    //std::cout << "PyDynamics::observation \n";
    
    PyObject *pEvent = SWIG_NewPointerObj((void*)(&event), swig_ObservationEvent, 0);
    test(pEvent);    

    PyObject *pObject = PyObject_CallMethod(pSelf, (char*)"observation", (char*)"O", pEvent, 0);
    test(pObject);
    
    Value* c_ptr = 0;

    SWIG_ConvertPtr(pObject, (void **) &c_ptr, swig_Value, 0);
    // vérifier que c'est une value
    //std::cout << "valeur reçue de python : " << c_ptr->writeToString () << "\n";

    Py_DECREF(pEvent); // clean up 
    Py_DECREF(pObject); // clean up 

    return c_ptr; //!!!
}

} // namespace pydynamics
