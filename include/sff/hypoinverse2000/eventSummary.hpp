#ifndef SFF_HYPOINVERSE2000_EVENTSUMMARY_HPP
#define SFF_HYPOINVERSE2000_EVENTSUMMARY_HPP
#include <memory>
#include "sff/utilities/time.hpp"
namespace SFF::HypoInverse2000
{
/*!
 * @class EventSummary "eventSummary.hpp" "sff/hypoinverse2000/eventSummary.hpp"
 * @brief Defines a year-2000 compatibile event summary.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class EventSummary
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Constructor.
     */
    EventSummary();
    /*!
     * @brief Copy constructor.
     * @param[in] summary   The event summary from which to initialize
     *                      this class.
     */
    EventSummary(const EventSummary &summary);
    /*!
     * @brief Move constructor.
     * @param[in,out] summary  The event summary from which to initialize this
     *                         class.  On exit, summary's behavior is undefined.
     */
    EventSummary(EventSummary &&summary) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] summary  The summary class to copy to this.
     * @result A deep copy of summary.
     */
    EventSummary& operator=(const EventSummary &summary);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] summary   Moves the memory from summary to this.  On exit,
     *                          summary's behavior is undefined.
     * @result The memory from summary moved to this.
     */
    EventSummary& operator=(EventSummary &&summary) noexcept;
    /*! @} */

    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Destructor.
     */
    ~EventSummary();
    /*!
     * @brief Resets the class.
     */
    void clear() noexcept;
    /*! @} */

    /*! @name Origin Time
     * @{
     */
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

    /*!
     * @brief Sets the event information from a header line read from an
     *        archive file.
     */
    void unpackString(const std::string &line);

    /*! @brief Hypocenter
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
    /*! @} */

    /*! @name Magnitudes
     * @{
     */
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

    /*! @name Quality Metrics
     * @{
     */
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
     * @brief Determines if the number of weighted residuals was set.
     * @result The number of weighted residuals.
     */
    [[nodiscard]] bool haveNumberOfWeightedResiduals() const noexcept;

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
    class EventSummaryImpl;
    std::unique_ptr<EventSummaryImpl> pImpl;
};
}
#endif