#ifndef SFF_SEGY_SILIXA_HPP
#define SFF_SEGY_SILIXA_HPP
#include <memory>
#include <string>
namespace SFF::SEGY::Silixa
{

/*!
 * @brief Defines the custom Silixa binary file header.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class BinaryFileHeader
{
public:
    /*! @name Constructors
     * @{
     */
    BinaryFileHeader();
    BinaryFileHeader(const BinaryFileHeader &header);
    BinaryFileHeader(BinaryFileHeader &&header) noexcept;
    /*! @} */
    /*! @name Operators
     * @{
     */
    BinaryFileHeader& operator=(const BinaryFileHeader &header);
    BinaryFileHeader& operator=(BinaryFileHeader &&header) noexcept;
    /*! @} */
 
    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Destructor.
     */
    ~BinaryFileHeader();
    /*!
     * @brief Resets all variables and releases memory.
     */
    void clear() noexcept;
    /*! @} */

    /*!
     * @brief Sets the binary file header.
     * @param[in] header   The binary header.  This is assumed to be in 
     *                     big-endian byte order.
     */
    void set(const char header[400]);
    /*!
     * @brief Gets the binary file header in string format.
     * @result The binary file header.  This will be in big-endian order.
     */
    std::string get() const;
    /*!
     * @brief Packs a binary header for writing to disk.
     * @param[out] header  The binary header.  This will be in big-endian order.
     */
    void get(char *header[]) const;

    /*!
     * @brief Sets the number of traces in the file.
     * @param[in] nTraces  The number of traces in the file.  
     * @throws std::invalid_argument if this is negative.
     */
    void setNumberOfTraces(int16_t nTraces);
    /*!
     * @brief Gets the number of traces in the file.
     * @result The number of traces in the file.
     */
    int getNumberOfTraces() const;

    /*!
     * @brief Sets the temporal sample interval.
     * @param[in] sampleInterval  The temporal sampling interval in
     *                            microseconds.
     * @throws std::invalid_argument if this is negative.
     */
    void setSampleInterval(int16_t sampleInterval);
    /*!
     * @brief Gets the temporal sample interval.
     * @result The temporal sampling interval in microseconds.
     */
    int getSampleInterval() const;

    /*!
     * @brief Sets the number of samples in each trace.
     * @param[in] nSamples  The number of samples per trace.
     * @throws std::invalid_argument if this is not positive.
     */
    void setNumberOfSamplesPerTrace(int16_t nSamples);
    /*!
     * @brief Gets the number of samples in each trace.
     * @result The number of samples per trace.
     */
    int getNumberOfSamplesPerTrace() const;
    /*!
     * @brief Determines whether or not a valid binary file header.
     */
    bool isValid() const noexcept;
private:
    class BinaryFileHeaderImpl;
    std::unique_ptr<BinaryFileHeaderImpl> pImpl;
};

/*
class SilixaTraceHeader
{

};
*/

/*!
 * @class Silixa silixa.hpp "sff/segy/silixa.hpp"
 * @brief Defines the Silixa's custom SEGY file format.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class Silixa
{
public:
    /*!
     * @brief Defines the Silixa binary header values.
     */
    //enum BinaryHeaderValue
    //{
    //    NUMBER_OF_TRACES_IN_FILE,  /*! The number of traces in the file. */
    //    SAMPLE_INTERVAL,           /*! The sample interval in micro-seconds. */
    //    SAMPLES_PER_TRACE          /*! The number of samples per trace. */
    //};
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
    /*! @} */

    /*!
     * @brief Reads the Silixa SEGY file into memory.
     * @param[in] fileName  The name of the Silixa SEGY file to read.
     * @throws std::invalid_argument if the 
     */
    void read(const std::string &fileName);

    /*! @name Text Header
     * @{
     */
    /*!
     * @brief Sets the 3200 character text header.
     * @param[in] text   The text header to set.  If this length is shorter
     *                   than 3200 then it will be padded with NULL terminators.
     *                   If the length exceeds 3200 then it will be truncated.
     */
    void setTextHeader(const std::string &text);
    /*!
     * @brief Gets the text header.
     * @throws std::runtime_error if the file is not loaded.
     */
    std::string getTextHeader() const;
    /*! @} */

    int getBinaryFileHeaderValue( ) const;
    void setBinaryFileHeaderValue(int value);
    
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
