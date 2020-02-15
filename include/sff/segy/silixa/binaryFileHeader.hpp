#ifndef SFF_SEGY_SILIXA_BINARYFILEHEADER_HPP
#define SFF_SEGY_SILIXA_BINARYFILEHEADER_HPP
#include <memory>
#include <string>
namespace SFF::SEGY::Silixa
{
/*!
 * @class BinaryFileHeader silixa.hpp "sff/segy/silixa.hpp"
 * @brief Defines the custom Silixa 400 byte binary file header.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class BinaryFileHeader
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Default constructor.
     */
    BinaryFileHeader();
    /*!
     * @brief Copy constructor.
     * @param[in] header  The header from which to initialize this class.
     */
    BinaryFileHeader(const BinaryFileHeader &header);
    /*!
     * @brief Move constructor.
     * @param[in,out] header   The header from which to initialize this class.
     *                         On exit, header's behavior is undefined.
     */
    BinaryFileHeader(BinaryFileHeader &&header) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] header   The header class to copy.
     * @result A deep copy of the header.
     */
    BinaryFileHeader& operator=(const BinaryFileHeader &header);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] header   The header class whose memory will be moved to
     *                         this.  On exit, header's behavior is undefined.
     * @result The memory from header moved to this.
     */
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
}
#endif
