#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <algorithm>
#include "sff/utilities/time.hpp"
#include "sff/nodal/fairfield/rg16.hpp"
#if __has_include(<filesystem>)
 #include <filesystem>
 namespace fs = std::filesystem;
 #define USE_FILESYSTEM 1
#elif __has_include(<experimental/filesystem>)
 #include <experimental/filesystem>
 namespace fs = std::experimental::filesystem;
 #define USE_FILESYSTEM 1
#endif
#include <gtest/gtest.h>

namespace
{

using namespace SFF;

TEST(Nodal, RG16)
{
    SFF::Nodal::Fairfield::RG16 rg16;
    //EXPECT_NO_THROW(rg16.read("data/002b.fcnt"));
}

}
