MESSAGE( "" )
MESSAGE( "!!! en dur a changer !!!" )
SET(VLE_BINARY_DIR /home/alsabadel/tmp/vle/build )
SET(VLE_SOURCE_DIR /home/alsabadel/tmp/vle )
#SET(VLE_BINARY_DIR /pub/install/vle-1.1/vle/build )
#SET(VLE_SOURCE_DIR /pub/install/vle-1.1/vle )

###SET(VLEDEPS_INCLUDE_DIRS /usr/include/glibmm-2.4;/usr/lib/x86_64-linux-gnu/glibmm-2.4/include;/usr/include/sigc++-2.0;/usr/lib/x86_64-linux-gnu/sigc++-2.0/include;/usr/include/glib-2.0;/usr/lib/x86_64-linux-gnu/glib-2.0/include;/usr/include/libxml2;/usr/include/cairomm-1.0;/usr/lib/x86_64-linux-gnu/cairomm-1.0/include;/usr/include/cairo;/usr/include/pixman-1;/usr/include/freetype2;/usr/include/libpng12;/usr/include/gtkmm-2.4;/usr/lib/x86_64-linux-gnu/gtkmm-2.4/include;/usr/include/atkmm-1.6;/usr/include/giomm-2.4;/usr/lib/x86_64-linux-gnu/giomm-2.4/include;/usr/include/pangomm-1.4;/usr/lib/x86_64-linux-gnu/pangomm-1.4/include;/usr/include/gtk-2.0;/usr/include/gtk-unix-print-2.0;/usr/include/gdkmm-2.4;/usr/lib/x86_64-linux-gnu/gdkmm-2.4/include;/usr/include/atk-1.0;/usr/include/pango-1.0;/usr/lib/x86_64-linux-gnu/gtk-2.0/include;/usr/include/gdk-pixbuf-2.0;/usr/include/gio-unix-2.0/ )

INCLUDE_DIRECTORIES(
    ${VLE_BINARY_DIR}/src
    ${VLE_SOURCE_DIR}/src
    ${PYTHON_INCLUDE_PATH}
    ${Boost_INCLUDE_DIRS}
    ${VLEDEPS_INCLUDE_DIRS})
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})


MESSAGE( "" )
MESSAGE( "{VLE_BINARY_DIR} : ${VLE_BINARY_DIR} " )
MESSAGE( "{VLE_SOURCE_DIR} : ${VLE_SOURCE_DIR} " )
MESSAGE( "{Boost_INCLUDE_DIRS} : ${Boost_INCLUDE_DIRS} " )
MESSAGE( "{VLEDEPS_INCLUDE_DIRS} : ${VLEDEPS_INCLUDE_DIRS} " )
MESSAGE( "" )
MESSAGE( "VLEDEPS_LIBRARY_DIRS} : ${VLEDEPS_LIBRARY_DIRS} " )
MESSAGE( "Boost_LIBRARY_DIRS} : ${Boost_LIBRARY_DIRS} " )
MESSAGE( "VLE_LIBRARIES} : ${VLE_LIBRARIES} " )
MESSAGE( "" )


SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(Dynamics.i PROPERTIES CPLUSPLUS ON)

SWIG_ADD_MODULE(PyDynamics python Dynamics.i ${VLE_SOURCE_DIR}/src/vle/devs/Dynamics.cpp ${VLE_SOURCE_DIR}/src/vle/devs/Dynamics.hpp)
SWIG_LINK_LIBRARIES(PyDynamics ${PYTHON_LIBRARIES} )
#??? SWIG_LINK_LIBRARIES(PyDynamics ${PYTHON_LIBRARIES} ${VLE_LIBRARIES})

# tout installe sous wrapping
INSTALL(TARGETS _PyDynamics DESTINATION wrapping)
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/PyDynamics.py DESTINATION wrapping)
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/DynamicsPYTHON_wrap.h DESTINATION wrapping)
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/DynamicsPYTHON_wrap.cxx DESTINATION wrapping)
INSTALL(FILES convert.py DESTINATION wrapping)

