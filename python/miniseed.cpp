#include <iostream>
#include <string>
#include "sff/miniseed/trace.hpp"
#include "sff/miniseed/sncl.hpp"
#include "miniseed.hpp"
#include "time.hpp"

using namespace PBSFF::MiniSEED;

///--------------------------------------------------------------------------///
///                                    SNCL                                  ///
///--------------------------------------------------------------------------///
/// Constructors
SNCL::SNCL() :
    mSNCL(std::make_unique<SFF::MiniSEED::SNCL> ())
{
}

SNCL::SNCL(const SNCL &sncl)
{
    *this = sncl;
}

SNCL::SNCL(const SFF::MiniSEED::SNCL &sncl)
{
    *this = sncl;
}

SNCL::SNCL(SNCL &&sncl) noexcept
{
    *this = std::move(sncl);
}

/// Operators
SNCL& SNCL::operator=(const SNCL &sncl)
{
    if (&sncl == this){return *this;}
    mSNCL = std::make_unique<SFF::MiniSEED::SNCL> (*sncl.mSNCL);
    return *this;
}

SNCL& SNCL::operator=(SNCL &&sncl) noexcept
{
    if (&sncl == this){return *this;}
    mSNCL = std::move(sncl.mSNCL);
    return *this;
}

SNCL& SNCL::operator=(const SFF::MiniSEED::SNCL &sncl)
{
    mSNCL = std::make_unique<SFF::MiniSEED::SNCL> (sncl);
    return *this;
}

/// Native class
const SFF::MiniSEED::SNCL& SNCL::getNativeClassReference() const noexcept
{
    return *mSNCL;
}

SFF::MiniSEED::SNCL SNCL::getNativeClass() const noexcept
{
    return *mSNCL;
}

/// Network
void SNCL::setNetwork(const std::string &s) 
{
    mSNCL->setNetwork(s);
}

std::string SNCL::getNetwork() const
{
    return mSNCL->getNetwork();
}

/// Station
void SNCL::setStation(const std::string &s)
{
    mSNCL->setStation(s);
}

std::string SNCL::getStation() const
{
    return mSNCL->getStation();
}

/// Channel
void SNCL::setChannel(const std::string &s) 
{
    mSNCL->setChannel(s);
}

std::string SNCL::getChannel() const
{
    return mSNCL->getChannel();
}

/// Location code
void SNCL::setLocationCode(const std::string &s) 
{
    mSNCL->setLocationCode(s);
}

std::string SNCL::getLocationCode() const
{
    return mSNCL->getLocationCode();
}

/// Resets class
void SNCL::clear() noexcept
{
    mSNCL->clear();
}

/// Converts a time to string
std::string SNCL::toString() const noexcept
{
    std::stringstream ss; 
    ss << *mSNCL;
    return ss.str();
}

/// Destructor
SNCL::~SNCL() = default;

///--------------------------------------------------------------------------///
///                                   Trace                                  ///
///--------------------------------------------------------------------------///
/// Constructors
Trace::Trace() :
    mTrace(std::make_unique<SFF::MiniSEED::Trace> ())
{
}

Trace::Trace(const Trace &trace)
{
    *this = trace;
}

Trace::Trace(const SFF::MiniSEED::Trace &trace)
{
    *this = trace;
}

Trace::Trace(Trace &&trace) noexcept
{
    *this = std::move(trace);
}

/// Operators
Trace& Trace::operator=(const Trace &trace)
{
    if (&trace == this){return *this;}
    mTrace = std::make_unique<SFF::MiniSEED::Trace> (*trace.mTrace);
    return *this;
}

Trace& Trace::operator=(Trace &&trace) noexcept
{
    if (&trace == this){return *this;}
    mTrace = std::move(trace.mTrace);
    return *this;
}

Trace& Trace::operator=(const SFF::MiniSEED::Trace &trace)
{
    mTrace = std::make_unique<SFF::MiniSEED::Trace> (trace);
    return *this;
}

void Trace::read(const std::string &fileName, const SNCL &sncl)
{
    auto snclNative = sncl.getNativeClassReference();
    mTrace->read(fileName, snclNative);
}

void Trace::setWaveform(
    const pybind11::array_t<double, pybind11::array::c_style |
                                    pybind11::array::forcecast> &x)
{
    pybind11::buffer_info xBuffer = x.request();
    auto length = static_cast<int> (xBuffer.size);
    const double *xPtr = (double *) (xBuffer.ptr);
    if (xPtr == nullptr)
    {
        throw std::runtime_error("x is null");
    }
    mTrace->setData(length, xPtr);
}

pybind11::array_t<double> Trace::getWaveform() const
{
    auto nSamples = getNumberOfSamples();
    auto y = pybind11::array_t<double, pybind11::array::c_style> (nSamples);
    pybind11::buffer_info yBuffer = y.request();
    auto yPtr = static_cast<double *> (yBuffer.ptr);
    mTrace->getData(nSamples, &yPtr);
    return y;

}

/// Start time
void Trace::setStartTime(const PBSFF::Time &time)
{
    auto t = time.getNativeClass();
    mTrace->setStartTime(t);
}

PBSFF::Time Trace::getStartTime() const
{
    PBSFF::Time tOut{mTrace->getStartTime()};
    return tOut;
}

/// Sampling rate
void Trace::setSamplingRate(const double samplingRate)
{
    mTrace->setSamplingRate(samplingRate);
}

double Trace::getSamplingRate() const
{
    return mTrace->getSamplingRate();
}

double Trace::getSamplingPeriod() const
{
    return mTrace->getSamplingPeriod();
}

/// SNCL
void Trace::setSNCL(const SNCL &sncl)
{
    auto snclNative = sncl.getNativeClassReference();
    mTrace->setSNCL(snclNative);
}

SNCL Trace::getSNCL() const
{
    return SNCL(mTrace->getSNCL());
}

/// Number of samples
int Trace::getNumberOfSamples() const noexcept
{
    return mTrace->getNumberOfSamples();
}

/// Destructor
void Trace::clear() noexcept
{
    mTrace->clear();
}

Trace::~Trace() = default;

///--------------------------------------------------------------------------///
///                             Initialize Modules                           ///
///--------------------------------------------------------------------------///
/// Initialize
void PBSFF::MiniSEED::initialize(pybind11::module &m)
{
    pybind11::module mseed = m.def_submodule("MiniSEED");
    mseed.attr("__doc__") = "Utilities for interacting with MiniSEED files.";
    //-----------------------------------SNCL---------------------------------//
    pybind11::class_<SNCL> sncl(mseed, "SNCL");
    sncl.def(pybind11::init<> ());
    sncl.doc() = R""""(
This defines the station/network/channel/location code.

Properties :
    network : str
        The network name - e.g., UU.
    station : str
        The station name - e.g., FORK.
    channel : str
        The channel code - e.g., EHZ.
    location_code : str
        The location code - e.g., 01.
)"""";
    sncl.def("__copy__", [](const SNCL &self)
    {
        return SNCL(self);
    });
    sncl.def("__repr__", [](const SNCL &self)
    {
        return self.toString();
    });
    sncl.def_property("network",
                      &SNCL::getNetwork,
                      &SNCL::setNetwork);
    sncl.def_property("station",
                      &SNCL::getStation,
                      &SNCL::setStation);
    sncl.def_property("channel",
                      &SNCL::getChannel,
                      &SNCL::setChannel);
    sncl.def_property("location_code",
                      &SNCL::getLocationCode,
                      &SNCL::setLocationCode);
    sncl.def("clear", 
             &SNCL::clear,
             "Resets the class and releases memory.");

    //----------------------------------Trace---------------------------------//
    pybind11::class_<Trace> trace(mseed, "Trace");
    trace.def(pybind11::init<> ());
    trace.doc() = R""""(
This defines a MiniSEED trace.

Properties :
    sampling_rate : double
        The sampling rate of the signal in Hz.
    sncl : SNCL
       The station/network/channel/location code of the trace.
    start_time : Time
        The start time of the trace.
    waveform : np.array
        The waveform data for this SNCL.

Read-only Properties
    number_of_samples : int
       The number of samples in the trace.
    sampling_period : double
       The sampling period of the signal.
)"""";
    trace.def("__copy__", [](const Trace &self)
    {
        return Trace(self);
    });
    trace.def_property("sampling_rate",
                       &Trace::getSamplingRate,
                       &Trace::setSamplingRate);
    trace.def_property("start_time",
                       &Trace::getStartTime,
                       &Trace::setStartTime);
    trace.def_property("waveform",
                       &Trace::getWaveform,
                       &Trace::setWaveform);
    trace.def_property("sncl",
                       &Trace::getSNCL,
                       &Trace::setSNCL);
    trace.def_property_readonly("number_of_samples",
                                &Trace::getNumberOfSamples);
    trace.def_property_readonly("sampling_period",
                                &Trace::getSamplingPeriod);
    trace.def("read",
              &Trace::read,
              "Loads the waveform in the MiniSEED file corresponding to the SNCL");
    trace.def("clear",
              &Trace::clear,
              "Releases memory and resets the class.");
}
