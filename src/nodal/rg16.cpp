#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#if __has_include(<filesystem>)
#include <filesystem>
 namespace fs = std::filesystem;
 #define USE_FILESYSTEM 1
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
 namespace fs = std::experimental::filesystem;
 #define USE_FILESYSTEM 1
#endif
#include "sff/nodal/fairfield/rg16.hpp"
#include "sff/nodal/fairfield/generalHeader1.hpp"

using namespace SFF::Nodal::Fairfield;

namespace
{

int32_t bcd(const unsigned char *ptr,
            const int n = 2)
{
    int32_t val = 0;
    if (n == 0){return val;}
    for (int i = 0; i<n; i=i+2)
    {
        val = val*10;
        val = val + (ptr[i] >> 4) & 15;
        if (i + 1 < n){val = val + ptr[i+1]&16;}
    }
    return val;
}

int unpackBase16CharToInteger(const char c)
{
    /*
    union
    {
        unsigned char cOneByte;
        uint8_t oneByte = 0;
    };
    cOneByte = static_cast<unsigned char> (c);
    int lsb1 = oneByte/16;
    int lsb2 = oneByte - lsb1*16;
    int result = lsb1*10 + lsb2;
    std::cout << static_cast<int> (oneByte) << " -> " << result << std::endl;
    */
    //std::cout << static_cast<int> (static_cast<std::uint8_t> (c)) << std::endl ;
    // Interpret base16 unsigned char as base10 int.
    // The idea is to strip out the "first" digit and "second" digit
    // in base 16, then convert back to base10 by multiplying the "first"
    // digit by std::pow(10,0) and "second" digit by std::pow(10,1).
    // This basically means that the largest representable number is
    // 165 = 15*10 + 15.
    // However, the max value of an unsigned char is
    // 255 = 15*16 + 15 = 15*16^1 + 15*16^0.
    // Below we simplify the std::pow(10, 1) = 10 and std::pow(10, 0) = 1
    // to avoid the use of logarithms.
    //int result = 0;
    auto base16 = static_cast<int> (static_cast<std::uint8_t> (c));
    auto firstDigit = base16%16; // First digit is remainder (mod16)
    auto secondDigit = (base16 - firstDigit)/16; // Should evenly divide
    int result = secondDigit*10 + firstDigit; // Put it in base 10
    unsigned char c1[1]; c1[0] = c;
    //std::cout << "bcd: " << bcd(c1, 1) << std::endl;
    //std::cout << result << " " << firstDigit << " " << secondDigit << " "
    //          << "new res: " << result << std::endl;
    return result;
}
}

class RG16::RG16Impl
{
public:
    GeneralHeader1 mGeneralHeader1;
};

/// C'tor
RG16::RG16() :
    pImpl(std::make_unique<RG16Impl> ())
{
}

/// Destructor
RG16::~RG16() = default;

/// Read the file
void RG16::read(const std::string &fileName)
{
#if USE_FILESYSTEM == 1
    if (!fs::exists(fileName))
    {
        std::string errmsg = "fcnt file = " + fileName + " does not exist";
        throw std::invalid_argument(errmsg);
    }
#endif
    // Open the file
    std::ifstream nodalFile(fileName, std::ios::in | std::ios::binary);
    // Begin unpacking
    nodalFile.seekg(10, nodalFile.beg);
    union
    {
        unsigned char cOneByte;
        uint8_t oneByte = 0;
    };
    // Unpack the start time
    char c1;
    nodalFile.read(&c1, 1*sizeof(char));
    int year = 2000 + unpackBase16CharToInteger(c1); // Nodals didn't exist in 1900's
    //std::cout << "Year:" << year << std::endl;
    // Number of header blocks
    nodalFile.read(&c1, 1*sizeof(char));
    std::cout << "ngen " << unpackBase16CharToInteger(c1) << std::endl;
    cOneByte = static_cast<unsigned char> (c1);
    int nGeneralHeaderBlocks = oneByte/16 + 1;
    std::cout << nGeneralHeaderBlocks << std::endl;
    int dayMSN = oneByte - (nGeneralHeaderBlocks - 1)*16;
    //std::cout << nGeneralHeaderBlocks << "," << dayMSN << std::endl;
    // Julian day
    nodalFile.read(&c1, 1*sizeof(char));
    int dayLSB3 = dayMSN*100 + unpackBase16CharToInteger(c1);
    //std::cout << dayMSN  << " " << dayLSB1 << " "
    //          << dayLSB2 << " " << dayLSB3 << " " <<  std::endl;

    std::array<int, 3> t3{};
    for (int i=0; i<3; ++i)
    {
        nodalFile.read(&c1, 1 * sizeof(char));
        t3[i] = unpackBase16CharToInteger(c1);
        //std::cout << t3[i] << std::endl;
    }
/*
    std::cout << year  << " " << t3[0] << " " << t3[1] << " " << t3[2] << std::endl;
    SFF::Utilities::Time startTime;
    startTime.setYear(year);
    startTime.setJulianDay(dayLSB3);
    startTime.setHour(t3[0]);
    startTime.setMinute(t3[1]);
    startTime.setSecond(t3[2]);
    std::cout << startTime << std::endl;

    // Unpack the sampling rate
    nodalFile.seekg(6, nodalFile.cur);
    nodalFile.read(&c1, 1*sizeof(char));
    cOneByte = static_cast<unsigned char> (c1);
    auto samplingRate = static_cast<int> (oneByte)/16;
    std::cout << unpackBase16CharToInteger(c1) << "," << samplingRate << std::endl;

    nodalFile.seekg(5, nodalFile.cur);
    nodalFile.read(&c1, 1*sizeof(char));
    int channelSets = unpackBase16CharToInteger(c1);
    std::cout << channelSets << std::endl;
*/
    // Read the general header
    nodalFile.seekg(0, nodalFile.beg);
    std::array<char, 32> cGeneralHeader1{};
    nodalFile.read(cGeneralHeader1.data(), cGeneralHeader1.size()*sizeof(char));
    pImpl->mGeneralHeader1.unpack(cGeneralHeader1.data());
    std::stringstream sstream;
    sstream << pImpl->mGeneralHeader1;
    std::cout << sstream.str() << std::endl;

    nodalFile.close();
}
