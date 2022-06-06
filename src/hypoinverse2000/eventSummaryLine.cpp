#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#ifndef DNDEBUG
#include <cassert>
#endif
#include "sff/hypoinverse2000/eventSummaryLine.hpp"
#include "sff/utilities/time.hpp"
#include "private/hypoinverse2000.hpp"

using namespace SFF::HypoInverse2000;

///--------------------------------------------------------------------------///
///                            Begin implementation                          ///
///--------------------------------------------------------------------------///
class EventSummaryLine::EventSummaryLineImpl
{
public:
    void clear()
    {
        mOriginTime.clear();

        mLatitude = 0;
        mLongitude = 0;
        mDepth = 0;
        mDistanceToClosestStation =-1;
        mAzimuthalGap = 0;
        mWeightedResiduals =-1;
        mSWeightedResiduals =-1;
        mTravelTimeRMS =-1;
        mEventIdentifier = 0;
        mPreferredMagnitude = 0;
        mNumberOfFirstMotions = 0;
        mHavePreferredMagnitudeLabel = ' ';

        mHaveOriginTime = false;
        mHaveLatitude = false;
        mHaveLongitude = false;
        mHaveDepth = false;
        mHaveAzimuthalGap = false;
        mHavePreferredMagnitude = false;
        mHaveEventIdentifier = false;
    }

    SFF::Utilities::Time mOriginTime;
    double mLatitude = 0;
    double mLongitude = 0;
    double mDepth = 0;
    double mDistanceToClosestStation =-1;
    double mAzimuthalGap = 0;
    double mPreferredMagnitude = 0;
    double mTravelTimeRMS = -1;
    uint64_t mEventIdentifier = 0;
    int mWeightedResiduals =-1;
    int mSWeightedResiduals =-1;
    int mNumberOfFirstMotions =-1;
    char mHavePreferredMagnitudeLabel = ' ';
    bool mHaveOriginTime = false;
    bool mHaveLatitude = false;
    bool mHaveLongitude = false;
    bool mHaveDepth = false;
    bool mHaveAzimuthalGap = false;
    bool mHavePreferredMagnitude = false;
    bool mHaveEventIdentifier = false;
};

/// C'tor
EventSummaryLine::EventSummaryLine() :
    pImpl(std::make_unique<EventSummaryLineImpl> ())
{
}

/// Copy c'tor
EventSummaryLine::EventSummaryLine(const EventSummaryLine &summary)
{
    *this = summary;
}

[[maybe_unused]] /// Move c'tor
EventSummaryLine::EventSummaryLine(EventSummaryLine &&summary) noexcept
{
    *this = std::move(summary);
}

/// Destructor
EventSummaryLine::~EventSummaryLine() = default;

/// Clears the class
void EventSummaryLine::clear() noexcept
{
    pImpl->clear();
}

/// Copy assignment operator
EventSummaryLine& EventSummaryLine::operator=(const EventSummaryLine &summary)
{
    if (&summary == this){return *this;}
    pImpl = std::make_unique<EventSummaryLineImpl> (*summary.pImpl);
    return *this;
}

/// Move assignment operator
EventSummaryLine&
EventSummaryLine::operator=(EventSummaryLine &&summary) noexcept
{
    if (&summary == this){return *this;}
    pImpl = std::move(summary.pImpl);
    return *this;
}

/// Unpacks a header line string
void EventSummaryLine::unpackString(const std::string &line)
{
    EventSummaryLine result;
    // Nothing to do
    if (line.empty())
    {
        *this = result;
        return;
    }
    auto headerPtr = line.c_str();
    auto lenos = line.size();
    // Unpack origin time
    SFF::Utilities::Time originTime;
    auto year = unpackIntPair(0, 4, headerPtr, lenos);
    if (year.first){originTime.setYear(year.second);}
    auto month = unpackIntPair(4, 6, headerPtr, lenos);
    auto dayOfMonth = unpackIntPair(6, 8, headerPtr, lenos);
    if (month.first && dayOfMonth.first)
    {
        int mTemp = month.second;
        int dTemp = dayOfMonth.second;
        originTime.setMonthAndDay(std::pair<int, int> (mTemp, dTemp));
    }
    //if (month.first){originTime.setMonth(month.second);}
    //auto dayOfMonth = unpackIntPair(6, 8, headerPtr, lenos);
    //if (dayOfMonth.first){originTime.setDayOfMonth(dayOfMonth.second);}
    auto hour = unpackIntPair(8, 10, headerPtr, lenos);
    if (hour.first){originTime.setHour(hour.second);}
    auto minute = unpackIntPair(10, 12, headerPtr, lenos);
    if (minute.first){originTime.setMinute(minute.second);}
    auto second = unpackIntPair(12, 14, headerPtr, lenos);
    if (second.first){originTime.setSecond(second.second);}
    auto microSecond = unpackIntPair(14, 16, headerPtr, lenos);
    if (microSecond.first)
    {
        microSecond.second = microSecond.second*10000;
        originTime.setMicroSecond(microSecond.second);
    }
    if (year.first && month.first && dayOfMonth.first &&
        hour.first && second.first && microSecond.first)
    {
        result.setOriginTime(originTime);
    }
    // Unpack the latitude
    auto latDegrees = unpackIntPair(16, 18, headerPtr, lenos);
    auto lSouth = unpackCharPair(18, headerPtr, lenos);
    //auto latMinutes = unpackIntPair(19, 21, headerPtr, lenos);
    //auto latMinutesFrac = unpackIntPair(21, 23, headerPtr, lenos);
    auto latFracMinutes = unpackDoublePair(19, 23, 2, headerPtr, lenos);
    if (latDegrees.first && latFracMinutes.first) //latMinutes.first && latMinutesFrac.first)
    {
        auto latitude = latDegrees.second
                      + latFracMinutes.second/60;
//                      + static_cast<double> (latMinutes.second)/60.
//                      + static_cast<double> (latMinutesFrac.second)/(60.*100.);
        if (lSouth.first)
        {
            if (lSouth.second == 'S'){latitude = -latitude;}
        }
        try
        {
            result.setLatitude(latitude);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Latitude is invalid: "
                      << std::string(e.what()) << std::endl;
        }
    }
    // Unpack the longitude
    auto lonDegrees = unpackIntPair(23, 26, headerPtr, lenos);
    auto lEast = unpackCharPair(26, headerPtr, lenos);
    //auto lonMinutes = unpackIntPair(27, 29, headerPtr, lenos);
    //auto lonMinutesFrac = unpackIntPair(29, 31, headerPtr, lenos);
    auto lonFracMinutes = unpackDoublePair(27, 31, 2, headerPtr, lenos);
    if (lonDegrees.first && lonFracMinutes.first) //lonMinutes.first && lonMinutesFrac.first)
    {
        auto longitude =-lonDegrees.second
                       - lonFracMinutes.second/60;
//                       - static_cast<double> (lonMinutes.second)/60.
//                       - static_cast<double> (lonMinutesFrac.second)/(60.*100.);
        if (lEast.first)
        {
            if (lEast.second == 'E'){longitude = -longitude;}
        }
        try
        {
            result.setLongitude(longitude);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Longitude is invalid: "
                      << std::string(e.what()) << std::endl;
        }
    }
    // Depth
    auto depth = unpackDoublePair(31, 36, 3, headerPtr, lenos);
    if (depth.first){result.setDepth(depth.second);}
    // Quality metrics
    auto nWeightedResiduals = unpackIntPair(39, 42, headerPtr, lenos);
    if (nWeightedResiduals.first && nWeightedResiduals.second >= 0)
    {
        result.setNumberOfWeightedResiduals(nWeightedResiduals.second);
    }
    auto azimuthalGap = unpackIntPair(42, 45, headerPtr, lenos);
    if (azimuthalGap.first &&
        azimuthalGap.second >= 0 && azimuthalGap.second < 360)
    {
        result.setAzimuthalGap(azimuthalGap.second);
    }
    auto distanceToClosestStation = unpackIntPair(45, 48, headerPtr, lenos);
    if (distanceToClosestStation.first && distanceToClosestStation.second >= 0)
    {
        result.setDistanceToClosestStation(distanceToClosestStation.second);
    }
    auto rms = unpackDoublePair(48, 52, 2, headerPtr, lenos);
    if (rms.first && rms.second >= 0)
    {
        result.setResidualTravelTimeRMS(rms.second);
    }

    auto nSWeightedResiduals = unpackIntPair(82, 85, headerPtr, lenos);
    if (nSWeightedResiduals.first && nSWeightedResiduals.second >= 0)
    {
        result.setNumberOfSWeightedResiduals(nSWeightedResiduals.second);
    }
    auto nFirstMotions = unpackIntPair(93, 96, headerPtr, lenos);
    if (nFirstMotions.first && nFirstMotions.second >= 0)
    {
        result.setNumberOfFirstMotions(nFirstMotions.second);
    }

    // Preferred magnitude
    auto prefMagLabel = unpackCharPair(146, headerPtr, lenos);
    if (prefMagLabel.first)
    {
        result.setPreferredMagnitudeLabel(prefMagLabel.second);
    }
    auto prefMag = unpackDoublePair(147, 150, 1, headerPtr, lenos);
    if (prefMag.first){result.setPreferredMagnitude(prefMag.second);}

    auto evid = unpackUInt64Pair(136, 146, headerPtr, lenos);
    if (evid.first){result.setEventIdentifier(evid.second);}

    // Finally copy the correct inputs to this
    *this = result;
}

/// Packs the class into a string
std::string EventSummaryLine::packString() const
{
    std::string result(164, ' ');
    if (haveOriginTime())
    {
        auto originTime = getOriginTime();
        setInteger(0, 4, originTime.getYear(), result);
        setInteger(4, 6, originTime.getMonth(), result);
        setInteger(6, 8, originTime.getDayOfMonth(), result);
        setInteger(8, 10, originTime.getHour(), result);
        setInteger(10, 12, originTime.getMinute(), result);
        setInteger(12, 14, originTime.getSecond(), result);
        setInteger(14, 16, originTime.getMicroSecond()/10000, result);
    }
    if (haveLatitude())
    {
        auto lat = getLatitude();
        auto latWhole = static_cast<int> (lat);
        setInteger(16, 18, latWhole, result, false);
        if (lat < 0){result[18] = 'S';}
        auto latFrac = (lat - latWhole)*60.;
        setInteger(19, 23, static_cast<int> (std::round(latFrac*100)),
                result, false);
    }
    if (haveLongitude())
    {
        auto lon = getLongitude();
        if (lon > 180){lon = lon - 360;}
        auto lonWhole = static_cast<int> (lon);
        setInteger(23, 26, std::abs(lonWhole), result, false);
        if (lonWhole > 0){result[26] = 'E';}
        auto lonFrac = (std::abs(lon) - std::abs(lonWhole))*60.;
        setInteger(27, 31,static_cast<int> (std::round(lonFrac*100)),
                result, false);
    }
    if (haveDepth())
    {
        setInteger(31, 36, static_cast<int> (std::round(getDepth()*100)),
                   result, false);
    }
    if (haveNumberOfWeightedResiduals())
    {
        setInteger(39, 42, getNumberOfWeightedResiduals(), result, false);
    }
    if (haveAzimuthalGap())
    {
        setInteger(42, 45, static_cast<int> (std::round(getAzimuthalGap())),
                   result, false);
    }
    if (haveDistanceToClosestStation())
    {
        setInteger(45, 48,
                   static_cast<int> (std::round(getDistanceToClosestStation())),
                   result, false);
    }
    if (haveEventIdentifier())
    {
        setInteger(136, 146, getEventIdentifier(), result, false);
    }
    if (haveResidualTravelTimeRMS())
    {
        setInteger(48, 52,
                   static_cast<int> (std::round(getResidualTravelTimeRMS()*100)),
                   result, false);
    }
    if (haveNumberOfSWeightedResiduals())
    {
        setInteger(82, 85, getNumberOfSWeightedResiduals(), result, false);
    }
    if (haveNumberOfFirstMotions())
    {
        setInteger(93, 96, getNumberOfFirstMotions(), result, false);
    }
    if (havePreferredMagnitudeLabel())
    {
        result[146] = getPreferredMagnitudeLabel();
    }
    if (havePreferredMagnitude())
    {
        setInteger(147, 150,
             static_cast<int> (std::round(getPreferredMagnitude()*100)),
                result, false);
    }
    return result;
}
/// Origin time
void EventSummaryLine::setOriginTime(const SFF::Utilities::Time &originTime) noexcept
{
    pImpl->mOriginTime = originTime;
    pImpl->mHaveOriginTime = true;
}

SFF::Utilities::Time EventSummaryLine::getOriginTime() const
{
    if (!haveOriginTime()){throw std::runtime_error("Origin time not set");}
    return pImpl->mOriginTime;
}

bool EventSummaryLine::haveOriginTime() const noexcept
{
    return pImpl->mHaveOriginTime;
}

/// Latitude
void EventSummaryLine::setLatitude(const double latitude)
{
    if (latitude < -90 || latitude > 90)
    {
        throw std::invalid_argument("latitude" + std::to_string(latitude)
                                   + " must be in range [-90,90]");
    }
    pImpl->mLatitude = latitude;
    pImpl->mHaveLatitude = true;
}

double EventSummaryLine::getLatitude() const
{
    if (!haveLatitude()){throw std::runtime_error("Latitude not set");}
    return pImpl->mLatitude;
}

bool EventSummaryLine::haveLatitude() const noexcept
{
    return pImpl->mHaveLatitude;
}

/// Longitude
void EventSummaryLine::setLongitude(const double longitude)
{
    if (longitude < -540 || longitude >= 540)
    {
        throw std::invalid_argument("longitude" + std::to_string(longitude)
                                  + " must be in range [-540,540)");
    }
    pImpl->mLongitude = longitude;
    while (pImpl->mLongitude < 0)
    {
        pImpl->mLongitude = pImpl->mLongitude + 360;
    }
    while (pImpl->mLongitude >= 360)
    {
        pImpl->mLongitude = pImpl->mLongitude - 360;
    }
    pImpl->mHaveLongitude = true;
}

double EventSummaryLine::getLongitude() const
{
    if (!haveLongitude()){throw std::runtime_error("Longitude not set");}
    return pImpl->mLongitude;
}

bool EventSummaryLine::haveLongitude() const noexcept
{
    return pImpl->mHaveLongitude;
}

/// Depth
void EventSummaryLine::setDepth(const double depth) noexcept
{
    pImpl->mDepth = depth;
    pImpl->mHaveDepth = true;
}

double EventSummaryLine::getDepth() const
{
    if (!haveDepth()){throw std::runtime_error("Depth not set");}
    return pImpl->mDepth;
}

bool EventSummaryLine::haveDepth() const noexcept
{
    return pImpl->mHaveDepth;
}

/// Weighted residuals
void EventSummaryLine::setNumberOfWeightedResiduals(const int nResiduals)
{
    if (nResiduals < 0)
    {
        throw std::invalid_argument("nResiduals cannot be negative");
    }
    pImpl->mWeightedResiduals = nResiduals;
}

int EventSummaryLine::getNumberOfWeightedResiduals() const
{
    if (!haveNumberOfWeightedResiduals())
    {
        throw std::runtime_error("Number of weighted residuals not set");
    }
    return pImpl->mWeightedResiduals;
}

bool EventSummaryLine::haveNumberOfWeightedResiduals() const noexcept
{
    return pImpl->mWeightedResiduals >= 0;
}

void EventSummaryLine::setNumberOfSWeightedResiduals(const int nResiduals)
{
    if (nResiduals < 0)
    {
        throw std::invalid_argument("nResiduals cannot be negative");
    }
    pImpl->mSWeightedResiduals = nResiduals;
}

int EventSummaryLine::getNumberOfSWeightedResiduals() const
{
    if (!haveNumberOfSWeightedResiduals())
    {
        throw std::runtime_error("Number of weighted residuals not set");
    }
    return pImpl->mSWeightedResiduals;
}

bool EventSummaryLine::haveNumberOfSWeightedResiduals() const noexcept
{
    return pImpl->mSWeightedResiduals >= 0;
}

/// Azimuthal gap
void EventSummaryLine::setAzimuthalGap(const double gap)
{
    if (gap < 0 || gap >= 360)
    {
        throw std::invalid_argument("gap = " + std::to_string(gap)
                                  + " must be in range [0,360)");
    }
    pImpl->mHaveAzimuthalGap = true;
    pImpl->mAzimuthalGap = gap;
}

double EventSummaryLine::getAzimuthalGap() const
{
    if (!haveAzimuthalGap()){throw std::runtime_error("Gap not set");}
    return pImpl->mAzimuthalGap;
}

bool EventSummaryLine::haveAzimuthalGap() const noexcept
{
    return pImpl->mHaveAzimuthalGap;
}

/// RMS
void EventSummaryLine::setResidualTravelTimeRMS(const double rms)
{
    if (rms < 0)
    {
        throw std::invalid_argument("rms = " + std::to_string(rms)
                                  + " must be positive");
    }
    pImpl->mTravelTimeRMS = rms;
}

double EventSummaryLine::getResidualTravelTimeRMS() const
{
    if (!haveResidualTravelTimeRMS())
    {
        throw std::runtime_error("RMS not set set");
    }
    return pImpl->mTravelTimeRMS;
}

bool EventSummaryLine::haveResidualTravelTimeRMS() const noexcept
{
    return pImpl->mTravelTimeRMS >= 0;
}

/// Preferred magnitude
void EventSummaryLine::setPreferredMagnitude(const double magnitude) noexcept
{
    pImpl->mHavePreferredMagnitude = true;
    pImpl->mPreferredMagnitude = magnitude;
}

double EventSummaryLine::getPreferredMagnitude() const
{
    if (!havePreferredMagnitude())
    {
        throw std::runtime_error("Magnitude not set");
    }
    return pImpl->mPreferredMagnitude;
}

bool EventSummaryLine::havePreferredMagnitude() const noexcept
{
    return pImpl->mHavePreferredMagnitude;
}

/// First motions
void EventSummaryLine::setNumberOfFirstMotions(const int nFirstMotions)
{
    if (nFirstMotions < 0)
    {
        throw std::invalid_argument("nFirstMotions = "
                                  + std::to_string(nFirstMotions)
                                  + " must be positive");
    }
    pImpl->mNumberOfFirstMotions = nFirstMotions;
}
int EventSummaryLine::getNumberOfFirstMotions() const
{
    if (!haveNumberOfFirstMotions())
    {
        throw std::runtime_error("Number of first motions not set");
    }
    return pImpl->mNumberOfFirstMotions;
}

bool EventSummaryLine::haveNumberOfFirstMotions() const noexcept
{
    return pImpl->mNumberOfFirstMotions >= 0;
}

/// Preferred magnitude label
void EventSummaryLine::setPreferredMagnitudeLabel(const char label)
{
    if (isblank(label))
    {
        throw std::invalid_argument("label cannot be blank");
    }
    pImpl->mHavePreferredMagnitudeLabel = label;
}

char EventSummaryLine::getPreferredMagnitudeLabel() const
{
    if (!havePreferredMagnitudeLabel())
    {
        throw std::runtime_error("Preferred magnitude label not yet set");
    }
    return pImpl->mHavePreferredMagnitudeLabel;
}

bool EventSummaryLine::havePreferredMagnitudeLabel() const noexcept
{
    return !isblank(pImpl->mHavePreferredMagnitudeLabel);
}

/// Event identifier
void EventSummaryLine::setEventIdentifier(const uint64_t evid) noexcept
{
    pImpl->mHaveEventIdentifier = true;
    pImpl->mEventIdentifier = evid;
}

uint64_t EventSummaryLine::getEventIdentifier() const
{
    if (!haveEventIdentifier()){throw std::runtime_error("evid not yet set");}
    return pImpl->mEventIdentifier;
}

bool EventSummaryLine::haveEventIdentifier() const noexcept
{
    return pImpl->mHaveEventIdentifier;
}

/// Distance to closest station
void EventSummaryLine::setDistanceToClosestStation(const double dist)
{
    if (dist < 0)
    {
        throw std::invalid_argument("distance must be positive");
    }
    pImpl->mDistanceToClosestStation = dist;
}

double EventSummaryLine::getDistanceToClosestStation() const
{
    if (!haveDistanceToClosestStation())
    {
        throw std::runtime_error("Distance to closest station not set");
    }
    return pImpl->mDistanceToClosestStation;
}

bool EventSummaryLine::haveDistanceToClosestStation() const noexcept
{
    return pImpl->mDistanceToClosestStation >= 0;
}

/// Output
std::ostream&
SFF::HypoInverse2000::operator<<(std::ostream &os,
                                 const EventSummaryLine &event)
{
    return os << event.packString();
}
