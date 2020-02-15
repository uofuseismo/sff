#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <fstream>
#include <algorithm>
#include "sff/segy/textualFileHeader.hpp"
#include "sff/segy/silixa.hpp"
#include "sff/segy/silixa/binaryFileHeader.hpp"
#include "sff/segy/silixa/traceHeader.hpp"
//#include "sff/segy/silixa.hpp"
//#include "sff/sac/enums.hpp"
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

TEST(SEGY, TextualFileHeader)
{
    // Load the reference
    std::ifstream refFile("data/referenceSilixaSEGYHeader.txt");
    std::string line;
    ASSERT_TRUE(refFile.is_open());
    std::getline(refFile, line);
    refFile.close();
    // Pick out the text header
    std::ifstream file("data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy",
                       std::ios::binary); 
    std::array<char, 3200> cdata;
    ASSERT_TRUE(file.is_open());
    file.read(cdata.data(), 3200);
    file.close();
    // Set the EBCDIC header and compare
    SEGY::TextualFileHeader header;
    header.setEBCDIC(cdata.data());
    auto text = header.getASCII();
    EXPECT_EQ(line, text);

    // Set the above as an ASCII header and ensure I recover the above
    header.clear();
    header.setASCII(line);
    auto ebcdicText = header.getEBCDIC();
    for (int i=0; i<static_cast<int> (cdata.size()); ++i)
    {
        EXPECT_EQ(cdata[i], ebcdicText[i]);
    }

    // Test copy c'tor
    SEGY::TextualFileHeader hCopy(header);
    text = header.getASCII();
    EXPECT_EQ(line, text);
}

TEST(SEGY, BinaryFileHeader)
{
    // Pick out the binary header
    std::ifstream file("data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy",
                       std::ios::binary);
    std::array<char, 400> cdata;
    ASSERT_TRUE(file.is_open());
    file.ignore(3200); // Skip first textual header
    file.read(cdata.data(), 400); // Read binary file header
    file.close();

    SFF::SEGY::Silixa::BinaryFileHeader header;
    header.set(cdata.data());
    EXPECT_EQ(header.getSampleInterval(), 500);
    EXPECT_EQ(header.getNumberOfTraces(), 1280);
    EXPECT_EQ(header.getNumberOfSamplesPerTrace(), 30000);

    // Test c'tor
    SFF::SEGY::Silixa::BinaryFileHeader headerCopy(header);
    EXPECT_EQ(headerCopy.getSampleInterval(), 500);
    EXPECT_EQ(headerCopy.getNumberOfTraces(), 1280);
    EXPECT_EQ(headerCopy.getNumberOfSamplesPerTrace(), 30000);

    // Ensure my endianness conversions work out
    EXPECT_NO_THROW(headerCopy.setSampleInterval(1500));
    EXPECT_NO_THROW(headerCopy.setNumberOfTraces(11280));
    EXPECT_NO_THROW(headerCopy.setNumberOfSamplesPerTrace(30005));
    auto temp = headerCopy.get();
    header.set(temp.data());
    EXPECT_EQ(header.getSampleInterval(), 1500);
    EXPECT_EQ(header.getNumberOfTraces(), 11280);
    EXPECT_EQ(header.getNumberOfSamplesPerTrace(), 30005);
    EXPECT_TRUE(header.isValid());
}

TEST(SEGY, TraceHeader)
{
    SEGY::Silixa::TraceHeader header;
    // Pick out the binary header
    std::ifstream file("data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy",
                       std::ios::binary);
    std::array<char, 240> cdata;
    ASSERT_TRUE(file.is_open());
    file.ignore(3600); // Skip first textual header
    file.read(cdata.data(), 240); // Read binary file header
    file.close();

    EXPECT_NO_THROW(header.set(cdata.data()));
 
    auto startTime = header.getStartTime();
    EXPECT_EQ(startTime.getYear(), 2019);
    EXPECT_EQ(startTime.getJulianDay(), 117);
    EXPECT_EQ(startTime.getMonth(), 4);
    EXPECT_EQ(startTime.getDayOfMonth(), 27);
    EXPECT_EQ(startTime.getHour(),   0);
    EXPECT_EQ(startTime.getMinute(), 0);
    EXPECT_EQ(startTime.getSecond(), 8);

    EXPECT_EQ(header.getNumberOfSamples(), 30000);
    EXPECT_EQ(header.getSampleInterval(), 500);
    EXPECT_TRUE(header.getIsCorrelated());

    // Test copy c'tor
    SEGY::Silixa::TraceHeader headerCopy(header);
    auto startTimeCopy = headerCopy.getStartTime();
    EXPECT_EQ(startTimeCopy.getYear(), 2019);
    EXPECT_EQ(startTimeCopy.getJulianDay(), 117);
    EXPECT_EQ(startTimeCopy.getMonth(), 4);
    EXPECT_EQ(startTimeCopy.getDayOfMonth(), 27);
    EXPECT_EQ(startTimeCopy.getHour(),   0);
    EXPECT_EQ(startTimeCopy.getMinute(), 0);
    EXPECT_EQ(startTimeCopy.getSecond(), 8);
    EXPECT_EQ(headerCopy.getNumberOfSamples(), 30000);
    EXPECT_EQ(headerCopy.getSampleInterval(), 500);
    EXPECT_TRUE(headerCopy.getIsCorrelated());

    // Test writing some variables
    startTimeCopy.setYear(2020);
    startTimeCopy.setJulianDay(45);
    startTimeCopy.setHour(1);
    startTimeCopy.setMinute(1);
    startTimeCopy.setSecond(1);
    headerCopy.setStartTime(startTimeCopy);
    headerCopy.setNumberOfSamples(150);
    headerCopy.setSampleInterval(333);
    headerCopy.setIsCorrelated(false);

    auto temp = headerCopy.get();
    header.set(temp.data());
    startTime = header.getStartTime();
    EXPECT_EQ(startTime.getYear(), 2020);
    EXPECT_EQ(startTime.getJulianDay(), 45);
    EXPECT_EQ(startTime.getHour(),   1); 
    EXPECT_EQ(startTime.getMinute(), 1); 
    EXPECT_EQ(startTime.getSecond(), 1);
    EXPECT_EQ(header.getNumberOfSamples(), 150);
    EXPECT_EQ(header.getSampleInterval(), 333);
    EXPECT_FALSE(header.getIsCorrelated()); 
}

TEST(SEGY, Trace)
{
//    SEGY::Silixa::Trace trace;
/*
    // Pick out the binary header
    std::ifstream file("data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy",
                       std::ios::binary);
    std::array<char, 240> cdata;
    ASSERT_TRUE(file.is_open());
    file.ignore(3600); // Skip first textual header
    file.read(cdata.data(), 240); // Read binary file header
    file.close();
*/

}

}
