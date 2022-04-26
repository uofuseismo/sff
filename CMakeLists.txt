cmake_minimum_required(VERSION 3.10)
project(SFF VERSION 0.1.0 LANGUAGES CXX)
enable_testing()

include(CheckCXXCompilerFlag)
set(CMAKE_CXX_STANDARD 20)
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
check_include_file_cxx(filesystem SFF_HAVE_STD_FS)
#link_libraries(stdc++fs ${GeographicLib_LIBRARIES})
if (${SFF_HAVE_STD_FS})
   MESSAGE("Using filesystem")
   link_libraries(stdc++fs)
else()
   check_include_file_cxx(experimental/filesystem SFF_HAVE_EXP_FS)
   if (${SFF_HAVE_EXP_FS})
      MESSAGE("Using experimental/filesystem")
      link_libraries(stdc++fs)
   else()
      message("Disabling std::filesystem")
   endif()
endif()

################################################################################
#                           Download the test data file                        #
################################################################################
#file(DOWNLOAD
#     http://home.chpc.utah.edu/~u6024448/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy
#     ${CMAKE_SOURCE_DIR}/testing/data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy
#     INACTIVITY_TIMEOUT 5
#     SHOW_PROGRESS)
#file(DOWNLOAD
#     http://home.chpc.utah.edu/~u6024448/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy
#     ${CMAKE_SOURCE_DIR}/testing/data/002b.fcnt
#     INACTIVITY_TIMEOUT 5)

################################################################################
#                         Look For Some Required Libraries                     #
################################################################################
find_package(GTest REQUIRED)
set(FindMiniSEED_DIR ${CMAKE_SOURCE_DIR}/CMakeModules)
set(FindTime_DIR     ${CMAKE_SOURCE_DIR}/CMakeModules)
find_package(FindMiniSEED)
find_package(FindTime REQUIRED)

if (${FindMiniSEED_FOUND})
   message("Found MiniSEED")
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
)

configure_file(${CMAKE_SOURCE_DIR}/include/private/version.hpp.in
               ${CMAKE_SOURCE_DIR}/include/sff/version.hpp)
set(PUBLIC_HEADER_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/sff)
set(PRIVATE_HEADER_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/private)

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
    src/segy/textualFileHeader.cpp
    src/nodal/generalHeader1.cpp
    src/nodal/rg16.cpp
    src/hypoinverse2000/eventSummary.cpp
    src/hypoinverse2000/eventSummaryLine.cpp
    src/hypoinverse2000/stationArchiveLine.cpp
    )
#set(HEADERS
#    include/sff/abstractBaseClass/trace.hpp
#    include/sff/sac/enums.hpp
#    include/sff/sac/header.hpp
#    include/sff/sac/waveform.hpp
#    include/sff/hypoinverse2000/eventSummary.hpp
#    include/sff/hypoinverse2000/eventSummaryLine.hpp
#    include/sff/hypoinverse2000/stationArchiveLine.hpp)
if (${FindMiniSEED_FOUND})
   set(MINISEED_SRC
       src/miniseed/sncl.cpp
       src/miniseed/trace.cpp
       src/miniseed/traceGroup.cpp)
   set(MINISEED_TEST_SRC testing/miniseed/miniseed.cpp)
   #set(MINISEED_HEADERS
   #    include/sff/miniseed/enums.hpp
   #    include/sff/miniseed/sncl.hpp
   #    include/sff/miniseed/trace.hpp
   #    include/sff/miniseed/traceGroup.hpp)
endif()

#cmake -DBUILD_SHARED_LIBS=YES /path/to/source 
set(SFF_PRIVATE_INCLUDES ${PRIVATE_HEADER_DIRECTORIES} ${TIME_INCLUDE_DIR})
set(SFF_PRIVATE_LIBRARIES ${TIME_LIBRARY})
if (${FindMiniSEED_FOUND})
   set(SFF_PRIVATE_INCLUDES ${SFF_PRIVATE_INCLUDES} ${MINISEED_INCLUDE_DIR})
   set(SFF_PRIVATE_LIBRARIES ${SFF_PRIVATE_LIBRARIES} ${MINISEED_LIBRARY})
endif()

set(BUILD_SHARED_LIBS YES)
add_library(sff ${SRC} ${MINISEED_SRC})# ${HEADERS} ${MINISEED_HEADERS})
set_target_properties(sff PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES 
                      CXX_EXTENSIONS NO)
target_link_libraries(sff PRIVATE ${SFF_PRIVATE_LIBRARIES})
target_include_directories(sff
                           PRIVATE ${SFF_PRIVATE_INCLUDES}
                           PUBLIC $<BUILD_INTERFACE:${PUBLIC_HEADER_DIRECTORIES}>
                                  $<INSTALL_INTERFACE:${PUBLIC_HEADER_DIRECTORIES}>)
#target_include_directories(sff PRIVATE ${PRIVATE_HEADER_DIRECTORIES} ${MINISEED_INCLUDE_DIR} ${TIME_INCLUDE_DIR})

if (WRAP_PYTHON)
   add_library(pysff MODULE
               python/time.cpp
               python/sac.cpp
               python/silixaSEGY.cpp
               python/hypoinverse2000.cpp
               python/pysff.cpp)
   target_link_libraries(pysff PRIVATE pybind11::module sff)# OpenMP::OpenMP_CXX)
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
               #testing/segy/silixa.cpp
               #testing/nodal/rg16.cpp
               testing/hypoinverse2000/hypoinverse2000.cpp
               ${MINISEED_TEST_SRC})
target_link_libraries(tests PRIVATE sff ${GTEST_BOTH_LIBRARIES} ${TIME_LIBRARY})
target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
add_test(NAME tests
         COMMAND tests)

# Also need to copy some test data
file(COPY ${CMAKE_SOURCE_DIR}/testing/data DESTINATION .)

################################################################################
#                                Installation                                  #
################################################################################
include(GNUInstallDirs)
if (WRAP_PYTHON)
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
install(DIRECTORY ${PUBLIC_HEADER_DIRECTORIES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
##########################################################################################
#                                     CPACK Packaging                                    #
##########################################################################################
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_PACKAGE_VENDOR "UUSS")
set(CPACK_PACKAGE_CONTACT "ben.baker@utah.edu")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A toolkit for reading and writing various seismic file formats.")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_VERBATIM_VARIABLES YES)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_COMPONENTS_ALL libraries headers)
set(CPACK_SOURCE_IGNORE_FILES
  /\\.git/
  \\.swp
  \\.orig
  /CMakeLists\\.txt\\.user
  /private/
)
include(CPack)
