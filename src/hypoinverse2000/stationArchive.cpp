#include <iostream>
#include <string>
#include <limits>
#include <cstdint>
#ifndef DNDEBUG
#include <cassert>
#endif
#include "sff/hypoinverse2000/stationArchive.hpp"
#include "sff/utilities/time.hpp"
#include "private/hypoinverse2000.hpp"

using namespace SFF::HypoInverse2000;

class StationArchive::StationArchiveImpl
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
        mPResidual = 0;
        mSResidual = 0;
        mPWeightUsed =-1;
        mSWeightUsed =-1;
        mPDelayTime = 0;
        mSDelayTime = 0;
        mEpicentralDistance =-1;
        mTakeOffAngle =-1;
        mPWeightCode =-1;
        mSWeightCode =-1;
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
    int mPWeightCode =-1;
    int mSWeightCode =-1;
    char mPFirstMotion = ' ';
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
};

/// Constructor
StationArchive::StationArchive() :
    pImpl(std::make_unique<StationArchiveImpl> ())
{
}

/// Copy c'tor
StationArchive::StationArchive(const StationArchive &station)
{
    *this = station;
}

/// Move c'tor
StationArchive::StationArchive(StationArchive &&station) noexcept
{
    *this = std::move(station);
}

/// Copy assignment operator
StationArchive& StationArchive::operator=(const StationArchive &station)
{
    if (&station == this){return *this;}
    pImpl = std::make_unique<StationArchiveImpl> (*station.pImpl);
    return *this;
}

/// Move assignment operator
StationArchive& StationArchive::operator=(StationArchive &&station) noexcept
{
    if (&station == this){return *this;}
    pImpl = std::move(station.pImpl);
    return *this;
}

/// Destructor
StationArchive::~StationArchive() = default;

/// Clears the class
void StationArchive::clear() noexcept
{
    pImpl->clear();
}

/// Unpacks a pick line
void StationArchive::unpackString(const std::string &line)
{
    StationArchive result;
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
        result.setPFirstMotion(pFirstMotion.second);
    }

    // P and S pick time
    SFF::Utilities::Time pickTime;
    auto year = unpackIntPair(17, 21, linePtr, lenos);
    auto month = unpackIntPair(21, 23, linePtr, lenos);
    auto dayOfMonth = unpackIntPair(23, 25, linePtr, lenos);
    auto hour = unpackIntPair(25, 27, linePtr, lenos);
    auto minute = unpackIntPair(27, 29, linePtr, lenos);
    auto pSecond = unpackIntPair(29, 32, linePtr, lenos);
    auto pMicroSecond = unpackIntPair(32, 35, linePtr, lenos);
    if (year.first && month.first && dayOfMonth.first &&
        hour.first && minute.first)
    {
        pickTime.setYear(year.second);
        pickTime.setMonth(month.second);
        pickTime.setDayOfMonth(dayOfMonth.second);
        pickTime.setHour(hour.second);
        pickTime.setMinute(minute.second);
    }
    if (year.first && month.first && dayOfMonth.first &&
        hour.first && minute.first && pSecond.first && pMicroSecond.first)
    {
        pickTime.setSecond(pSecond.second);
        pMicroSecond.second = pMicroSecond.second*10000;
        pickTime.setMicroSecond(pMicroSecond.second);
        result.setPPickTime(pickTime);
    }
    auto sSecond = unpackIntPair(41, 44, linePtr, lenos);
    auto sMicroSecond = unpackIntPair(44, 46, linePtr, lenos);
    if (year.first && month.first && dayOfMonth.first &&
        hour.first && minute.first && sSecond.first && sMicroSecond.first)
    {
        pickTime.setSecond(sSecond.second);
        sMicroSecond.second = sMicroSecond.second*10000;
        pickTime.setMicroSecond(sMicroSecond.second);
        result.setSPickTime(pickTime);
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
    auto pResidual = unpackDoublePair(34, 38, 2, 2, linePtr, lenos);
    if (pResidual.first){result.setPResidual(pResidual.second);}
    auto sResidual = unpackDoublePair(50, 54, 2, 2, linePtr, lenos);
    if (sResidual.first){result.setSResidual(sResidual.second);}
    // Weight used
    auto pWeightUsed = unpackDoublePair(38, 41, 1, 2, linePtr, lenos);
    if (pWeightUsed.first && pWeightUsed.second >= 0)
    {
        result.setPWeightUsed(pWeightUsed.second);
    }
    auto sWeightUsed = unpackDoublePair(63, 66, 1, 2, linePtr, lenos);
    if (sWeightUsed.first && sWeightUsed.second >= 0)
    {
        result.setSWeightUsed(sWeightUsed.second);
    }
    // Static corrections
    auto pDelayTime = unpackDoublePair(66, 70, 2, 2, linePtr, lenos);
    if (pDelayTime.first){result.setPDelayTime(pDelayTime.second);}
    auto sDelayTime = unpackDoublePair(70, 74, 2, 2, linePtr, lenos);
    if (sDelayTime.first){result.setSDelayTime(sDelayTime.second);}
    // Takeoff angle and epicentral distance
    auto distance = unpackDoublePair(74, 78, 3, 1, linePtr, lenos);
    if (distance.first && distance.second >= 0)
    {
        result.setEpicentralDistance(distance.second);
    }
    auto angle = unpackIntPair(78, 81, linePtr, lenos);
    if (angle.first && angle.second >= 0 && angle.second <= 180)
    {
        result.setTakeOffAngle(angle.second);
    }
    // Finally copy result back
    *this = result;
}

/// Network name
void StationArchive::setNetworkName(const std::string &network) noexcept
{
    std::string scopy(network,
                      0,std::min(static_cast<int> (network.size()), 2));
    rtrim(scopy);
    if (scopy.empty()){return;}
    pImpl->mNetwork = network;
    pImpl->mHaveNetwork = true;
}

std::string StationArchive::getNetworkName() const
{
    if (!haveNetworkName()){throw std::runtime_error("Network name not set");}
    return pImpl->mNetwork;
}

bool StationArchive::haveNetworkName() const noexcept
{
    return pImpl->mHaveNetwork;
}

/// Station name
void StationArchive::setStationName(const std::string &station) noexcept
{
    std::string scopy(station,
                 0, std::min(static_cast<int> (station.size()), 5));
    rtrim(scopy);
    if (scopy.empty()){return;}
    pImpl->mStation = scopy;
    pImpl->mHaveStation = true;
}

std::string StationArchive::getStationName() const
{
    if (!haveStationName()){throw std::runtime_error("Station name not set");}
    return pImpl->mStation;
}

bool StationArchive::haveStationName() const noexcept
{
    return pImpl->mHaveStation;
}

/// Channel name
void StationArchive::setChannelName(const std::string &channel) noexcept
{
    std::string scopy(channel,
                 0, std::min(static_cast<int> (channel.size()), 3));
    rtrim(scopy);
    if (scopy.empty()){return;}
    pImpl->mChannel = scopy;
    pImpl->mHaveChannel = true;
}

std::string StationArchive::getChannelName() const
{
    if (!haveChannelName()){throw std::runtime_error("Channel name not set");}
    return pImpl->mChannel;
}

bool StationArchive::haveChannelName() const noexcept
{
    return pImpl->mHaveChannel;
}

/// Location code
void StationArchive::setLocationCode(const std::string &location) noexcept
{
    std::string scopy(location,
                 0, std::min(static_cast<int> (location.size()), 2));
    rtrim(scopy);
    if (scopy.empty()){return;}
    pImpl->mLocationCode = scopy;
    pImpl->mHaveLocationCode = true;
}

std::string StationArchive::getLocationCode() const
{
    if (!haveLocationCode())
    {
        throw std::runtime_error("Location code not set");
    }
    return pImpl->mLocationCode;
}

bool StationArchive::haveLocationCode() const noexcept
{
    return pImpl->mHaveLocationCode;
}

/// P First motion
void StationArchive::setPFirstMotion(char firstMotion) noexcept
{
    pImpl->mPFirstMotion = firstMotion;
    pImpl->mHavePFirstMotion = true;
}

char StationArchive::getPFirstMotion() const
{
    if (!havePFirstMotion())
    {
        throw std::runtime_error("P first motion not set");
    }
    return pImpl->mPFirstMotion;
}

bool StationArchive::havePFirstMotion() const noexcept
{
    return pImpl->mHavePFirstMotion;
}

/// P remark
void StationArchive::setPRemark(const std::string &remark) noexcept
{
    std::string scopy(remark,
                 0, std::min(static_cast<int> (remark.size()), 2));
    trim(scopy);
    if (scopy.empty()){return;}
    pImpl->mPRemark = scopy;
    pImpl->mHavePRemark = true;
}

std::string StationArchive::getPRemark() const
{
    if (!havePRemark()){throw std::runtime_error("P remark not set");}
    return pImpl->mPRemark;
}

bool StationArchive::havePRemark() const noexcept
{
    return pImpl->mHavePRemark;
}

/// P weight code
void StationArchive::setPWeightCode(const uint16_t weightCode) noexcept
{
    pImpl->mPWeightCode = weightCode;
}

int StationArchive::getPWeightCode() const
{
    if (!havePWeightCode()){throw std::runtime_error("P weight code not set");}
    return pImpl->mPWeightCode;
}

bool StationArchive::havePWeightCode() const noexcept
{
    return pImpl->mPWeightCode >= 0;
}

/// P pick time
void StationArchive::setPPickTime(const SFF::Utilities::Time &pickTime) noexcept
{
    pImpl->mPPick = pickTime;
    pImpl->mHavePPick = true;
}

SFF::Utilities::Time StationArchive::getPPickTime() const
{
    if (!havePPickTime()){throw std::runtime_error("P pick time not set");}
    return pImpl->mPPick;
}

bool StationArchive::havePPickTime() const noexcept
{
    return pImpl->mHavePPick;
}

/// P residual
void StationArchive::setPResidual(double residual) noexcept
{
    pImpl->mPResidual = residual;
    pImpl->mHavePResidual = true;
}

double StationArchive::getPResidual() const
{
    if (!havePResidual()){throw std::runtime_error("P residual not set");}
    return pImpl->mPResidual;
}

bool StationArchive::havePResidual() const noexcept
{
    return pImpl->mHavePResidual;
}

/// P weight used
void StationArchive::setPWeightUsed(double weightUsed)
{
    if (weightUsed < 0)
    {
        throw std::invalid_argument("P weight used must be non-negative");
    }
    pImpl->mPWeightUsed = weightUsed;
}

double StationArchive::getPWeightUsed() const
{
    if (!havePWeightUsed()){throw std::runtime_error("P weight used not set");}
    return pImpl->mPWeightUsed;
}

bool StationArchive::havePWeightUsed() const noexcept
{
    return pImpl->mPWeightUsed >= 0;
}

/// P static correction
void StationArchive::setPDelayTime(double correction) noexcept
{
    pImpl->mPDelayTime = correction;
    pImpl->mHavePDelayTime = true;
}

double StationArchive::getPDelayTime() const
{
    if (!havePDelayTime())
    {
        throw std::runtime_error("S delay time not set");
    }
    return pImpl->mPDelayTime;
}

bool StationArchive::havePDelayTime() const noexcept
{
    return pImpl->mHavePDelayTime;
}

/// S pick time
void StationArchive::setSPickTime(const SFF::Utilities::Time &pickTime) noexcept
{
    pImpl->mSPick = pickTime;
    pImpl->mHaveSPick = true;
}

SFF::Utilities::Time StationArchive::getSPickTime() const
{
    if (!haveSPickTime()){throw std::runtime_error("S pick time not set");}
    return pImpl->mSPick;
}

bool StationArchive::haveSPickTime() const noexcept
{
    return pImpl->mHaveSPick;
}

/// S weight code
void StationArchive::setSWeightCode(uint16_t weightCode) noexcept
{
    pImpl->mSWeightCode = weightCode;
}

int StationArchive::getSWeightCode() const
{
    if (!haveSWeightCode()){throw std::runtime_error("S weight code not set");}
    return pImpl->mSWeightCode;
}

bool StationArchive::haveSWeightCode() const noexcept
{
    return pImpl->mSWeightCode >= 0;
}

/// S residual
void StationArchive::setSResidual(double residual) noexcept
{
    pImpl->mSResidual = residual;
    pImpl->mHaveSResidual = true;
}

double StationArchive::getSResidual() const
{
    if (!haveSResidual()){throw std::runtime_error("S residual not set");}
    return pImpl->mSResidual;
}

bool StationArchive::haveSResidual() const noexcept
{
    return pImpl->mHaveSResidual;
}

/// S remark
void StationArchive::setSRemark(const std::string &remark) noexcept
{
    std::string scopy(remark,
                      0, std::min(static_cast<int> (remark.size()), 2));
    trim(scopy);
    if (scopy.empty()){return;}
    pImpl->mSRemark = scopy;
    pImpl->mHaveSRemark = true;
}

std::string StationArchive::getSRemark() const
{
    if (!haveSRemark()){throw std::runtime_error("S remark not set");}
    return pImpl->mSRemark;
}

bool StationArchive::haveSRemark() const noexcept
{
    return pImpl->mHaveSRemark;
}

/// S weight used
void StationArchive::setSWeightUsed(double weightUsed)
{
    if (weightUsed < 0)
    {
        throw std::invalid_argument("S weight used must be non-negative");
    }
    pImpl->mSWeightUsed = weightUsed;
}

double StationArchive::getSWeightUsed() const
{
    if (!haveSWeightUsed()){throw std::runtime_error("S weight used not set");}
    return pImpl->mSWeightUsed;
}

bool StationArchive::haveSWeightUsed() const noexcept
{
    return pImpl->mSWeightUsed >= 0;
}

/// S static correction
void StationArchive::setSDelayTime(const double correction) noexcept
{
    pImpl->mSDelayTime = correction;
    pImpl->mHaveSDelayTime = true;
}

double StationArchive::getSDelayTime() const
{
    if (!haveSDelayTime())
    {
        throw std::runtime_error("S static correction not set");
    }
    return pImpl->mSDelayTime;
}

bool StationArchive::haveSDelayTime() const noexcept
{
    return pImpl->mHaveSDelayTime;
}

/// Take off angle
void StationArchive::setTakeOffAngle(const double angle)
{
    if (angle < 0 || angle > 180)
    {
        throw std::invalid_argument("Takeoff angle must be in range [0,180]");
    }
    pImpl->mTakeOffAngle = angle;
}

double StationArchive::getTakeOffAngle() const
{
    if (!haveTakeOffAngle()){throw std::runtime_error("Takeoff angle not set");}
    return pImpl->mTakeOffAngle;
}

bool StationArchive::haveTakeOffAngle() const noexcept
{
    return pImpl->mTakeOffAngle >= 0;
}

/// Epicentral distance
void StationArchive::setEpicentralDistance(const double distance)
{
    if (distance < 0)
    {
        throw std::invalid_argument("Epicentral distance must be positive");
    }
    pImpl->mEpicentralDistance = distance;
}

double StationArchive::getEpicentralDistance() const
{
    if (!haveEpicentralDistance())
    {
        throw std::runtime_error("Epicentral distance not set");
    }
    return pImpl->mEpicentralDistance;
}

bool StationArchive::haveEpicentralDistance() const noexcept
{
    return pImpl->mEpicentralDistance >= 0;
}