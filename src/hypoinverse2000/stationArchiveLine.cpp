#include <iostream>
#include <limits>
#include <array>
#include <cstdint>
#ifndef DNDEBUG
#include <cassert>
#endif
#include "sff/hypoinverse2000/stationArchiveLine.hpp"
#include "sff/utilities/time.hpp"
#include "private/hypoinverse2000.hpp"

using namespace SFF::HypoInverse2000;

class StationArchiveLine::StationArchiveLineImpl
{
public:
    void clear() noexcept
    {
        mPPick.clear();
        mSPick.clear();
        mNetwork.clear();
        mStation.clear();
        mChannel.clear();
        mLocationCode.clear();
        mPRemark.clear();
        mSRemark.clear();
        mPFirstMotion = ' ';
        mAmplitudeMagnitudeLabel = ' ';
        mDurationMagnitudeLabel = ' ';
        mDataSourceCode = ' ';
        mPResidual = 0;
        mSResidual = 0;
        mPWeightUsed =-1;
        mSWeightUsed =-1;
        mPDelayTime = 0;
        mSDelayTime = 0;
        mEpicentralDistance =-1;
        mTakeOffAngle =-1;
        mAzimuth =-1;
        mDurationMagnitude = 0;
        mAmplitudeMagnitude = 0;
        mAmplitude =-1;
        mPeriodOfAmplitudeMeasurement =-1;
        mCodaDuration =-1;
        mPImportance =-1;
        mSImportance =-1;
        mPWeightCode =-1;
        mSWeightCode =-1;
        mDurationMagnitudeWeightCode =-1;
        mAmplitudeMagnitudeWeightCode =-1;
        mAmplitudeUnits = AmplitudeUnits::PEAK_TO_PEAK;
        mHaveNetwork = false;
        mHaveStation = false;
        mHaveChannel = false;
        mHaveLocationCode = false;
        mHavePPick = false;
        mHaveSPick = false;
        mHavePFirstMotion = false;
        mHavePRemark = false;
        mHaveSRemark = false;
        mHavePDelayTime = false;
        mHaveSDelayTime = false;
        mHaveDurationMagnitude = false;
        mHaveAmplitudeMagnitude = false;
        mHaveAmplitudeUnits = false;
    }
    SFF::Utilities::Time mPPick;
    SFF::Utilities::Time mSPick;
    std::string mNetwork;
    std::string mStation;
    std::string mChannel;
    std::string mLocationCode;
    std::string mPRemark;
    std::string mSRemark;
    double mPResidual = 0;
    double mSResidual = 0;
    double mPWeightUsed =-1;
    double mSWeightUsed =-1;
    double mPDelayTime = 0;
    double mSDelayTime = 0;
    double mEpicentralDistance =-1;
    double mTakeOffAngle =-1;
    double mDurationMagnitude = 0;
    double mAmplitudeMagnitude = 0;
    double mPImportance =-1;
    double mSImportance =-1;
    double mAmplitude =-1;
    double mPeriodOfAmplitudeMeasurement =-1;
    double mCodaDuration =-1;
    double mAzimuth =-1;
    int mPWeightCode =-1;
    int mSWeightCode =-1;
    int mDurationMagnitudeWeightCode =-1;
    int mAmplitudeMagnitudeWeightCode =-1;
    AmplitudeUnits mAmplitudeUnits = AmplitudeUnits::PEAK_TO_PEAK;
    char mPFirstMotion = ' ';
    char mAmplitudeMagnitudeLabel = ' ';
    char mDurationMagnitudeLabel = ' ';
    char mDataSourceCode = ' ';
    bool mHaveNetwork = false;
    bool mHaveStation = false;
    bool mHaveChannel = false;
    bool mHaveLocationCode = false;
    bool mHavePPick = false;
    bool mHavePFirstMotion = false;
    bool mHavePResidual = false;
    bool mHavePRemark = false;
    bool mHaveSPick = false;
    bool mHaveSRemark = false;
    bool mHaveSResidual = false;
    bool mHavePDelayTime = false;
    bool mHaveSDelayTime = false;
    bool mHaveDurationMagnitude = false;
    bool mHaveAmplitudeMagnitude = false;
    bool mHaveAmplitudeUnits = false;
};

/// Constructor
StationArchiveLine::StationArchiveLine() :
    pImpl(std::make_unique<StationArchiveLineImpl> ())
{
}

/// Copy c'tor
[[maybe_unused]]
StationArchiveLine::StationArchiveLine(const StationArchiveLine &station)
{
    *this = station;
}

/// Move c'tor
[[maybe_unused]]
StationArchiveLine::StationArchiveLine(StationArchiveLine &&station) noexcept
{
    *this = std::move(station);
}

/// Copy assignment operator
StationArchiveLine&
StationArchiveLine::operator=(const StationArchiveLine &station)
{
    if (&station == this){return *this;}
    pImpl = std::make_unique<StationArchiveLineImpl> (*station.pImpl);
    return *this;
}

/// Move assignment operator
StationArchiveLine&
StationArchiveLine::operator=(StationArchiveLine &&station) noexcept
{
    if (&station == this){return *this;}
    pImpl = std::move(station.pImpl);
    return *this;
}

/// Destructor
StationArchiveLine::~StationArchiveLine() = default;

/// Clears the class
void StationArchiveLine::clear() noexcept
{
    pImpl->clear();
}

/// Unpacks a pick line
void StationArchiveLine::unpackString(const std::string &line)
{
    StationArchiveLine result;
    // Nothing to do
    if (line.empty())
    {
        *this = result;
        return;
    }
    auto linePtr = line.c_str();
    auto lenos = line.size();

    auto station = unpackStringPair(0, 5, linePtr, lenos);
    // Documentation says this should be left justified
    if (station.first)
    {
        rtrim(station.second);
        result.setStationName(station.second);
    }
    auto network = unpackStringPair(5, 7, linePtr, lenos);
    if (network.first){result.setNetworkName(network.second);}
    auto channel = unpackStringPair(9, 12, linePtr, lenos);
    if (channel.first){result.setChannelName(channel.second);}
    auto location = unpackStringPair(111, 113, linePtr, lenos);
    if (location.first){result.setLocationCode(location.second);}
    // Remarks
    auto pRemark = unpackStringPair(13, 15, linePtr, lenos);
    if (pRemark.first){result.setPRemark(pRemark.second);}
    auto sRemark = unpackStringPair(46, 48, linePtr, lenos);
    if (sRemark.first){result.setSRemark(sRemark.second);}
    auto pFirstMotion = unpackCharPair(15, linePtr, lenos);
    if (pFirstMotion.first && pFirstMotion.second != ' ')
    {
        result.setFirstMotion(pFirstMotion.second);
    }

    // P and S pick time
    SFF::Utilities::Time pickTime, pickTimeBase;
    auto year = unpackIntPair(17, 21, linePtr, lenos);
    auto month = unpackIntPair(21, 23, linePtr, lenos);
    auto dayOfMonth = unpackIntPair(23, 25, linePtr, lenos);
    auto hour = unpackIntPair(25, 27, linePtr, lenos);
    auto minute = unpackIntPair(27, 29, linePtr, lenos);
    //auto pSecond = unpackIntPair(29, 32, linePtr, lenos);
    //auto pMicroSecond = unpackIntPair(32, 34, linePtr, lenos);
    auto pDecimalSecond = unpackDoublePair(29, 34, 3, linePtr, lenos);
    if (year.first && month.first && dayOfMonth.first &&
        hour.first && minute.first)
    {
        pickTime.setYear(year.second);
        pickTime.setMonth(month.second);
        pickTime.setDayOfMonth(dayOfMonth.second);
        pickTime.setHour(hour.second);
        pickTime.setMinute(minute.second);
        pickTimeBase = pickTime;
    }
    if (year.first && month.first && dayOfMonth.first &&
        hour.first && minute.first && pDecimalSecond.first) //(pSecond.first || pMicroSecond.first))
    {
        // Sometimes arrivals have like 70 seconds which breaks things.
        pickTime = pickTime + pDecimalSecond.second;
        //double secondSign = +1;
        //if (pSecond.second < 0){secondSign =-1;}
        //         + secondSign*(std::abs(pSecond.second)
        //                     + pMicroSecond.second/100.);
        //std::cout << secondSign*(std::abs(pSecond.second) + pMicroSecond.second/100.) << "," << pDecimalSecond.second << std::endl;
/*
        int seconds = pSecond.second;
        int extraSeconds = (seconds/60)*60;
        seconds = seconds%60;
#ifndef DNDEBUG
        assert(extraSeconds + seconds == pSecond.second); 
#endif
        while (seconds > 60)
        {
            extraSeconds = extraSeconds + 60;
            seconds = seconds - 60;
        }

        pickTime.setSecond(seconds); //pSecond.second);
        pMicroSecond.second = pMicroSecond.second*10000;
        pickTime.setMicroSecond(pMicroSecond.second);
        pickTime = pickTime + extraSeconds;
*/
        result.setPPickTime(pickTime);
    }
    //auto sSecond = unpackIntPair(41, 44, linePtr, lenos);
    //auto sMicroSecond = unpackIntPair(44, 46, linePtr, lenos);
    auto sDecimalSecond = unpackDoublePair(41, 46, 3, linePtr, lenos);
    if (year.first && month.first && dayOfMonth.first &&
        hour.first && minute.first && sDecimalSecond.first) //(sSecond.first || sMicroSecond.first))
    {
        pickTime = pickTimeBase; // Incase there is a P and S time
        pickTime = pickTime + sDecimalSecond.second;
        //double secondSign = +1;
        //if (sSecond.second < 0){secondSign =-1;}
        //pickTime = pickTime
        //         + secondSign*(std::abs(sSecond.second)
        //                     + sMicroSecond.second/100.);
/*
        int seconds = sSecond.second;
        int extraSeconds = (seconds/60)*60;
        seconds = seconds%60;
#ifndef DNDEBUG
        assert(extraSeconds + seconds == sSecond.second);
#endif
        pickTime.setSecond(seconds); //sSecond.second);
        sMicroSecond.second = sMicroSecond.second*10000;
        pickTime.setMicroSecond(sMicroSecond.second);
        pickTime = pickTime + extraSeconds;
*/
        result.setSPickTime(pickTime);
    }
    if (result.havePRemark() && !result.havePPickTime())
    {
        std::cerr << "Failed to get P pick time from " << line << std::endl;
    }
    if (result.haveSRemark() && !result.haveSPickTime())
    {
        std::cerr << "Failed to get S pick time from " << line << std::endl;
    }
    // Weight code (I think UUSS or Jiggle has a bug.  These values are assigned
    // even when there is no corresponding pick).
    auto pWeightCode = unpackIntPair(16, 17, linePtr, lenos);
    if (pWeightCode.first && pWeightCode.second >= 0 && result.havePPickTime())
    {
        result.setPWeightCode(pWeightCode.second);
    }
    auto sWeightCode = unpackIntPair(49, 50, linePtr, lenos);
    if (sWeightCode.first && sWeightCode.second >= 0 && result.haveSPickTime())
    {
        result.setSWeightCode(sWeightCode.second);
    }
    // Residuals
    auto pResidual = unpackDoublePair(34, 38, 2, linePtr, lenos);
    if (pResidual.first){result.setPResidual(pResidual.second);}
    auto sResidual = unpackDoublePair(50, 54, 2, linePtr, lenos);
    if (sResidual.first){result.setSResidual(sResidual.second);}
    // Amplitude
    auto amplitude = unpackDoublePair(54, 61, 5, linePtr, lenos);
    if (amplitude.first && amplitude.second >= 0)
    {
        result.setAmplitude(amplitude.second);
    }
    auto ampUnitsCode = unpackIntPair(61, 63, linePtr, lenos);
    if (ampUnitsCode.first)
    {
        if (ampUnitsCode.second == 0)
        {
            result.setAmplitudeUnits(AmplitudeUnits::PEAK_TO_PEAK);
        }
        else if (ampUnitsCode.second == 1)
        {
            result.setAmplitudeUnits(AmplitudeUnits::ZERO_TO_PEAK);
        }
        else if (ampUnitsCode.second == 2)
        {
            result.setAmplitudeUnits(AmplitudeUnits::DIGITAL_COUNTS);
        }
    }
    // Weight used
    auto pWeightUsed = unpackDoublePair(38, 41, 1, linePtr, lenos);
    if (pWeightUsed.first && pWeightUsed.second >= 0)
    {
        result.setPWeightUsed(pWeightUsed.second);
    }
    auto sWeightUsed = unpackDoublePair(63, 66, 1, linePtr, lenos);
    if (sWeightUsed.first && sWeightUsed.second >= 0)
    {
        result.setSWeightUsed(sWeightUsed.second);
    }
    // Static corrections
    auto pDelayTime = unpackDoublePair(66, 70, 2, linePtr, lenos);
    if (pDelayTime.first){result.setPDelayTime(pDelayTime.second);}
    auto sDelayTime = unpackDoublePair(70, 74, 2, linePtr, lenos);
    if (sDelayTime.first){result.setSDelayTime(sDelayTime.second);}
    // Takeoff angle, azimuth, and epicentral distance
    auto distance = unpackDoublePair(74, 78, 3, linePtr, lenos);
    if (distance.first && distance.second >= 0)
    {
        result.setEpicentralDistance(distance.second);
    }
    auto angle = unpackIntPair(78, 81, linePtr, lenos);
    if (angle.first && angle.second >= 0 && angle.second <= 180)
    {
        result.setTakeOffAngle(angle.second);
    }
    auto azimuth = unpackIntPair(91, 94, linePtr, lenos);
    if (azimuth.first && azimuth.second >= 0 && azimuth.second <= 360)
    {
        result.setAzimuth(azimuth.second);
    }
    // Magnitudes
    auto durMag = unpackDoublePair(94, 97, 1, linePtr, lenos);
    if (durMag.first){result.setDurationMagnitude(durMag.second);}
    auto ampMag = unpackDoublePair(97, 100, 1, linePtr, lenos);
    if (ampMag.first){result.setAmplitudeMagnitude(ampMag.second);}
    auto durMagWeightCode = unpackIntPair(82, 83, linePtr, lenos);
    if (durMagWeightCode.first && durMagWeightCode.second >= 0)
    {
        result.setDurationMagnitudeWeightCode(durMagWeightCode.second);
    }
    auto ampMagWeightCode = unpackIntPair(81, 82, linePtr, lenos);
    if (ampMagWeightCode.first && ampMagWeightCode.second >= 0)
    {
        result.setAmplitudeMagnitudeWeightCode(ampMagWeightCode.second);
    }
    auto period = unpackDoublePair(83, 86, 1, linePtr, lenos);
    if (period.first && period.second > 0)
    {
        result.setPeriodOfAmplitudeMeasurement(period.second);
    }
    auto duration = unpackIntPair(87, 91, linePtr, lenos);
    if (duration.first && duration.second > 0)
    {
        result.setCodaDuration(duration.second);
    }
    auto durMagLabel = unpackCharPair(109, linePtr, lenos);
    if (durMagLabel.first && durMagLabel.second != ' ')
    {
        result.setDurationMagnitudeLabel(durMagLabel.second);
    }
    auto ampMagLabel = unpackCharPair(110, linePtr, lenos);
    if (ampMagLabel.first && ampMagLabel.second != ' ')
    {
        result.setAmplitudeMagnitudeLabel(ampMagLabel.second);
    }
    // Importance
    auto pImportance = unpackDoublePair(100, 104, 1, linePtr, lenos);
    if (pImportance.first && pImportance.second >= 0)
    {
        result.setPImportance(pImportance.second);
    }
    auto sImportance = unpackDoublePair(104, 108, 1, linePtr, lenos);
    if (sImportance.first && sImportance.second >= 0)
    {
        result.setSImportance(sImportance.second);
    }
    // Data source code
    auto dataSourceCode = unpackCharPair(108, linePtr, lenos);
    if (dataSourceCode.first && dataSourceCode.second != ' ')
    {
        result.setDataSourceCode(dataSourceCode.second);
    }
    // Finally copy result back
    *this = result;
}

/// Packs a hypo string
std::string StationArchiveLine::packString() const noexcept
{
    std::string result(113, ' ');
    // SNCL
    if (haveStationName()){setString(0, 5, getStationName(), result);}
    if (haveNetworkName()){setString(5, 7, getNetworkName(), result);}
    if (haveChannelName()){setString(9, 12, getChannelName(), result);}
    if (haveLocationCode()){setString(111, 113, getLocationCode(), result);}
    if (havePRemark())
    {
        auto remark = getPRemark();
        if (remark.size() == 1)
        { remark.push_back(' '); }
        setString(13, 15, remark, result);
    }
    if (haveSRemark())
    {
        auto remark = getSRemark();
        if (remark.size() == 1)
        { remark.push_back(' '); }
        setString(46, 48, remark, result);
    }
    if (haveFirstMotion()){result[15] = getFirstMotion();}
    // A little strange - but a 4 seems to be assigned to the P weight
    // when we have an S pick.  HypoInverse seems to hunt for this number
    // so may as well fill it.  Likewise, fill S with 0 which seems dangerous.
    int pWeightCode = 4;
    if (havePWeightCode()){pWeightCode = getPWeightCode();}
    setInteger(16, 17, pWeightCode, result);
    int sWeightCode = 0;
    if (haveSWeightCode()){sWeightCode = getSWeightCode();}
    setInteger(49, 50, sWeightCode, result);
    if (havePPickTime() || haveSPickTime())
    {
        // Sometimes both P and S picks are set.  Typically one of the picks
        // is filled with zeros.
        if (havePPickTime() && haveSPickTime())
        {
            auto p = getPPickTime();
            auto s = getSPickTime();
            if (p.getYear() != s.getYear() ||
                p.getJulianDay() != s.getJulianDay() ||
                p.getHour() != s.getHour() ||
                p.getMinute() != s.getMinute())
            {
                if ( (p.getSecond() != 0 && p.getMicroSecond() != 0) &&
                     (s.getSecond() != 0 && s.getMicroSecond() != 0) )
                {
                    std::cerr << "P and S pick defined - output may be buggy"
                              << std::endl;
                }
            }
        }
        SFF::Utilities::Time pickTime;
        if (havePPickTime())
        {
            pickTime = getPPickTime();
        }
        else
        {
            pickTime = getSPickTime();
        }
        setInteger(17, 21, pickTime.getYear(), result);
        setInteger(21, 23, pickTime.getMonth(), result);
        setInteger(23, 25, pickTime.getDayOfMonth(), result);
        setInteger(25, 27, pickTime.getHour(), result);
        setInteger(27, 29, pickTime.getMinute(), result);
        if (havePPickTime())
        {
            setInteger(30, 32, pickTime.getSecond(), result, false);
            setInteger(32, 34, pickTime.getMicroSecond() / 1000, result);
        }
        if (haveSPickTime())
        {
            if (havePPickTime()){pickTime = getSPickTime();}
            setInteger(42, 44, pickTime.getSecond(), result, false);
            setInteger(44, 46, pickTime.getMicroSecond() / 1000, result);
        }
    }
    if (havePResidual())
    {
        setInteger(34, 38, static_cast<int> (std::round(getPResidual() * 100)),
                   result, false);
    }
    if (havePWeightUsed())
    {
        setInteger(38, 41, static_cast<int> (std::round(getPWeightUsed() * 100)),
                   result, false);
    }
    if (haveSResidual())
    {
        setInteger(50, 54, static_cast<int> (std::round(getSResidual() * 100)),
                   result, false);
    }
    if (haveAmplitude())
    {
        setInteger(54, 61, static_cast<int> (std::round(getAmplitude() * 100)),
                   result, false);
    }
    if (haveAmplitudeUnits())
    {
        auto amplitudeUnits = static_cast<int> (getAmplitudeUnits());
        setInteger(61, 63, amplitudeUnits, result, false);
    }
    if (haveSWeightUsed())
    {
        setInteger(63, 66, static_cast<int> (std::round(getSWeightUsed()*100)),
                   result, false);
    }
    if (haveEpicentralDistance())
    {
        setInteger(74, 78, static_cast<int> (std::round(getEpicentralDistance()*10)),
                   result, false);
    }
    if (haveTakeOffAngle())
    {
        setInteger(78, 81, static_cast<int> (std::round(getTakeOffAngle())),
                   result, false);
    }
    if (haveAzimuth())
    {
        setInteger(91, 94, static_cast<int> (std::round(getAzimuth())),
                result, false);
    }
    if (havePDelayTime())
    {
        setInteger(66, 70, static_cast<int> (std::round(getPDelayTime()*100)),
                   result, false);
    }
    if (haveSDelayTime())
    {
        setInteger(70, 74, static_cast<int> (std::round(getSDelayTime()*100)),
                   result, false);
    }
    if (haveAmplitudeMagnitude())
    {
        setInteger(97, 100, static_cast<int> (std::round(getAmplitudeMagnitude()*100)),
                   result, false);
    }
    if (haveAmplitudeMagnitudeWeightCode())
    {
        setInteger(81, 82,  getAmplitudeMagnitudeWeightCode(), result);
    }
    if (haveDurationMagnitude())
    {
        setInteger(94, 97,
             static_cast<int> (std::round(getDurationMagnitude()*100)),
                   result, false);
    }
    if (haveDurationMagnitudeWeightCode())
    {
        setInteger(82, 83, getDurationMagnitudeWeightCode(), result);
    }
    if (havePeriodOfAmplitudeMeasurement())
    {
        setInteger(83, 86,
                   static_cast<int> (std::round(getPeriodOfAmplitudeMeasurement()*100)),
                   result, false);
    }
    if (haveCodaDuration())
    {
        setInteger(87, 91, static_cast<int> (std::round(getCodaDuration())),
                result, false);
    }
    if (havePImportance())
    {
        setInteger(100, 104,
                   static_cast<int> (std::round(getPImportance()*1000)),
                   result, false);
    }
    if (haveSImportance())
    {
        setInteger(104, 108,
                   static_cast<int> (std::round(getSImportance()*1000)),
                   result, false);
    }
    if (haveDataSourceCode()){result[108] = getDataSourceCode();}
    if (haveDurationMagnitudeLabel())
    {
        result[109] = getDurationMagnitudeLabel();
    }
    if (haveAmplitudeMagnitudeLabel())
    {
        result[110] = getAmplitudeMagnitudeLabel();
    }
    return result;
}

/// Network name
void StationArchiveLine::setNetworkName(const std::string &network) noexcept
{
    std::string scopy(network,
                      0,std::min(static_cast<int> (network.size()), 2));
    rtrim(scopy);
    if (scopy.empty()){return;}
    pImpl->mNetwork = network;
    pImpl->mHaveNetwork = true;
}

std::string StationArchiveLine::getNetworkName() const
{
    if (!haveNetworkName()){throw std::runtime_error("Network name not set");}
    return pImpl->mNetwork;
}

bool StationArchiveLine::haveNetworkName() const noexcept
{
    return pImpl->mHaveNetwork;
}

/// Station name
void StationArchiveLine::setStationName(const std::string &station) noexcept
{
    std::string scopy(station,
                 0, std::min(static_cast<int> (station.size()), 5));
    rtrim(scopy);
    if (scopy.empty()){return;}
    pImpl->mStation = scopy;
    pImpl->mHaveStation = true;
}

std::string StationArchiveLine::getStationName() const
{
    if (!haveStationName()){throw std::runtime_error("Station name not set");}
    return pImpl->mStation;
}

bool StationArchiveLine::haveStationName() const noexcept
{
    return pImpl->mHaveStation;
}

/// Channel name
void StationArchiveLine::setChannelName(const std::string &channel) noexcept
{
    std::string scopy(channel,
                 0, std::min(static_cast<int> (channel.size()), 3));
    rtrim(scopy);
    if (scopy.empty()){return;}
    pImpl->mChannel = scopy;
    pImpl->mHaveChannel = true;
}

std::string StationArchiveLine::getChannelName() const
{
    if (!haveChannelName()){throw std::runtime_error("Channel name not set");}
    return pImpl->mChannel;
}

bool StationArchiveLine::haveChannelName() const noexcept
{
    return pImpl->mHaveChannel;
}

/// Location code
void StationArchiveLine::setLocationCode(const std::string &location) noexcept
{
    std::string scopy(location,
                 0, std::min(static_cast<int> (location.size()), 2));
    rtrim(scopy);
    if (scopy.empty()){return;}
    pImpl->mLocationCode = scopy;
    pImpl->mHaveLocationCode = true;
}

std::string StationArchiveLine::getLocationCode() const
{
    if (!haveLocationCode())
    {
        throw std::runtime_error("Location code not set");
    }
    return pImpl->mLocationCode;
}

bool StationArchiveLine::haveLocationCode() const noexcept
{
    return pImpl->mHaveLocationCode;
}

/// P First motion
void StationArchiveLine::setFirstMotion(const char firstMotion) noexcept
{
    pImpl->mPFirstMotion = firstMotion;
    pImpl->mHavePFirstMotion = true;
}

char StationArchiveLine::getFirstMotion() const
{
    if (!haveFirstMotion())
    {
        throw std::runtime_error("P first motion not set");
    }
    return pImpl->mPFirstMotion;
}

bool StationArchiveLine::haveFirstMotion() const noexcept
{
    return pImpl->mHavePFirstMotion;
}

/// P remark
void StationArchiveLine::setPRemark(const std::string &remark) noexcept
{
    std::string scopy(remark,
                 0, std::min(static_cast<int> (remark.size()), 2));
    trim(scopy);
    if (scopy.empty()){return;}
    pImpl->mPRemark = scopy;
    pImpl->mHavePRemark = true;
}

std::string StationArchiveLine::getPRemark() const
{
    if (!havePRemark()){throw std::runtime_error("P remark not set");}
    return pImpl->mPRemark;
}

bool StationArchiveLine::havePRemark() const noexcept
{
    return pImpl->mHavePRemark;
}

/// P weight code
void StationArchiveLine::setPWeightCode(const uint16_t weightCode) noexcept
{
    pImpl->mPWeightCode = weightCode;
}

int StationArchiveLine::getPWeightCode() const
{
    if (!havePWeightCode()){throw std::runtime_error("P weight code not set");}
    return pImpl->mPWeightCode;
}

bool StationArchiveLine::havePWeightCode() const noexcept
{
    return pImpl->mPWeightCode >= 0;
}

/// P pick time
void StationArchiveLine::setPPickTime(
    const SFF::Utilities::Time &pickTime) noexcept
{
    pImpl->mPPick = pickTime;
    pImpl->mHavePPick = true;
}

SFF::Utilities::Time StationArchiveLine::getPPickTime() const
{
    if (!havePPickTime()){throw std::runtime_error("P pick time not set");}
    return pImpl->mPPick;
}

bool StationArchiveLine::havePPickTime() const noexcept
{
    return pImpl->mHavePPick;
}

/// P residual
void StationArchiveLine::setPResidual(const double residual) noexcept
{
    pImpl->mPResidual = residual;
    pImpl->mHavePResidual = true;
}

double StationArchiveLine::getPResidual() const
{
    if (!havePResidual()){throw std::runtime_error("P residual not set");}
    return pImpl->mPResidual;
}

bool StationArchiveLine::havePResidual() const noexcept
{
    return pImpl->mHavePResidual;
}

/// P weight used
void StationArchiveLine::setPWeightUsed(const double weightUsed)
{
    if (weightUsed < 0)
    {
        throw std::invalid_argument("P weight used must be non-negative");
    }
    pImpl->mPWeightUsed = weightUsed;
}

double StationArchiveLine::getPWeightUsed() const
{
    if (!havePWeightUsed()){throw std::runtime_error("P weight used not set");}
    return pImpl->mPWeightUsed;
}

bool StationArchiveLine::havePWeightUsed() const noexcept
{
    return pImpl->mPWeightUsed >= 0;
}

/// P static correction
void StationArchiveLine::setPDelayTime(const double correction) noexcept
{
    pImpl->mPDelayTime = correction;
    pImpl->mHavePDelayTime = true;
}

double StationArchiveLine::getPDelayTime() const
{
    if (!havePDelayTime())
    {
        throw std::runtime_error("S delay time not set");
    }
    return pImpl->mPDelayTime;
}

bool StationArchiveLine::havePDelayTime() const noexcept
{
    return pImpl->mHavePDelayTime;
}

/// P importance
void StationArchiveLine::setPImportance(const double importance)
{
    if (importance < 0)
    {
        throw std::invalid_argument("Importance must be positive");
    }
    pImpl->mPImportance = importance;
}

double StationArchiveLine::getPImportance() const
{
    if (!havePImportance()){throw std::runtime_error("P importance not set");}
    return pImpl->mPImportance;
}

bool StationArchiveLine::havePImportance() const noexcept
{
    return pImpl->mPImportance >= 0;
}

/// S pick time
void StationArchiveLine::setSPickTime(
    const SFF::Utilities::Time &pickTime) noexcept
{
    pImpl->mSPick = pickTime;
    pImpl->mHaveSPick = true;
}

SFF::Utilities::Time StationArchiveLine::getSPickTime() const
{
    if (!haveSPickTime()){throw std::runtime_error("S pick time not set");}
    return pImpl->mSPick;
}

bool StationArchiveLine::haveSPickTime() const noexcept
{
    return pImpl->mHaveSPick;
}

/// S weight code
void StationArchiveLine::setSWeightCode(
    const uint16_t weightCode) noexcept
{
    pImpl->mSWeightCode = weightCode;
}

int StationArchiveLine::getSWeightCode() const
{
    if (!haveSWeightCode()){throw std::runtime_error("S weight code not set");}
    return pImpl->mSWeightCode;
}

bool StationArchiveLine::haveSWeightCode() const noexcept
{
    return pImpl->mSWeightCode >= 0;
}

/// S residual
void StationArchiveLine::setSResidual(const double residual) noexcept
{
    pImpl->mSResidual = residual;
    pImpl->mHaveSResidual = true;
}

double StationArchiveLine::getSResidual() const
{
    if (!haveSResidual()){throw std::runtime_error("S residual not set");}
    return pImpl->mSResidual;
}

bool StationArchiveLine::haveSResidual() const noexcept
{
    return pImpl->mHaveSResidual;
}

/// S remark
void StationArchiveLine::setSRemark(const std::string &remark) noexcept
{
    std::string scopy(remark,
                      0, std::min(static_cast<int> (remark.size()), 2));
    trim(scopy);
    if (scopy.empty()){return;}
    pImpl->mSRemark = scopy;
    pImpl->mHaveSRemark = true;
}

std::string StationArchiveLine::getSRemark() const
{
    if (!haveSRemark()){throw std::runtime_error("S remark not set");}
    return pImpl->mSRemark;
}

bool StationArchiveLine::haveSRemark() const noexcept
{
    return pImpl->mHaveSRemark;
}

/// S weight used
void StationArchiveLine::setSWeightUsed(const double weightUsed)
{
    if (weightUsed < 0)
    {
        throw std::invalid_argument("S weight used must be non-negative");
    }
    pImpl->mSWeightUsed = weightUsed;
}

double StationArchiveLine::getSWeightUsed() const
{
    if (!haveSWeightUsed()){throw std::runtime_error("S weight used not set");}
    return pImpl->mSWeightUsed;
}

bool StationArchiveLine::haveSWeightUsed() const noexcept
{
    return pImpl->mSWeightUsed >= 0;
}

/// S static correction
void StationArchiveLine::setSDelayTime(const double correction) noexcept
{
    pImpl->mSDelayTime = correction;
    pImpl->mHaveSDelayTime = true;
}

double StationArchiveLine::getSDelayTime() const
{
    if (!haveSDelayTime())
    {
        throw std::runtime_error("S static correction not set");
    }
    return pImpl->mSDelayTime;
}

bool StationArchiveLine::haveSDelayTime() const noexcept
{
    return pImpl->mHaveSDelayTime;
}

/// S importance
void StationArchiveLine::setSImportance(const double importance)
{
    if (importance < 0)
    {
        throw std::invalid_argument("Importance must be positive");
    }
    pImpl->mSImportance = importance;
}

double StationArchiveLine::getSImportance() const
{
    if (!haveSImportance()){throw std::runtime_error("S importance not set");}
    return pImpl->mSImportance;
}

bool StationArchiveLine::haveSImportance() const noexcept
{
    return pImpl->mSImportance >= 0;
}

/// Take off angle
void StationArchiveLine::setTakeOffAngle(const double angle)
{
    if (angle < 0 || angle > 180)
    {
        throw std::invalid_argument("Takeoff angle must be in range [0,180]");
    }
    pImpl->mTakeOffAngle = angle;
}

double StationArchiveLine::getTakeOffAngle() const
{
    if (!haveTakeOffAngle()){throw std::runtime_error("Takeoff angle not set");}
    return pImpl->mTakeOffAngle;
}

bool StationArchiveLine::haveTakeOffAngle() const noexcept
{
    return pImpl->mTakeOffAngle >= 0;
}

/// Azimuth angle
void StationArchiveLine::setAzimuth(const double azimuth)
{
    if (azimuth < 0 || azimuth > 360)
    {
        throw std::invalid_argument("Takeoff angle must be in range [0,360)");
    }
    pImpl->mAzimuth = azimuth;
}

double StationArchiveLine::getAzimuth() const
{
    if (!haveAzimuth()){throw std::runtime_error("Azimuth not set");}
    return pImpl->mAzimuth;
}

bool StationArchiveLine::haveAzimuth() const noexcept
{
    return pImpl->mAzimuth >= 0;
}

/// Epicentral distance
void StationArchiveLine::setEpicentralDistance(const double distance)
{
    if (distance < 0)
    {
        throw std::invalid_argument("Epicentral distance must be positive");
    }
    pImpl->mEpicentralDistance = distance;
}

double StationArchiveLine::getEpicentralDistance() const
{
    if (!haveEpicentralDistance())
    {
        throw std::runtime_error("Epicentral distance not set");
    }
    return pImpl->mEpicentralDistance;
}

bool StationArchiveLine::haveEpicentralDistance() const noexcept
{
    return pImpl->mEpicentralDistance >= 0;
}

/// Duration magnitude
void StationArchiveLine::setDurationMagnitude(const double magnitude) noexcept
{
    pImpl->mDurationMagnitude = magnitude;
    pImpl->mHaveDurationMagnitude = true;
}

double StationArchiveLine::getDurationMagnitude() const
{
    if (!haveDurationMagnitude())
    {
        throw std::runtime_error("Duration magnitude not set");
    }
    return pImpl->mDurationMagnitude;
}

bool StationArchiveLine::haveDurationMagnitude() const noexcept
{
    return pImpl->mHaveDurationMagnitude;
}

/// Duration magnitude weight code
void StationArchiveLine::setDurationMagnitudeWeightCode(const int code)
{
    if (code < 0)
    {
        throw std::invalid_argument("Weight code cannot be negative");
    }
    pImpl->mDurationMagnitudeWeightCode = code;
}

int StationArchiveLine::getDurationMagnitudeWeightCode() const
{
    if (!haveDurationMagnitudeWeightCode())
    {
        throw std::runtime_error("Duration mag weight code not yet set");
    }
    return pImpl->mDurationMagnitudeWeightCode;
}

bool StationArchiveLine::haveDurationMagnitudeWeightCode() const noexcept
{
    return pImpl->mDurationMagnitudeWeightCode >= 0;
}

/// Duration magnitude label
void StationArchiveLine::setDurationMagnitudeLabel(const char label)
{
    if (std::isblank(label))
    {
        throw std::invalid_argument("Label cannot be blank");
    }
    pImpl->mDurationMagnitudeLabel = label;
}

char StationArchiveLine::getDurationMagnitudeLabel() const
{
    if (!haveDurationMagnitudeLabel())
    {
        throw std::runtime_error("Duration magnitude label not set");
    }
    return pImpl->mDurationMagnitudeLabel;
}

bool StationArchiveLine::haveDurationMagnitudeLabel() const noexcept
{
    return pImpl->mDurationMagnitudeLabel != ' ';
}

/// Amplitude magnitude
void StationArchiveLine::setAmplitudeMagnitude(const double magnitude) noexcept
{
    pImpl->mAmplitudeMagnitude = magnitude;
    pImpl->mHaveAmplitudeMagnitude = true;
}

double StationArchiveLine::getAmplitudeMagnitude() const
{
    if (!haveAmplitudeMagnitude())
    {
        throw std::runtime_error("Amplitude magnitude not set");
    }
    return pImpl->mAmplitudeMagnitude;
}

bool StationArchiveLine::haveAmplitudeMagnitude() const noexcept
{
    return pImpl->mHaveAmplitudeMagnitude;
}

/// Amplitude magnitude weight code
void StationArchiveLine::setAmplitudeMagnitudeWeightCode(const int code)
{
    if (code < 0)
    {
        throw std::invalid_argument("Weight code cannot be negative");
    }
    pImpl->mAmplitudeMagnitudeWeightCode = code;
}

int StationArchiveLine::getAmplitudeMagnitudeWeightCode() const
{
    if (!haveAmplitudeMagnitudeWeightCode())
    {
        throw std::runtime_error("Amplitude mag weight code not yet set");
    }
    return pImpl->mAmplitudeMagnitudeWeightCode;
}

bool StationArchiveLine::haveAmplitudeMagnitudeWeightCode() const noexcept
{
    return pImpl->mAmplitudeMagnitudeWeightCode >= 0;
}

/// Amplitude magnitude label
void StationArchiveLine::setAmplitudeMagnitudeLabel(const char label)
{
    if (std::isblank(label))
    {
        throw std::invalid_argument("Label cannot be blank");
    }
    pImpl->mAmplitudeMagnitudeLabel = label;
}

char StationArchiveLine::getAmplitudeMagnitudeLabel() const
{
    if (!haveAmplitudeMagnitudeLabel())
    {
        throw std::runtime_error("Amplitude magnitude label not set");
    }
    return pImpl->mAmplitudeMagnitudeLabel;
}

bool StationArchiveLine::haveAmplitudeMagnitudeLabel() const noexcept
{
    return pImpl->mAmplitudeMagnitudeLabel != ' ';
}

/// Data Source code
void StationArchiveLine::setDataSourceCode(const char label)
{
    if (std::isblank(label))
    {
        throw std::invalid_argument("Label cannot be blank");
    }
    pImpl->mDataSourceCode = label;
}

char StationArchiveLine::getDataSourceCode() const
{
    if (!haveDataSourceCode())
    {
        throw std::runtime_error("Data source code not set");
    }
    return pImpl->mDataSourceCode;
}

bool StationArchiveLine::haveDataSourceCode() const noexcept
{
    return pImpl->mDataSourceCode != ' ';
}

/// The amplitude
void StationArchiveLine::setAmplitude(const double amplitude)
{
    if (amplitude < 0)
    {
        throw std::invalid_argument("Amplitude cannot be negative");
    }
    pImpl->mAmplitude = amplitude;
}

double StationArchiveLine::getAmplitude() const
{
    if (!haveAmplitude()){throw std::runtime_error("Amplitude not set");}
    return pImpl->mAmplitude;
}

bool StationArchiveLine::haveAmplitude() const noexcept
{
    return pImpl->mAmplitude >= 0;
}

/// Amplitude units
void StationArchiveLine::setAmplitudeUnits(
    const AmplitudeUnits units) noexcept
{
    pImpl->mAmplitudeUnits = units;
    pImpl->mHaveAmplitudeUnits = true;
}

AmplitudeUnits StationArchiveLine::getAmplitudeUnits() const
{
    if (!haveAmplitudeUnits())
    {
        throw std::runtime_error("Amplitude units were not set");
    }
    return pImpl->mAmplitudeUnits;
}

bool StationArchiveLine::haveAmplitudeUnits() const noexcept
{
    return pImpl->mHaveAmplitudeUnits;
}

/// Period of amplitude measurement
void StationArchiveLine::setPeriodOfAmplitudeMeasurement(const double period)
{
    if (period <= 0)
    {
        throw std::invalid_argument("Period must be positive");
    }
    pImpl->mPeriodOfAmplitudeMeasurement = period;
}

double StationArchiveLine::getPeriodOfAmplitudeMeasurement() const
{
    if (!havePeriodOfAmplitudeMeasurement())
    {
        throw std::runtime_error("Period not yet set");
    }
    return pImpl->mPeriodOfAmplitudeMeasurement;
}
bool StationArchiveLine::havePeriodOfAmplitudeMeasurement() const noexcept
{
    return pImpl->mPeriodOfAmplitudeMeasurement >= 0;
}

/// Duration of coda magnitude

void StationArchiveLine::setCodaDuration(const double duration)
{
    if (duration <= 0)
    {
        throw std::invalid_argument("Duration must be positive");
    }
    pImpl->mCodaDuration = duration;
}

double StationArchiveLine::getCodaDuration() const
{
    if (!haveCodaDuration())
    {
        throw std::runtime_error("Coda duration was not set");
    }
    return pImpl->mCodaDuration;
}

bool StationArchiveLine::haveCodaDuration() const noexcept
{
    return pImpl->mCodaDuration > 0;
}
