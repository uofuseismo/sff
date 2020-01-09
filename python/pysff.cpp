#include "sff/version.hpp"
#include "time.hpp"
//#include "sac.hpp"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(pysff, m)
{
    m.attr("__version__") = SFF_VERSION;
    //------------------------------------------------------------------------//
    //                                Time                                    //
    //------------------------------------------------------------------------//
    pybind11::class_<PBSFF::Time> time(m, "Time");
    time.def(pybind11::init<> ());
    time.def("__add__", [](PBSFF::Time &a, const PBSFF::Time &b)
    {
        return a + b;
    }, pybind11::is_operator());
    time.def("__sub__", [](PBSFF::Time &a, const PBSFF::Time &b)
    {
        return a - b;
    }, pybind11::is_operator());
    time.doc() = "This is used for managing converting between epochal and date-times.";
    time.def_property("epoch",
                      &PBSFF::Time::getEpochalTime,
                      &PBSFF::Time::setEpochalTime,
                      "This defines the UTC time in seconds since epoch (Jan 1, 1970).");
    time.def_property("year",
                      &PBSFF::Time::getYear,
                      &PBSFF::Time::setYear,
                      "This defines the time's year - e.g., 2020 indicates the year 2020.  This must be greater than 1900.");
    time.def_property("julian_day",
                      &PBSFF::Time::getJulianDay,
                      &PBSFF::Time::setJulianDay,
                      "There are two ways to specify the day of the year.  The first is the Julian day.  In this case, this must be in the range [1,366] where 366 accounts for leap years.  Setting this variable will invalidate the month and day of the month.");
    time.def_property("month",
                      &PBSFF::Time::getMonth,
                      &PBSFF::Time::setMonth,
                      "The other way to specify the day of the year is by specifying the month and the day of the month with the day_of_month attribute.   This is the month and must be in the range [1,12].  Setting this variable then this will invalidate the Julian day.");
    time.def_property("day_of_month",
                      &PBSFF::Time::getDayOfMonth,
                      &PBSFF::Time::setDayOfMonth,
                      "The other way to specify the day of the year is by speciyfing the month with the month attribute and the day of the month.  This is the day of the month and must be in the range [1,31].  Setting this variable will invalidate the Julian day.");
    time.def_property("hour",
                      &PBSFF::Time::getHour,
                      &PBSFF::Time::setHour,
                      "This specifies the hour of the day and must be in the range [0,23].");
    time.def_property("minute",
                      &PBSFF::Time::getMinute,
                      &PBSFF::Time::setMinute,
                      "This specifies the minute of the hour and must be in the range [0,59].");
    time.def_property("second",
                      &PBSFF::Time::getSecond,
                      &PBSFF::Time::setSecond,
                      "This specifies the second of the minute and must be in the range [0,59].");
    time.def_property("micro_second",
                      &PBSFF::Time::getMicroSecond,
                      &PBSFF::Time::setMicroSecond,
                      "This specifies the micro-second and must be in the range [0,999999].");
/*
    //------------------------------------------------------------------------//
    //                                  SAC                                   //
    //------------------------------------------------------------------------//
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
                     "Sets the sampling rate which is specified in Hz.  This must be positive.");
    sac.def_property("sampling_period",
                     &PBSFF::SAC::getSamplingPeriod,
                     &PBSFF::SAC::setSamplingPeriod,
                     "Sets the sampling period which is specified in seconds.  This must be positive.");
    sac.def_property_readonly("number_of_samples",
                              &PBSFF::SAC::getNumberOfSamples,
                              "Gets the number of samples in the signal.");
    sac.def("set_float_header",
            &PBSFF::SAC::setDoubleHeaderVariable,
            "Sets a floating precision header variable.");
    sac.def("set_integer_header",
            &PBSFF::SAC::setIntegerHeaderVariable,
            "Sets an integer precision header variable.");
    sac.def("set_logical_header",
            &PBSFF::SAC::setLogicalHeaderVariable,
            "Sets a logical precision header variable.");
    sac.def("set_character_header",
            &PBSFF::SAC::setCharacterHeaderVariable,
            "Sets a character-string header variable.  Nominally, the length of the string should not exceed 8.  However, if setting event name then this can be length 16.  Variables exceeding length 8 or 16 will be truncated.");


    // Map the SAC enums to a variable name 
    pybind11::enum_<SFF::SAC::Double> (sac, "FloatHeaderVariable")
        .value("delta",    SFF::SAC::Double::DELTA)
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
        .value("stla",     SFF::SAC::Double::STLA)
        .value("stlo",     SFF::SAC::Double::STLO)
        .value("stel",     SFF::SAC::Double::STEL)
        .value("stdp",     SFF::SAC::Double::STDP)
        .value("evla",     SFF::SAC::Double::EVLA)
        .value("evlo",     SFF::SAC::Double::EVLO)
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
        .value("az",       SFF::SAC::Double::AZ)
        .value("baz",      SFF::SAC::Double::BAZ)
        .value("gcarc",    SFF::SAC::Double::GCARC)
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
    pybind11::enum_<SFF::SAC::Integer> (sac, "IntegerHeaderVariable")
        .value("nzyear",   SFF::SAC::Integer::NZYEAR)
        .value("nzjday",   SFF::SAC::Integer::NZJDAY)
        .value("nzhour",   SFF::SAC::Integer::NZHOUR)
        .value("nzmin",    SFF::SAC::Integer::NZMIN)
        .value("nzsec",    SFF::SAC::Integer::NZSEC)
        .value("nzmsec",   SFF::SAC::Integer::NZMSEC)
        .value("nvhdr",    SFF::SAC::Integer::NVHDR)
        .value("norid",    SFF::SAC::Integer::NORID)
        .value("nevid",    SFF::SAC::Integer::NEVID)
        //.value("npts",   SFF::SAC::Integer::NPTS)    // Don't let user mess with this
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
    pybind11::enum_<SFF::SAC::Logical> (sac, "LogicalHeaderVariable")
        .value("leven",   SFF::SAC::Logical::LEVEN)
        .value("lpspol",  SFF::SAC::Logical::LPSPOL)
        .value("lovrok",  SFF::SAC::Logical::LOVROK)
        .value("lcalda",  SFF::SAC::Logical::LCALDA)
        .value("lunused", SFF::SAC::Logical::UNUSED);
    //  .export_values();
    pybind11::enum_<SFF::SAC::Character> (sac, "CharacterHeaderVariable")
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
    //  .export_values();
*/
}
