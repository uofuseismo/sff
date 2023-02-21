#ifndef PYSFF_MINISEED_HPP
#define PYSFF_MINISEED_HPP
#ifdef USE_MSEED
#include <memory>
#include <string>
#include <pybind11/numpy.h>
#include "time.hpp"
#include "sff/sac/enums.hpp"
namespace SFF::MiniSEED
{
class SNCL;
class Trace;
}

namespace PBSFF::MiniSEED
{
class SNCL
{
public:
    /// @brief Constructor.
    SNCL();
    SNCL(const SNCL &sncl);
    explicit SNCL(const SFF::MiniSEED::SNCL &sncl);
    SNCL(SNCL &&sncl) noexcept;

    /// @brief Operators
    SNCL& operator=(const SNCL &sncl);
    SNCL& operator=(SNCL &&sncl) noexcept;
    SNCL& operator=(const SFF::MiniSEED::SNCL &sncl);
 
    /// @brief Native class.
    const SFF::MiniSEED::SNCL& getNativeClassReference() const noexcept;
    SFF::MiniSEED::SNCL getNativeClass() const noexcept;

    /// @brief Network code
    void setNetwork(const std::string &network);
    [[nodiscard]] std::string getNetwork() const;

    /// @brief Station code
    void setStation(const std::string &station);
    [[nodiscard]] std::string getStation() const;

    /// @brief Channel code
    void setChannel(const std::string &channel);
    [[nodiscard]] std::string getChannel() const;

    /// @brief Location code
    void setLocationCode(const std::string &locationCode);
    [[nodiscard]] std::string getLocationCode() const;

    /// @brief A string representation of the SNCL.
    [[nodiscard]] std::string toString() const noexcept;

    /// @brief Resets class and releases memory.
    void clear() noexcept;
    /// @brief Destructor.
    ~SNCL();
private:
    std::unique_ptr<SFF::MiniSEED::SNCL> mSNCL;
};

class Trace
{
public:
    /// @brief Constructor.
    Trace();
    Trace(const Trace &trace);
    explicit Trace(const SFF::MiniSEED::Trace &trace);
    Trace(Trace &&trace) noexcept;

    /// @brief Operators
    Trace& operator=(const Trace &trace);
    Trace& operator=(Trace &&trace) noexcept;
    Trace& operator=(const SFF::MiniSEED::Trace &trace);

    /// Reads a miniseed waveform from file
    void read(const std::string &fileName, const SNCL &sncl);
    /// Writes a miniseed waveform to file
    void write(const std::string &fileName);
    /// Sets the data
    void setWaveform(const pybind11::array_t<double, pybind11::array::c_style | pybind11::array::forcecast> &x);
    pybind11::array_t<double> getWaveform() const;

    /// Sets/gets the start time
    void setStartTime(const PBSFF::Time &time);
    PBSFF::Time getStartTime() const;

    /// @brief SNCL
    void setSNCL(const SNCL &sncl);
    SNCL getSNCL() const; 

    /// @brief Sampling rate
    void setSamplingRate(const double samplingRate);
    [[nodiscard]] double getSamplingRate() const;
    [[nodiscard]] double getSamplingPeriod() const;

    /// @brief Number of samples.
    [[nodiscard]] int getNumberOfSamples() const noexcept;
 
    /// @brief Native class.
    const SFF::MiniSEED::Trace& getNativeClassReference() const noexcept;
    SFF::MiniSEED::Trace getNativeClass() const noexcept;

    /// @brief Reset class.
    void clear() noexcept;
    /// @brief Destructor.
    ~Trace();
private:
    std::unique_ptr<SFF::MiniSEED::Trace> mTrace;
};
void initialize(pybind11::module &m);
}
#endif
#endif
