#include <cstdio>
#include <cstdlib>
#include <string>
#include <array>
#include "sff/segy/silixa/binaryFileHeader.hpp"
#include "private/byteSwap.hpp"

using namespace SFF::SEGY::Silixa;

namespace
{
/*
struct BinaryFileStruct
{
    // Bytes 3200:3220
    int32_t jobID = 0;
    int32_t lineNumber = 0;
    int32_t reelNumber = 0;
    int16_t nTracesInFile = 0; // Silixa overrides this
    int16_t nAuxTracesPerFile = 0;
    int16_t sampleInterval = 0;
    int16_t originalSampleInterval = 0;
    // Bytes 3220:3240
    int16_t nSamplesPerTrace = 0; // Silixa overrides this
    int16_t nOriginalSamplesPerTrace = 0;
    int16_t byteOrder = 0; // Mandatory
    int16_t ensembleFold = 0;
    int16_t traceSortingCode = 0;
    int16_t verticalSumCode = 0;
    int16_t startSweepFrequency = 0;
    int16_t endSweepFrequency = 0;
    int16_t sweepLength = 0;
    int16_t sweepCode = 0;
    // Bytes 3240:3260
    int16_t traceNumberWithSweep = 0;
    int16_t startSweepTaperLength = 0;
    int16_t endSweepTaperLength = 0;
    int16_t taperType = 0;
    int16_t correlatedTraces = 0;
    int16_t binaryGainRecovered = 0;
    int16_t amplitudeRecoverMethod = 0;
    int16_t measurementSystem = 1; // (meters instead of feet)
    int16_t impulseSignalPolarity = 0;
    int16_t vibratoryPolarityCode = 0; 
    // Bytes 3260:3280 
    int16_t pad1; // Silixa pads
    int32_t nTracesInFileExtended = 0;
    int32_t nSamplesPerTraceExtended = 0; 
    int16_t pad2; // 3272
    double sampleIntervalExtended = 0; // IEEE float
    // Bytes 3280:3300
    double originalSampleIntervalExtended = 0; // IEEE float
    int32_t nOriginalSamplesPerTraceExtended = 0;
    int32_t ensembleFoldExtended = 0;
    int32_t integerConstant = 0;
    // Bytes 3300:3500
    char unassigned1[200];
    // Bytes 3500:3520
    uint8_t majorRevisionNumber = 0;
    uint8_t minorRevisionNumber = 0;
    int8_t fixedLengthFlag = 0;
    int8_t nExtendedTextFileHeaders = 0;
    int32_t maxTraceHeaders = 0;
    int8_t timeBasisCode = 4; // UTC
    uint64_t nTracesInStream = 0; // 0 means all files in this dataset
    // Bytes 3520:3532
    uint64_t byteOffset = 0; // Byte offset of first 
    int32_t nDataTrailerStanzas = 0;
    char unassigned2[68];
};
*/

/*
struct HeaderData
{
    HeaderData() :
        mData() 
    {
    }
    union
    {
        struct BinaryFileStruct mData;
        char mCharacterHeader[400];
    };
};
*/

/*
#ifndef BIG_ENDIAN
#define BIG_ENDIAN 0
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1
#endif
 
int testByteOrder()
{
    short int word = 0x0001;
    char *b = (char *)&word;
    return (b[0] ? LITTLE_ENDIAN : BIG_ENDIAN);
}

int16_t unpackShort(const char c[2], const bool lswap)
{
    union
    {
        char c2[2];
        int16_t val;
    };
    if (lswap)
    {
        c2[0] = c[1];
        c2[1] = c[0];
    }
    else
    {
        c2[0] = c[0];
        c2[1] = c[1];
    }
    return val;
}

int32_t unpackInt(const char c[4], const bool lswap)
{
    union
    {
        char c4[2];
        int32_t val;
    };
    if (lswap)
    {
        c4[0] = c[3];
        c4[1] = c[2];
        c4[2] = c[1];
        c4[3] = c[0];
    }
    else
    {
        c4[0] = c[0];
        c4[1] = c[1];
        c4[2] = c[2];
        c4[3] = c[3];
    }
    return val;
}

void packShort(int16_t valIn, char c[2], const bool lswap)
{
    union
    {
        char c2[2];
        int16_t val;
    };
    val = valIn;
    if (lswap)
    {
        c[0] = c2[1];
        c[1] = c2[0];
    }
    else
    {
        c[0] = c2[0];
        c[1] = c2[1];
    }
}

void packInt(const int valIn, char c[4], const bool lswap)
{
    union
    {
        char c4[2];
        int32_t val;
    };
    val = valIn; 
    if (lswap)
    {
        c[0] = c4[3];
        c[1] = c4[2];
        c[2] = c4[1];
        c[3] = c4[0];
    }
    else
    {
        c[0] = c4[0];
        c[1] = c4[1];
        c[2] = c4[2];
        c[3] = c4[3];
    }
}
*/

}

class BinaryFileHeader::BinaryFileHeaderImpl
{
public:
    BinaryFileHeaderImpl()
    {
        std::fill(mHeader.begin(), mHeader.end(), 0);
        packShort(mByteFormat, mHeader.begin()+24, mSwapBytes);
    }
    void updateValid()
    {
        mIsValid = false;
        if (mTracesInFile >= 0 && mSampleInterval > 0 &&
            mSamplesPerTrace >= 0 && mByteFormat == 5)
        {
            mIsValid = true;
        }
    }
    
    //HeaderData mHeader;
    std::array<char, 400> mHeader;
    int mTracesInFile = 0;
    int mSampleInterval = 0;
    int mSamplesPerTrace = 0;
    const int16_t mByteFormat = 5;
    bool mIsValid = false;
    /// File is in big endian format
    const bool mSwapBytes = testByteOrder() == LITTLE_ENDIAN ? true : false;
};

/// Constructor
BinaryFileHeader::BinaryFileHeader() :
    pImpl(std::make_unique<BinaryFileHeaderImpl> ())
{
}

/// Copy c'tor
BinaryFileHeader::BinaryFileHeader(const BinaryFileHeader &header)
{
    *this = header;
}

/// Move c'tor
BinaryFileHeader::BinaryFileHeader(BinaryFileHeader &&header) noexcept
{
    *this = std::move(header);
}

/// Copy assignment
BinaryFileHeader& BinaryFileHeader::operator=(const BinaryFileHeader &header)
{
    if (&header == this){return *this;}
    pImpl = std::make_unique<BinaryFileHeaderImpl> (*header.pImpl);
    return *this;
}

/// Move assignment
BinaryFileHeader&
BinaryFileHeader::operator=(BinaryFileHeader &&header) noexcept
{
    if (&header == this){return *this;}
    pImpl = std::move(header.pImpl);
    return *this;
}

/// Destructor
BinaryFileHeader::~BinaryFileHeader() = default; 

/// Clears the header
void BinaryFileHeader::clear() noexcept
{
    std::fill(pImpl->mHeader.begin(), pImpl->mHeader.end(), 0);
    pImpl->mTracesInFile = 0;
    pImpl->mSampleInterval = 0;
    pImpl->mSamplesPerTrace = 0;
    //pImpl->mByteFormat = 5;
    packShort(pImpl->mByteFormat, pImpl->mHeader.begin()+24, pImpl->mSwapBytes);
    pImpl->mIsValid = false;
}

/// Sets the header
void BinaryFileHeader::set(const char *header)
{
    if (header == nullptr)
    {
        throw std::invalid_argument("Header is NULL\n");
    }
    pImpl->mIsValid = false;
    std::copy(header, header+400, pImpl->mHeader.begin());
    pImpl->mTracesInFile = unpackShort(header+12, pImpl->mSwapBytes);
    pImpl->mSampleInterval = unpackShort(header+16, pImpl->mSwapBytes);
    //pImpl->mByteFormat = unpackShort(header+24, pImpl->mSwapBytes);
    if (unpackShort(header+24, pImpl->mSwapBytes) != 5)
    {
        throw std::invalid_argument("Only IEEE floats supported\n");
    }
    // N.B. 20:21 is also samples per trace but this is more robust
    pImpl->mSamplesPerTrace =  unpackInt(header+62, pImpl->mSwapBytes);
    pImpl->updateValid();
}

/// Gets the header
std::string BinaryFileHeader::get() const
{
    std::string result(pImpl->mHeader.data(), pImpl->mHeader.size());
    return result;
}

/// Gets the header
void BinaryFileHeader::get(char *headerIn[]) const
{
    auto header = *headerIn;
    if (header == nullptr)
    {
        throw std::invalid_argument("header is NULL");
    }
    std::copy(pImpl->mHeader.begin(), pImpl->mHeader.end(), header);
}

/// Sets the number of samples
void BinaryFileHeader::setNumberOfSamplesPerTrace(const int16_t nSamples)
{
    if (nSamples < 0)
    {
        throw std::invalid_argument("nSamples = " + std::to_string(nSamples)
                                  + " must be positive\n");
    }
    pImpl->mSamplesPerTrace = nSamples;
    pImpl->updateValid();
    packShort(nSamples, pImpl->mHeader.begin()+20, pImpl->mSwapBytes);
    packInt(pImpl->mSamplesPerTrace, pImpl->mHeader.begin()+62,
            pImpl->mSwapBytes);
}

/// Get number of samples per trace
int BinaryFileHeader::getNumberOfSamplesPerTrace() const
{
    return pImpl->mSamplesPerTrace;
}

/// Set the number of traces
void BinaryFileHeader::setNumberOfTraces(const int16_t nTraces)
{
    if (nTraces < 0)
    {
        throw std::invalid_argument("nTraces = " + std::to_string(nTraces)
                                  + " must be positive\n");
    }
    pImpl->mTracesInFile = nTraces;
    pImpl->updateValid();
    packShort(nTraces, pImpl->mHeader.begin()+12, pImpl->mSwapBytes);

}

/// Get the number of traces
int BinaryFileHeader::getNumberOfTraces() const
{
    return pImpl->mTracesInFile;
}

/// Set the sampling interval
void BinaryFileHeader::setSampleInterval(const int16_t sampleInterval)
{
    if (sampleInterval < 0)
    {
        throw std::invalid_argument("sampleInterval = "
                                  + std::to_string(sampleInterval)
                                  + " must be positive\n");
    }
    pImpl->mSampleInterval = sampleInterval;
    pImpl->updateValid();
    packShort(sampleInterval, pImpl->mHeader.begin()+16, pImpl->mSwapBytes);
}

/// Get sampling interval
int BinaryFileHeader::getSampleInterval() const
{
    return pImpl->mSampleInterval;
}

bool BinaryFileHeader::isValid() const noexcept
{
    return pImpl->mIsValid;
}
