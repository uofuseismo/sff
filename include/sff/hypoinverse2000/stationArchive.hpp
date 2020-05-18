#ifndef SFF_HYPOINVERSE2000_STATIONARCHIVE_HPP
#define SFF_HYPOINVERSE2000_STATIONARCHIVE_HPP
#include <memory>
#include "sff/utilities/time.hpp"
namespace SFF::HypoInverse2000
{
/*!
 * @class StationArchive "stationArchive.hpp" "sff/hypoinverse2000/stationArchive.hpp"
 * @brief Defines a year-2000 compatibile station archive line.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class StationArchive
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Default constructor.
     */
    StationArchive();
    /*!
     * @brief Copy constructor.
     * @param[in] station  The station archive class from which to initialize
     *                     this class.
     */
    StationArchive(const StationArchive &station);
    /*!
     * @brief Move constructor.
     * @param[in,out] station  The station archive from which to initialize
     *                         this class.  On exit, station's behavior is
     *                         undefined.
     */
    StationArchive(StationArchive &&station) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] station  The station class to copy to this.
     * @return A deep copy of station.
     */
    StationArchive& operator=(const StationArchive &station);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] station  Moves the memory from station to this.
     * @return The memory from station moved to this.
     */
    StationArchive& operator=(StationArchive &&station) noexcept;
    /*! @} */

    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Default destructor.
     */
    ~StationArchive();
    /*!
     * @brief Frees memory and resets the class.
     */
    void clear() noexcept;
    /*! @} */

    /*! @name SNCL
     * @{
     */
    /*!
     * @brief Sets the network code of the station on which the pick was made.
     * @param[in] network   The network name.  This should have two letters.
     */
    void setNetworkName(const std::string &network) noexcept;
    /*!
     * @return The network to which the station belongs.
     * @throws std::runtime_error if this is not set.
     */
    std::string getNetworkName() const;
    /*!
     * @return True indicates that the network name was set.
     */
    bool haveNetworkName() const noexcept;

    /*!
     * @brief Sets the name of the station on which the pick was made.
     * @param[in] station   The station's name.  This can have up to five
     *                       letters.
     */
    void setStationName(const std::string &station) noexcept;
    /*!
     * @return The name of the station name.
     * @throws std::runtime_error if this is not set.
     */
    std::string getStationName() const;
    /*!
     * @return True indicates that the station's name was set.
     */
    bool haveStationName() const noexcept;

    /*!
     * @brief Sets the station's channel code on which the pick was made.
     * @param[in] channel   The station's channel.  This should have
     *                      three letters.
     */
    void setChannelName(const std::string &channel) noexcept;
    /*!
     * @return The station's channel name.
     * @throws std::runtime_error if this is not set.
     */
    std::string getChannelName() const;
    /*!
     * @return True indicates that the channel name was set.
     */
    bool haveChannelName() const noexcept;

    /*!
     * @brief Sets the station's location code on which the pick was made.
     * @param[in] location  The station's location code.  This should have
     *                      two letters.
     */
    void setLocationCode(const std::string &location) noexcept;
    /*!
     * @return The station's location code.
     * @throws std::runtime_error if this is not set.
     */
    std::string getLocationCode() const;
    /*!
     * @return True indicates that the location code was set.
     */
    bool haveLocationCode() const noexcept;
    /*! @} */
private:
    class StationArchiveImpl;
    std::unique_ptr<StationArchiveImpl> pImpl;
};
}
#endif
