#ifndef SFF_MINISEED_ENUMS_HPP
#define SFF_MINISEED_ENUMS_HPP 1
namespace SFF::MiniSEED
{
/*!
 * @class Precision enums.hpp "sff/miniseed/enums.hpp"
 * @brief Defines the precision of the data in the trace.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */
enum class Precision 
{
    INT32,    /*!< 32-bit integer. */
    FLOAT32,  /*!< 32-bit floating precision. */
    FLOAT64,  /*!< 64-bit floating precision. */
    UNKNOWN   /*1< An unknown precision. */
};
}
#endif
