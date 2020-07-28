#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <stdint.h>
#include "sff/nodal/fairfield/generalHeader1.hpp"
#include "sff/utilities/time.hpp"
#include "private/byteSwap.hpp"

using namespace SFF::Nodal::Fairfield;

namespace
{

#define BCD_FFF (15+10*(15+10*(15)))	  /* bcd interpretation of FFF */


// https://stuff.mit.edu/afs/athena/software/cwpsu/cwpsu_v44r1/arch/amd64_ubuntu1404/include/segd.h
struct Header
{
     unsigned char f[2];   /* 01-02 File number (0-9999) */
     int16_t y;            /* 03-04 Format code (unsigned short) */ 
     char k1_k2;           /* 05    General constants */
     char k3_k4;           /* 06    General constants */
     char k5_k6;           /* 07    General constants */
     char k7_k8;           /* 08    General constants */
     char k9_k10;          /* 09    General constants */
     char k11_k12;         /* 10    General constants */
     unsigned char yr;     /* 11    Year (0-99) */
     unsigned char gh_dy1; /* 12    Number blocks in general header */
                              /* 12     - day of year (x--) */
     unsigned char dy;     /* 13    Day of year (xx) */
     unsigned char h;      /* 14    Hour of day */
     unsigned char mi;     /* 15    Minute of hour */
     unsigned char se;     /* 16    Second of minute */
     unsigned char m[3];   /* 17    Manufacturer's code */
                              /* 18-19 and serial number */
     unsigned char b[3];   /* 20-22 Bytes per scan (multiplexed only) */
     unsigned char i;      /* 23    Base scan interval */
     unsigned char p_sbx;  /* 24    Polarity */
                           /* 24    - Number of scans per block */
     unsigned char sb;     /* 25    Number of scans per block */
     unsigned char z_r1;   /* 26    Record type */
                           /* 26    - Record length - not used by Faified */
     unsigned char r;      /* 27    Record length */
     unsigned char str;    /* 28    Scan types per record  */
     unsigned char cs;     /* 29    Channels sets per scan type */ 
     unsigned char sk;     /* 30    Skew blocks */
     unsigned char ec;     /* 31    Extended header length */
     unsigned char ex;     /* 32    External header length */
};

int16_t getUnsignedShort(const char c2[2])
{
    auto n1 = static_cast<int> (c2[0]);
    auto n2 = static_cast<int> (c2[1]); 
    int n = (n1<<8) | n2;
    auto result = static_cast<int16_t> (n);
    return result;
}

int bcd(const unsigned char *ptr , int begin , const int n)
{
    uint32_t val = 0;
    if (n == 0) return static_cast<int> (val);
    for (int i=0; i<n; ++i)
    {
        val *= 10;
        if (begin++ & 1) val += (*ptr++ & 15);
        else val += (*ptr >> 4) & 15;
    }
    return static_cast<int> (val);
}

}

class GeneralHeader1::GeneralHeader1Impl
{
public:
    SFF::Utilities::Time mTime;
    int mFileNumber = 0;
    int mDataFormatCode = 0;
    std::array<int, 6> mConstants{0, 0, 0, 0, 0, 0};
    int mGeneralHeaders = 1;
    int mManufacturersCode = 20;
    int mSerialNumber = 0; 
    int mBaseScanInterval = 0;
    int mPolarityCode = 0;
    int mScanTypesPerRecord = 0;
    int mChannelSetsPerScan = 0;
    int mNumberOfSkewBlocks = 0;
    int mRecordLength = BCD_FFF;
    int mNumberOfExtendedHeaderBlocks = 0;
    int mNumberOfExternalHeaderBlocks = 0;
    int mCentury = 2000;
};

/// C'tor
GeneralHeader1::GeneralHeader1() :
    pImpl(std::make_unique<GeneralHeader1Impl> ())
{
}

GeneralHeader1::GeneralHeader1(const GeneralHeader1 &gh1)
{
   *this = gh1;
}

[[maybe_unused]]
GeneralHeader1::GeneralHeader1(GeneralHeader1 &&gh1) noexcept
{
    *this = std::move(gh1);
}

/// Destructor
GeneralHeader1::~GeneralHeader1() = default;

/// Copy assignment
GeneralHeader1& GeneralHeader1::operator=(const GeneralHeader1 &gh1)
{
    if (&gh1 == this){return *this;}
    pImpl = std::make_unique<GeneralHeader1Impl> (*gh1.pImpl);
    return *this;
}

/// Move assignment
GeneralHeader1& GeneralHeader1::operator=(GeneralHeader1 &&gh1) noexcept
{
    if (&gh1 == this){return *this;}
    pImpl = std::move(gh1.pImpl);
    return *this;
}

/// Unpacks the data read from the binary file
void GeneralHeader1::unpack(const char data[])
{
    struct Header gh1;
    gh1.f[0] = static_cast<unsigned char> (data[0]);
    gh1.f[1] = static_cast<unsigned char> (data[1]);
    gh1.y = getUnsignedShort(&data[2]);

    gh1.k1_k2 = data[4];
    gh1.k3_k4 = data[5];
    gh1.k5_k6 = data[6];
    gh1.k7_k8 = data[7];
    gh1.k9_k10 = data[8];
    gh1.k11_k12 = data[9];

    gh1.yr = static_cast<unsigned char> (data[10]);
    gh1.gh_dy1 = static_cast<unsigned char> (data[11]);

    gh1.dy = static_cast<unsigned char> (data[12]);
    gh1.h  = static_cast<unsigned char> (data[13]);
    gh1.mi = static_cast<unsigned char> (data[14]);
    gh1.se = static_cast<unsigned char> (data[15]);

    gh1.m[0] = static_cast<unsigned char> (data[16]);
    gh1.m[1] = static_cast<unsigned char> (data[17]);
    gh1.m[2] = static_cast<unsigned char> (data[18]);
    //printf("manufacturer's serial number: %02x%02x\n", (gh1).m[1], (gh1).m[2]);
 
    gh1.b[0]  = static_cast<unsigned char> (data[19]);
    gh1.b[1]  = static_cast<unsigned char> (data[20]);
    gh1.b[2]  = static_cast<unsigned char> (data[21]);
    gh1.i     = static_cast<unsigned char> (data[22]);
    gh1.p_sbx = static_cast<unsigned char> (data[23]);

    gh1.sb = static_cast<unsigned char> (data[24]);
    gh1.z_r1 = static_cast<unsigned char> (data[25]);
    gh1.r = static_cast<unsigned char> (data[26]);
    gh1.str = static_cast<unsigned char> (data[27]);

    gh1.cs = static_cast<unsigned char> (data[28]);
    gh1.sk = static_cast<unsigned char> (data[29]);
    gh1.ec = static_cast<unsigned char> (data[30]);
    gh1.ex = static_cast<unsigned char> (data[31]);

    // Unpack the values
    pImpl->mFileNumber = bcd(static_cast<unsigned char *> (&gh1.f[0]),  0, 4);
    auto year = bcd(static_cast<unsigned char *> (&gh1.yr),    0, 2);
    year = year + pImpl->mCentury;
    pImpl->mGeneralHeaders
        = bcd(static_cast<unsigned char *> (&gh1.gh_dy1), 0, 1);
    auto day  = bcd(static_cast<unsigned char *> (&gh1.gh_dy1), 1, 3);
    
    auto hour   = bcd(static_cast<unsigned char *> (&gh1.h),  0, 2);
    auto minute = bcd(static_cast<unsigned char *> (&gh1.mi), 0, 2);
    auto sec    = bcd(static_cast<unsigned char *> (&gh1.se), 0, 2);
    pImpl->mManufacturersCode 
        = bcd(static_cast<unsigned char *> (&gh1.m[0]), 0, 2);
    pImpl->mSerialNumber
       = bcd(static_cast<unsigned char *> (&gh1.m[1]), 1, 4);
    //char c2[2];
    //c2[0] = gh1.m[1];
    //c2[1] = gh1.m[2];
    //std::cout << "Hey" << static_cast<int> (getUnsignedShort(c2)) << std::endl;
    pImpl->mBaseScanInterval = (gh1.i*1000) >> 4;
    pImpl->mScanTypesPerRecord
        = bcd(static_cast<unsigned char *> (&gh1.str), 0, 2);
    pImpl->mPolarityCode = gh1.p_sbx >> 4;
    pImpl->mRecordLength = bcd(static_cast<unsigned char *> (&gh1.r), 0, 3); // TODO

    pImpl->mChannelSetsPerScan
        =  bcd(static_cast<unsigned char *> (&gh1.cs),  0, 2);
    pImpl->mNumberOfSkewBlocks
        =  bcd(static_cast<unsigned char *> (&gh1.sk),  0, 2);
    pImpl->mNumberOfExtendedHeaderBlocks
        =  bcd(static_cast<unsigned char *> (&gh1.ec),  0, 2);
    pImpl->mNumberOfExternalHeaderBlocks
        =  bcd(static_cast<unsigned char *> (&gh1.ex),  0, 2);

    SFF::Utilities::Time t0;
    t0.setYear(year);
    t0.setJulianDay(day);
    t0.setHour(hour);
    t0.setMinute(minute);
    t0.setSecond(sec);
    pImpl->mTime = t0;
    //std::cout << t0 << std::endl;
}

SFF::Utilities::Time GeneralHeader1::getStartTime() const noexcept
{
    return pImpl->mTime;
}

int GeneralHeader1::getFileNumber() const noexcept
{
    return pImpl->mFileNumber;
}

int GeneralHeader1::getBaseScanInterval() const noexcept
{
    return pImpl->mBaseScanInterval;
}

int GeneralHeader1::getManufacturersCode() const noexcept
{
    return pImpl->mManufacturersCode;
}

int GeneralHeader1::getSerialNumber() const noexcept
{
    return pImpl->mSerialNumber;
}

int GeneralHeader1::getNumberOfGeneralHeaders() const noexcept
{
    return pImpl->mGeneralHeaders;
}

int GeneralHeader1::getRecordLength() const noexcept
{
    return pImpl->mRecordLength;
}

int GeneralHeader1::getDataFormatCode() const noexcept
{
    return pImpl->mDataFormatCode;
}

int GeneralHeader1::getPolarityCode() const noexcept
{
    return pImpl->mPolarityCode;
}

int GeneralHeader1::getNumberOfSkewBlocks() const noexcept
{
    return pImpl->mNumberOfSkewBlocks;
}

int GeneralHeader1::getNumberOfChannelSetsPerScanType() const noexcept
{
    return pImpl->mChannelSetsPerScan;
}

int GeneralHeader1::getNumberOfExtendedHeaders() const noexcept
{
    return pImpl->mNumberOfExtendedHeaderBlocks;
}

int GeneralHeader1::getNumberOfExternalHeaders() const noexcept
{
    return pImpl->mNumberOfExternalHeaderBlocks;
}

std::ostream&
SFF::Nodal::Fairfield::operator<<(std::ostream &os, const GeneralHeader1 &gh1)
{
    std::stringstream ssTime;
    ssTime << gh1.getStartTime();
    std::string result
       = "Start time = " + ssTime.str() + "\n"
       + "File number = " + std::to_string(gh1.getFileNumber()) + "\n"
       + "Data format code = " + std::to_string(gh1.getDataFormatCode()) + "\n"
       + "Number of general headers = "
       + std::to_string(gh1.getNumberOfGeneralHeaders()) + "\n"
       + "Manufacturer's code = " 
       + std::to_string(gh1.getManufacturersCode()) + "\n"
       + "Serial number = "
       + std::to_string(gh1.getSerialNumber()) + "\n"
       + "Base scan interval = " 
       + std::to_string(gh1.getBaseScanInterval()) + "\n"
       + "Polarity code = " 
       + std::to_string(gh1.getPolarityCode()) + "\n"
       + "Record length = " 
       + std::to_string(gh1.getRecordLength()) + "\n"
       + "Channel sets per scan = "
       + std::to_string(gh1.getNumberOfChannelSetsPerScanType()) + "\n"
       + "Number of skew blocks = " 
       + std::to_string(gh1.getNumberOfSkewBlocks()) + "\n"
       + "Number of extended headers = "
       + std::to_string(gh1.getNumberOfExtendedHeaders()) + "\n" 
       + "Number of external headers = "
       + std::to_string(gh1.getNumberOfExternalHeaders()) + "\n";
/*
    std::fill(result, result+27, '\0');
    sprintf(result, "%04d-%02d-%02dT%02d:%02d:%02d.%06d",
            time.getYear(), time.getMonth(), time.getDayOfMonth(),
            time.getHour(), time.getMinute(), time.getSecond(),
            time.getMicroSecond());
*/
    return os << result;
}

