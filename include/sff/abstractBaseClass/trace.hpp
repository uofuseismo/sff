#ifndef SFF_ABSTRACTBASECLASS_TRACE_HPP
#define SFF_ABSTRACTBASECLASS_TRACE_HPP
#include <memory>
#include <vector>
#include "sff/utilities/time.hpp"
#include "sff/formats.hpp"
namespace SFF::AbstractBaseClass
{
/*!
 * @class ITrace time.hpp "sff/utilities/time.hpp"
 * @brief The abstract base class for a seismic trace.  For example, a SAC file
 *        is a seismic trace is it simply encapsulates a time series.
 * @copyright Ben Baker (University of Utah) distributed under the MIT license.  
 */
class ITrace
{
public:
    virtual ~ITrace() = default;
    virtual int getNumberOfSamples() const = 0;
    virtual double getSamplingRate() const = 0;
    virtual double getSamplingPeriod() const = 0;
    virtual void getData(int npts, double *data[]) const = 0;
    virtual void getData(int npts, float *data[]) const = 0;
    //virtual void getData(int npts, int *data[]) const = 0;
    virtual SFF::Utilities::Time getStartTime() const = 0;
    virtual SFF::Format getFormat() const noexcept = 0;
};
}
#endif
