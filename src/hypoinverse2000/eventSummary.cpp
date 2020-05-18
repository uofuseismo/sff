#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#ifndef DNDEBUG
#include <cassert>
#endif
#include "sff/hypoinverse2000/eventSummary.hpp"
#include "sff/utilities/time.hpp"

using namespace SFF::HypoInverse2000;

namespace
{

char unpackChar(const int i1, const char *stringPtr, const int maxLen)
{
    if (i1 >= maxLen){return '\0';}
    if (stringPtr[i1] == ' '){return '\0';}
    return stringPtr[i1];
}

std::pair<bool, char> unpackCharPair(const int i1, const char *stringPtr,
                                     const int maxLen)
{
    auto c = unpackChar(i1, stringPtr, maxLen);
    if (c == '\0')
    {
        return std::pair(false, c);
    }
    else
    {
        return std::pair(true, c);
    }
}

int unpackInt(const int i1, const int i2, const char *stringPtr,
              const int maxLen)
{
    if (i1 >= maxLen){return std::numeric_limits<int>::max();}
    char subString[8] = {"\0\0\0\0\0\0\0"};
    std::copy(stringPtr+i1,  stringPtr+std::min(i1 + maxLen, i2), subString);
    try
    {
        return std::stoi(subString);
    }
    catch (const std::exception &e)
    {
        return std::numeric_limits<int>::max();
    }
}

std::pair<bool, int> unpackIntPair(const int i1, const int i2,
                                   const char *stringPtr,
                                   const int maxLen)
{
    auto i = unpackInt(i1, i2, stringPtr, maxLen);
    return std::pair(i < std::numeric_limits<int>::max(), i);
}

double unpackDouble(const int i1, const int i2,
                    const int whole, const int decimal,
                    const char *stringPtr,
                    const int maxLen)
{
#ifndef DNDEBUG
    assert(i2 - i1 == whole + decimal);
#endif
    double result = std::numeric_limits<double>::max();
    auto j1 = i1;
    auto j2 = i1 + whole;
    auto i = unpackInt(j1, j2, stringPtr, maxLen);
    j1 = i1 + whole;
    j2 = i2;
    auto ifrac = unpackInt(j1, j2, stringPtr, maxLen);
    if (ifrac < std::numeric_limits<int>::max())
    {
        result = static_cast<double> (ifrac)/(std::pow(10, decimal));
        if (i < std::numeric_limits<int>::max())
        {
            result = result + i;
        }
    }
    return result;
}

std::pair<bool, double> unpackDoublePair(const int i1, const int i2,
                                         const int whole, const int decimal,
                                         const char *stringPtr,
                                         const int maxLen)
{
    auto d = unpackDouble(i1, i2, whole, decimal, stringPtr, maxLen);
    return std::pair(d < std::numeric_limits<int>::max(), d);
}

}

///--------------------------------------------------------------------------///
///                            Begin implementation                          ///
///--------------------------------------------------------------------------///
class EventSummary::EventSummaryImpl
{
public:
    void clear()
    {
        mOriginTime.clear();

        mLatitude = 0;
        mLongitude = 0;
        mDepth = 0;
        mAzimuthalGap = 0;
        mWeightedResiduals =-1;
        mTravelTimeRMS =-1;
        mPreferredMagnitude = 0;

        mHaveOriginTime = false;
        mHaveLatitude = false;
        mHaveLongitude = false;
        mHaveDepth = false;
        mHaveAzimuthalGap = false;
        mHavePreferredMagnitude = false;
    }

    SFF::Utilities::Time mOriginTime;
    double mLatitude = 0;
    double mLongitude = 0;
    double mDepth = 0;
    double mAzimuthalGap = 0;
    double mPreferredMagnitude = 0;
    double mTravelTimeRMS = -1;
    int mWeightedResiduals =-1;
    bool mHaveOriginTime = false;
    bool mHaveLatitude = false;
    bool mHaveLongitude = false;
    bool mHaveDepth = false;
    bool mHaveAzimuthalGap = false;
    bool mHavePreferredMagnitude = false;
};

/// C'tor
EventSummary::EventSummary() :
    pImpl(std::make_unique<EventSummaryImpl> ())
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

/// Destructor
EventSummary::~EventSummary() = default;

/// Clears the class
void EventSummary::clear() noexcept
{
    pImpl->clear();
}

/// Copy assignment operator
EventSummary& EventSummary::operator=(const EventSummary &summary)
{
    if (&summary == this){return *this;}
    pImpl = std::make_unique<EventSummaryImpl> (*summary.pImpl);
    return *this;
}

/// Move assignment operator
EventSummary& EventSummary::operator=(EventSummary &&summary) noexcept
{
    if (&summary == this){return *this;}
    pImpl = std::move(summary.pImpl);
    return *this;
}

/// Unpacks a header line string
void EventSummary::unpackString(const std::string &line)
{
    EventSummary result;
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
    if (month.first){originTime.setMonth(month.second);}
    auto dayOfMonth = unpackIntPair(6, 8, headerPtr, lenos);
    if (dayOfMonth.first){originTime.setDayOfMonth(dayOfMonth.second);}
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
    auto latMinutes = unpackIntPair(19, 21, headerPtr, lenos);
    auto latMinutesFrac = unpackIntPair(21, 23, headerPtr, lenos);
    if (latDegrees.first && latMinutes.first && latMinutesFrac.first)
    {
        auto latitude = latDegrees.second
                      + static_cast<double> (latMinutes.second)/60.
                      + static_cast<double> (latMinutesFrac.second)/(60.*100.);
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
    auto lonMinutes = unpackIntPair(27, 29, headerPtr, lenos);
    auto lonMinutesFrac = unpackIntPair(29, 31, headerPtr, lenos);
    if (lonDegrees.first && lonMinutes.first && lonMinutesFrac.first)
    {
        auto longitude =-lonDegrees.second
                       - static_cast<double> (lonMinutes.second)/60.
                       - static_cast<double> (lonMinutesFrac.second)/(60.*100.);
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
    auto depth = unpackDoublePair(31, 36, 3, 2, headerPtr, lenos);
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
    auto rms = unpackDoublePair(48, 52, 2, 2, headerPtr, lenos);
    if (rms.first && rms.second >= 0)
    {
        result.setResidualTravelTimeRMS(rms.second);
    }
    // Preferred magnitude
    auto prefMag = unpackDoublePair(147, 150, 1, 2, headerPtr, lenos);
    if (prefMag.first){result.setPreferredMagnitude(prefMag.second);}
    // Finally copy the correct inputs to this
    *this = result;
}

/// Origin time
void EventSummary::setOriginTime(const SFF::Utilities::Time &originTime) noexcept
{
    pImpl->mOriginTime = originTime;
    pImpl->mHaveOriginTime = true;
}

SFF::Utilities::Time EventSummary::getOriginTime() const
{
    if (!haveOriginTime()){throw std::runtime_error("Origin time not set");}
    return pImpl->mOriginTime;
}

bool EventSummary::haveOriginTime() const noexcept
{
    return pImpl->mHaveOriginTime;
}

/// Latitude
void EventSummary::setLatitude(const double latitude)
{
    if (latitude < -90 || latitude > 90)
    {
        throw std::invalid_argument("latitude" + std::to_string(latitude)
                                   + " must be in range [-90,90]");
    }
    pImpl->mLatitude = latitude;
    pImpl->mHaveLatitude = true;
}

double EventSummary::getLatitude() const
{
    if (!haveLatitude()){throw std::runtime_error("Latitude not set");}
    return pImpl->mLatitude;
}

bool EventSummary::haveLatitude() const noexcept
{
    return pImpl->mHaveLatitude;
}

/// Longitude
void EventSummary::setLongitude(const double longitude)
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

double EventSummary::getLongitude() const
{
    if (!haveLongitude()){throw std::runtime_error("Longitude not set");}
    return pImpl->mLongitude;
}

bool EventSummary::haveLongitude() const noexcept
{
    return pImpl->mHaveLongitude;
}

/// Depth
void EventSummary::setDepth(const double depth) noexcept
{
    pImpl->mDepth = depth;
    pImpl->mHaveDepth = true;
}

double EventSummary::getDepth() const
{
    if (!haveDepth()){throw std::runtime_error("Depth not set");}
    return pImpl->mDepth;
}

bool EventSummary::haveDepth() const noexcept
{
    return pImpl->mHaveDepth;
}

/// Weighted residuals
void EventSummary::setNumberOfWeightedResiduals(int nResiduals)
{
    if (nResiduals < 0)
    {
        throw std::invalid_argument("nResiduals cannot be negative");
    }
    pImpl->mWeightedResiduals = nResiduals;
}

int EventSummary::getNumberOfWeightedResiduals() const
{
    if (!haveNumberOfWeightedResiduals())
    {
        throw std::runtime_error("Number of weighted residuals not set");
    }
    return pImpl->mWeightedResiduals;
}

bool EventSummary::haveNumberOfWeightedResiduals() const noexcept
{
    return pImpl->mWeightedResiduals >= 0;
}

/// Azimuthal gap
void EventSummary::setAzimuthalGap(double gap)
{
    if (gap < 0 || gap >= 360)
    {
        throw std::invalid_argument("gap = " + std::to_string(gap)
                                  + " must be in range [0,360)");
    }
    pImpl->mHaveAzimuthalGap = true;
    pImpl->mAzimuthalGap = gap;
}

double EventSummary::getAzimuthalGap() const
{
    if (!haveAzimuthalGap()){throw std::runtime_error("Gap not set");}
    return pImpl->mAzimuthalGap;
}

bool EventSummary::haveAzimuthalGap() const noexcept
{
    return pImpl->mHaveAzimuthalGap;
}

/// RMS
void EventSummary::setResidualTravelTimeRMS(double rms)
{
    if (rms < 0)
    {
        throw std::invalid_argument("rms = " + std::to_string(rms)
                                  + " must be positive");
    }
    pImpl->mTravelTimeRMS = rms;
}

double EventSummary::getResidualTravelTimeRMS() const
{
    if (!haveResidualTravelTimeRMS())
    {
        throw std::runtime_error("RMS not set set");
    }
    return pImpl->mTravelTimeRMS;
}

bool EventSummary::haveResidualTravelTimeRMS() const noexcept
{
    return pImpl->mTravelTimeRMS >= 0;
}

/// Preferred magnitude
void EventSummary::setPreferredMagnitude(double magnitude) noexcept
{
    pImpl->mHavePreferredMagnitude = true;
    pImpl->mPreferredMagnitude = magnitude;
}

double EventSummary::getPreferredMagnitude() const
{
    if (!havePreferredMagnitude())
    {
        throw std::runtime_error("Magnitude not set");
    }
    return pImpl->mPreferredMagnitude;
}

bool EventSummary::havePreferredMagnitude() const noexcept
{
    return pImpl->mHavePreferredMagnitude;
}