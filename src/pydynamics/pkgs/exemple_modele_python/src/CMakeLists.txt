include_directories(${CMAKE_SOURCE_DIR}/src ${VLE_INCLUDE_DIRS}
  ${VLE_DEPS_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${CELLDEVS_INCLUDE_DIRS} 
  ${CELLQSS_INCLUDE_DIRS}
  ${DECISION_INCLUDE_DIRS} ${DIFFERENCE_EQU_INCLUDE_DIRS}
  ${DIFFERENTIAL_EQU_INCLUDE_DIRS} ${DSDEVS_INCLUDE_DIRS} ${FSA_INCLUDE_DIRS}
  ${PETRINET_INCLUDE_DIRS})

link_directories(${VLE_LIBRARY_DIRS}
  ${VLE_DEPS_LIBRARY_DIRS} ${CELLDEVS_LIBRARY_DIRS}
  ${CELLQSS_LIBRARY_DIRS} ${DECISION_LIBRARY_DIRS}
  ${DIFFERENCE_EQU_LIBRARY_DIRS} ${DIFFERENTIAL_EQU_LIBRARY_DIRS}
  ${DSDEVS_LIBRARY_DIRS} ${FSA_LIBRARY_DIRS} ${PETRINET_LIBRARY_DIRS})

###DeclareDevsDynamics(Simple "Simple.cpp")

#####

###INSTALL(FILES ModeleEssai.py DESTINATION pythonsrc)
INSTALL(DIRECTORY . DESTINATION pythonsrc FILES_MATCHING PATTERN "*.py")

#####


#
# this macro manage generated C++ code
#
#
CheckAndDeclareGeneratedModels()

