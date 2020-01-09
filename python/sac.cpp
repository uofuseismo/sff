#include <cstdio>
#include <cstdlib>
#include <string>
#include "sff/sac/waveform.hpp"
#include "sff/sac/header.hpp"
#include "sac.hpp"

using namespace PBSFF;

/// Constructor
SAC::SAC() :
    mWaveform(std::make_unique<SFF::SAC::Waveform> ())
{
}

/// Copy c'tor
SAC::SAC(const SAC &sac)
{
    *this = sac;
}

SAC::SAC(const SFF::SAC::Waveform &sac)
{
    *this = sac;
}

/// Copy assignment operator
SAC& SAC::operator=(const SAC &sac)
{
    if (&sac == this){return *this;}
    mWaveform
        = std::make_unique<SFF::SAC::Waveform> (*sac.mWaveform);
    return *this;
}

SAC& SAC::operator=(const SFF::SAC::Waveform &sac)
{
    mWaveform = std::make_unique<SFF::SAC::Waveform> (sac);
    return *this;
}

/// Destructor
SAC::~SAC() = default;

/// Loads a time series from disk
void SAC::read(const std::string &fileName)
{
    mWaveform->read(fileName);
}

/// Writes a time series to disk
void SAC::write(const std::string &fileName)
{
    mWaveform->write(fileName);
}

/// Sampling period
void SAC::setSamplingPeriod(const double dt)
{
    if (dt <= 0)
    {
        throw std::invalid_argument("Sampling period must be positive\n");
    }
    mWaveform->setHeader(SFF::SAC::Double::DELTA, dt);
}

double SAC::getSamplingPeriod() const
{
    return mWaveform->getSamplingPeriod();
}

/// Sets the waveform
void SAC::setWaveform(
    const pybind11::array_t<double, pybind11::array::c_style |
                            pybind11::array::forcecast> &x)
{
    pybind11::buffer_info xbuf = x.request();
    auto len = static_cast<int> (xbuf.size);
    const double *xptr = (double *) (xbuf.ptr);
    if (xptr == nullptr)
    {   
        throw std::runtime_error("x is null");
    }   
    mWaveform->setData(len, xptr);
}

/// Gets the waveform
pybind11::array_t<double> SAC::getWaveform() const
{
    auto npts = mWaveform->getNumberOfSamples();
    auto y = pybind11::array_t<double, pybind11::array::c_style> (npts);
    pybind11::buffer_info ybuf = y.request();
    auto yptr = static_cast<double *> (ybuf.ptr);
    mWaveform->getData(npts, &yptr);
    return y;
}

/// Gets the number of samples
int SAC::getNumberOfSamples() const
{
    return mWaveform->getNumberOfSamples();
}

/// Sampling rate
void SAC::setSamplingRate(const double rate)
{
    if (rate <= 0)
    {
        throw std::invalid_argument("Sampling rate must be positive\n");
    }
    setSamplingPeriod(1.0/rate);
}

double SAC::getSamplingRate() const
{
    return mWaveform->getSamplingRate();
}

/// Double header 
void SAC::setDoubleHeaderVariable(const double value,
                                  const SFF::SAC::Double name)
{
    mWaveform->setHeader(name, value);
}

double SAC::getDoubleHeaderVariable(
    const SFF::SAC::Double name) const
{
    return mWaveform->getHeader(name);
}

/// Integer header
void SAC::setIntegerHeaderVariable(int value,
                                   const SFF::SAC::Integer name)
{
    // Don't let user mess with npts
    if (name == SFF::SAC::Integer::NPTS)
    {
        if (mWaveform->getNumberOfSamples() != value)
        {
            std::string errmsg
             = "The number of samples cannot be modified through the header.  ";
            errmsg = errmsg
                   + "This can only be modified by setting the waveform.";
            throw std::invalid_argument(errmsg);
        }
        return; // Do nothing
    }
    mWaveform->setHeader(name, value);
}

int SAC::getIntegerHeaderVariable(
    const SFF::SAC::Integer name) const
{
    return mWaveform->getHeader(name);
}

/// Logical header
void SAC::setLogicalHeaderVariable(bool value,
                                  const SFF::SAC::Logical name)
{
    mWaveform->setHeader(name, value);
}

bool SAC::getLogicalHeaderVariable(
    const SFF::SAC::Logical name) const
{
    return mWaveform->getHeader(name);
}

/// Character header
void SAC::setCharacterHeaderVariable(
    const std::string &value,
    const SFF::SAC::Character name)
{
    mWaveform->setHeader(name, value);
}

std::string SAC::getCharacterHeaderVariable(
    const SFF::SAC::Character name) const
{
    // The string is null terminated so for compiled language work we're fine.
    // However, Python gets confused because the allocated length is 8 or 16.
    // Hence it has to be trimmed.
    auto stemp = mWaveform->getHeader(name);
    auto lenos = strnlen(stemp.c_str(), 8);
    std::string result(stemp.c_str(), lenos); // Trim for python
    return result;
}
