# - Try to find the libsqlite libraries
# Once done this will define
#
# SQLite_FOUND - system has libsqlite
# SQLITE_INCLUDE_DIR - the libsqlite include directory
# SQLITE_LIBRARIES - libsqlite library
FIND_PATH(SQLITE_INCLUDE_DIR sqlite3.h /usr/include /usr/local/include )
FIND_LIBRARY(SQLITE_LIBRARIES NAMES sqlite3 PATHS /usr/lib /usr/local/lib )
if(SQLITE_INCLUDE_DIR AND SQLITE_LIBRARIES)
 set(SQLite_FOUND TRUE)
endif(SQLITE_INCLUDE_DIR AND SQLITE_LIBRARIES)

IF(SQLITE_INCLUDE_DIR AND SQLITE_LIBRARIES)
  SET(SQLite_FOUND 1)
  if(NOT SQLite_FIND_QUIETLY)
   message(STATUS "Found libsqlite: ${SQLITE_LIBRARIES}")
  endif(NOT SQLite_FIND_QUIETLY)
ELSE(SQLITE_INCLUDE_DIR AND SQLITE_LIBRARIES)
  SET(SQLite_FOUND 0 CACHE BOOL "Not found sqlite library")
ENDIF(SQLITE_INCLUDE_DIR AND SQLITE_LIBRARIES)

MARK_AS_ADVANCED(SQLITE_INCLUDE_DIR SQLITE_LIBRARIES)
