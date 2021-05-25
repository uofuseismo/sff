#ifndef SFF_UTILITIES_TIME_HPP
#define SFF_UTILITIES_TIME_HPP
#include <memory>
namespace SFF::Utilities
{
/// @class Time time.hpp "sff/utilities/time.hpp"
/// @brief A class for managing calendar and epochal time.
/// @copyright Ben Baker (University of Utah) distributed under the MIT license.
class Time
{
public:
    /// @name Constructors
    /// @{
    /// @brief Default constructor which initializes epochal time to the
    ///        epoch, i.e., January 01, 1970.
    Time();
    /// @brief Copy constructor.
    /// @param[in] time  The class from which to initialize this class.
    Time(const Time &time); 
    /// @brief Move constructor.
    /// @param[in,out] time  The class from which to initialize.  On exit
    ///                      time's behavior will be undefined.
    Time(Time &&time) noexcept;
    /// @brief Constructs an Earthworm time class from an epochal time.
    /// @param[in] epoch  The number of seconds since the epoch (Jan 1, 1970)
    ///                   in UTC for which the date will be initialized.
    explicit Time(double epoch);
    /// @brief Creates a time from a string representation that must have format:
    ///        YYYY-MM-DDTHH:MM:SS.SSSSSS.
    /// @param[in] time  The time string from which to initalize the time.
    explicit Time(const std::string &time);
    /// @}

    /// @name Operators
    /// @{
    /// @brief Assignment operator.
    /// @param[in] time  The class to copy.
    /// @result A deep copy of the input class.
    Time& operator=(const Time &time);
    /// @brief Move assignment operator.
    /// @param[in,out] time  The class to move.  On exit time's behavior
    ///                      will be undefined.
    /// @result The input class.
    Time& operator=(Time &&time) noexcept;
    /// @}

    /// @name Destructors
    /// @{
    /// @brief Default destructor.
    ~Time();
    /// @brief Resets the time on the class to January 01, 1970.
    void clear() noexcept;
    /// @}

    /*!
     * @name Epochal Time Setters/Getters
     * @{
     */
    /*!
     * @brief Sets the epochal time.
     * @param[in] epoch  The number of seconds since the epoch (Jan 1, 1970)
     *                   in UTC for which the date will be initialized.
     */
    void setEpoch(double epoch);
    /*!
     * @brief Gets the epochal time (seconds) correpsonding to the time
     *        set in the class.
     * @result The UTC epochal time in seconds since the epoch.
     * @throws std::invalid_argument if the time is improperly set.
     */
    [[nodiscard]] double getEpoch() const;
    /*! @} */

    /// @name Year
    /// @{
    /// @brief Sets the year.
    /// @param[in] year  The 4-digit year to set.
    void setYear(int year);
    /// @result The 4-digit year.
    [[nodiscard]] int getYear() const noexcept;
    /// @}

    /// @name Day of Year
    /// @{
    /// @brief Sets the day of the year.
    /// @note This will override the month and day of month set with
    ///       \c setMonthAndDay().
    /// @param[in] jday  The day of the year to set.  This is in the
    ///                  range of [1,366] for leap years and [1,365]
    ///                  for non-leap years.
    /// @throws std::invalid_argument if jday is out of range.
    void setDayOfYear(int jday);
    /// @result The day of the year.  This is in the range [1,366] where 366
    ///         accounts for leap years.
    [[nodiscard]] int getDayOfYear() const noexcept;
    /// @}

    /// @name Calendar Day
    /// @{
    /// @brief Sets the month and the day of the month.
    /// @note This will override the current day of the year.
    /// @param[in] monthAndDay  monthAndDay.first is the month which must
    ///                        be in the range [1,12] and monthAndDay.second
    ///                        is the day of the month which must be in the
    ///                        range [1,31].
    /// @throws std::invalid_argument if month or day of month is out of range.
    void setMonthAndDay(const std::pair<int, int> &monthAndDay);
    /// @result The month.  This is in the range [1,12].
    [[nodiscard]] int getMonth() const noexcept;
    /// @brief Gets the day of the month corresponding to the time set
    ///        in the class.
    /// @result The day of the month.  This is in the range [1,31].
    [[nodiscard]] int getDayOfMonth() const noexcept;
    /// @}

    /// @name Hour
    /// @{
    /// @brief Sets the hour.
    /// @param[in] hour  The hour to set.  This is in the range [0,23].
    /// @throws std::invalid_argument if hour is out of range.
    void setHour(int hour);
    /// @result The hour of the day.  This is in the range [0,23].
    [[nodiscard]] int getHour() const noexcept;
    /// @}

    /// @name Minute
    /// @{
    /// @brief Sets the minute.
    /// @param[in] minute  The minute to set.  This is in the range [0,59].
    /// @throws std::invalid_argument if minute is out of range.
    void setMinute(int minute);
    /// @result The minute of the hour.  This is in the range [0,59].
    [[nodiscard]] int getMinute() const noexcept;
    /// @}

    /// @name Second
    /// @{
    /// @brief The integer part of the second to set.
    /// @param[in] second  The integral second to set.  This is in the
    ///                    range [0,59].
    /// @throws std::invalid_argument if second is out of range.
    void setSecond(int second);
    /// @result The integer second.  This is in the range [0,59].
    [[nodiscard]] int getSecond() const noexcept;
    /// @}

    /// @name Micro-second
    /// @{
    /// @brief Sets the microsecond.  
    /// @param[in] musec  The microsecond to set.  This must be in the range
    ///                   [0,999999].
    /// @throws std::invalid_argument if microsecond is negative or too large.
    void setMicroSecond(int musec);
    /// @result The microsecond component of the set time.
    [[nodiscard]] int getMicroSecond() const noexcept;
    ///
    /// @} 

    /// @brief Swaps two time classes.
    /// @param[in,out] lhs  Class to exchange with rhs.
    /// @param[in,out] rhs  Class to exchange with lhs.
    friend void swap(Time &lhs, Time &rhs);
private:
     class TimeImpl;
     std::unique_ptr<TimeImpl> pImpl;
}; // End class
/*!
 *  @brief Swaps two time classes, lhs and rhs.
 *  @param[in,out] lhs  On exit this will contain the information in rhs.
 *  @param[in,out] rhs  On exit this will contain the information in lhs.
 */
void swap(Time &lhs, Time &rhs);
/*!
 * @brief Computes the sum of two times a la: x + y.
 * @param[in] x   The time.
 * @param[in] y   The time to add to x.
 * @result The sum of the two times: x + y.
 */
Time operator+(const Time &x, const Time &y);
/*!
 * @brief Adds seconds to a time a la: x + y (seconds).
 * @param[in] x   The time.
 * @param[in] y   The number of seconds to add to x.
 * @result The sum of the time in x with the number of seconds in y: x + y. 
 */
Time operator+(const Time &x, double y); 
/*!
 * @brief Computes the difference between two times a la: x - y.
 * @param[in] x   The time.
 * @param[in] y   The time to subtract from x.
 * @result The difference between the two times: x - y.
 */
Time operator-(const Time &x, const Time &y);
/*!
 * @brief Removes seconds from a time a la: x - y (seconds).
 * @param[in] x   The time.
 * @param[in] y   The number of seconds to subtract from to x.
 * @result The difference between the time in x and the
 *         number of seconds in y: x - y.
 */
Time operator-(const Time &x, double y);
/*!
 * @param[in] lhs  The left hand side of the equality.
 * @param[in] rhs  The right hand side of the equality.
 * @result True indicates that lhs == rhs, i.e., the times are equal.
 */
bool operator==(const Time &lhs, const Time &rhs);
/*!
 * @param[in] lhs  The left hand side of the inequality.
 * @param[in] rhs  The right hand side of the inequality.
 * @result True indicates that lhs != rhs, i.e., the times are not equal.
 */
bool operator!=(const Time &lhs, const Time &rhs);
/*!
 * @param[in] lhs  The left hand side of the comparitor.
 * @param[in] rhs  The right hand side of the comparitor.
 * @result True indicates that lhs > rhs, i.e., the lhs is later than the rhs.
 */
bool operator>(const Time &lhs, const Time &rhs);
/*!
 * @param[in] lhs  The left hand side of the comparitor.
 * @param[in] rhs  The right hand side of the compatitor.
 * @result True indicates that lhs < rhs, i.e, the lhs is earlier than the rhs.
 */
bool operator<(const Time &lhs, const Time &rhs);
/*!
 * @brief Outputs a time as YYYY-MM-DDTHH:MM:SS.SSSSSS
 * @param[in] os    An output stream object.
 * @param[in] time  The time stamp
 * @return A formatted time.
 */
std::ostream& operator<<(std::ostream &os, const Time &time);

}

#endif
