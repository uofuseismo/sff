cmake_minimum_required(VERSION 3.10)
project(SFF VERSION 0.1.0 LANGUAGES CXX)
enable_testing()

include(CheckCXXCompilerFlag)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FindOpenMP QUIET)
if (OPENMP_FOUND)
   message("OpenMP found")
   string(APPEND CMAKE_CXX_FLAGS " ${OpenMP_CXX_FLAGS}")
endif()

###############################################################################
#                         Check Completeness of CXX Compiler                  #
###############################################################################
check_cxx_source_compiles("
#include <memory>
int main () {
  std::unique_ptr<int> foo = std::make_unique<int>();
}
"
  HAVE_STD__MAKE_UNIQUE
)
if (${HAVE_STD__MAKE_UNIQUE})
   message("Using standard make_unique")
   add_definitions(-DHAVE_STD__MAKE_UNIQUE)
endif()
check_cxx_source_compiles("
#include <cstdlib>
int main () {
  double *a = static_cast<double *> (aligned_alloc(64, 100));
}
"
  HAVE_ALIGNED_ALLOC
)
if (${HAVE_ALIGNED_ALLOC})
   message("Using standard aligned_alloc")
   add_definitions(-DHAVE_ALIGNED_ALLOC)
endif()
# Requiring CXX17 means this will exist
link_libraries(stdc++fs)

################################################################################
#                         Look For Some Required Libraries                     #
################################################################################
find_package(GTest REQUIRED)

if (WRAP_PYTHON)
   find_package(PythonInterp 3)
   find_package(PythonLibs 3 REQUIRED)
   message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
   message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
   message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
   find_package(pybind11 REQUIRED)
endif()

################################################################################
#                                Include Directories                           #
################################################################################
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

configure_file(${CMAKE_SOURCE_DIR}/include/sff/version.hpp.in
               ${CMAKE_SOURCE_DIR}/include/sff/version.hpp)

################################################################################
#                               Set Source and Libraries                       #
################################################################################
set(SRC
    src/utilities/time.cpp
    src/utilities/version.cpp
    src/sac/header.cpp
    src/sac/waveform.cpp)

#cmake -DBUILD_SHARED_LIBS=YES /path/to/source 
set(BUILD_SHARED_LIBS YES)
add_library(sff ${SRC})
set_property(TARGET sff PROPERTY CXX_STANDARD 17)

if (WRAP_PYTHON)
   add_library(pysff MODULE
               python/time.cpp
               #python/sac.cpp
               #python/multiChannelMatchedFilterParameters.cpp
               #python/multiChannelMatchedFilter.cpp
               python/pysff.cpp)
   target_link_libraries(pysff PRIVATE
                         pybind11::module sff OpenMP::OpenMP_CXX)
   #set_property(TARGET pyforged PROPERTY CXX_STD_14) # Uncomment for old Intel CXX compiler doesn't work
   set_property(TARGET pysff PROPERTY PREFIX "")
endif()

################################################################################
#                                 Unit Tests                                   #
################################################################################
add_executable(utilitiesTest
               testing/utilities/main.cpp
               testing/utilities/time.cpp)
target_link_libraries(utilitiesTest PRIVATE sff ${GTEST_BOTH_LIBRARIES})
add_test(NAME utilitiesTest
         COMMAND utilitiesTest)

################################################################################
#                                Installation                                  #
################################################################################
include(GNUInstallDirs)
if (MFLIB_WRAP_PYTHON)
   install(TARGETS sff pysff
           RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
           ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
else()
   install(TARGETS sff
           RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
           ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

##########################################################################################
#                                     CPACK Packaging                                    #
##########################################################################################
set(CPACK_PACKAGE_NAME "sff")
set(CPACK_PACKAGE_VENDOR "UUSS")
set(CPACK_PACKAGE_CONTACT "bbaker@seis.utah.edu")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A toolkit for reading and writing various seismic file formats.")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
