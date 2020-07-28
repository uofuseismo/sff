#ifndef SFF_HYPOINVERSE2000_EVENTSUMMARY_HPP
#define SFF_HYPOINVERSE2000_EVENTSUMMARY_HPP
#include <vector>
#include <memory>
namespace SFF::HypoInverse2000
{
class EventSummaryLine;
class StationArchiveLine;
/*!
 * class EventSummary "eventSummary.hpp" "sff/hypoinverse2000/eventSummary.hpp"
 * @brief Defines an event summary.  An event summary is an amalgamation of 
 *        event information and its corresponding picks.
 * @note By using this API some information in the event summary line will be
 *       modified, such as number of polarities, to preserve self-consistency.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class EventSummary
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Constructor
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
     * @param[in,out] summary  The event summary from which to initialize
     *                         this class.  On exit, summary's behavior
     *                         is undefined.
     */
    EventSummary(EventSummary &&summary) noexcept;
    /*! @} */

    /*! @name Operators
     * @{
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] summary   The event summary to copy to this.
     * @result A deep copy of the event summary.
     */ 
    EventSummary& operator=(const EventSummary &summary);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] summary   The event summary whose memory will be moved
     *                          to this.  On exit, summary's behavior is
     *                          undefined.
     * @result The memory from summary moved to this.
     */
    EventSummary& operator=(EventSummary &&summary) noexcept;
    /*!
     * @brief Gets the i'th pick.
     * @result A reference to the i'th pick.
     * @note Accessing a nonexistant element results in undefined behavior.
     */
    StationArchiveLine& operator[](size_t i);
    /*!
     * @brief Gets the i'th pick.
     * @result A constant reference to the i'th pick.
     * @note Accessing a nonexistant element results in undefined behavior.
     */
    const StationArchiveLine& operator[](size_t i) const;
    /*! @} */

    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Destructor.
     */
    ~EventSummary();
    /*!
     * @brief Releases the memory and resets the class.
     */
    void clear() noexcept;

    /*! @name Event Information
     * @{
     */
    /*!
     * @brief Sets the event information from a header line read from an
     *        archive file.
     * @param[in] lines  The lines defining the event summary.  The first
     *                   line corresponds to the header line.  The subsequent
     *                   lines correspond to the picks.
     */
    void unpackString(const std::vector<std::string> &lines);
    /*!
     * @brief Converts the event information contained in this class to an
     *        output hypoinverse2000 archive file.
     * @return The event information and pick information for an output archive
     *         file.
     * @note You still must add the final bogus line to make this valid for
     *       hypoinverse.
     */
    [[nodiscard]] std::string packString() const;
    /*!
     * @brief Sets the event summary information (e.g., latitude, longitude,
     *        depth, origin time, etc.)
     * @param[in] eventSummary  The event information.
     * @note Some of this information may be overwritten.
     */
    void setEventInformation(const EventSummaryLine &eventSummary);
    /*!
     * @brief Gets the event summary line.
     */
    [[nodiscard]] EventSummaryLine getEventInformation() const;
    /*! @} */

    /*! @name Picks
     * @{
     */
    /*!
     * @brief Clears all picks from the event summary.
     */
    void clearPicks() noexcept;
    /*!
     * @brief Adds a P phase pick to the event.
     * @param[in] pPick   The P-phase pick.
     * @throws std::invalid_argument if the P pick time is not set.
     */
    void addPPick(const StationArchiveLine &pPick);
    /*!
     * @brief Adds an S phase pick to the event.
     * @param[in] sPick   The S-phase pick.
     * @throws std::invalid_argument if the S pick time is not set.
     */
    void addSPick(const StationArchiveLine &sPick);

    /*!
     * @brief Gets the number of picks.
     * @result The number of picks set in the class.
     */
    [[nodiscard]] int getNumberOfPicks() const noexcept;
private:
    class EventSummaryImpl;
    std::unique_ptr<EventSummaryImpl> pImpl;
};
};
#endif
