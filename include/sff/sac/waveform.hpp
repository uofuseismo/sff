#ifndef SFF_SAC_WAVEFORM_HPP
#define SFF_SAC_WAVEFORM_HPP
#include <memory>
#include <string>
#include <vector>
#include "sff/abstractBaseClass/trace.hpp"
#include "sff/utilities/time.hpp"
#include "sff/formats.hpp"
#include "sff/sac/enums.hpp"

namespace SFF::SAC
{
/// @class Waveform "waveform.hpp" "sff/sac/waveform.hpp"
/// @brief The SAC waveform class.  A SAC waveform is comprised of a time series
///        and is characterized by a SAC header.
/// @copyright Ben Baker (University of Utah) distributed under the MIT license. 
class Waveform : public SFF::AbstractBaseClass::ITrace
{
public:
    /// @name Constructors
    /// @{

    /// @brief Constructor.
    Waveform();
    /// @brief Copy constructor.
    /// @param[in] waveform  The waveform class from which to
    ///                      construct this class.
    Waveform(const Waveform &waveform);
    /// @brief Move constructor.
    /// @param[in,out] waveform  The waveform class to move to this class.
    ///                          On exit, waveform's behavior will be undefined.
    Waveform(Waveform &&waveform) noexcept;
    /// @}

    /// @name Operators
    /// @{

    /// @brief Copy assignment operator.
    /// @param[in] waveform  The waveform class to copy.
    /// @result A deep copy of the input waveform.
    Waveform& operator=(const Waveform &waveform);
    /// @brief Move assignment operator.
    /// @param[in,out] waveform  The waveform to move.  On exit waveform's
    ///                          behavior will be undefined.
    Waveform& operator=(Waveform &&waveform) noexcept;
    /// @}

    /// @name double Header Variables
    /// @{

    /// @brief Gets a float header variable.
    /// @result The value of the header variable.  If the header
    ///         variable has not been set then this will be -12345.
    [[nodiscard]] double getHeader(const Double variableName) const noexcept;
    /// @brief Sets a float header variable.
    /// @param[in] variableName  The name of the header variable to set.
    /// @param[in] value         The value of the header variable.
    /// @throws std::invalid_argument if attempting to set Double::Delta
    ///         with a negative value.
    void setHeader(const Double variableName, double value);
    /// @}

    /// @name Integer Header Variables
    /// @{

    /// @brief Gets an integer header variable.
    /// @result The value of the header variable.  If the header
    ///         variable has not been set then this will be -12345.
    [[nodiscard]] int getHeader(const Integer variableName) const noexcept;
    /// @brief Sets an integer header variable.
    /// @param variableName  The name of the integer variable to set.
    ///                      Note, that you cannot set Integer::NPTS
    ///                      with this function.
    /// @param value         The value of the variable.
    /// @throws std::invalid_argument if attempting to set Integer::NPTS
    ///         to a negative number, if any of the time variables are
    ///         out of range, or if the user attemps to modify Integer::IFTYPE.
    void setHeader(const Integer variableName, int value);
    /// @}

    /// @name Logical Header Variables
    /// @{

    /// @brief Gets a logical header variable.
    /// @param variableName  The name of the logical variable to get.
    /// @result The value of the header variable.  If the header variable
    ///         has not been set then this will be -12345.  Otherwise,
    ///         0 indicates false while 1 indicates true.
    [[nodiscard]] int getHeader(const Logical variableName) const noexcept;
    /// @brief Sets a logical header variable.
    /// @param variableName  The name of the logical variable to set.
    /// @param value         The value of the variable.
    /// @note That after a variable is set it can only to toggled on or off.
    void setHeader(const Logical variableName, bool value) noexcept;
    /// @}

    /// @name Character Header Variables
    /// @{
 
    /// @brief Gets a character header variable.
    /// @result The value of the header variable.  If the header variable
    ///         has not been set then this will be "-12345".
    [[nodiscard]] std::string getHeader(const Character variableName) const noexcept;
    /// @brief Sets a character header variable.
    /// @param[in] variableName  The variable name to set.
    /// @param[in] value         The value of the character to set.  If the the
    ///                          length is too long then it will be truncated.
    void setHeader(const Character variableName,
                   const std::string &value) noexcept;
    /// @}

    /// @brief Checks if this class is a valid representation of a SAC file.
    ///        This means that the header is defined and that there is data.
    /// @result True indicates that this class represents a valid SAC waveform. 
    [[nodiscard]] bool isValid() const noexcept;
    /// @brief Sets the sampling period.
    /// @param[in] dt   The sampling period in seconds.
    /// @throws std::invalid_argument if dt is not positive.
    void setSamplingPeriod(double dt);
    /// @brief Gets the sampling period.
    /// @result The sampling period in seconds of the waveform.
    /// @throws std::runtime_error if the sampling period was never properly
    ///         set in the SAC header.
    /// @sa isValid()
    [[nodiscard]] double getSamplingPeriod() const override;
    /// @brief Sets the sampling rate.
    /// @param[in] df   The sampling period in Hz.
    /// @throws std::invalid_argument if df is not positive.
    void setSamplingRate(double df);
    /// @brief Gets the sampling rate.
    /// @result The sampling rate in Hz of the waveform.
    /// @throws std::runtime_error if the sampling period was never properly
    ///         set in the SAC header.
    /// @sa isValid()
    [[nodiscard]] double getSamplingRate() const override;
    /// @brief Gets the number of points in the waveform.
    /// @result The number of samples in the waveform.
    /// @note If the waveform is not properly initialized then this can
    ///       be negative.  In this case the value will likely be -12345.
    /// @sa isValid()
    [[nodiscard]] int getNumberOfSamples() const noexcept override;
    /// @brief Convenience function to set the start time.
    /// @param[in] startTime   The start time of the trace.
    /// @note This will set set Double::B to 0.
    void setStartTime(const Utilities::Time &startTime) noexcept;
    /// @brief Convenience function to get the start time.
    /// @result The start time.
    /// @throws std::runtime_error if the header variables compmrising the
    ///         start time (NZYEAR, NZJDAY, NZHOUR, NZMIN, NZMSEC, B) were not
    ///         set.
    [[nodiscard]] SFF::Utilities::Time getStartTime() const override;
    /// @result The end time.
    /// @throws std::runtime_error if \c getStartTime() throws,
    ///         \c getSamplingPeriod() throws, or
    ///         \c getNumberOfSamples() throws.
    [[nodiscard]] SFF::Utilities::Time getEndTime() const;
    /// @brief Gets the seismic data format.
    /// @result The seismic data format which in this instance is SAC.
    [[nodiscard]] SFF::Format getFormat() const noexcept override; 
    /// @brief Sets the data.
    /// @param[in] npts  The number of samples in the waveform.  This must be
    ///                  positive. 
    /// @param[in] data  The waveform data.  This is an array of dimension
    ///                  [npts].
    /// @throws std::invalid_argument if npts is not positive or data is NULL.
    void setData(int npts, const double data[]);
    /// @copydoc setData
    void setData(int npts, const float data[]);
    /// @brief Returns a pointer to the data.
    /// @result A pointer to the data.  This can be NULL.  The length of
    ///         the pointer is given by \c getNumberOfSamples().
    [[nodiscard]] const float *getDataPointer() const noexcept;

    void getData(int npts, double *data[]) const override;
    void getData(int npts, float *data[]) const override;
    //void getData(int npts, int *data[]) const override;
    /// @brief Returns a copy of the data.
    /// @result A copy of the waveform data.
    [[nodiscard]] std::vector<double> getData() const noexcept;

    /// @brief Loads a SAC data file.
    /// @param[in] fileName  The name of file to read.
    /// @throws std::invalid_argument if fileName does not exist
    ///         or the SAC file is unreadable.
    void read(const std::string &fileName);
    /// @brief Loads a SAC data file between the desired times t0 and t1.
    /// @param[in] fileName  The name of the file to read.
    /// @param[in] t0        The start time to read.  Upon a successful
    ///                      read all samples in the trace will be at or
    ///                      after this time.
    /// @param[in] t1        The end time to read.  Upon a successful read
    ///                      all samples in the trace will be before or
    ///                      at this time.
    /// @throws std::invalid_argument if t0 >= t1, t1 is before the start
    ///         time of the trace, or t0 is after the end time of the
    ///         trace, the fileName does not exist or the SAC files is
    ///         unreadable. 
    void read(const std::string &fileName,
              const SFF::Utilities::Time &t0,
              const SFF::Utilities::Time &t1);
    /// @brief Writes the SAC file.
    /// @param[out] fileName  The SAC file to write.
    /// @throws std::invalid_argument if the path to fileName is invalid.
    /// @throws std::runtime_error if the SAC class is not valid or.
    /// @sa \c isValid()
    void write(const std::string &fileName, const bool lswap = false) const;

    /// @name Destructors
    /// @{

    /// @brief Resets the header and clears the time series.
    void clear() noexcept;
    /// @brief Destructor.
    ~Waveform() override;
    /// @}
private:
    class WaveformImpl;
    std::unique_ptr<WaveformImpl> pImpl;
};

}
#endif
