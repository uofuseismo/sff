#include <iostream>
#include <string>
#include <limits>
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
        mNetwork.clear();
        mStation.clear();
        mChannel.clear();
        mLocationCode.clear();
        mHaveNetwork = false;
        mHaveStation = false;
        mHaveChannel = false;
        mHaveLocationCode = false;
    }
    std::string mNetwork;
    std::string mStation;
    std::string mChannel;
    std::string mLocationCode;
    bool mHaveNetwork = false;
    bool mHaveStation = false;
    bool mHaveChannel = false;
    bool mHaveLocationCode = false;
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
    auto pRemark = unpackStringPair(13, 15, linePtr, lenos);
    //auto pFirstMotion = unpackCharPair(15, linePtr, lenos);
    //auto pWeightCode = unpackIntPair(16, 17, linePtr, lenos);

    /// Finally copy result back
    *this = result;
}

/// Network name
void StationArchive::setNetworkName(const std::string &network) noexcept
{
    std::string scopy(network, std::min(static_cast<int> (network.size()), 2));
    rtrim(scopy);
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
    std::string scopy(station, std::min(static_cast<int> (station.size()), 5));
    rtrim(scopy);
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
    std::string scopy(channel, std::min(static_cast<int> (channel.size()), 3));
    rtrim(scopy);
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
    std::string scopy(location, std::min(static_cast<int> (location.size()), 2));
    rtrim(scopy);
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