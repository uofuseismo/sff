#ifndef SFF_SAC_HPP
#define SFF_SAC_HPP
#include <memory>
#include <string>
#include <pybind11/numpy.h>
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
    enum DoubleHeaderType
    {
        DELTA,     /*!< The sampling period in seconds.  This is required
                        and must be positive. */
        DEPMIN,    /*!< Minimum value of the dependent variable. */
        DEPMAX,    /*!< Maximum value of the dependent variable. */
        SCALE,     /*!< Scale factor when multiplying the dependent variable. */
        ODELTA,    /*!< Observed increment if different than delta. */
        B,         /*!< Start time of trace relative to GMT time. */
        E,         /*!< End time of trace relative to GMT start time. */
        O,         /*!< Origin time in seconds relative to reference time. */
        A,         /*!< First arrival time in seconds relative to reference time. */
        //INTERNAL1, /*!< Internal variable for use by SAC.  */
        T0,        /*!< First user defined pick relative to reference time. */
        T1,        /*!< Second user defined pick relative to reference time. */
        T2,        /*!< Third user defined pick relative to reference time. */
        T3,        /*!< Fourth user defined pick relative to reference time. */
        T4,        /*!< Fifth user defined pick relative to reference time. */
        T5,        /*!< Sixth user defined pick relative to reference time. */
        T6,        /*!< Seventh user defined pick relative to reference time. */
        T7,        /*!< Eighth user defined pick relative to reference time. */
        T8,        /*!< Ninth user defined pick relative to reference time. */
        T9,        /*!< Tenth user defined pick relative to reference time. */
        F,         /*!< End time of event relative to reference time. */
        RESP0,     /*!< First instrument response parameter. */
        RESP1,     /*!< Second instrument response parameter. */
        RESP2,     /*!< Third instrument response parameter. */
        RESP3,     /*!< Fourth instrument response parameter. */
        RESP4,     /*!< Fifth instrument response parameter. */
        RESP5,     /*!< Sixth instrument response parameter. */
        RESP6,     /*!< Seventh instrument response parameter. */
        RESP7,     /*!< Eighth instrument response parameter. */
        RESP8,     /*!< Ninth instrument response parameter. */
        RESP9,     /*!< Tenth instrument response parameter. */
        STLA,      /*!< Station latitude in degrees.  North is positive. */
        STLO,      /*!< Station longitude in degrees.  East is positive. */
        STEL,      /*!< Station elevation above sea level in meters. */
        STDP,      /*!< Station depth below surface in meters. */
        EVLA,      /*!< Event latitude in degrees.  North is positive. */
        EVLO,      /*!< Event longitude in degrees.  East is is positive. */
        EVEL,      /*!< Event elevation in meters. */
        EVDP,      /*!< Event depth below surface in kilometers. */
        MAG,       /*!< The event magnitude. */
        USER0,     /*!< First user defined variable. */
        USER1,     /*!< Second user defined variable. */
        USER2,     /*!< Third user defined variable. */
        USER3,     /*!< Fourth user defined variable. */
        USER4,     /*!< Fifth user defined variable. */
        USER5,     /*!< Sixth user defined variable. */
        USER6,     /*!< Seventh user defined variable. */
        USER7,     /*!< Eighth user defined variable. */
        USER8,     /*!< Ninth user defined variable. */
        USER9,     /*!< Tenth user defined variable. */
        DIST,      /*!< Source receiver distance in kilometers. */
        AZ,        /*!< The event to station azimuth in degrees measured
                        positive clockwise from north.  This is in the range
                        [0,360). */
        BAZ,       /*!< The station to event azimuth in degrees measured
                        positive clockwise from north.   This is in the range
                        [0,360). */
        GCARC,     /*!< The station to event great circle distance
                        in degrees. */
        //INTERNAL2, /*!< Internal variable for use by SAC. */
        //INTERNAL3, /*!< Internal variable for use by SAC. */
        DEPMEN,    /*!< Mean value of dependent variable. */
        CMPAZ,     /*!< The component azimuth.  This is measured in degrees
                        positive clockwise from north. */
        CMPINC,    /*!< The component incident angle.  This is measured in
                        degrees positive from vertical.  Note, that this is
                        different than the SEED convention. */
        XMINIMUM,  /*!< The minimum value of x for a spectral file.  */
        XMAXIMUM,  /*!< The maximum value of x for a spectral file.  */
        YMINIMUM,  /*!< The minimum value of y for a spectral file.  */
        YMAXIMUM,  /*!< The maximum value of y for a spectral file.  */
        UNUSED0,   /*!< First unused header variable. */
        UNUSED1,   /*!< Second unused header variable. */
        UNUSED2,   /*!< Third unused header variable. */
        UNUSED3,   /*!< Fourth unused header variable. */
        UNUSED4,   /*!< Fifth unused header variable. */
        UNUSED5,   /*!< Sixth unused header variable. */
        UNUSED6    /*!< Seventh unused header variable. */
    };
    enum IntegerHeaderType
    {
        NZYEAR,    /*!< The four-digit GMT year. */
        NZJDAY,    /*!< The GMT Julian day.  This must be in the range [1,366]. */
        NZHOUR,    /*!< The GMT hour.  This must be in the range [0,23]. */
        NZMIN,     /*!< The GMT minute.  This must be in the range [0,59]. */
        NZSEC,     /*!< The GMT second.  This must be in the range [0,59]. */
        NZMSEC,    /*!< The GMT millisecond.  This must be in the range [0,999]. */
        NVHDR,     /*!< Header version number. */
        NORID,     /*!< The CSS 3.0 origin ID. */
        NEVID,     /*!< The CSS 3.0 event ID. */
        NPTS,      /*! The number of points.  This is required and cannot be
                       negative. */
        //INTERNAL1, /*! This is used internally by SAC. */
        NWFID,     /*! CSS 3.0 Waveform ID. */
        NXSIZE,    /*!< For spectral files this is the length. */
        NYSIZE,    /*!< For spectral files this is the width. */
        IUNUSED0,  /*!< An unused header variable. */
        IFTYPE,    /*!< Type of file:
                        ITIME is time series file.
                        IRLIM is a spectral file with real and imaginary parts.
                        IAMPH is a spectral file with amplitude and phase.
                        IXY is a general x versus y file.
                        IXYZ is a general 3D file. */
        IDEP,      /*!< The type of dependent variable:
                        IUNKN is unknown.
                        IDISP indicates nanometers.
                        IVEL indicates velocity in nanometers/second.
                        IACC indicates acceleration in nanometers/second/second.
                        IVOLTS indicates volts.  */
        IZTYPE,    /*!< The time equivalence. */
        IUNUSED1,  /*!< An unused header variable. */
        IINST,     /*!< Type of recording instrument. */
        ISTREG,    /*!< Station geographic region. */
        IEVREG,    /*!< Event geographic region. */
        IEVTYP,    /*!< The event type. */
        IQUAL,     /*!< Quality of data. */
        ISYNTH,    /*!< Synthetic data flag. */
        IMAGTYP,   /*!< Source magnitude type. */
        IMAGSRC,   /*!< Source magnitude information. */
        IUNUSED2,  /*!< The third unused header variable. */
        IUNUSED3,  /*!< The fourth unused header variable. */
        IUNUSED4,  /*!< The fifth unused header variable. */
        IUNUSED5,  /*!< The sixth unused header variable. */
        IUNUSED6,  /*!< The seventh unused header variable. */
        IUNUSED7,  /*!< The eighth unused header variable. */
        IUNUSED8,  /*!< The ninth unused header variable. */
        IUNUSED9   /*!< The tenth unused header variable. */
    };
    enum LogicalHeaderType
    {
        LEVEN,     /*!< True if the data are evenly spaced. */
        LPSPOL,    /*!< True if the station components have a positive polarity
                        under the left-hand rule. */
        LOVROK,    /*!< True if it is okay to overwite this file on disk. */
        LCALDA,    /*!< If true then the distance, azimuth, back-azimuth
                        and great-circle distance are to be calculated from
                       the station and event coordinates. */
        LUNUSED    /*!< Undefined.  The user can specify this. */
    };
    enum CharacterHeaderType
    {
        KSTNM,  /*!< The station name. */
        KEVNM,  /*!< The event name.  */
        KHOLE,  /*!< The location code. */
        KO,     /*!< The origin time label. */
        KA,     /*!< The first arrival time label. */
        KT0,    /*!< The label corresponding to the T0 arrival. */
        KT1,    /*!< The label corresponding to the T1 arrival. */
        KT2,    /*!< The label corresponding to the T2 arrival. */
        KT3,    /*!< The label corresponding to the T3 arrival. */
        KT4,    /*!< The label corresponding to the T4 arrival. */
        KT5,    /*!< The label corresponding to the T5 arrival. */
        KT6,    /*!< The label corresponding to the T6 arrival. */
        KT7,    /*!< The label corresponding to the T7 arrival. */
        KT8,    /*!< The label corresponding to the T8 arrival. */
        KT9,    /*!< The label corresponding to the T9 arrival. */
        KF,     /*!< The label corresponding to the event end time. */
        KUSER0, /*!< Undefined.  The user can specify this. */
        KUSER1, /*!< Undefined.  The user can specify this. */
        KUSER2, /*!< Undefined.  The user can specify this. */
        KCMPNM, /*!< The channel (component) name. */
        KNETWK, /*!< The network to which the station belongs. */
        KDATRD, /*!< Date data was read onto a computer.  This is deprecated. */
        KINST   /*!< Generic name of recording instrument. */
    };
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
    void setWaveform(const pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast> &x);
    pybind11::array_t<double> getWaveform() const;    
    /// Sets the sampling period
    void setSamplingPeriod(double samplingPeriod);
    double getSamplingPeriod() const;
    void setSamplingRate(double samplingRate);
    double getSamplingRate() const;
    /// Gets the number of samples
    int getNumberOfSamples() const;
    /// The header variables
    void setDoubleHeaderVariable(double value,
                                 const SFF::SAC::Double name);
    double getDoubleHeaderVariable(const SFF::SAC::Double name) const;
    void setIntegerHeaderVariable(int value,
                                  const SFF::SAC::Integer name);
    int getIntegerHeaderVariable(const SFF::SAC::Integer name) const;
    void setLogicalHeaderVariable(bool value,
                                  const SFF::SAC::Logical name);
    bool getLogicalHeaderVariable(const SFF::SAC::Logical name) const;
    void setCharacterHeaderVariable(const std::string &value,
                                    const SFF::SAC::Character name);
    std::string getCharacterHeaderVariable(const SFF::SAC::Character name) const;

    /// Destrutcor
    ~SAC();
private:
    std::unique_ptr<SFF::SAC::Waveform> mWaveform;
};
}
#endif
