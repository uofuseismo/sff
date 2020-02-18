#ifndef SFF_SEGY_SILIXA_TRACE_HPP
#define SFF_SEGY_SILIXA_TRACE_HPP
#include <memory>
#include <string>
#include "sff/abstractBaseClass/trace.hpp"
#include "sff/segy/silixa/traceHeader.hpp"
#include "sff/utilities/time.hpp"
namespace SFF::SEGY::Silixa
{
/*!
 * @brief This is a container for the time series data.
 */
class Trace : public SFF::AbstractBaseClass::ITrace
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Default constructor.
     */
    Trace();
    /*!
     * @brief Copy constructor.
     * @param[in] trace  The trace class from which to initialize this class.
     */
    Trace(const Trace &trace);
    /*!
     * @brief Move constructor.
     * @param[in,out] trace  The trace class from which to initialize this
     *                       class.  On exit, trace's behavior is undefined.
     */
    Trace(Trace &&trace) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] trace  The trace class to copy to this.
     * @result A deep copy of the trace class.
     */
    Trace& operator=(const Trace &trace);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] trace  The trace class whose memory will be moved to this.
     *                       On exit, trace's behavior is undefined.
     * @result The memory from trace moved to this.
     */
    Trace& operator=(Trace &&trace) noexcept;
    /*! @} */

    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Destructor.
     */
    ~Trace();
    /*!
     * @brief Releases the memory on the class and resets the variables.
     */
    void clear() noexcept;
    /*! @} */

    /*!@ name Data
     * @{
     */
    /*!
     * @brief Unpacks the header and time series data from a character array.
     * @param[in] len   The length of x.  This should be 240 + 4*nSamples.
     *                  The number of samples should be known from the binary
     *                  file header.
     * @param[in] x     The array containing the trace header and time series.
     *                  This is an array whose dimension is [len].
     * @throws std::invalid_argument if x is NULL or the header and len yield
     *         an inconsistency.
     */
    void set(int len, const char x[]);
    /*!
     * @brief Sets the time series.
     * @param[in] nSamples  The number of points in the time series.
     * @param[in] x         The time series to set.  This is an array whose
     *                      dimension is [nSamples].
     */
    void setData(int nSamples, const double x[]);
    /*! @copydoc setData */
    void setData(int nSamples, const float x[]);

    /*!
     * @brief Gets the time series data.
     * @param[in] nSamples   The number of points in x.  This must match
     *                       the result of \c getNumberOfSamples().
     * @param[out] x     The time series.  This is an array whose dimension
     *                   is [nSamples]. 
     * @throws std::invalid_argument if x is NULL and nSamples is positive.
     */
    void getData(int nSamples, double *x[]) const override;
    /*! @copydoc getData */
    void getData(int nSamples, float *x[]) const override;
    /*!
     * @brief Gets the number of samples in the trace.
     * @result The number of samples in the trace.
     */
    int getNumberOfSamples() const override;
    /*! @} */

    /*! @name Sampling Rate
     * @{
     */
    /*!
     * @brief Sets the sampling rate in Hz.
     * @param[in] df  The sampling rate in Hz.  Silixa should sample at 2000 Hz.
     * @throws std::invalid_argument if df is not positive.
     */
    void setSamplingRate(double df);
    /*!
     * @brief Sets the sampling period in seconds.
     * @param[in] dt  The sampling period in seconds.  Silixa should sample at 
     *                0.0005 seconds. 
     * @throws std::invalid_argument if dt is not positive.
     */
    void setSamplingPeriod(double dt);
    /*!
     * @brief Gets the trace sampling rate.
     * @result The sampling rate in Hz.
     * @throws std::runtime_error if this was not set.
     */
    double getSamplingRate() const override;
    /*!
     * @brief Gets the sampling period.
     * @result The sampling period in seconds.
     * @throws std::runtime_error if this was not set.
     */ 
    double getSamplingPeriod() const override;
    /*! @} */

    /*!
     * @brief Sets the trace start time.
     * @param[in] startTime  The UTC time of the trace start.
     */
    void setStartTime(const SFF::Utilities::Time &time);
    /*!
     * @brief Gets the start time of the trace.
     * @result The start time of the trace in UTC.
     */
    SFF::Utilities::Time getStartTime() const override;

    /*! 
     * @brief Sets the trace number.
     * @param[in] traceNumber  The trace number.
     */
    void setTraceNumber(int traceNumber);
    /*! 
     * @brief Gets the trace number.
     * @result The trace number.
     */
    int getTraceNumber() const;

    /*! 
     * @brief Toggles whether or not the traces are correleated.
     * @param[in] isCorrelated   If true then the traces are correlated.
     */
    void setIsCorrelated(const bool isCorrelated);
    /*! 
     * @brief Determines whether or not the traces are correlated.
     * @result True indicates that the traces are correlated.
     */
    bool getIsCorrelated() const;

    /*!
     * @brief Gets the data format e.g., SILIXA_SEGY.
     * @result The data format.
     */
    SFF::Format getFormat() const noexcept override;

private:
    class TraceImpl;
    std::unique_ptr<TraceImpl> pImpl;
};
}
#endif
