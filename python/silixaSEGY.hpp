#ifndef SFF_SILIXASEGY_HPP
#define SFF_SILIXASEGY_HPP
#include <memory>
#include <string>
#include <pybind11/numpy.h>
#include "time.hpp"

namespace SFF::SEGY::Silixa
{
class TraceGroup;
class Trace;
}

namespace PBSFF::SEGY::Silixa
{
class TraceGroup
{
public:
    /// C'tor
    TraceGroup();
    /// Copy c'tor
    TraceGroup& operator=(const TraceGroup &group);
    TraceGroup& operator=(const SFF::SEGY::Silixa::TraceGroup &group); 
    /// Destructor
    ~TraceGroup();
private:
    std::unique_ptr<SFF::SEGY::Silixa::TraceGroup> pImpl;
};
class Trace
{
public:
    /// C'tor
    Trace();
    /// Copy c'tor
    Trace(const Trace &trace);
    Trace(const SFF::SEGY::Silixa::Trace &trace);
    /// Copy assignment
    Trace& operator=(const Trace &trace);
    Trace& operator=(const SFF::SEGY::Silixa::Trace &trace);
    /// Destructor
    ~Trace();
    /// Sets/gets the waveform
    void setWaveform(const pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast> &x);
    pybind11::array_t<double> getWaveform() const;
    /// Sets/gets the sampling period
    void setSamplingPeriod(double samplingPeriod);
    double getSamplingPeriod() const;
    void setSamplingRate(double samplingRate);
    double getSamplingRate() const;
    /// Sets/gets the start time
    void setStartTime(const PBSFF::Time &time);
    PBSFF::Time getStartTime() const;
    /// Gets the number of samples
    int getNumberOfSamples() const;
private:
    std::unique_ptr<SFF::SEGY::Silixa::Trace> mWaveform;
};
void initializeTrace(pybind11::module &m);
}
#endif
