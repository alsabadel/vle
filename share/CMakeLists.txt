ADD_SUBDIRECTORY(doc)
ADD_SUBDIRECTORY(pixmaps)
ADD_SUBDIRECTORY(dtd)
ADD_SUBDIRECTORY(template)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/gvle.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/gvle.rc @ONLY)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/vfl.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/vfl.rc @ONLY)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/eov.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/eov.rc @ONLY)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/oov.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/oov.rc @ONLY)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_SOURCE_DIR}/vle.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/vle.rc @ONLY)

