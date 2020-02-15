#ifndef SFF_SEGY_SILIXA_HPP
#define SFF_SEGY_SILIXA_HPP
#include <memory>
#include <string>
#include "sff/abstractBaseClass/trace.hpp"
#include "sff/segy/textualFileHeader.hpp"
#include "sff/segy/silixa/binaryFileHeader.hpp"
#include "sff/segy/silixa/traceHeader.hpp"
#include "sff/utilities/time.hpp"

namespace SFF::SEGY::Silixa
{

/*!
 * @brief This is a container for the time series data.
 */
class Trace //: public SFF::AbstractBaseClass::ITrace
{
public:
    /*! @name Constructors
     * @{
     */
    Trace();
    Trace(const Trace &trace);
    Trace(Trace &&trace) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    Trace& operator=(const Trace &trace);
    Trace& operator=(Trace &&trace) noexcept;
    /*! @} */

    /*! @name Destructors
     * @{
     */
    ~Trace();
    void clear() noexcept;
    /*! @} */

    /*!
     * @brief Sets the trace header.
     * @note The number of samples in the trace header will be made consistent
     *       with the number of samples set in \c setData().
     */
    //void setTraceHeader( );
    /*!
     * @brief Sets the time series.
     * @param[in] nSamples   The number of samples in the time series.
     * @param[in] x          The time series to set.  This is an array whose
     *                       dimension is [nSamples].
     */
    void setData(int nSamples, const double x[]);
    /*! @copydoc setData */
    void setData(int nSamples, const float x[]);

    /*!
     * @brief Gets the time series data.
     * @param[in] nSamples  The number of samples in x.  This must match
     *                      the result of \c getNumberOfSamples().
     * @param[out] x        The time series.  This is an array whose dimension
     *                      is [nSamples]. 
     */
    void getData(int nSamples, double *x[]) const;
    /*! @copydoc getData */
    void getData(int nSamples, float *x[]) const;

    /*!
     * @brief Gets the number of samples in the trace.
     * @result The number of samples in the trace.
     */
    int getNumberOfSamples() const;
private:
    class TraceImpl; 
};

/*!
 * @class Silixa silixa.hpp "sff/segy/silixa.hpp"
 * @brief Defines Silixa's custom SEGY file format.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class Silixa
{
public:
    /*!
     * @brief Defines the Silixa trace header values.
     */
    enum TraceHeaderValue
    {
        TRACE_NUMBER,       /*!< Trace sequence number within line. */
        RECEIVER_DEPTH,     /*!< Receiver elevation below rotary kelly
                                 bushing. This is expressed as meters 
                                 times the elevation scalar. */
        SOURCE_DEPTH,       /*!< Source depth below source.  This is
                                 expressed as meters times th elevation
                                 scalar. */
        ELEVATION_SCALAR,   /*!< Scales the receiver and source depth.
                                 This can be \f$ \pm 1, \pm 100, \cdots \f$.
                                 If this is positive then it is used as a 
                                 multiplier.  If it is negative then it is
                                 used as a divisor.  A value of zero is assumed
                                 to equal 1.  */
        COORDINATE_SCALAR,  /*!< Scalar applied to all coordinates.  This can be
                                 \f$ \pm 1, \pm 100, \cdots \f$.  If this is 
                                 posiitive then it used as a multiplier.  If it
                                 is negative then it is used as a divisor.  A
                                 zero value will treated as a scalar of 1.  */ 
        SOURCE_EASTING,     /*!< The source easting.  This is expressed in 
                                 meters times the coordinate scalar.  This is in
                                 the NAD83 projection. */ 
        SOURCE_NORTHING,    /*!< The source northing.  This is expressed in
                                 meters times the coordinate scalar.  This is in
                                 the NAD83 projection. */
        RECEIVER_EASTING,   /*!< The receiver easting.  This is expressed in 
                                 meters times the coordinate scalar.  This is in
                                 the NAD83 projection. */
        RECEIVER_NORTHING,  /*!< The receiver northing.  This is expressed in
                                 meters times the coordinate scalar.  This is in
                                 the NAD83 projection. */
        COORDINATE_UNITS,   /*!< The coorrdinate units.  */
        NUMBER_OF_SAMPLES_PER_TRACE,  /*!< The number of samples per trace. */
        SAMPLE_INTERVAL,    /*!< The sampling interval in micro-seconds. */
        CORRELATED,         /*!< A binary value indicating this is correlated
                                 (1) or is not (0). */
        YEAR,               /*!< The year of the trace start. */
        JULIAN_DAY,         /*!< The day of the year of the trace start. This
                                 should be in the range [1,366]. */
        HOUR,               /*!< The hour of the day of the trace start. This
                                 should be in the range [0,23]. */
        MINUTE,             /*!< The minute of the hour of the trace start. 
                                 This should be in the range [0,59]. */
        SECOND,             /*!< The second of the minute of the trace start. 
                                 This should be in the range [0,59]. */
        TIME_BASIS_CODE,    /*!< The time basis code which can be: (1) Local,
                                 (2) GMT, (3) Other, (4) UTC, (5) GPS. */
        DISTANCE_ALONG_FIBER, /*!< The distance along the fiber of the
                                   measurement. */
    };
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Default constructor.
     */
    Silixa();
    /*! @} */

    /*! @name Destrutcors
     * @{
     */
    /*!
     * @brief Default destructor.
     */
    ~Silixa();
    /*!
     * @brief Clears the class and releases memory.
     */
    void clear() noexcept;
    /*!
     * @brief Clears the traces from memory.
     */
    void clearTraces() noexcept;
    /*! @} */

    /*!
     * @brief Reads the Silixa SEGY file into memory.
     * @param[in] fileName  The name of the Silixa SEGY file to read.
     * @throws std::invalid_argument if the 
     */
    void read(const std::string &fileName);

    /*! @name Textual Header
     * @{
     */
    /*!
     * @brief Sets the 3200 character text header.
     * @param[in] text   The text header to set.  If this length is shorter
     *                   than 3200 then it will be padded with NULL terminators.
     *                   If the length exceeds 3200 then it will be truncated.
     */
    void setTextualHeader(const SFF::SEGY::TextualFileHeader &textFileHeader);
    SFF::SEGY::TextualFileHeader getTextualFileHeader() const;
    /*!
     * @brief Gets the text header.
     * @throws std::runtime_error if the file is not loaded.
     */
    //std::string getTextHeader() const;
    /*! @} */

    BinaryFileHeader getBinaryFileHeader() const;
    
    /*!
     * @brief Determines the number of traces.
     * @result the number of traces.
     */
    int getNumberOfTraces() const;

    //void addTrace(const std::pair<TraceHeader, Trace> &trace);
    //std::pair<TraceHeader, Trace> getTrace(int traceNumber) const;
    //Trace getTrace(int traceNumber) const;
    /*! 
     * @brief Checks if this class is a valid representation of a Silixa SEGY
     *        file.  This means that the text header and  binary file header are
     *        set and the traces are valid.
     * @result True indicates that this class represents a valid Silixa SEGY.
     */
    bool isValid() const noexcept;

private:
    class SilixaImpl; 
    std::unique_ptr<SilixaImpl> pImpl;
};
}
#endif
