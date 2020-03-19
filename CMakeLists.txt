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
else()
   message("Using custom aligned_alloc")
endif()

include(CheckIncludeFileCXX)
check_include_file_cxx(filesystem RTSEIS_HAVE_STD_FS)
#link_libraries(stdc++fs ${GeographicLib_LIBRARIES})
if (${RTSEIS_HAVE_STD_FS})
   MESSAGE("Using filesystem")
   link_libraries(stdc++fs)
else()
   check_include_file_cxx(experimental/filesystem RTSEIS_HAVE_EXP_FS)
   if (${RTSEIS_HAVE_EXP_FS})
      MESSAGE("Using experimental/filesystem")
      link_libraries(stdc++fs)
   else()
      message("Disabling std::filesystem")
   endif()
endif()

################################################################################
#                           Download the test data file                        #
################################################################################
file(DOWNLOAD
     http://home.chpc.utah.edu/~u6024448/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy
     ${CMAKE_SOURCE_DIR}/testing/data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy
     INACTIVITY_TIMEOUT 5)
#    SHOW_PROGRESS)

################################################################################
#                         Look For Some Required Libraries                     #
################################################################################
find_package(GTest REQUIRED)
set(FindMiniSEED_DIR ${CMAKE_SOURCE_DIR}/CMakeModules)
find_package(FindMiniSEED)

if (${MINISEED_FOUND})
   message("Found miniSEED")
   link_libraries(${MINISEED_LIBRARY})
endif()

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
    ${MINISEED_INCLUDE_DIR}
)

configure_file(${CMAKE_SOURCE_DIR}/include/sff/version.hpp.in
               ${CMAKE_SOURCE_DIR}/include/sff/version.hpp)
set(PUBLIC_HEADER_DIRECTORIES
    include/sff)
set(PRIVATE_HEADER_DIRECTORIES
    include/private)

################################################################################
#                               Set Source and Libraries                       #
################################################################################
set(SRC
    src/utilities/time.cpp
    src/utilities/version.cpp
    src/sac/header.cpp
    src/sac/waveform.cpp
    src/segy/silixaBinaryFileHeader.cpp
    src/segy/silixaTraceHeader.cpp
    src/segy/silixaTrace.cpp
    src/segy/silixaTraceGroup.cpp
    src/segy/textualFileHeader.cpp)
if (${MINISEED_FOUND})
   set(MINISEED_SRC
       src/miniseed/sncl.cpp
       src/miniseed/trace.cpp
       src/miniseed/traceGroup.cpp)
endif()

#cmake -DBUILD_SHARED_LIBS=YES /path/to/source 
set(BUILD_SHARED_LIBS YES)
add_library(sff ${SRC} ${MINISEED_SRC})
#set_target_properties(sff PROPERTIES
#                      CXX_STANDARD 17
#                      CXX_STANDARD_REQUIRED YES 
#                      CXX_EXTENSIONS NO) 
target_include_directories(sff PUBLIC  ${PUBLIC_HEADER_FILES})
target_include_directories(sff PRIVATE ${PRIVATE_HEADER_FILES})

if (WRAP_PYTHON)
   add_library(pysff MODULE
               python/time.cpp
               python/sac.cpp
               python/silixaSEGY.cpp
               #python/multiChannelMatchedFilterParameters.cpp
               #python/multiChannelMatchedFilter.cpp
               python/pysff.cpp)
   target_link_libraries(pysff PRIVATE
                         pybind11::module sff ${MINISEED_LIBRARY} OpenMP::OpenMP_CXX)
   #set_property(TARGET pyforged PROPERTY CXX_STD_14) # Uncomment for old Intel CXX compiler doesn't work
   set_property(TARGET pysff PROPERTY PREFIX "")
   file(COPY ${CMAKE_SOURCE_DIR}/python/unit_tests.py DESTINATION .)
endif()

################################################################################
#                                 Unit Tests                                   #
################################################################################
add_executable(tests
               testing/main.cpp
               testing/utilities/time.cpp
               testing/sac/sac.cpp
               testing/segy/silixa.cpp)
target_link_libraries(tests PRIVATE sff ${GTEST_BOTH_LIBRARIES})
target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
add_test(NAME tests
         COMMAND tests)

# Also need to copy some test data
file(COPY ${CMAKE_SOURCE_DIR}/testing/data DESTINATION .)

################################################################################
#                                Installation                                  #
################################################################################
include(GNUInstallDirs)
if (MFLIB_WRAP_PYTHON)
   install(TARGETS sff pysff
           RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
           ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
           PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
else()
   install(TARGETS sff
           RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
           ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
           PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
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
