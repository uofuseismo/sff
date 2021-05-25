#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <array>
#include "sff/segy/silixa/traceHeader.hpp"
#include "sff/utilities/time.hpp"
#include "private/byteSwap.hpp"

using namespace SFF::SEGY::Silixa;

class TraceHeader::TraceHeaderImpl
{
public:
    TraceHeaderImpl()
    {
        mStartTime.setEpoch(0);
        clear();
    } 
    /// Resets the header
    void clear() noexcept
    {
        std::fill(mHeader.begin(), mHeader.end(), 0); 
        packInt(mTraceNumber,             mHeader.data() + 0,  mSwapBytes);
        packInt(mReceiverDepthBelowRKB,   mHeader.data() + 40, mSwapBytes);
        packInt(mSourceDepthBelowSurface, mHeader.data() + 48, mSwapBytes);

        packShort(mElevationScalar,  mHeader.data() + 68, mSwapBytes);
        packShort(mCoordinateScalar, mHeader.data() + 70, mSwapBytes);

        packInt(mSourceEasting,    mHeader.data() + 72, mSwapBytes);
        packInt(mSourceNorthing,   mHeader.data() + 76, mSwapBytes);
        packInt(mReceiverEasting,  mHeader.data() + 80, mSwapBytes);
        packInt(mReceiverNorthing, mHeader.data() + 84, mSwapBytes);

        packShort(mCoordinateUnits, mHeader.data() + 88,  mSwapBytes);
        packShort(mSamples,         mHeader.data() + 114, mSwapBytes);
        packShort(mSampleInterval,  mHeader.data() + 116, mSwapBytes);
        packShort(mCorrelated,      mHeader.data() + 124, mCorrelated);

        packStartTime();
 
        packInt(mSamples,            mHeader.data()+232, mSwapBytes);
        packInt(mDistanceAlongFiber, mHeader.data()+236, mSwapBytes);
    }
    /// Convenience utility to pack the start time
    void packStartTime()
    {
        packShort(mStartTime.getYear(),      mHeader.data()+156, mSwapBytes);
        packShort(mStartTime.getDayOfYear(), mHeader.data()+158, mSwapBytes);
        packShort(mStartTime.getHour(),      mHeader.data()+160, mSwapBytes);
        packShort(mStartTime.getMinute(),    mHeader.data()+162, mSwapBytes);
        packShort(mStartTime.getSecond(),    mHeader.data()+164, mSwapBytes);
        packShort(mTimeBasisCode,            mHeader.data()+168, mSwapBytes);
    }
//private:
    std::array<char, 240> mHeader{};
    SFF::Utilities::Time mStartTime;

    int mTraceNumber = 0;
    int mReceiverDepthBelowRKB = 0;
    int mSourceDepthBelowSurface = 0;
 
    int mSourceEasting = 0;
    int mSourceNorthing = 0;
    int mReceiverEasting = 0;
    int mReceiverNorthing = 0;
    int mSamples = 0;
    int mSampleInterval = 0;
    int mDistanceAlongFiber = 0;

    int16_t mCoordinateUnits = 0;
    int16_t mElevationScalar = 1;
    int16_t mCoordinateScalar = 1; 
    int16_t mCorrelated = 2;
    const int16_t mTimeBasisCode = 4; // UTC
    const bool mSwapBytes = testByteOrder() == LITTLE_ENDIAN;
};

/// Constructor
TraceHeader::TraceHeader() :
    pImpl(std::make_unique<TraceHeaderImpl> ())
{
}

/// Copy c'tor
TraceHeader::TraceHeader(const TraceHeader &header)
{
    *this = header;
}

/// Move c'tor
[[maybe_unused]]
TraceHeader::TraceHeader(TraceHeader &&header) noexcept
{
    *this = std::move(header);
}

/// Copy assignment operator
TraceHeader& TraceHeader::operator=(const TraceHeader &header)
{
    if (&header == this){return *this;}
    pImpl = std::make_unique<TraceHeaderImpl> (*header.pImpl);
    return *this;
}

/// Move assignment operator
TraceHeader& TraceHeader::operator=(TraceHeader &&header) noexcept
{
    if (&header == this){return *this;}
    pImpl = std::move(header.pImpl);
    return *this;
}

/// Destructor
TraceHeader::~TraceHeader() = default;

/// Clears the class
void TraceHeader::clear() noexcept
{
    pImpl->clear();
}

/// Sets the header
void TraceHeader::set(const char *header)
{
    if (header == nullptr)
    {
        throw std::invalid_argument("header is NULL\n");
    }
    auto swap = pImpl->mSwapBytes;
    // Unpack the header
    std::copy(header, header+240, pImpl->mHeader.data());

    pImpl->mTraceNumber             = unpackInt(pImpl->mHeader.data()+0,  swap);
    pImpl->mReceiverDepthBelowRKB   = unpackInt(pImpl->mHeader.data()+40, swap);
    pImpl->mSourceDepthBelowSurface = unpackInt(pImpl->mHeader.data()+48, swap);

    pImpl->mElevationScalar  = unpackShort(pImpl->mHeader.data()+68, swap);
    pImpl->mCoordinateScalar = unpackShort(pImpl->mHeader.data()+70, swap);

    pImpl->mSourceEasting    = unpackInt(pImpl->mHeader.data()+72, swap);
    pImpl->mSourceNorthing   = unpackInt(pImpl->mHeader.data()+76, swap);
    pImpl->mReceiverEasting  = unpackInt(pImpl->mHeader.data()+80, swap);
    pImpl->mReceiverNorthing = unpackInt(pImpl->mHeader.data()+84, swap);

    pImpl->mCoordinateUnits = unpackShort(pImpl->mHeader.data()+88,  swap);
    pImpl->mSampleInterval  = unpackShort(pImpl->mHeader.data()+116, swap);
    pImpl->mCorrelated      = unpackShort(pImpl->mHeader.data()+124, swap);

    auto year      = unpackShort(pImpl->mHeader.data()+156, swap);
    auto julday    = unpackShort(pImpl->mHeader.data()+158, swap);
    auto hour      = unpackShort(pImpl->mHeader.data()+160, swap);
    auto minute    = unpackShort(pImpl->mHeader.data()+162, swap);
    auto second    = unpackShort(pImpl->mHeader.data()+164, swap);
    auto basisCode = unpackShort(pImpl->mHeader.data()+166, swap);
    if (basisCode != pImpl->mTimeBasisCode)
    {
        clear();
        throw std::invalid_argument("Can only handle UTC time\n");
    }
    pImpl->mStartTime.setYear(year);
    pImpl->mStartTime.setDayOfYear(julday);
    pImpl->mStartTime.setHour(hour);
    pImpl->mStartTime.setMinute(minute);
    pImpl->mStartTime.setSecond(second);

    pImpl->mSamples            = unpackInt(pImpl->mHeader.data()+232, swap);
    pImpl->mDistanceAlongFiber = unpackInt(pImpl->mHeader.data()+236, swap);
}

/// Gets the header
void TraceHeader::get(char *headerIn[]) const
{
    auto header = *headerIn;
    if (header == nullptr)
    {
        throw std::invalid_argument("header is NULL\n");
    }
    std::copy(pImpl->mHeader.begin(), pImpl->mHeader.end(), header);
}

std::string TraceHeader::get() const noexcept
{
    std::string result(pImpl->mHeader.begin(), pImpl->mHeader.size());
    return result;
}

/// Set the trace number
void TraceHeader::setTraceNumber(const int traceNumber)
{
    packInt(traceNumber, pImpl->mHeader.data()+0,  pImpl->mSwapBytes);
    pImpl->mTraceNumber = traceNumber;
}

/// Get the trace number
int TraceHeader::getTraceNumber() const
{
    return pImpl->mTraceNumber;
}

/// Gets the number of samples
void TraceHeader::setNumberOfSamples(const int nSamples)
{
    if (nSamples < 0)
    {
        throw std::invalid_argument("nSamples = " + std::to_string(nSamples)
                                  + " cannot be negative\n");
    }
    packShort(nSamples, pImpl->mHeader.data()+114, pImpl->mSwapBytes);
    packInt(nSamples,   pImpl->mHeader.data()+232, pImpl->mSwapBytes);
    pImpl->mSamples = nSamples;
}

int TraceHeader::getNumberOfSamples() const
{
    return pImpl->mSamples;
}

/// Gets the sample interval
void TraceHeader::setSampleInterval(const int16_t sampleInterval)
{
    if (sampleInterval < 0)
    {   
        throw std::invalid_argument("sampleInterval = "
                                  + std::to_string(sampleInterval)
                                  + " must be positive\n");
    }
    packShort(sampleInterval, pImpl->mHeader.data()+116, pImpl->mSwapBytes);
    pImpl->mSampleInterval = sampleInterval;
}

int TraceHeader::getSampleInterval() const
{
    return pImpl->mSampleInterval;
}

/// Gets the trace start time
void TraceHeader::setStartTime(const SFF::Utilities::Time &startTime)
{
    pImpl->mStartTime = startTime;
    pImpl->packStartTime();
}

SFF::Utilities::Time TraceHeader::getStartTime() const
{
    return pImpl->mStartTime;
}

/// Correlated
void TraceHeader::setIsCorrelated(const bool isCorrelated)
{
    int16_t correlated = 1;
    if (isCorrelated){correlated = 2;}
    packShort(correlated, pImpl->mHeader.data()+124, pImpl->mSwapBytes);
    pImpl->mCorrelated = correlated;
}

bool TraceHeader::getIsCorrelated() const
{
    return (pImpl->mCorrelated == 2);
}

/// Sets/gets the distance along fiber
void TraceHeader::setDistanceAlongFiber(const int distance)
{
    packInt(distance, pImpl->mHeader.data()+236, pImpl->mSwapBytes);
    pImpl->mDistanceAlongFiber = distance;
}

int TraceHeader::getDistanceAlongFiber() const
{
    return pImpl->mDistanceAlongFiber;
}
