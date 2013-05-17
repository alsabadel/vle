add_subdirectory(vle)
add_subdirectory(apps)

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

INCLUDE(FindPythonLibs)

add_subdirectory(pydynamics)
