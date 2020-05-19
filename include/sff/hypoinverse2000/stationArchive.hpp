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

    /*!
     * @brief Sets the event information from a station line read from an
     *        archive file.
     */
    void unpackString(const std::string &line);

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
    [[nodiscard]] std::string getNetworkName() const;
    /*!
     * @return True indicates that the network name was set.
     */
    [[nodiscard]] bool haveNetworkName() const noexcept;

    /*!
     * @brief Sets the name of the station on which the pick was made.
     * @param[in] station   The station's name.  This can have up to five
     *                      letters.
     */
    void setStationName(const std::string &station) noexcept;
    /*!
     * @return The name of the station name.
     * @throws std::runtime_error if this is not set.
     */
    [[nodiscard]] std::string getStationName() const;
    /*!
     * @return True indicates that the station's name was set.
     */
    [[nodiscard]] bool haveStationName() const noexcept;

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
    [[nodiscard]] std::string getChannelName() const;
    /*!
     * @return True indicates that the channel name was set.
     */
    [[nodiscard]] bool haveChannelName() const noexcept;

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
    [[nodiscard]] std::string getLocationCode() const;
    /*!
     * @return True indicates that the location code was set.
     */
    [[nodiscard]] bool haveLocationCode() const noexcept;
    /*! @} */

    /*! @name Source-Receiver Distance And Take-Off Angle
     * @{
     */
    /*!
     * @brief Sets the source-receiver epicentral distance.
     * @param[in] distance  The distance in kilometers.
     * @throws std::invalid_argument if this is not positive.
     */
    void setEpicentralDistance(double distance);
    /*!
     * @return The source-receiver epicentral distance in kilometers.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] double getEpicentralDistance() const;
    /*!
     * @return True indicates that the epicentral distance was set.
     */
    [[nodiscard]] bool haveEpicentralDistance() const noexcept;
    /*!
     * @brief Sets the takeoff angle (emergence angle at source).
     * @param angle  The takeoff angle in degrees.  This must be in the
     *               range [0,180] where 0 is up.
     * @throws std::invalid_argument if the angle is out of bounds.
     */
    void setTakeOffAngle(double angle);
    /*!
     * @return The takeoff angle in degrees.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] double getTakeOffAngle() const;
    /*!
     * @return True indicates that the takeoff angle was set.
     */
    [[nodiscard]] bool haveTakeOffAngle() const noexcept;
    /*! @} */

    /*! @name P Pick Information
     * @{
     */
    /*!
     * @brief Sets the P pick time.
     */
    /*!
     * @brief Sets the time of the P arrival.
     * @param pickTime   The UTC time of the P arrival.
     */
    void setPPickTime(const SFF::Utilities::Time &pickTime) noexcept;
    /*!
     * @brief Gets the UTC time of the P arrival.
     * @throws std::runtime_error if the P pick time was not set.
     */
    [[nodiscard]] SFF::Utilities::Time getPPickTime() const;
    /*!
     * @return True indicates that the P arrival time was set.
     */
    [[nodiscard]] bool havePPickTime() const noexcept;
    /*!
     * @brief Sets the P remark.
     * @param[in] remark  This an up to 2 letter string describing the P pick.
     *                    For example, an impulsive P could be "IP".
     */
    void setPRemark(const std::string &remark) noexcept;
    /*!
     * @return The P remark.
     * @throws std::runtime_error if the P remark was not set.
     */
    [[nodiscard]] std::string getPRemark() const;
    /*!
     * @return True indicates that the P remark was set.
     */
    [[nodiscard]] bool havePRemark() const noexcept;

    /*!
     * @brief Sets the P first motion, e.g., U for up and D for down.
     * @param[in] firstMotion  Sets the P first motion.
     */
    void setPFirstMotion(char firstMotion) noexcept;
    /*!
     * @return The P first motion.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] char getPFirstMotion() const;
    /*!
     * @return True indicates that the P first motion was set.
     */
    [[nodiscard]] bool havePFirstMotion() const noexcept;

    /*!
     * @brief Sets the P travel time residual.
     * @param[in] residual  The P travel time residual in seconds.
     */
    void setPResidual(double residual) noexcept;
    /*!
     * @return Gets the P travel time residual in seconds.
     * @throws std::runtime_error if the P residual was not set.
     */
    [[nodiscard]] double getPResidual() const;
    /*!
     * @return True indicates that the P residual was set.
     */
    [[nodiscard]] bool havePResidual() const noexcept;

    /*!
     * @brief Sets the P weight code.
     * @param[in] weightCode  The weight code.
     */
    void setPWeightCode(uint16_t weightCode) noexcept;
    /*!
     * @result The P weight code.
     * @throws std::runtime_error if the P weight code was not set.
     */
    [[nodiscard]] int getPWeightCode() const;
    /*!
     * @return True indicates that the P weight code was set.
     */
    [[nodiscard]] bool havePWeightCode() const noexcept;

    /*!
     * @brief Sets the P weight used.
     * @param[in] weightUsed  The weight used during the location.  This must
     *                        be non-negative.
     * @throws std::invalid_argument if weightUsed is negative.
     */
    void setPWeightUsed(double weightUsed);
    /*!
     * @return The P weight used by HypoInverse2000.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] double getPWeightUsed() const;
    /*!
     * @return True indicates that the P weight used was set.
     */
    [[nodiscard]] bool havePWeightUsed() const noexcept;

    /*!
     * @brief Sets the delay time for a P pick.
     * @param[in] delay  The delay time in seconds to add to P pick.
     */
    void setPDelayTime(double delay) noexcept;
    /*!
     * @return The delay time for a P pick in seconds.
     * @throws std::runtime_error if the P delay time was not set.
     */
    [[nodiscard]] double getPDelayTime() const;
    /*!
     * @result True indicates that the P delay time was set.
     */
    [[nodiscard]] bool havePDelayTime() const noexcept;
    /*! @} */

    /*! @name S Pick Information
     * @{
     */
    /*!
     * @brief Sets the time of the S arrival.
     * @param pickTime   The UTC time of the S arrival.
     */
    void setSPickTime(const SFF::Utilities::Time &pickTime) noexcept;
    /*!
     * @brief Gets the UTC time of the S arrival.
     * @throws std::runtime_error if the S pick time was not set.
     */
    [[nodiscard]] SFF::Utilities::Time getSPickTime() const;
    /*!
     * @return True indicates that the S arrival time was set.
     */
    [[nodiscard]] bool haveSPickTime() const noexcept;

    /*!
     * @brief Sets the S remark.
     * @param[in] remark  This an up to 2 letter string describing the S pick.
     *                    For example, an emergent S could be "ES".
     */
    void setSRemark(const std::string &remark) noexcept;
    /*!
     * @return The S remark.
     * @throws std::runtime_error if the S remark was not set.
     */
    [[nodiscard]] std::string getSRemark() const;
    /*!
     * @return True indicates that the S remark was set.
     */
    [[nodiscard]] bool haveSRemark() const noexcept;

    /*!
     * @brief Sets the S travel time residual.
     * @param[in] residual  The S travel time residual in seconds.
     */
    void setSResidual(double residual) noexcept;
    /*!
     * @return Gets the S travel time residual in seconds.
     * @throws std::runtime_error if the S residual was not set.
     */
    [[nodiscard]] double getSResidual() const;
    /*!
     * @return True indicates that the S residual was set.
     */
    [[nodiscard]] bool haveSResidual() const noexcept;

    /*!
     * @brief Sets the S weight code.
     * @param[in] weightCode  The weight code.
     */
    void setSWeightCode(uint16_t weightCode) noexcept;
    /*!
     * @result The S weight code.
     * @throws std::runtime_error if the S weight code was not set.
     */
    [[nodiscard]] int getSWeightCode() const;
    /*!
     * @return True indicates that the S weight code was set.
     */
    [[nodiscard]] bool haveSWeightCode() const noexcept;

    /*!
     * @brief Sets the S weight used.
     * @param[in] weightUsed  The weight used during the location.  This must
     *                        be non-negative.
     * @throws std::invalid_argument if weightUsed is negative.
     */
    void setSWeightUsed(double weightUsed);
    /*!
     * @return The S weight used by HypoInverse2000.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] double getSWeightUsed() const;
    /*!
     * @return True indicates that the S weight used was set.
     */
    [[nodiscard]] bool haveSWeightUsed() const noexcept;

    /*!
     * @brief Sets the delay time to add to an S pick.
     * @param[in] delay  The delay time to be added to an S pick
     *                   in seconds.
     */
    void setSDelayTime(double correction) noexcept;
    /*!
     * @return The delay time for an S pick in seconds.
     * @throws std::runtime_error if the S delay time was not set.
     */
    [[nodiscard]] double getSDelayTime() const;
    /*!
     * @result True indicates that the S static delay time was set.
     */
    [[nodiscard]] bool haveSDelayTime() const noexcept;
    /*! @} */
private:
    class StationArchiveImpl;
    std::unique_ptr<StationArchiveImpl> pImpl;
};
}
#endif
