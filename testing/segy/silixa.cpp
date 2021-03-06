#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <array>
#include <fstream>
#include <algorithm>
#include "sff/segy/textualFileHeader.hpp"
#include "sff/segy/silixa/traceGroup.hpp"
#include "sff/segy/silixa/binaryFileHeader.hpp"
#include "sff/segy/silixa/traceHeader.hpp"
#include "sff/segy/silixa/trace.hpp"
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
    file.ignore(3600); // Skip first textual header and binary file header
    file.read(cdata.data(), 240); // Read trace header
    file.close();

    EXPECT_NO_THROW(header.set(cdata.data()));

    EXPECT_EQ(header.getTraceNumber(), 1);
 
    auto startTime = header.getStartTime();
    EXPECT_EQ(startTime.getYear(), 2019);
    EXPECT_EQ(startTime.getDayOfYear(), 117);
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
    EXPECT_EQ(headerCopy.getTraceNumber(), 1);
    auto startTimeCopy = headerCopy.getStartTime();
    EXPECT_EQ(startTimeCopy.getYear(), 2019);
    EXPECT_EQ(startTimeCopy.getDayOfYear(), 117);
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
    startTimeCopy.setDayOfYear(45);
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
    EXPECT_EQ(startTime.getDayOfYear(), 45);
    EXPECT_EQ(startTime.getHour(),   1); 
    EXPECT_EQ(startTime.getMinute(), 1); 
    EXPECT_EQ(startTime.getSecond(), 1);
    EXPECT_EQ(header.getNumberOfSamples(), 150);
    EXPECT_EQ(header.getSampleInterval(), 333);
    EXPECT_FALSE(header.getIsCorrelated()); 
}

TEST(SEGY, Trace)
{
    SEGY::Silixa::Trace trace;
    // Pick out the binary header
    std::ifstream file("data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy",
                       std::ios::binary);
    std::vector<char> cdata;
    cdata.resize(240 + 30000*4);
    ASSERT_TRUE(file.is_open());
    file.ignore(3600); // Skip textual header and binary file header
    file.read(cdata.data(), cdata.size()); // Read trace header and data
    file.close();

    EXPECT_EQ(trace.getFormat(), SFF::Format::SILIXA_SEGY);
    EXPECT_NO_THROW(trace.set(cdata.size(), cdata.data()));
    EXPECT_EQ(trace.getTraceNumber(), 1);
    EXPECT_EQ(trace.getNumberOfSamples(), 30000);
    EXPECT_NEAR(trace.getSamplingPeriod(), 0.0005, 1.e-8);
    EXPECT_NEAR(trace.getSamplingRate(), 2000, 1.e-8);
 
    std::vector<double> wave8(trace.getNumberOfSamples());
    std::vector<float>  wave4(trace.getNumberOfSamples());
    auto wave8Ptr = wave8.data();
    auto wave4Ptr = wave4.data();
    EXPECT_NO_THROW(trace.getData(wave8.size(), &wave8Ptr));
    EXPECT_NO_THROW(trace.getData(wave4.size(), &wave4Ptr));
    EXPECT_NEAR(wave8[0],      0,                 1.e-6);
    EXPECT_NEAR(wave8[1],      2854.354736328125, 1.e-2);
    EXPECT_NEAR(wave8[29999], -3018.015380859375, 1.e-2); 
    double diff = 0;
    #pragma omp simd
    for (int i=0; i<trace.getNumberOfSamples(); ++i)
    {
        diff = std::max(diff, std::abs(wave8[i] - wave4[i]));
    }
    EXPECT_NEAR(diff, 0, 1.e-8);

    // Test copy c'tor
    SEGY::Silixa::Trace traceCopy(trace);
    EXPECT_EQ(traceCopy.getFormat(), SFF::Format::SILIXA_SEGY);
    EXPECT_NO_THROW(traceCopy.set(cdata.size(), cdata.data()));
    EXPECT_EQ(traceCopy.getNumberOfSamples(), 30000);
    EXPECT_NEAR(traceCopy.getSamplingPeriod(), 0.0005, 1.e-8);
    EXPECT_NEAR(traceCopy.getSamplingRate(), 2000, 1.e-8);
    EXPECT_NO_THROW(traceCopy.getData(wave8.size(), &wave8Ptr));
    EXPECT_NEAR(wave8[0],      0,                 1.e-6);
    EXPECT_NEAR(wave8[1],      2854.354736328125, 1.e-2);
    EXPECT_NEAR(wave8[29999], -3018.015380859375, 1.e-2); 
}

TEST(SEGY, TraceGroup)
{
    SEGY::Silixa::TraceGroup group;
try
{
 group.read("data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy");
}
catch (const std::exception &e)
{
std::cout << e.what() << std::endl;
}
    EXPECT_NO_THROW(
        group.read("data/FORGE_78-32_iDASv3-P11_UTC190427000008.sgy"));
    EXPECT_EQ(group.getNumberOfTraces(), 1280);
    EXPECT_EQ(group.getNumberOfSamplesPerTrace(), 30000);
    std::vector<float> wave(group.getNumberOfSamplesPerTrace());
    int j = 0;
    for (auto const &trace : group)
    {
        EXPECT_EQ(trace.getTraceNumber(), j+1);
        EXPECT_EQ(trace.getNumberOfSamples(), 30000);
        EXPECT_NEAR(trace.getSamplingRate(), 2000, 1.e-8);
        auto wavePtr = wave.data();
        EXPECT_NO_THROW(trace.getData(wave.size(), &wavePtr));
        if (j == 0)
        {
            EXPECT_NEAR(wave[0],      0,                 1.e-6);
            EXPECT_NEAR(wave[1] ,     2854.354736328125, 1.e-2);
            EXPECT_NEAR(wave[29999], -3018.015380859375, 1.e-2);
            FILE *test = fopen("das.txt", "w");
            for (const auto &w : wave)
            {
                fprintf(test, "%f\n", w);
            }
            fclose(test);
        }
        j = j + 1;
    }
    EXPECT_EQ(j, 1280);
}

}
