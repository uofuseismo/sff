#ifndef SFF_FORMATS_HPP
#define SFF_FORMATS_HPP
namespace SFF
{
/*!
 * @brief Defines the seicmic data format.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.
 */ 
enum class Format
{
    SAC,         /*!< Seismic Analysis Code (SAC) format. */
    SILIXA_SEGY, /*!< Silixa's custom SEGY format. */
    MINISEED     /*!< MiniSEED format. */
};
}
#endif
