#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#ifndef DNDEBUG
#include <cassert>
#endif
#include "sff/hypoinverse2000/stationArchive.hpp"
#include "sff/utilities/time.hpp"

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