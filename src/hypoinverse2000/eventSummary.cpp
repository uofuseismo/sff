#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "sff/hypoinverse2000/eventSummary.hpp"
#include "sff/hypoinverse2000/eventSummaryLine.hpp"
#include "sff/hypoinverse2000/stationArchiveLine.hpp"

using namespace SFF::HypoInverse2000;

namespace
{

/// Gets the azimuthal gap
/// @retval The azimuthal gap in degrees.
/// @retval A negative indicates the gap cannot be computed.
double getAzimuthalGap(const std::vector<StationArchiveLine> &picks)
{
    if (picks.empty()){return -1;}
    std::vector<double> az;
    az.reserve(picks.size() + 1);
    for (const auto &pick : picks)
    {
        if (pick.haveAzimuth())
        {
            az.push_back(pick.getAzimuth());
        }
    }
    // No azimuths
    if (az.empty()){return -1;}
    // Only one pick so the gap is 360 degrees.
    if (az.size() == 1){return 360;}
    // Sort into ascending order and make a dumby index  at end
    std::sort(az.begin(), az.end());
    az.push_back(az[0] + 360);
    double azGap = -1;
    for (int i=0; i<static_cast<int> (az.size()) - 1; ++i)
    {
        azGap = std::max(azGap, az[i+1] - az[i]);
    }
    return azGap;
}
/// @result The number of first motions.
int getNumberOfPolarities(const std::vector<StationArchiveLine> &picks)
{
    int nfm = 0;
    for (const auto &pick : picks)
    {
        if (pick.haveFirstMotion()){nfm = nfm + 1;}
    }
    return nfm;
}
/// @retval The smallest source-to-receiver distance in km
/// @retval A negative indicates that this could not be computed.
double getSmallestDistance(const std::vector<StationArchiveLine> &picks)
{
    auto dmin = std::numeric_limits<double>::max();
    for (const auto &pick : picks)
    {
        if (pick.haveEpicentralDistance())
        {
            dmin = std::min(dmin, pick.getEpicentralDistance());
        }
    }
    if (dmin == std::numeric_limits<double>::max()){return -1;}
    return dmin;
}

}
class EventSummary::EventSummaryImpl
{
public:
    EventSummaryLine mHeader;
    std::vector<StationArchiveLine> mPicks;
};

/// C'tor
EventSummary::EventSummary() :
    pImpl(std::make_unique<EventSummaryImpl>())
{
}

/// Copy c'tor
EventSummary::EventSummary(const EventSummary &summary)
{
    *this = summary;
}

/// Move c'tor
EventSummary::EventSummary(EventSummary &&summary) noexcept
{
    *this = std::move(summary);
}

/// Copy assignment
EventSummary& EventSummary::operator=(const EventSummary &summary)
{
    if (&summary == this){return *this;}
    pImpl = std::make_unique<EventSummaryImpl> (*summary.pImpl);
    return *this;
}

/// Move assignment
EventSummary& EventSummary::operator=(EventSummary &&summary) noexcept
{
    if (&summary == this){return *this;}
    pImpl = std::move(summary.pImpl);
    return *this;
}

/// Access pick
StationArchiveLine& EventSummary::operator[](size_t i)
{
    if (i >= pImpl->mPicks.size())
    {
        throw std::invalid_argument("i: " + std::to_string(i)
                                  + " must be in range [0,"
                                  + std::to_string(getNumberOfPicks() - 1)
                                  + "]");
    }
    return pImpl->mPicks[i];
}

/// Access a pick
const StationArchiveLine& EventSummary::operator[](size_t i) const
{
    if (i >= pImpl->mPicks.size())
    {
        throw std::invalid_argument("i: " + std::to_string(i)
                                        + " must be in range [0,"
                                        + std::to_string(getNumberOfPicks() - 1)
                                        + "]");
    }
    return pImpl->mPicks[i];
}

/// Destructor
EventSummary::~EventSummary() = default;

/// Reset the class
void EventSummary::clear() noexcept
{
    pImpl->mHeader.clear();
    pImpl->mPicks.clear();
}

/// Gets number of picks
int EventSummary::getNumberOfPicks() const noexcept
{
    return static_cast<int> (pImpl->mPicks.size());
}

/// Clears the picks
void EventSummary::clearPicks() noexcept
{
    pImpl->mPicks.clear();
}

/// Adds a p pick
void EventSummary::addPPick(const StationArchiveLine &pick)
{
    if (!pick.havePPickTime())
    {
        throw std::invalid_argument("P pick time not set");
    }
    pImpl->mPicks.push_back(pick);
    // Update internal information
    auto nfm = getNumberOfPolarities(pImpl->mPicks);
    pImpl->mHeader.setNumberOfFirstMotions(nfm);
    auto azGap = getAzimuthalGap(pImpl->mPicks);
    if (azGap >= 0 && azGap < 360){pImpl->mHeader.setAzimuthalGap(azGap);}
    auto dmin = getSmallestDistance(pImpl->mPicks);
    if (dmin >= 0){pImpl->mHeader.setDistanceToClosestStation(dmin);}
}

/// Adds an s pick
void EventSummary::addSPick(const StationArchiveLine &pick)
{
    if (!pick.haveSPickTime())
    {
        throw std::invalid_argument("S pick time not set");
    }
    pImpl->mPicks.push_back(pick);
    auto azGap = getAzimuthalGap(pImpl->mPicks);
    if (azGap >= 0 && azGap < 360){pImpl->mHeader.setAzimuthalGap(azGap);}
    auto dmin = getSmallestDistance(pImpl->mPicks);
    if (dmin >= 0){pImpl->mHeader.setDistanceToClosestStation(dmin);}
}

/// Unpacks
void EventSummary::unpackString(const std::vector<std::string> &lines)
{
    clear();
    if (lines.empty())
    {
        throw std::invalid_argument("There must be at least 1 line to parse");
    }
    pImpl->mHeader.unpackString(lines[0]);
    for (int i=1; i<static_cast<int> (lines.size()); ++i)
    {
        // Unpack the pick information
        StationArchiveLine pick;
        try
        {
            pick.unpackString(lines[i]);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error unpacking pick: " << std::to_string(i)
                      << std::endl << e.what() << std::endl
                      << "lines = " << lines[i] << std::endl;
            continue;
       } 
       // Add it
       try
       {
            if (pick.havePRemark()) //PickTime())
            {
                addPPick(pick);
            }
            else
            {
                addSPick(pick);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error adding pick: " << std::to_string(i)
                      << std::endl << e.what() << std::endl
                      << "lines = " << lines[i] << std::endl;
        }
    }
}

/// Sets the event information
void EventSummary::setEventInformation(const EventSummaryLine &eventSummary)
{
    pImpl->mHeader = eventSummary;
    auto nfm = getNumberOfPolarities(pImpl->mPicks);
    pImpl->mHeader.setNumberOfFirstMotions(nfm);
    auto azGap = getAzimuthalGap(pImpl->mPicks);
    if (azGap >= 0 && azGap < 360){pImpl->mHeader.setAzimuthalGap(azGap);}
    auto dmin = getSmallestDistance(pImpl->mPicks);
    if (dmin >= 0){pImpl->mHeader.setDistanceToClosestStation(dmin);}
}

/// Gets the event information
EventSummaryLine EventSummary::getEventInformation() const
{
    return pImpl->mHeader;
}

/// Packs a string
std::string EventSummary::packString() const
{
    std::string result;
    result = pImpl->mHeader.packString() + "\n";
    for (const auto &pick : pImpl->mPicks)
    {
        result.append(pick.packString() + "\n");
    }
    return result;
}
