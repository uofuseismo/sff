#include <cstdio>
#include <cstdlib>
#include <string>
#include "sff/sac/waveform.hpp"
#include "sff/sac/header.hpp"
#include "sff/utilities/time.hpp"
#include "time.hpp"
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

/// Start time
void SAC::setStartTime(const PBSFF::Time &time)
{
    auto t = time.getNativeClass();
    mWaveform->setStartTime(t);
}

PBSFF::Time SAC::getStartTime() const
{
    auto t = mWaveform->getStartTime();
    PBSFF::Time tout(t);
    return tout;
}

/// Double header 
void SAC::setDoubleHeaderVariable(const SFF::SAC::Double name,
                                  const double value)
{
    mWaveform->setHeader(name, value);
}

double SAC::getDoubleHeaderVariable(
    const SFF::SAC::Double name) const
{
    return mWaveform->getHeader(name);
}

/// Integer header
void SAC::setIntegerHeaderVariable(const SFF::SAC::Integer name,
                                   const int value)
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
void SAC::setLogicalHeaderVariable(const SFF::SAC::Logical name, 
                                   const bool value)
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
    const SFF::SAC::Character name,
    const std::string &value)
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

/// Initialize the class
void PBSFF::initializeSAC(pybind11::module &m)
{
    pybind11::class_<PBSFF::SAC> sac(m, "SAC");
    sac.def(pybind11::init<> ());
    sac.doc() = "This is used for reading and writing SAC files.";
    sac.def("read",
            &PBSFF::SAC::read,
            "Loads a waveform from disk corresponding to the given file name.");
    sac.def("write",
            &PBSFF::SAC::write,
            "Writes a waveform to disk corresponding to the given file name.");
    sac.def_property("data",
                     &PBSFF::SAC::getWaveform,
                     &PBSFF::SAC::setWaveform,
                     "Accesses the waveform data");
    sac.def_property("sampling_rate",
                     &PBSFF::SAC::getSamplingRate,
                     &PBSFF::SAC::setSamplingRate,
                     "The sampling rate which is specified in Hz.  This must be positive.");
    sac.def_property("sampling_period",
                     &PBSFF::SAC::getSamplingPeriod,
                     &PBSFF::SAC::setSamplingPeriod,
                     "The sampling period which is specified in seconds.  This must be positive.");
    sac.def_property("start_time",
                     &PBSFF::SAC::getStartTime,
                     &PBSFF::SAC::setStartTime, 
                     "The time of the first sample in the trace.");
    sac.def_property_readonly("number_of_samples",
                              &PBSFF::SAC::getNumberOfSamples,
                              "Gets the number of samples in the signal.");
    sac.def("set_float_header",
            &PBSFF::SAC::setDoubleHeaderVariable,
            "Sets a floating precision header variable.");
    sac.def("get_float_header",
            &PBSFF::SAC::getDoubleHeaderVariable,
            "Gets a floating precision header variable.");

    sac.def("set_integer_header",
            &PBSFF::SAC::setIntegerHeaderVariable,
            "Sets an integer precision header variable.");
    sac.def("get_integer_header",
            &PBSFF::SAC::getIntegerHeaderVariable,
            "Gets an integer precision header variable.");

    sac.def("set_logical_header",
            &PBSFF::SAC::setLogicalHeaderVariable,
            "Sets a logical precision header variable.");
    sac.def("set_logical_header",
            &PBSFF::SAC::getLogicalHeaderVariable,
            "Gets a logical precision header variable.");

    sac.def("set_character_header",
            &PBSFF::SAC::setCharacterHeaderVariable,
            "Sets a character-string header variable.  Nominally, the length of the string should not exceed 8.  However, if setting event name then this can be length 16.  Variables exceeding length 8 or 16 will be truncated.");
    sac.def("get_character_header",
            &PBSFF::SAC::getCharacterHeaderVariable,
            "Gets a character-string header variable.");



    // Map the SAC enums to a variable name 
    pybind11::enum_<SFF::SAC::Double> (sac, "Float")
        .value("delta",    SFF::SAC::Double::DELTA, "The sampling period in seconds.")
        .value("depmin",   SFF::SAC::Double::DEPMIN)
        .value("depmax",   SFF::SAC::Double::DEPMAX)
        .value("scale",    SFF::SAC::Double::SCALE)
        .value("odelta",   SFF::SAC::Double::ODELTA)
        .value("b",        SFF::SAC::Double::B)
        .value("e",        SFF::SAC::Double::E)
        .value("o",        SFF::SAC::Double::O)
        .value("a",        SFF::SAC::Double::A)
        //.value("internal1", SFF::SAC::Double::INTERNAL1)
        .value("t0",       SFF::SAC::Double::T0)
        .value("t1",       SFF::SAC::Double::T1)
        .value("t2",       SFF::SAC::Double::T2)
        .value("t3",       SFF::SAC::Double::T3)
        .value("t4",       SFF::SAC::Double::T4)
        .value("t5",       SFF::SAC::Double::T5)
        .value("t6",       SFF::SAC::Double::T6)
        .value("t7",       SFF::SAC::Double::T7)
        .value("t8",       SFF::SAC::Double::T8)
        .value("t9",       SFF::SAC::Double::T9)
        .value("f",        SFF::SAC::Double::F)
        .value("resp0",    SFF::SAC::Double::RESP0)
        .value("resp1",    SFF::SAC::Double::RESP1)
        .value("resp2",    SFF::SAC::Double::RESP2)
        .value("resp3",    SFF::SAC::Double::RESP3)
        .value("resp4",    SFF::SAC::Double::RESP4)
        .value("resp5",    SFF::SAC::Double::RESP5)
        .value("resp6",    SFF::SAC::Double::RESP6)
        .value("resp7",    SFF::SAC::Double::RESP7)
        .value("resp8",    SFF::SAC::Double::RESP8)
        .value("resp9",    SFF::SAC::Double::RESP9)
        .value("stla",     SFF::SAC::Double::STLA, "The station latitude in degrees.")
        .value("stlo",     SFF::SAC::Double::STLO,
                "The station longitude in degrees.")
        .value("stel",     SFF::SAC::Double::STEL)
        .value("stdp",     SFF::SAC::Double::STDP)
        .value("evla",     SFF::SAC::Double::EVLA,
               "The event latitude in degrees.")
        .value("evlo",     SFF::SAC::Double::EVLO,
               "The event longitude in degrees.")
        .value("evel",     SFF::SAC::Double::EVEL)
        .value("evdp",     SFF::SAC::Double::EVDP)
        .value("mag",      SFF::SAC::Double::MAG)
        .value("user0",    SFF::SAC::Double::USER0)
        .value("user1",    SFF::SAC::Double::USER1)
        .value("user2",    SFF::SAC::Double::USER2)
        .value("user3",    SFF::SAC::Double::USER3)
        .value("user4",    SFF::SAC::Double::USER4)
        .value("user5",    SFF::SAC::Double::USER5)
        .value("user6",    SFF::SAC::Double::USER6)
        .value("user7",    SFF::SAC::Double::USER7)
        .value("user8",    SFF::SAC::Double::USER8)
        .value("user9",    SFF::SAC::Double::USER9)
        .value("dist",     SFF::SAC::Double::DIST)
        .value("az",       SFF::SAC::Double::AZ,
               "The source-to-receiver azimuth in degrees.  This is measured positive clockwise from north.")
        .value("baz",      SFF::SAC::Double::BAZ,
               "The receiver-to-source azimuth in degrees.  This is measured positive clockwise from north.")
        .value("gcarc",    SFF::SAC::Double::GCARC,
               "The source-receiver great circle distance in degrees.")
        //.value("internal2", SFF::SAC::Double::INTERNAL2)
        //.value("internal3", SFF::SAC::Double::INTERNAL3)
        .value("depmen",   SFF::SAC::Double::DEPMEN)
        .value("cmpaz",    SFF::SAC::Double::CMPAZ)
        .value("cmpinc",   SFF::SAC::Double::CMPINC)
        .value("xminimum", SFF::SAC::Double::XMINIMUM)
        .value("xmaximum", SFF::SAC::Double::XMAXIMUM)
        .value("yminimum", SFF::SAC::Double::YMINIMUM)
        .value("ymaximum", SFF::SAC::Double::YMAXIMUM)
        .value("unused0",  SFF::SAC::Double::UNUSED0)
        .value("unused1",  SFF::SAC::Double::UNUSED1)
        .value("unused2",  SFF::SAC::Double::UNUSED2)
        .value("unused3",  SFF::SAC::Double::UNUSED3)
        .value("unused4",  SFF::SAC::Double::UNUSED4)
        .value("unused5",  SFF::SAC::Double::UNUSED5)
        .value("unused6",  SFF::SAC::Double::UNUSED6);
    //    .export_values();
    pybind11::enum_<SFF::SAC::Integer> (sac, "Integer")
        .value("nzyear",   SFF::SAC::Integer::NZYEAR)
        .value("nzjday",   SFF::SAC::Integer::NZJDAY)
        .value("nzhour",   SFF::SAC::Integer::NZHOUR)
        .value("nzmin",    SFF::SAC::Integer::NZMIN)
        .value("nzsec",    SFF::SAC::Integer::NZSEC)
        .value("nzmsec",   SFF::SAC::Integer::NZMSEC)
        .value("nvhdr",    SFF::SAC::Integer::NVHDR)
        .value("norid",    SFF::SAC::Integer::NORID)
        .value("nevid",    SFF::SAC::Integer::NEVID)
        .value("npts",     SFF::SAC::Integer::NPTS,
               "The number of samples in the time series.  This is readonly.")
        .value("nwfid",    SFF::SAC::Integer::NWFID)
        .value("nxsize",   SFF::SAC::Integer::NXSIZE)
        .value("nysize",   SFF::SAC::Integer::NYSIZE)
        .value("unused0",  SFF::SAC::Integer::UNUSED0)
        .value("iftype",   SFF::SAC::Integer::IFTYPE)
        .value("idep",     SFF::SAC::Integer::IDEP)
        .value("iztype",   SFF::SAC::Integer::IZTYPE)
        .value("iunused1", SFF::SAC::Integer::UNUSED1)
        .value("iinst",    SFF::SAC::Integer::IINST)
        .value("istreg",   SFF::SAC::Integer::ISTREG)
        .value("ievreg",   SFF::SAC::Integer::IEVREG)
        .value("ievtyp",   SFF::SAC::Integer::IEVTYP)
        .value("iqual",    SFF::SAC::Integer::IQUAL)
        .value("isynth",   SFF::SAC::Integer::ISYNTH)
        .value("imagtyp",  SFF::SAC::Integer::IMAGTYP)
        .value("imagsrc",  SFF::SAC::Integer::IMAGSRC)
        .value("iunused2", SFF::SAC::Integer::UNUSED2)
        .value("iunused3", SFF::SAC::Integer::UNUSED3)
        .value("iunused4", SFF::SAC::Integer::UNUSED4)
        .value("iunused5", SFF::SAC::Integer::UNUSED5)
        .value("iunused6", SFF::SAC::Integer::UNUSED6)
        .value("iunused7", SFF::SAC::Integer::UNUSED7)
        .value("iunused8", SFF::SAC::Integer::UNUSED8)
        .value("iunused9", SFF::SAC::Integer::UNUSED9);
    //    .export_values();
    pybind11::enum_<SFF::SAC::Logical> (sac, "Logical")
        .value("leven",   SFF::SAC::Logical::LEVEN)
        .value("lpspol",  SFF::SAC::Logical::LPSPOL)
        .value("lovrok",  SFF::SAC::Logical::LOVROK)
        .value("lcalda",  SFF::SAC::Logical::LCALDA)
        .value("lunused", SFF::SAC::Logical::UNUSED);
    //  .export_values();
    pybind11::enum_<SFF::SAC::Character> (sac, "Character")
        .value("kstnm",   SFF::SAC::Character::KSTNM)
        .value("kevnm",   SFF::SAC::Character::KEVNM)
        .value("khole",   SFF::SAC::Character::KHOLE)
        .value("ko",      SFF::SAC::Character::KO)
        .value("ka",      SFF::SAC::Character::KA)
        .value("kt0",     SFF::SAC::Character::KT0)
        .value("kt1",     SFF::SAC::Character::KT1)
        .value("kt2",     SFF::SAC::Character::KT2)
        .value("kt3",     SFF::SAC::Character::KT3)
        .value("kt4",     SFF::SAC::Character::KT4)
        .value("kt5",     SFF::SAC::Character::KT5)
        .value("kt6",     SFF::SAC::Character::KT6)
        .value("kt7",     SFF::SAC::Character::KT7)
        .value("kt8",     SFF::SAC::Character::KT8)
        .value("kt9",     SFF::SAC::Character::KT9)
        .value("kf",      SFF::SAC::Character::KF)
        .value("kuser0",  SFF::SAC::Character::KUSER0)
        .value("kuser1",  SFF::SAC::Character::KUSER1)
        .value("kuser2",  SFF::SAC::Character::KUSER2)
        .value("kcmpnm",  SFF::SAC::Character::KCMPNM)
        .value("knetwk",  SFF::SAC::Character::KNETWK)
        .value("kdatrd",  SFF::SAC::Character::KDATRD)
        .value("kinst",   SFF::SAC::Character::KINST);
}
