#ifndef SFF_SEGY_SILIXA_TRACEGROUP_HPP
#define SFF_SEGY_SILIXA_TRACEGROUP_HPP
#include <memory>
#include <vector>
#include "sff/segy/silixa/binaryFileHeader.hpp"
#include "sff/segy/silixa/trace.hpp"

namespace SFF::SEGY
{
class TextualFileHeader;
}

/*
namespace SFF::SEGY::Silixa
{
typedef Trace* TraceIterator;
};
*/

namespace SFF::SEGY::Silixa
{
template<typename C>
using TraceIterator = typename std::vector<SFF::SEGY::Silixa::Trace>::iterator;
template<typename C>
using ConstTraceIterator = typename std::vector<SFF::SEGY::Silixa::Trace>::const_iterator;
using TraceReference = SFF::SEGY::Silixa::Trace&;
using ConstTraceReference = const SFF::SEGY::Silixa::Trace&;

/*!
 * @class TraceGroup "traceGroup.hpp" "sff/segy/silixa/traceGroup.hpp"
 * @brief This is a container for the Silixa file and contains all components
 *        Silixa's SEGY file definition.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
class TraceGroup
{
public:
    /*! @name Constructors
     * @{
     */
    /*!
     * @brief Constructor.
     */
    TraceGroup();
    /*!
     * @brief Copy constructor.
     * @param[in] group  The trace group class from which to initialize
     *                   this class.
     */
    TraceGroup(const TraceGroup &group);
    /*!
     * @brief Move constructor.
     * @param[in,out] group  The trace group whose memory will be used to
     *                       initialize this class.  On exit, group's behavior
     *                       is undefined.
     */
    TraceGroup(TraceGroup &&group) noexcept;
    /*! @} */

    /*! @name Operators
     * @{ 
     */
    /*!
     * @brief Copy assignment operator.
     * @param[in] group   The group to copy to this.
     * @result A deep copy of group.
     */
    TraceGroup& operator=(const TraceGroup &group);
    /*!
     * @brief Move assignment operator.
     * @param[in,out] group   The group whose memory will be moved to this.
     *                        On exit, group's behavior is undefined.
     * @result The memory from group moved to this.
     */
    TraceGroup& operator=(TraceGroup &&group) noexcept;
    /*!
     * @brief Returns a the trace at the indicated position.
     * @param[in] index   The index of the desired trace in the trace group.
     * @result The index'th trace.
     */
    Trace operator[](size_t index);
    /*!
     * @brief Returns a constant reference at the indicated position.
     * @param[in] index   The index of the desired trace in the trace group.
     * @result A const reference to the index'th trace.
     */
    ConstTraceReference operator[](size_t index) const;

    /*! @} */
 
    /*! @name Destructors
     * @{
     */
    /*!
     * @brief Destructor.
     */
    ~TraceGroup();
    /*!
     * @brief Clears the memory and resets the class.
     */
    void clear() noexcept;
    /*!
     * @brief Clears the traces from memory.
     */
    void clearTraces() noexcept; 
    /*! @} */

    /*!
     * @brief Reads a Silixa SEGY file from disk.
     * @throws std::invalid_argument if the fileName does not exist or the file
     *         is improperly formated.
     */
    void read(const std::string &fileName);

    /*!
     * @brief Gets the number of samples in each trace.
     * @result The number of samples in each trace.
     */
    int getNumberOfSamplesPerTrace() const;
    /*!
     * @brief Gets the number of traces.
     * @result The number of traces in the group.
     */
    int getNumberOfTraces() const; 

    /*! @name Iterators
     * @{
     */
    TraceIterator<SFF::SEGY::Silixa::Trace> begin();
    TraceIterator<SFF::SEGY::Silixa::Trace> end();
    ConstTraceIterator<SFF::SEGY::Silixa::Trace> begin() const;
    ConstTraceIterator<SFF::SEGY::Silixa::Trace> end() const;

    /*!
     * @brief Returns the trace at the given index.
     * @result The trace at the given index.
     * @throws std::invalid_argument if the index is greater than or equal to
     *         \c getNumberOfTraces().
     */
    Trace at(size_t index);
    /*! 
     * @brief Return a trace reference to the trace at the given index.
     * @result A reference to the trace
     * @throws std::invalid_argument if the index is greater than or equal
     *         to \c getNumberOfTraces().
     */
    ConstTraceReference at(size_t index) const;
    /*! @} */
private:
    class TraceGroupImpl;
    std::unique_ptr<TraceGroupImpl> pImpl;
};
} 
#endif
