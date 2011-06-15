project (strigi)

# This is the aggregate build file. It serves only to call the build in the
# subdirectories. Each of the projects in the subdirectories is buildable
# separately.

cmake_minimum_required(VERSION 2.6)
# for testing to work in cmake, this command must be called in the root src dir
enable_testing()

option(STRIGI_SYNC_SUBMODULES "Try to update the Strigi submodules automatically. Note that the update may fail if you have pending changes in one of the submodules." FALSE)

if(STRIGI_SYNC_SUBMODULES)
  if (NOT GIT_EXECUTABLE)
  # Make it possible to override GIT_EXECUTABLE
    find_program(GIT_EXECUTABLE NAMES git)
  endif()
  if(NOT GIT_EXECUTABLE)
    message(FATAL_ERROR "Could not find git. Aborting.")
  endif()
endif()

macro(check_subdir _subDirectory)
  message(STATUS "Checking: ${strigi_SOURCE_DIR}/${_subDirectory}/CMakeLists.txt")
  if(NOT EXISTS "${strigi_SOURCE_DIR}/${_subDirectory}/CMakeLists.txt")
    message(STATUS "No CMakeLists.txt found in ${_subDirectory}")
    if(STRIGI_SYNC_SUBMODULES)
      message(STATUS "Trying to download the ${_subDirectory} submodule")
      execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init -- ${_subDirectory}
                      WORKING_DIRECTORY ${strigi_SOURCE_DIR})
    else()
      set(showError 1)
    endif()
  else()
    if(STRIGI_SYNC_SUBMODULES)
      message(STATUS "Trying to update the ${_subDirectory} submodule")
      execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --rebase -- ${_subDirectory}
                      WORKING_DIRECTORY ${strigi_SOURCE_DIR})
    endif()
  endif()
endmacro()

check_subdir(libstreams)
check_subdir(libstreamanalyzer)
check_subdir(strigiutils)
check_subdir(strigidaemon)
check_subdir(strigiclient)

if(MSVC)
  add_definitions(-wd4251)
  add_definitions(-wd4355)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
  add_definitions(-D_USE_MATH_DEFINES)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Zc:wchar_t-")
endif(MSVC)

if(showError)
  message(FATAL_ERROR "No CMakeLists.txt was found in one of your sources subdirectory\n"
                      "Make sure you downloaded the sub-modules files using:\n"
                      "  git submodule update --init"
         )
else()
  add_subdirectory(libstreams) # Must be first
  add_subdirectory(libstreamanalyzer) # Must be second
  add_subdirectory(strigiutils)
  if(NOT WIN32)
    add_subdirectory(strigidaemon)
  endif()
  add_subdirectory(strigiclient) # Must be AFTER strigidaemon
endif()

