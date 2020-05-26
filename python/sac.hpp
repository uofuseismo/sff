#ifndef SFF_SAC_HPP
#define SFF_SAC_HPP
#include <memory>
#include <string>
#include <pybind11/numpy.h>
#include "time.hpp"
#include "sff/sac/enums.hpp"
namespace SFF::SAC
{
class Waveform;
}

namespace PBSFF
{
class SAC
{
public:
    /// Constructor
    SAC();
    /// Copy c'tor
    SAC(const SAC &sac);
    SAC(const SFF::SAC::Waveform &sac);
    /// Copy assignment operator
    SAC& operator=(const SAC &sac);
    SAC& operator=(const SFF::SAC::Waveform &sac);
    /// Reads a SAC waveform from file
    void read(const std::string &fileName);
    /// Writes a SAC waveform to file
    void write(const std::string &fileName);
    /// Sets the data
    void setWaveform(pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast> &x);
    pybind11::array_t<double> getWaveform() const;    
    /// Sets the sampling period
    void setSamplingPeriod(double samplingPeriod);
    double getSamplingPeriod() const;
    void setSamplingRate(double samplingRate);
    double getSamplingRate() const;
    /// Sets/gets the start time
    void setStartTime(const PBSFF::Time &time);
    PBSFF::Time getStartTime() const;
    /// Gets the number of samples
    int getNumberOfSamples() const;
    /// The header variables
    void setDoubleHeaderVariable(const SFF::SAC::Double name, double value);
    double getDoubleHeaderVariable(const SFF::SAC::Double name) const;
    void setIntegerHeaderVariable(const SFF::SAC::Integer name, int value);
    int getIntegerHeaderVariable(const SFF::SAC::Integer name) const;
    void setLogicalHeaderVariable(const SFF::SAC::Logical name, bool value);
    bool getLogicalHeaderVariable(const SFF::SAC::Logical name) const;
    void setCharacterHeaderVariable(const SFF::SAC::Character name,
                                    const std::string &value);
    std::string getCharacterHeaderVariable(const SFF::SAC::Character name) const;

    /// Destrutcor
    ~SAC();
private:
    std::unique_ptr<SFF::SAC::Waveform> mWaveform;
};
void initializeSAC(pybind11::module &m);
}
#endif
