#include <cstdlib>
#include <cstring>
#include <string>
#include <array>
#include <cmath>
#include <algorithm>
#include <fstream>
#include "sff/utilities/time.hpp"
#include "sff/sac/waveform.hpp"
#include "sff/sac/header.hpp"
#if __has_include(<filesystem>)
 #include <filesystem>
 namespace fs = std::filesystem;
 #define USE_FILESYSTEM 1
#elif __has_include(<experimental/filesystem>)
 #include <experimental/filesystem>
 namespace fs = std::experimental::filesystem;
 #define USE_FILESYSTEM 1
#endif

using namespace SFF::SAC;

namespace
{
float *alignedAllocFloat(const int npts)
{
    size_t nbytes = static_cast<size_t> (npts)*sizeof(float);
#ifdef HAVE_ALIGNED_ALLOC
    float *data = static_cast<float *> (aligned_alloc(64, nbytes));
#else
    void *dataTemp = malloc(nbytes);
    posix_memalign(&dataTemp, 64, nbytes);
    auto data = static_cast<float *> (dataTemp);
#endif
    return data;
}
}
//static double *alignedAllocDouble(const int npts);

class Waveform::WaveformImpl
{
public:
    /// Constructor
    WaveformImpl()
    {
        // Must give header version
        mHeader.setHeader(Integer::NVHDR, 6);
        // Must be an evenly spaced time series file
        mHeader.setHeader(Integer::IFTYPE, 1);
        mHeader.setHeader(Logical::LEVEN, true); // Default if not set
        // Force the start time to be the epoch
        /*
        mHeader.setHeader(Integer::NZYEAR, 1970); /// = default;
        mHeader.setHeader(Integer::NZJDAY, 1);
        mHeader.setHeader(Integer::NZHOUR, 0);
        mHeader.setHeader(Integer::NZMIN,  0);
        mHeader.setHeader(Integer::NZSEC,  0);
        mHeader.setHeader(Integer::NZMSEC, 0);
        */
        // Turns out b =-12345 is okay but looks screwy when plotted
        mHeader.setHeader(Double::B, 0);
    }
    WaveformImpl(const WaveformImpl &waveform)
    {
        *this = waveform;
    } 
    /// Copy assignment
    WaveformImpl& operator=(const WaveformImpl &waveform)
    {
        if (&waveform == this){return *this;}
        // Release old memory
        clear();
        mHeader = waveform.mHeader;
        int npts = mHeader.getHeader(Integer::NPTS);
        if (npts > 0 && waveform.mData)
        {
            mData = alignedAllocFloat(npts);
            auto nbytes = static_cast<size_t> (npts)*sizeof(float);
            std::memcpy(mData, waveform.mData, nbytes);
        }
        return *this;
    }
    /// Destructor
    ~WaveformImpl()
    {
        clear();
    }
    void freeData()
    {
        if (mData){free(mData);}
        mHeader.setHeader(Integer::NPTS, 0);
        mData = nullptr;
    }
    void clear()
    {
        freeData();
        mHeader.clear();
    }

//private:
    class Header mHeader;
    float *__attribute__((aligned(64))) mData = nullptr;
};

/// Constructor
Waveform::Waveform() :
    pImpl(std::make_unique<WaveformImpl> ())
{
}

/// Copy constructor
[[maybe_unused]]
Waveform::Waveform(const Waveform &waveform)
{
    *this = waveform;
}

/// Move constructor
[[maybe_unused]]
Waveform::Waveform(Waveform &&waveform) noexcept
{
    *this = std::move(waveform);
}

/// Copy assignment operator
Waveform& Waveform::operator=(const Waveform &waveform)
{
    if (&waveform == this){return *this;}
    if (pImpl){pImpl.reset();}
    pImpl = std::make_unique<WaveformImpl> (*waveform.pImpl);
    return *this;
}

/// Move assignment operator
Waveform& Waveform::operator=(Waveform &&waveform) noexcept
{
    if (&waveform == this){return *this;}
    if (pImpl){pImpl.reset();}
    pImpl = std::move(waveform.pImpl);
    return *this;
}

/// Destructor
Waveform::~Waveform() = default;

/// Resets class
void Waveform::clear() noexcept
{
    pImpl->mHeader.clear();
    if (pImpl->mData){free(pImpl->mData);}
    pImpl->mData = nullptr;
}

/// Loads a waveform
void Waveform::read(const std::string &fileName)
{
    clear();
#if USE_FILESYSTEM == 1
    if (!fs::exists(fileName))
    {
        std::string errmsg = "SAC file = " + fileName + " does not exist";
        throw std::invalid_argument(errmsg);
    }
#endif
    // Old way
    //std::ifstream sacfl(fileName, std::ios::in | std::ios::binary);
    //std::vector<char> buffer(std::istreambuf_iterator<char> (sacfl), {});
    //size_t nbytes = buffer.size();
    // Read the binary file
    std::ifstream sacfl(fileName, std::ios::in | std::ios::binary);
    sacfl.seekg(0, sacfl.end);
    size_t nbytes = sacfl.tellg();
    if (nbytes < 632)
    {
        std::string errmsg = "SAC file has less than 632 bytes; nbytes = "
                           + std::to_string(nbytes);
        throw std::invalid_argument(errmsg);
    }
    std::array<char, 632> cheader{};
    sacfl.seekg(0, sacfl.beg);
    //std::vector<char> buffer(nbytes); 
    sacfl.read(cheader.data(), cheader.size()*sizeof(char)); //buffer.data(), nbytes);
    auto nbytesRemaining = nbytes - cheader.size()*sizeof(char);
    //sacfl.close();
    // Figure out the byte order
    const char *cdat = cheader.data(); //buffer.data();
    union
    {
        char c4[4];
        int npts = 0;
    };
    std::memcpy(c4, &cdat[316], 4*sizeof(char));
    size_t nbytesEst = static_cast<size_t> (npts)*sizeof(float) + 632;
    bool lswap = false;
    if (nbytesEst != nbytes)
    {
        std::reverse(c4, c4+4);
        nbytesEst = static_cast<size_t> (npts)*sizeof(float) + 632;
        if (nbytesEst != nbytes)
        {
            std::string errmsg = "Cannot determine endianness of file";
            throw std::invalid_argument(errmsg);
        }
        lswap = true;
    }
    // Unpack the header (this will check npts and delta are valid)
    try
    {
        pImpl->mHeader.setFromBinaryHeader(cdat, lswap);
    }
    catch (const std::invalid_argument &ia)
    {
        pImpl->mHeader.clear();
        throw std::invalid_argument(ia);
    }
    // Unpack the data
    pImpl->mData = alignedAllocFloat(npts);
    if (!lswap)
    {
        auto cdata = reinterpret_cast<char *> (pImpl->mData);
        sacfl.read(cdata, nbytesRemaining);
/*
        auto fdata = reinterpret_cast<const float *> (buffer.data() + 632);
        auto *mData = pImpl->mData;
        #pragma omp simd aligned(mData: 64)
        for (auto i=0; i<npts; i++)
        {
            mData[i] = static_cast<double> (fdata[i]);
        }
*/
    }
    else
    {
        std::vector<char> buffer(nbytesRemaining);
        sacfl.read(buffer.data(), nbytesRemaining);
        auto cdata = buffer.data(); //reinterpret_cast<const char *> (buffer.data() + 632);
        // Reverse the byte order
        union
        {
            char crev[4];
            float f4 = 0;
        };
        #pragma omp simd
        for (auto i=0; i<npts; i++)
        {
            auto indx = 4*i; //632 + 4*i;
            crev[0] = cdata[indx+3];
            crev[1] = cdata[indx+2];
            crev[2] = cdata[indx+1];
            crev[3] = cdata[indx+0];
            //std::reverse_copy(&cdat[632+4*i], &cdat[632+4*i]+4, crev);
            pImpl->mData[i] = f4; //static_cast<double> (f4);
        }
    }
    sacfl.close();
}

/// Writes a waveform
void Waveform::write(const std::string &fileName, const bool lswap) const
{
    if (!isValid())
    {
        throw std::runtime_error("SAC waveform is not valid");
    }
    // Make sure the root directory exists
#if USE_FILESYSTEM == 1
    fs::path path(fileName);
    if (!path.has_relative_path())
    {
        fs::path pathName = path.parent_path();
        if (!fs::create_directories(pathName))
        {
            std::string errmsg = "Failed to make directory "
                               + std::string(pathName.c_str());
            throw std::invalid_argument(errmsg);
        }
    }
#endif
    // Pack the header
    int npts = getNumberOfSamples();
    auto nbytes = sizeof(float)*static_cast<size_t> (npts);
    std::array<char, 632> cheader{};
    pImpl->mHeader.getBinaryHeader(cheader.data(), lswap); //cdata.data(), lswap);
    // Write header 
    std::ofstream outfile(fileName,
                          std::ofstream::binary | std::ofstream::trunc);
    outfile.write(cheader.data(), cheader.size()*sizeof(char));
    // Pack the data
    if (!lswap)
    {
        auto cdata = reinterpret_cast<const char *> (pImpl->mData);
        outfile.write(cdata, nbytes);
        outfile.close();
/*
        auto fdata = reinterpret_cast<float *> (cdata.data() + 632);
        auto mData = pImpl->mData;
        #pragma omp simd aligned(mData: 64)
        for (auto i=0; i<npts; ++i)
        {
            fdata[i] = static_cast<float> (mData[i]);//pImpl->mData[i]);
        }
*/
    }
    else
    {
        union
        {
            char c4[4];
            float f4 = 0;
        };
        std::vector<char> cdata(nbytes); 
        auto mData = pImpl->mData;
        #pragma omp simd aligned(mData: 64)
        for (int i=0; i<npts; ++i)
        {
            f4 = static_cast<float> (mData[i]); //pImpl->mData[i]);
            auto indx = i*4; //632 + i*4;
            cdata[indx]   = c4[3];
            cdata[indx+1] = c4[2];
            cdata[indx+2] = c4[1];
            cdata[indx+3] = c4[0];
        }
        outfile.write(cdata.data(), nbytes);
        outfile.close();
    }
/*
    // Write it 
    std::ofstream outfile(fileName,
                          std::ofstream::binary | std::ofstream::trunc);
    outfile.write(cdata.data(), nbytes);
    outfile.close();
*/
}

/// Gets the trace start time
SFF::Utilities::Time Waveform::getStartTime() const
{
    int year   = pImpl->mHeader.getHeader(SAC::Integer::NZYEAR);
    int jday   = pImpl->mHeader.getHeader(SAC::Integer::NZJDAY);
    int hour   = pImpl->mHeader.getHeader(SAC::Integer::NZHOUR);
    int minute = pImpl->mHeader.getHeader(SAC::Integer::NZMIN);
    int isec   = pImpl->mHeader.getHeader(SAC::Integer::NZSEC);
    int musec  = pImpl->mHeader.getHeader(SAC::Integer::NZMSEC)*1000;
    double b = pImpl->mHeader.getHeader(SAC::Double::B); 
    if (year   ==-12345 || jday ==-12345 || hour  ==-12345 || 
        minute ==-12345 || isec ==-12345 || musec ==-12345 ||
        b ==-12345.0)
    {
        throw std::runtime_error("Header start time is not yet set\n");
    }
    // Create the time
    Utilities::Time startTime;
    startTime.setYear(year);
    startTime.setDayOfYear(jday);
    startTime.setHour(hour);
    startTime.setMinute(minute);
    startTime.setSecond(isec);
    startTime.setMicroSecond(musec);
    // May have to deal with b
    if (b == 0){return startTime;}
    double epochalTime = startTime.getEpoch() + b;
    startTime.setEpoch(epochalTime);
    return startTime;
}

/// Sets the trace start time
[[maybe_unused]]
void Waveform::setStartTime(const Utilities::Time &startTime) noexcept
{
     pImpl->mHeader.setHeader(SAC::Integer::NZYEAR, startTime.getYear()); 
     pImpl->mHeader.setHeader(SAC::Integer::NZJDAY, startTime.getDayOfYear());
     pImpl->mHeader.setHeader(SAC::Integer::NZHOUR, startTime.getHour());
     pImpl->mHeader.setHeader(SAC::Integer::NZMIN,  startTime.getMinute());
     pImpl->mHeader.setHeader(SAC::Integer::NZSEC,  startTime.getSecond());
     auto millisec = static_cast<int> (std::lround((startTime.getMicroSecond()*1.e-3)));
     pImpl->mHeader.setHeader(SAC::Integer::NZMSEC, millisec);
     pImpl->mHeader.setHeader(SAC::Double::B, 0.0);    
}

/// Sets a double header value
[[maybe_unused]]
void Waveform::setHeader(const Double variableName, const double value)
{
    pImpl->mHeader.setHeader(variableName, value);
}

/// Gets a double header value
[[maybe_unused]]
double Waveform::getHeader(const Double variableName) const noexcept
{
    return pImpl->mHeader.getHeader(variableName);
}

/// Sets an integer header value
[[maybe_unused]]
void Waveform::setHeader(const Integer variableName, const int value)
{
    if (variableName == Integer::NPTS)
    {
        throw std::invalid_argument("NPTS cannot be set with this function");
    }
    if (variableName == Integer::IFTYPE)
    {
        throw std::invalid_argument("IFTYPE cannot be set with this function");
    }
    pImpl->mHeader.setHeader(variableName, value);
}

/// Gets an integer header value
int Waveform::getHeader(const Integer variableName) const noexcept
{
    return pImpl->mHeader.getHeader(variableName);
}

/// Sets a logical header value
[[maybe_unused]]
void Waveform::setHeader(const Logical variableName, const bool value) noexcept
{
    pImpl->mHeader.setHeader(variableName, value);
}

/// Gets a logical header value
[[maybe_unused]]
int Waveform::getHeader(const Logical variableName) const noexcept
{
    return pImpl->mHeader.getHeader(variableName);
}

/// Sets a character header value
[[maybe_unused]]
void Waveform::setHeader(const Character variableName,
                         const std::string &value) noexcept
{
    pImpl->mHeader.setHeader(variableName, value);
}

/// Gets a character header value
std::string Waveform::getHeader(const Character variableName) const noexcept
{
    return pImpl->mHeader.getHeader(variableName);
}
                         
/// Gets the waveform sampling period
double Waveform::getSamplingPeriod() const
{
    auto dt = pImpl->mHeader.getHeader(Double::DELTA);
    if (dt <= 0){throw std::runtime_error("Sampling rate not yet set\n");}
    return dt;
}

/// Sets the sampling period
void Waveform::setSamplingPeriod(const double dt)
{
    if (dt <= 0)
    {
        throw std::invalid_argument("Sampling period must be positive\n");
    }
    pImpl->mHeader.setHeader(Double::DELTA, dt);
}

/// Sets the waveform sampling rate
void Waveform::setSamplingRate(const double df)
{
    if (df <= 0)
    {
        throw std::invalid_argument("Sampling rate must be positive\n");
    }
    pImpl->mHeader.setHeader(Double::DELTA, 1./df);
}

/// Gets the waveform sampling rate
double Waveform::getSamplingRate() const
{
    return 1/getSamplingPeriod();
}

/// Gets the number of samples in the waveform
int Waveform::getNumberOfSamples() const noexcept
{
    return pImpl->mHeader.getHeader(Integer::NPTS);
}

/// Gets the file format
SFF::Format Waveform::getFormat() const noexcept
{
    return SFF::Format::SAC;
}

/// Checks if this is a valid trace
bool Waveform::isValid() const noexcept
{
    if (!pImpl){return false;}
    if (getSamplingPeriod() <= 0){return false;}
    if (getNumberOfSamples() < 0){return false;}
    return pImpl->mData != nullptr;
}

/// Gets a pointer to the data
const float *Waveform::getDataPointer() const noexcept
{
    return pImpl->mData;
}

/// Get a copy of the data
void Waveform::getData(const int npts, double *dataIn[]) const
{
    int n = getNumberOfSamples();
    if (npts < n)
    {
        throw std::invalid_argument("npts = " + std::to_string(npts)
                                  + " must be at least "
                                  + std::to_string(n) + "\n");
    }
    auto *mData = pImpl->mData;
    auto *data = *dataIn;
    std::copy(mData, mData+n, data); 
}

/*
void Waveform::getData(const int npts, int *dataIn[]) const
{
    int n = getNumberOfSamples();
    if (npts < n)
    {
        throw std::invalid_argument("npts = " + std::to_string(npts)
                                  + " must be at least "
                                  + std::to_string(n) + "\n");
    }
    auto *mData = pImpl->mData;
    auto *data = *dataIn;
    std::copy(mData, mData+n, data);
}
*/

void Waveform::getData(const int npts, float *dataIn[]) const
{
    int n = getNumberOfSamples();
    if (npts < n)
    {
        throw std::invalid_argument("npts = " + std::to_string(npts)
                                  + " must be at least "
                                  + std::to_string(n) + "\n");
    }
    auto *mData = pImpl->mData;
    auto *data = *dataIn;
    std::copy(mData, mData+n, data);
}

/// Gets a copy of the data
std::vector<double> Waveform::getData() const noexcept
{
    int npts = getNumberOfSamples();
    if (npts > 0 && pImpl->mData)
    {
        std::vector<double> data(npts);
        double *dataPtr = data.data();
        getData(npts, &dataPtr);
        return data;
    }
    else
    {
        std::vector<double> data(0);
        return data;
    }
}

/// Sets the waveform data
[[maybe_unused]]
void Waveform::setData(const int npts, const double x[])
{
    pImpl->freeData();
    if (npts <= 0)
    {
        throw std::invalid_argument("npts = " + std::to_string(npts)
                                  + " must be positive\n");
    }
    if (x == nullptr)
    {
        throw std::invalid_argument("x is NULL");
    }
    pImpl->mHeader.setHeader(Integer::NPTS, npts);
    pImpl->mData = alignedAllocFloat(npts);
    auto mData = pImpl->mData;
    std::copy(x, x+npts, mData); 
    //std::memcpy(pImpl->mData, x, static_cast<size_t> (npts)*sizeof(double));
}

[[maybe_unused]]
void Waveform::setData(const int npts, const float x[])
{
    pImpl->freeData();
    if (npts <= 0)
    {
        throw std::invalid_argument("npts = " + std::to_string(npts)
                                  + " must be positive\n");
    }
    if (x == nullptr)
    {
        throw std::invalid_argument("x is NULL");
    }
    pImpl->mHeader.setHeader(Integer::NPTS, npts);
    pImpl->mData = alignedAllocFloat(npts);
    auto mData = pImpl->mData;
    std::copy(x, x+npts, mData); 
}

//============================================================================//
/*
static double *alignedAllocDouble(const int npts)
{
    size_t nbytes = static_cast<size_t> (npts)*sizeof(double);
#ifdef HAVE_ALIGNED_ALLOC
    double *data = static_cast<double *> (std::aligned_alloc(64, nbytes));
#else
    void *dataTemp = malloc(nbytes);
    posix_memalign(&dataTemp, 64, nbytes);
    auto data = static_cast<double *> (dataTemp);
#endif
    return data;
}
*/
