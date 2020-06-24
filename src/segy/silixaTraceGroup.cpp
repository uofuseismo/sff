#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <limits>
#include "sff/segy/silixa/traceGroup.hpp"
#include "sff/segy/silixa/trace.hpp"
#include "sff/segy/silixa/binaryFileHeader.hpp"
#include "sff/segy/textualFileHeader.hpp"
#if __has_include(<filesystem>)
 #include <filesystem>
 namespace fs = std::filesystem;
 #define USE_FILESYSTEM 1
#elif __has_include(<experimental/filesystem>)
 #include <experimental/filesystem>
 namespace fs = std::experimental::filesystem;
 #define USE_FILESYSTEM 1
#endif

using namespace SFF::SEGY::Silixa;

class TraceGroup::TraceGroupImpl
{
public:
    SFF::SEGY::TextualFileHeader mTextualFileHeader;
    SFF::SEGY::Silixa::BinaryFileHeader mBinaryFileHeader;
    std::vector<SFF::SEGY::Silixa::Trace> mTraces;
};

/// Constructor
TraceGroup::TraceGroup() :
    pImpl(std::make_unique<TraceGroupImpl> ())
{
}

/// Copy c'tor
[[maybe_unused]]
TraceGroup::TraceGroup(const TraceGroup &group)
{
    *this = group;
}

/// Move c'tor
[[maybe_unused]]
TraceGroup::TraceGroup(TraceGroup &&group) noexcept
{
    *this = std::move(group);
}

/// Copy assignment
TraceGroup& TraceGroup::operator=(const TraceGroup &group)
{
    if (&group == this){return *this;}
    pImpl = std::make_unique<TraceGroupImpl> (*group.pImpl);
    return *this;
}

/// Move assignment
TraceGroup& TraceGroup::operator=(TraceGroup &&group) noexcept
{
    if (&group == this){return *this;}
    pImpl = std::move(group.pImpl);
    return *this;
}

/// Destructor
TraceGroup::~TraceGroup() = default;

/// Clears the class
void TraceGroup::clear() noexcept
{
    pImpl->mTextualFileHeader.clear();
    pImpl->mBinaryFileHeader.clear();
    pImpl->mTraces.clear();
}

/// Clears the traces
[[maybe_unused]]
void TraceGroup::clearTraces() noexcept
{
    pImpl->mBinaryFileHeader.setNumberOfTraces(0);
    pImpl->mTraces.clear();
}

/// Load the file
void TraceGroup::read(const std::string &fileName)
{
    clear();
#if USE_FILESYSTEM == 1
    if (!fs::exists(fileName))
    {
        std::string errmsg = "SEGY file = " + fileName + " does not exist";
        throw std::invalid_argument(errmsg);
    }
#endif     
    // Read the file
    std::ifstream segyfl(fileName, std::ios::in | std::ios::binary);
    if (segyfl)
    {
        segyfl.seekg(0, segyfl.end);
        auto length = segyfl.tellg();
        if (length < 3600)
        {
            throw std::invalid_argument("File must be at least 3600 bytes\n");
        }
        segyfl.seekg(0, segyfl.beg);
        // Read the textual header and binary header
        std::array<char, 3200> textHeader{};
        std::array<char, 400> binaryFileHeader{};
        segyfl.read(textHeader.data(), 3200);
        segyfl.read(binaryFileHeader.data(), 400);
        try 
        {
            pImpl->mTextualFileHeader.setEBCDIC(textHeader.data());
        }
        catch (const std::exception &e)
        {
            clear();
            auto errmsg = std::string(e.what())
                        + "EBCDIC header is malformed\n";
            throw std::invalid_argument(errmsg);
        }
        try
        {
            pImpl->mBinaryFileHeader.set(binaryFileHeader.data());
        }
        catch (const std::exception &e)
        {
            clear();
            auto errmsg = std::string(e.what())
                        + "Binary file header is malformed\n";
            throw std::invalid_argument(errmsg);
        } 
        // If I haven't choked yet I can now unpack the traces
        auto nTraces = pImpl->mBinaryFileHeader.getNumberOfTraces();
        auto nSamples = pImpl->mBinaryFileHeader.getNumberOfSamplesPerTrace();
        auto estSize = 3600 + nTraces*(240 + 4*nSamples);
        if (estSize != length)
        {
            clear();
            throw std::invalid_argument("File size is incorrect\n");
        }
        // Now take it down
        int traceLen = 240 + 4*nSamples;
        std::vector<char> cdata(traceLen);
        pImpl->mTraces.resize(nTraces);
        for (int i=0; i<nTraces; ++i)
        {
            //int offset = 0*traceLen*i;
            segyfl.read(cdata.data(), traceLen);
            try
            {
                pImpl->mTraces[i].set(traceLen, cdata.data());
            }
            catch (const std::exception &e)
            {
                clear();
                auto errmsg = std::string(e.what())
                            + "Failed to set trace "
                            + std::to_string(i);
                throw std::invalid_argument(errmsg);
            }
        }
        segyfl.close();
    }
    else
    {
       throw std::invalid_argument("Error reading file\n");
    }   
}

/// Gets the number of samples in each trace
int TraceGroup::getNumberOfSamplesPerTrace() const
{
    return pImpl->mBinaryFileHeader.getNumberOfSamplesPerTrace();
}

/// Gets the number of traces
int TraceGroup::getNumberOfTraces() const
{
    return static_cast<int> (pImpl->mTraces.size());
}

/// Iterators
TraceIterator<SFF::SEGY::Silixa::Trace> TraceGroup::begin()
{
    return pImpl->mTraces.begin();
}

ConstTraceIterator<SFF::SEGY::Silixa::Trace> TraceGroup::begin() const
{
    return pImpl->mTraces.begin();
}

TraceIterator<SFF::SEGY::Silixa::Trace> TraceGroup::end()
{
    return pImpl->mTraces.end();
}

ConstTraceIterator<SFF::SEGY::Silixa::Trace> TraceGroup::end() const
{
    return pImpl->mTraces.end();
}

Trace TraceGroup::operator[](const size_t index)
{
    return pImpl->mTraces[index];
}

ConstTraceReference TraceGroup::operator[](const size_t index) const
{
    return pImpl->mTraces[index];
} 

Trace TraceGroup::at(const size_t index)
{
    return pImpl->mTraces.at(index);
}

ConstTraceReference TraceGroup::at(const size_t index) const
{
    return pImpl->mTraces.at(index);
}
