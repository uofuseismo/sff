# Already in cache, be silent
if (MINISEED_INCLUDE_DIR AND MINISEED_LIBRARY)
    set(MINISEED_FIND_QUIETLY TRUE)
endif()

#if (NOT BUILD_SHARED_LIBS)
    #set(MINISEED "libmseed.a")
#else()
    set(MINISEED mseed)
#endif

# Find the include directory
find_path(MINISEED_INCLUDE_DIR
          NAMES libmseed.h
          HINTS $ENV{MINISEED_ROOT}/include
                $ENV{MINISEED_ROOT}/
                /usr/local/include)
# Find the library components
find_library(MINISEED_LIBRARY
             NAMES ${MINISEED}
             PATHS $ENV{MINISEED}/lib/
                   $ENV{MINISEED}/
                   /usr/local/lib64
                   /usr/local/lib
            )
# Handle the QUIETLY and REQUIRED arguments and set MKL_FOUND to TRUE if
# all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MINISEED
                                  DEFAULT_MSG MINISEED_INCLUDE_DIR MINISEED_LIBRARY)
mark_as_advanced(MINISEED_INCLUDE_DIR MINISEED_LIBRARY)
