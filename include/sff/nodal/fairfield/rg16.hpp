#ifndef SFF_NODAL_FAIRFIELD_RG16
#define SFF_NODAL_FAIRFIELD_RG16
#include <memory>
#include "sff/utilities/time.hpp"
namespace SFF::Nodal::Fairfield
{
/*!
 * @brief This class is used for reading the .fcnt files corresponding to the
 *        RG16 Fairfield Nodals used at University of Utah.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class RG16
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Default constructor.
     */
    RG16();
    /*!
     * @brief Copy constructor.
     * @param[in] rg16  The class from which to initialize this class.
     */
    RG16(const RG16 &rg16);
    /*!
     * @brief Move constructor.
     * @param[in,out] rg16  The class from which to initialize this class.
     *                      On exit, rg16's behavior is undefined.
     */ 
    RG16(RG16 &&rg16) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] rg16   The RG16 nodal class to copy to this.
     * @result A deep copy of the RG16 nodal class.
     */
    RG16& operator=(const RG16 &rg16);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] rg16  The RG16 nodal class whose memory will be moved
     *                      to this.  On exit, RG16's behavior is undefined.
     * @result The memory from rg16 moved to this.
     */
    RG16& operator=(RG16 &&rg16) noexcept;
    /*! @} */

    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Default destructor.
     */
    ~RG16();
    /*!
     * @brief Releases the memory and resets the class.
     */
    void clear() noexcept;
    /*! @} */

    /*!
     * @brief Reads the fcnt file.
     * @param[in] fileName   The name of the fcnt file to read.
     * @throws std::invalid_argument if the file does not exist or cannot be
     *         read.
     */
    void read(const std::string &fileName);
private:
    class RG16Impl;
    std::unique_ptr<RG16Impl> pImpl;
};
}
#endif
