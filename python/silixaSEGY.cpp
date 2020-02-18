#include <cstdio>
#include <cstdlib>
#include <string>
#include "sff/segy/silixa/trace.hpp"
#include "sff/utilities/time.hpp"
#include "time.hpp"
#include "silixaSEGY.hpp"

using namespace PBSFF::SEGY::Silixa;

/// Constructor
Trace::Trace() :
    mWaveform(std::make_unique<SFF::SEGY::Silixa::Trace> ())
{
}

/// Copy c'tor
Trace::Trace(const Trace &trace)
{
    *this = trace;
}

/// Copy c'tor
Trace::Trace(const SFF::SEGY::Silixa::Trace &trace)
{
    *this = trace;
}


/// Copy assignment operator
Trace& Trace::operator=(const Trace &trace)
{
    if (&trace == this){return *this;}
    mWaveform = std::make_unique<SFF::SEGY::Silixa::Trace> (*trace.mWaveform); 
    return *this;
}


/// Copy assignment operator
Trace& Trace::operator=(const SFF::SEGY::Silixa::Trace &trace)
{
    mWaveform = std::make_unique<SFF::SEGY::Silixa::Trace> (trace); 
    return *this;
}

/// Destructor
Trace::~Trace() = default;

/// Sets the waveform
void Trace::setWaveform(
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
pybind11::array_t<double> Trace::getWaveform() const
{
    auto npts = mWaveform->getNumberOfSamples();
    auto y = pybind11::array_t<double, pybind11::array::c_style> (npts);
    pybind11::buffer_info ybuf = y.request();
    auto yptr = static_cast<double *> (ybuf.ptr);
    mWaveform->getData(npts, &yptr);
    return y;
}

/// Gets the sampling period 
double Trace::getSamplingPeriod() const
{
    return mWaveform->getSamplingPeriod();
}

/// Gets the sampling rate
double Trace::getSamplingRate() const
{
    return mWaveform->getSamplingRate();
}

/// Get start time 
PBSFF::Time Trace::getStartTime() const
{
    PBSFF::Time result(mWaveform->getStartTime());
    return result;
}

/// Initialize the class
void PBSFF::SEGY::Silixa::initializeTrace(pybind11::module &m)
{
    pybind11::class_<PBSFF::SEGY::Silixa::Trace> trace(m, "Trace");
    trace.def(pybind11::init<> ());
    trace.doc() = "This is used for manipulating traces contained in Silixa SEGY files.";

    trace.def("get_sampling_period",
              &PBSFF::SEGY::Silixa::Trace::getSamplingPeriod,
              "Returns the trace's sampling period in seconds.");
    trace.def("get_sampling_rate",
              &PBSFF::SEGY::Silixa::Trace::getSamplingRate,
              "Returns the trace's sampling rate in Hz.");

    trace.def("get_data",
              &PBSFF::SEGY::Silixa::Trace::getWaveform,
              "Gets the waveform data as a NumPy array.");
    trace.def("set_data",
              &PBSFF::SEGY::Silixa::Trace::setWaveform,
              "Sets the waveform data from a NumPy array.");

}

