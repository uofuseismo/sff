#include <cstdio>
#include <cstdlib>
#include <string>
#include "sff/segy/silixa/traceHeader.hpp"
#include "sff/segy/silixa/trace.hpp"
#include "private/byteSwap.hpp"

using namespace SFF::SEGY::Silixa;

namespace
{

static float *alignedAllocFloat(const int npts)
{
    size_t nbytes = static_cast<size_t> (npts)*sizeof(float);
#ifdef HAVE_ALIGNED_ALLOC
    float *data = static_cast<float *> (std::aligned_alloc(64, nbytes));
#else
    void *dataTemp = malloc(nbytes);
    posix_memalign(&dataTemp, 64, nbytes);
    auto data = static_cast<float *> (dataTemp);
#endif
    return data;
}

}

class Trace::TraceImpl
{
public:
    TraceImpl()
    {
        mHeader.setSampleInterval(500); 
    }
    /// Copy c'tor
    TraceImpl(const TraceImpl &trace)
    {
        *this = trace;
    }
    /// Copy assignment operator.
    TraceImpl& operator=(const TraceImpl &trace)
    {
        if (&trace == this){return *this;}
        mHeader = trace.mHeader;
        mSamples = trace.mSamples;
        if (mSamples > 0 && trace.mData)
        {
            mData = alignedAllocFloat(mSamples);
            std::copy(trace.mData, trace.mData+mSamples, mData);
        }
        return *this;
    }
    /// Destructor
    ~TraceImpl()
    {
        clear();
    }
    /// Clears the class and resets the header
    void clear() noexcept
    {
        if (mData){free(mData);}
        mData = nullptr;
        mHeader.clear();
        mSamples = 0;
    }
/// private:
    float *__attribute__((aligned(64))) mData = nullptr;
    TraceHeader mHeader;
    int mSamples = 0;
    const bool mSwapBytes = testByteOrder() == LITTLE_ENDIAN ? true : false;
};

/// Constructor
Trace::Trace() :
    pImpl(std::make_unique<TraceImpl> ())
{
}

/// Copy c'tor
Trace::Trace(const Trace &trace)
{
    *this = trace;
}

/// Move c'tor
Trace::Trace(Trace &&trace) noexcept 
{
    *this = std::move(trace);
}

/// Copy assignment operator
Trace& Trace::operator=(const Trace &trace)
{
    if (&trace == this){return *this;}
    if (pImpl){clear();}
    pImpl = std::make_unique<TraceImpl> (*trace.pImpl);
    return *this;
}

/// Move assignment operator
Trace& Trace::operator=(Trace &&trace) noexcept
{
    if (&trace == this){return *this;}
    if (pImpl){clear();}
    pImpl = std::move(trace.pImpl);
    return *this;
}

/// Destructor
Trace::~Trace()
{
    clear();
}

/// Clears the class
void Trace::clear() noexcept
{
    pImpl->clear();
}

/// Gets the data
void Trace::getData(const int nSamples, float *xIn[]) const
{
    auto nSamplesRef = getNumberOfSamples();
    if (nSamples != nSamplesRef)
    {
        throw std::invalid_argument("nSamples = " + std::to_string(nSamples)
                                  + " must equal " + std::to_string(nSamplesRef)
                                  + "\n");
    }
    if (nSamples == 0){return;}
    auto x = *xIn;
    if (x == nullptr){throw std::invalid_argument("x is NULL\n");}
    auto data = pImpl->mData;
    std::copy(data, data+nSamplesRef, x);
}

/// Gets the data
void Trace::getData(const int nSamples, double *xIn[]) const
{
    auto nSamplesRef = getNumberOfSamples();
    if (nSamples != nSamplesRef)
    {
        throw std::invalid_argument("nSamples = " + std::to_string(nSamples)
                                  + " must equal " + std::to_string(nSamplesRef)
                                  + "\n");
    }
    if (nSamples == 0){return;}
    auto x = *xIn;
    if (x == nullptr){throw std::invalid_argument("x is NULL\n");}
    auto data = pImpl->mData;
    #pragma omp simd aligned(data: 64)
    for (int i=0; i<nSamples; ++i){x[i] = data[i];}
}


/// Gets the number of samples
int Trace::getNumberOfSamples() const
{
    return pImpl->mSamples;
}

/// Sets the trace header and data
void Trace::set(int len, const char x[])
{
    // Unpack the header
    TraceHeader header;
    header.set(x);
    auto nSamplesEst = header.getNumberOfSamples();
    auto lenEst = 240 + 4*nSamplesEst;
    if (lenEst != len)
    {
        throw std::invalid_argument("len = " + std::to_string(len)
                                  + " should equal "
                                  + std::to_string(lenEst) + "\n");
    }
    pImpl->mSamples = nSamplesEst;
    if (pImpl->mData){free(pImpl->mData);}
    pImpl->mData = alignedAllocFloat(pImpl->mSamples);
    auto data = pImpl->mData;
    auto lswap = pImpl->mSwapBytes;
    #pragma omp simd aligned(data: 64)
    for (int i=0; i<nSamplesEst; ++i)
    {
        data[i] = unpackFloat(x+240+4*i, lswap);;
    } 
}

/// Sets the sampling period in micro-seconds
void Trace::setSamplingPeriod(const double dt) 
{
    auto dtMicroSeconds = static_cast<int16_t> (dt*1000000 + 0.5);
    pImpl->mHeader.setSampleInterval(dtMicroSeconds);
}

double Trace::getSamplingRate() const
{
    auto dt = getSamplingPeriod();
    return static_cast<double> (1./dt);
}

double Trace::getSamplingPeriod() const
{
    auto dt = static_cast<double> (pImpl->mHeader.getSampleInterval())*1.e-6;
    if (dt <= 0)
    {
        throw std::invalid_argument("Sampling period not yet correctly set\n");
    }
    return dt;
}

/// Sets the start time
void Trace::setStartTime(const SFF::Utilities::Time &time)
{
    pImpl->mHeader.setStartTime(time);
}

/// Gets the trace start time
SFF::Utilities::Time Trace::getStartTime() const
{
    return pImpl->mHeader.getStartTime();
}

/// Gets the format
SFF::Format Trace::getFormat() const noexcept
{
    return SFF::Format::SILIXA_SEGY;
}
