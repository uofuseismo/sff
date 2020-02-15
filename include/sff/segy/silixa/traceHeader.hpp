#ifndef SFF_SEGY_SILIXA_TRACEHEADER_HPP
#define SFF_SEGY_SILIXA_TRACEHEADER_HPP
#include <memory>
#include <string>
#include "sff/utilities/time.hpp"
namespace SFF::SEGY::Silixa
{
/*!
 * @class TraceHeader "traceHeader.hpp" "sff/segy/silixa/traceHeader.hpp"
 * @brief Defines Silixa's custom 240 byte SEGY trace header format.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class TraceHeader
{
public:
    /*! @name Constructors
     * @{
     */
    /*! 
     * @brief Default constructor.
     */
    TraceHeader();
    /*! 
     * @brief Copy constructor.
     * @param[in] header  The trace header from which to initialize this class.
     */
    TraceHeader(const TraceHeader &header);
    /*! 
     * @brief Move constructor.
     * @param[in,out] header  The trace header from which to initialize this
     *                        class.  On exit, header's behavior is undefined.
     */
    TraceHeader(TraceHeader &&header) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    /*! 
     * @brief Copy assignment operator.
     * @param[in] header   The header class to copy to this.
     * @result A deep copy of header.
     */
    TraceHeader& operator=(const TraceHeader &header);
    /*! 
     * @brief Move assignment operator.
     * @param[in,out] header  The header class to move to this.  On exit,
     *                        header's behavior is undefined.
     * @result The memory from header moved to this.
     */
    TraceHeader& operator=(TraceHeader &&header) noexcept;
    /*! @} */

    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Destructor.
     */
    ~TraceHeader();
    /*!
     * @brief Clears the class.
     */
    void clear() noexcept;
    /*! @} */

    /*!
     * @brief Sets the 240 byte trace header.
     * @param[in] header   The trace header.  This is assumed to be in big
     *                     endian format.
     * @throws std::invalid_argument if header is NULL.
     */
    void set(const char header[240]);
    /*!
     * @brief Gets the 240 byte trace header.
     * @param[out] header   The trace header.  This will be in big
     *                      endian format.
     * @throws std::invalid_argument if header is NULL.
     */
    void get(char *header[]) const;
    /*! 
     * @brief Gets the 240 byte trace header.
     * @result The trace header.  This will be in big endian format.
     */
    std::string get() const noexcept;

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
     * @brief Sets the number of samples in the trace.
     * @param[in] nSamples  The number of samples in the trace.
     * @throws std::invalid_argument if this is not positive.
     */
    void setNumberOfSamples(int nSamples);
    /*! 
     * @brief Gets the number of samples in the trace.
     * @result The number of samples in the trace.
     */
    int getNumberOfSamples() const;

    /*!
     * @brief Sets the trace's temporal sample interval.
     * @param[in] sampleInterval  The temporal sampling interval in
     *                            microseconds.
     * @throws std::invalid_argument if this is not positive.
     */
    void setSampleInterval(int16_t sampleInterval);
    /*! 
     * @brief Gets the trace's temporal sample interval.
     * @result The temporal sampling interval in microseconds.
     */
    int getSampleInterval() const;

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
     * @brief Sets the start time of the first sample.
     * @param[in] time   The UTC start time of the trace.
     */
    void setStartTime(const SFF::Utilities::Time &time);
    /*!
     * @brief Gets the trace start time.
     * @result The UTC time corresponding to the first sample in the trace.
     */
    SFF::Utilities::Time getStartTime() const;
private:
    class TraceHeaderImpl;
    std::unique_ptr<TraceHeaderImpl> pImpl;
};

}
#endif
