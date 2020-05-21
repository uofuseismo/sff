#ifndef SFF_HYPOINVERSE2000_STATIONARCHIVELINE_HPP
#define SFF_HYPOINVERSE2000_STATIONARCHIVELINE_HPP
#include <memory>
#include "sff/utilities/time.hpp"
namespace SFF::HypoInverse2000
{
/*!
 * @brief Defines different amplitude unit types.
 */
enum class AmplitudeUnits
{
    PEAK_TO_PEAK = 0,   /*! Peak to peak amplitude in millimeters. */
    ZERO_TO_PEAK = 1,   /*! Zero to peak amplitude in millimeters. */
    DIGITAL_COUNTS = 2  /*! Digital counts (UCB). */
};
/*!
 * @class StationArchiveLine "stationArchiveLine.hpp" "sff/hypoinverse2000/stationArchiveLine.hpp"
 * @brief Defines a year-2000-compatibile station archive line.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class StationArchiveLine
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Default constructor.
     */
    StationArchiveLine();
    /*!
     * @brief Copy constructor.
     * @param[in] station  The station archive class from which to initialize
     *                     this class.
     */
    StationArchiveLine(const StationArchiveLine &station);
    [[maybe_unused]] /*!
     * @brief Move constructor.
     * @param[in,out] station  The station archive from which to initialize
     *                         this class.  On exit, station's behavior is
     *                         undefined.
     */
    StationArchiveLine(StationArchiveLine &&station) noexcept;
    /*! @} */

    /*!
     * @brief Sets the event information from a station line read from an
     *        archive file.
     */
    void unpackString(const std::string &line);
    /*!
     * @brief Converts the class members to a line in a station line in an
     *        archive file.
     * @return The line describing the pick.
     */
    [[nodiscard]] std::string packString() const noexcept;

    /*! @name Operators
     * @{
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] station  The station class to copy to this.
     * @return A deep copy of station.
     */
    StationArchiveLine& operator=(const StationArchiveLine &station);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] station  Moves the memory from station to this.
     * @return The memory from station moved to this.
     */
    StationArchiveLine& operator=(StationArchiveLine &&station) noexcept;
    /*! @} */

    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Default destructor.
     */
    ~StationArchiveLine();
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

    /*! @name Source-Receiver Distance, Azimuth, And Take-Off Angle
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
     * @brief Sets the source-to-receiver azimuth in degrees.
     * @param[in] azimuth  The source to receiver azimuth in degrees.
     *                     This is positive east of north.
     * @throws std::invalid_argument if this is not in the range [0,360].
     */
    void setAzimuth(double azimuth);
    /*!
     * @return The soruce to receiver azimuth in degrees.
     * @throws std::runtime_error if the azimuth was not set.
     */
    [[nodiscard]] double getAzimuth() const;
    /*!
     * @return True indicates that the azimuth was set.
     */
    [[nodiscard]] bool haveAzimuth() const noexcept;

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

    /*!
     * @brief Sets the P importance.
     * @param[in] importance  The importance of the P arrival.
     */
    void setPImportance(double importance);
    /*!
     * @return The importance of the P arrival.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] double getPImportance() const;
    /*!
     * @return True indicates that the P importance was set.
     */
    [[nodiscard]] bool havePImportance() const noexcept;
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

    /*!
     * @brief Sets the S importance.
     * @param[in] importance  The importance of the S arrival.
     */
    void setSImportance(double importance);
    /*!
     * @return The importance of the S arrival.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] double getSImportance() const;
    /*!
     * @return True indicates that the S importance was set.
     */
    [[nodiscard]] bool haveSImportance() const noexcept;
    /*! @} */

    /*! @name Magnitude
     * @{
     */
    /*!
     * @brief Sets the amplitude magnitude, e.g., Richter magnitude, for the
     *        station.
     * @param magnitude  The amplitude magnitude.
     */
    void setAmplitudeMagnitude(double magnitude) noexcept;
    /*!
     * @return The amplitude magnitude for the station.
     * @throws std::runtime_error if the amplitude magnitude was not set.
     */
    [[nodiscard]] double getAmplitudeMagnitude() const;
    /*!
     * @return True indicates that the amplitude magnitude was set.
     */
    [[nodiscard]] bool haveAmplitudeMagnitude() const noexcept;

    /*!
     * @brief Sets the amplitude magnitude weight code.
     * @param code  The amplitude magnitude weight code.  This must be
     *              non-negative.
     * @throws std::invalid_argument if the weight code is negative.
     */
    void setAmplitudeMagnitudeWeightCode(int code);
    /*!
     * @return The amplitude magnitude weight code for the station.
     * @throws std::runtime_error if the amplitude magnitude weight
     *         code was not set.
     */
    [[nodiscard]] int getAmplitudeMagnitudeWeightCode() const;
    /*!
     * @return True indicates that the amplitude magnitude weight code was set.
     */
    [[nodiscard]] bool haveAmplitudeMagnitudeWeightCode() const noexcept;

    /*!
     * @brief Sets the amplitude magnitude label.
     * @param[in] label  The amplitude magnitude label.
     * @throws std::invalid_argument if this is blank.
     */
    void setAmplitudeMagnitudeLabel(char label);
    /*!
     * @result The amplitude magnitude label.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] char getAmplitudeMagnitudeLabel() const;
    /*!
     * @return True indicates the amplitude magnitude label was set.
     */
    [[nodiscard]] bool haveAmplitudeMagnitudeLabel() const noexcept;

    /*!
     * @brief Sets the period at which the amplitude was measured.
     * @param[in] period  The period of the amplitude measurement in seconds.
     * @throws std::invalid_argument if this is not positive.
     */
    void setPeriodOfAmplitudeMeasurement(double period);
    /*!
     * @return The period at which the amplitude was measured.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] double getPeriodOfAmplitudeMeasurement() const;
    /*!
     * @return True indicates that the period was set.
     */
    [[nodiscard]] bool havePeriodOfAmplitudeMeasurement() const noexcept;

    /*!
     * @brief Sets the duration magnitude, e.g., coda magnitude, for the
     *        station.
     * @param magnitude  The duration magnitude.
     */
    void setDurationMagnitude(double magnitude) noexcept;
    /*!
     * @return The duration magnitude for the station.
     * @throws std::runtime_error if the amplitude magnitude was not set.
     */
    [[nodiscard]] double getDurationMagnitude() const;
    /*!
     * @return True indicates that the duration magnitude was set.
     */
    [[nodiscard]] bool haveDurationMagnitude() const noexcept;

    /*!
     * @brief Sets the duration magnitude weight code.
     * @param code  The duration magnitude weight code.  This must be
     *              non-negative.
     * @throws std::invalid_argument if the weight code is negative.
     */
    void setDurationMagnitudeWeightCode(int code);
    /*!
     * @return The duration magnitude weight code for the station.
     * @throws std::runtime_error if the duration magnitude weight
     *         code was not set.
     */
    [[nodiscard]] int getDurationMagnitudeWeightCode() const;
    /*!
     * @return True indicates that the duration magnitude weight code was set.
     */
    [[nodiscard]] bool haveDurationMagnitudeWeightCode() const noexcept;

    /*!
     * @brief Sets the duration magnitude label.
     * @param[in] label  The duration magnitude label.
     * @throws std::invalid_argument if this is blank.
     */
    void setDurationMagnitudeLabel(char label);
    /*!
     * @result The duration magnitude label.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] char getDurationMagnitudeLabel() const;
    /*!
     * @return True indicates the duration magnitude label was set.
     */
    [[nodiscard]] bool haveDurationMagnitudeLabel() const noexcept;

    /*!
     * @brief Sets the coda duration.
     * @param[in] duration  The coda magnitude duration in seconds.
     * @throws std::invalid_argument if this is not positive.
     */
    void setCodaDuration(double duration);
    /*!
     * @return The coda magnitude duration in seconds.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] double getCodaDuration() const;
    /*!
     * @return True indicates that the coda duration was set.
     */
    [[nodiscard]] bool haveCodaDuration() const noexcept;
    /*! @} */

    /*! @name Miscellaneous
     * @{
     */
    /*!
     * @brief Sets the pick's data source.  For example J may indicate Jiggle.
     * @param[in] code  The data source code.
     * @throws std::invalid_argument if the code is blank.
     */
    void setDataSourceCode(char code);
    /*!
     * @return The data source code.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] char getDataSourceCode() const;
    /*!
     * @return True indicates that the data source code was set.
     */
    [[nodiscard]] bool haveDataSourceCode() const noexcept;

    /*!
     * @brief Sets the amplitude (normally peak-to-peak).
     * @param[in] amplitude  The amplitude.  This must be non-negative.
     * @throws std::invalid_argument if this is negative.
     */
    void setAmplitude(double amplitude);
    /*!
     * @return Gets the amplitude.
     * @throw std::runtime_error if this is not set.
     */
    [[nodiscard]] double getAmplitude() const;
    /*!
     * @return True indicates that the amplitude was set.
     */
    [[nodiscard]] bool haveAmplitude() const noexcept;
    /*!
     * @brief Sets the amplitude units.
     */
     /*!
      * @brief Defines the amplitude units.
      * @param units   The amplitude units.
      */
    void setAmplitudeUnits(AmplitudeUnits units) noexcept;
    /*!
     * @return The amplitude units.
     * @throws std::runtime_error if the amplitud eunits weree not set.
     */
    [[nodiscard]] AmplitudeUnits getAmplitudeUnits() const;
    /*!
     * @return True indicates that the amplitude units were set.
     */
    [[nodiscard]] bool haveAmplitudeUnits() const noexcept;
    /*! @} */
private:
    class StationArchiveLineImpl;
    std::unique_ptr<StationArchiveLineImpl> pImpl;
};
}
#endif
