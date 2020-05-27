#ifndef SFF_HYPOINVERSE2000_EVENTSUMMARYLINE_HPP
#define SFF_HYPOINVERSE2000_EVENTSUMMARYLINE_HPP
#include <memory>
#include "sff/utilities/time.hpp"
namespace SFF::HypoInverse2000
{
/*!
 * @class EventSummaryLine "eventSummaryLine.hpp" "sff/hypoinverse2000/eventSummaryLine.hpp"
 * @brief Defines a year-2000 compatibile event summary line in an archive file.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class EventSummaryLine
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Constructor.
     */
    EventSummaryLine();
    /*!
     * @brief Copy constructor.
     * @param[in] summary   The event summary from which to initialize
     *                      this class.
     */
    EventSummaryLine(const EventSummaryLine &summary);
    [[maybe_unused]] /*!
     * @brief Move constructor.
     * @param[in,out] summary  The event summary from which to initialize this
     *                         class.  On exit, summary's behavior is undefined.
     */
    EventSummaryLine(EventSummaryLine &&summary) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] summary  The summary class to copy to this.
     * @result A deep copy of summary.
     */
    EventSummaryLine& operator=(const EventSummaryLine &summary);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] summary   Moves the memory from summary to this.  On exit,
     *                          summary's behavior is undefined.
     * @result The memory from summary moved to this.
     */
    EventSummaryLine& operator=(EventSummaryLine &&summary) noexcept;
    /*! @} */

    /*! @name Destructor
     * @{
     */
    /*!
     * @brief Destructor.
     */
    ~EventSummaryLine();
    /*!
     * @brief Resets the class.
     */
    void clear() noexcept;
    /*! @} */

    /*!
     * @brief Sets the event information from a header line read from an
     *        archive file.
     * @param[in] line   The event information line to unpack.
     */
    void unpackString(const std::string &line);
    /*!
     * @brief Packs the information contained in this class into a line to 
     *        write to the archive file.
     */
    [[nodiscard]] std::string packString() const;

    /*! @brief Hypocenter and Origin Time
     * @{
     */
    /*!
     * @brief Sets the event latitude.
     * @param[in] latitude  The event latitude in degrees.  This must be in
     *                      the range [-90,90].
     * @throws std::invalid_argument if latitude is out of bounds.
     */
    void setLatitude(double latitude);
    /*!
     * @brief Gets the event latitude.
     * @result The event's latitude in degrees.
     * @throws std::runtime_error if the latitude was not set.
     */
    [[nodiscard]] double getLatitude() const;
    /*!
     * @brief Determines if the event latitude was set.
     * @result True indicates that the latitude was set.
     */
    [[nodiscard]] bool haveLatitude() const noexcept;

    /*!
     * @brief Sets the event longitude.
     * @param[in] longitue  The event latitude in degrees.  This must be in
     *                      the range [-540,540).
     * @throws std::invalid_argument if longitude is out of bounds.
     */
    void setLongitude(double longitude);
    /*!
     * @brief Gets the event longitude.
     * @result The event's lontiude in degrees.  This will be in the range
     *         of [0,360).
     * @throws std::runtime_error if the longitude was not set.
     */
    [[nodiscard]] double getLongitude() const;
    /*!
     * @brief Determines if the event longitude was set.
     * @result True indicates that the longitude was set.
     */
    [[nodiscard]] bool haveLongitude() const noexcept;

    /*!
     * @brief Sets the event depth.
     * @param[in] depth  The event depth in kilometers.
     */
    void setDepth(double depth) noexcept;
    /*!
     * @brief Gets the event depth.
     * @result The event's depth in kilometers.
     * @throws std::runtime_error if the depth was not set.
     */
    [[nodiscard]] double getDepth() const;
    /*!
     * @brief Determines if the event depth was set.
     * @result True indicates that the depth was set.
     */
    [[nodiscard]] bool haveDepth() const noexcept;

    /*!
     * @brief Sets the origin time.
     * @param[in] originTime  The event's origin time.
     */
    void setOriginTime(const SFF::Utilities::Time &originTime) noexcept;
    /*!
     * @brief Gets the event origin time.
     * @result The origin time of the event.
     * @throws std::runtime_error if the event origin time was not set.
     */
    [[nodiscard]] SFF::Utilities::Time getOriginTime() const;
    /*!
     * @brief Determines if the event origin time was set.
     * @result True indicates that the event origin time was set.
     */
    [[nodiscard]] bool haveOriginTime() const noexcept;
    /*! @} */

    /*! @name Magnitudes
     * @{
     */
    /*!
     * @brief Sets the preferred magnitude label.
     * @param[in] label  The preferred magnitude label.
     * @throws std::invalid_argument if this is blank.
     */
    void setPreferredMagnitudeLabel(char label);
    /*!
     * @return Gets the preferred magnitude label.
     * @throws std::runtime_error if the preferred magnitude label was not set.
     */
    [[nodiscard]] char getPreferredMagnitudeLabel() const;
    /*!
     * @result True indicates that the preferred magnitude labelw as set.
     */
    [[nodiscard]] bool havePreferredMagnitudeLabel() const noexcept;
    /*!
     * @brief Sets the preferred magnitude.
     * @param magnitude   The preferred magnitude.
     */
    void setPreferredMagnitude(double magnitude) noexcept;
    /*!
     * @brief Gets the preferred magnitude.
     * @result The preferred magnitude.
     * @throws std::runtime_error if the preferred magnitude is not set.
     */
    [[nodiscard]] double getPreferredMagnitude() const;
    /*!
     * @brief Determines if the preferred magnitude was set.
     * @return True indicates that the preferred magnitude was set.
     */
    [[nodiscard]] bool havePreferredMagnitude() const noexcept;
    /*! @} */

    /*!
     * @brief Sets the event identifier.
     * @param evid  The event identifier.
     */
    void setEventIdentifier(uint64_t evid) noexcept;
    /*!
     * @return Gets the event identifier.
     * @throws std::runtime_error if the event identifier was not set.
     */
    [[nodiscard]] uint64_t getEventIdentifier() const;
    /*!
     * @return True indicates that the event identifier was set.
     */
    [[nodiscard]] bool haveEventIdentifier() const noexcept;

    /*!
     * @brief Sets the number of picks with first motions.
     * @param[in] nFirstMotions  The number of first motions.
     * @throws std::invalid_argument if the number of first motions is
     *         not positive.
     */
    void setNumberOfFirstMotions(int nFirstMotions);
    /*!
     * @return Gets the number of first motions.
     * @throws std::invalid_argument if the number of first motions was
     *         not set.
     */
    [[nodiscard]] int getNumberOfFirstMotions() const;
    /*!
     * @return True indicates that the number of first motions was set.
     */
    [[nodiscard]] bool haveNumberOfFirstMotions() const noexcept;

    /*! @name Quality Metrics
     * @{
     */
    /*!
     * @param[in] distance  Sets the distance from the source to the closest
     *                      station in kilometers.
     * @throws std::invalid_argument if distance is not positive.
     */
    void setDistanceToClosestStation(double distance);
    /*!
     * @return The distance from the source to the closest station in
     *         kilometers.
     */
    [[nodiscard]] double getDistanceToClosestStation() const;
    /*!
     * @return True indicates the distance to the closest station was set.
     */
    [[nodiscard]] bool haveDistanceToClosestStation() const noexcept;

    /*!
     * @brief Sets the azimuthal gap.
     * @param gap   The azimuthal gap in degrees.  This must be in the
     *              range [0,360)
     * @throws std::invalid_argument if the gap is out of bounds.
     */
    void setAzimuthalGap(double gap);
    /*!
     * @brief Gets the azimuthal gap.
     * @result The azimuthal gap in degrees.
     * @throws std::runtime_error if the gap was not set.
     */
    [[nodiscard]] double getAzimuthalGap() const;
    /*!
     * @brief Determines if the azimuthal gap was set.
     * @result True indicates that the gap was set.
     */
    [[nodiscard]] bool haveAzimuthalGap() const noexcept;

    /*!
     * @brief Sets the number of P and S weighted residuals
     *        contributing to the location.
     * @param nResiduals  The number of weighted residuals.
     * @throws std::invalid_argument if this is not positive.
     */
    void setNumberOfWeightedResiduals(int nResiduals);
    /*!
     * @brief Gets the number of P and S weighted residuals.
     * @result The number of P and S weighted residuals contributing to the
     *         solution.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] int getNumberOfWeightedResiduals() const;
    /*!
     * @result True indicates the number of weighted residuals was set.
     */
    [[nodiscard]] bool haveNumberOfWeightedResiduals() const noexcept;

    /*!
     * @brief Sets the number of S weighted residuals
     *        contributing to the location.
     * @param nResiduals  The number of S weighted residuals.
     * @throws std::invalid_argument if this is not positive.
     */
    void setNumberOfSWeightedResiduals(int nResiduals);
    /*!
     * @brief Gets the number of S weighted residuals.
     * @result The number of S weighted residuals contributing to the solution.
     * @throws std::runtime_error if this was not set.
     */
    [[nodiscard]] int getNumberOfSWeightedResiduals() const;
    /*!
     * @result True indicates the number of S weighted residuals was set.
     */
    [[nodiscard]] bool haveNumberOfSWeightedResiduals() const noexcept;

    /*!
     * @brief Sets the residual travel time RMS.
     * @param rms  The root-mean-squared of the residual travel times.
     * @throws std::invalid_argument if this is not positive.
     */
    void setResidualTravelTimeRMS(double rms);
    /*!
     * @result The residual travel time RMS.
     * @throws std::runtime_error if the residual travel time RMS was not set.
     */
    [[nodiscard]] double getResidualTravelTimeRMS() const;
    /*!
     * @return True indicates the the residual travel time RMS was set.
     */
    [[nodiscard]] bool haveResidualTravelTimeRMS() const noexcept;
    /*! @} */
private:
    class EventSummaryLineImpl;
    std::unique_ptr<EventSummaryLineImpl> pImpl;
};
}
#endif
