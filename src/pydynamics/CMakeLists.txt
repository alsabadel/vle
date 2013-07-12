#Sources Vle
include_directories(${VLE_BINARY_DIR}/src ${VLE_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIRS} ${VLEDEPS_INCLUDE_DIRS})

link_directories(${VLEDEPS_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

#Sources Python
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

#Utilitaire Swig
SET(CMAKE_SWIG_FLAGS "")

#Création de _PyDynamics.so
SET_SOURCE_FILES_PROPERTIES(Dynamics.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(testDynamics python Dynamics.i testDynamics.cpp testDynamics.hpp)
SWIG_LINK_LIBRARIES(testDynamics ${PYTHON_LIBRARIES} vlelib)

#Installation de la librairie crée
INSTALL(TARGETS _testDynamics DESTINATION "lib/python/lib-dynload")
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/pydynamics/testDynamics.py DESTINATION "/lib/python")
