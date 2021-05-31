#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <array>
#include <algorithm>
#include "sff/miniseed/sncl.hpp"

using namespace SFF::MiniSEED;

#define NETWORK_LENGTH 10 
#define STATION_LENGTH 10
#define CHANNEL_LENGTH 10
#define LOCATION_LENGTH 10

class SNCL::SNCLImpl
{
public:
    std::array<char, NETWORK_LENGTH + 1> mNetwork{"\0\0\0\0\0\0\0\0\0\0"};
    std::array<char, STATION_LENGTH + 1> mStation{"\0\0\0\0\0\0\0\0\0\0"};
    std::array<char, CHANNEL_LENGTH + 1> mChannel{"\0\0\0\0\0\0\0\0\0\0"};
    std::array<char, LOCATION_LENGTH + 1> mLocation{"\0\0\0\0\0\0\0\0\0\0"};
};

/// Constructors
SNCL::SNCL() :
    pImpl(std::make_unique<SNCLImpl> ())
{
}

SNCL::SNCL(const SNCL &sncl)
{
    *this = sncl;
}

/// Operators
SNCL::SNCL(SNCL &&sncl) noexcept
{
    *this = std::move(sncl);
}

SNCL& SNCL::operator=(const SNCL &sncl)
{
    if (&sncl == this){return *this;}
    pImpl = std::make_unique<SNCLImpl> (*sncl.pImpl);
    return *this;
}

SNCL& SNCL::operator=(SNCL &&sncl) noexcept
{
    if (&sncl == this){return *this;}
    pImpl = std::move(sncl.pImpl);
    return *this;
}

bool SNCL::operator==(const SNCL &sncl) noexcept
{
    if (getNetwork() != sncl.getNetwork()){return false;}
    if (getStation() != sncl.getStation()){return false;}
    if (getChannel() != sncl.getChannel()){return false;}
    if (getLocationCode() != sncl.getLocationCode()){return false;}
    return true;
}

bool SNCL::operator!=(const SNCL &sncl) noexcept
{
    return !(*this == sncl);
}

/// Destructors
SNCL::~SNCL() = default;

void SNCL::clear() noexcept
{
    std::fill(pImpl->mNetwork.begin(),  pImpl->mNetwork.end(),  '\0');
    std::fill(pImpl->mStation.begin(),  pImpl->mStation.end(),  '\0');
    std::fill(pImpl->mChannel.begin(),  pImpl->mChannel.end(),  '\0');
    std::fill(pImpl->mLocation.begin(), pImpl->mLocation.end(), '\0');
}

/// Network
int SNCL::getMaximumNetworkLength() const noexcept
{
    return NETWORK_LENGTH;
}

std::string SNCL::getNetwork() const noexcept
{
    std::string result(pImpl->mNetwork.data()); //, NETWORK_LENGTH);
    return result;
}

void SNCL::setNetwork(const std::string &str) noexcept
{
    constexpr size_t maxlen = NETWORK_LENGTH;
    size_t len = std::min(str.size(), maxlen);
    std::memset(pImpl->mNetwork.data(), 0, NETWORK_LENGTH*sizeof(char));
    std::memcpy(pImpl->mNetwork.data(), str.data(), len*sizeof(char));
}

/// Station
int SNCL::getMaximumStationLength() const noexcept
{
    return STATION_LENGTH;
}

std::string SNCL::getStation() const noexcept
{
    std::string result(pImpl->mStation.data()); //, STATION_LENGTH);
    return result;
}

void SNCL::setStation(const std::string &str) noexcept
{
    constexpr size_t maxlen = STATION_LENGTH;
    size_t len = std::min(str.size(), maxlen);
    std::memset(pImpl->mStation.data(), 0, STATION_LENGTH*sizeof(char));
    std::memcpy(pImpl->mStation.data(), str.data(), len*sizeof(char));
}

/// Channel
int SNCL::getMaximumChannelLength() const noexcept
{
    return CHANNEL_LENGTH;
}

std::string SNCL::getChannel() const noexcept
{
    std::string result(pImpl->mChannel.data()); //, CHANNEL_LENGTH);
    return result;
}

void SNCL::setChannel(const std::string &str) noexcept
{
    constexpr size_t maxlen = CHANNEL_LENGTH;
    size_t len = std::min(str.size(), maxlen);
    std::memset(pImpl->mChannel.data(), 0, CHANNEL_LENGTH*sizeof(char));
    std::memcpy(pImpl->mChannel.data(), str.data(), len*sizeof(char));
}

/// Location code
int SNCL::getMaximumLocationCodeLength() const noexcept
{
    return LOCATION_LENGTH;
}

std::string SNCL::getLocationCode() const noexcept
{
    std::string result(pImpl->mLocation.data()); //LOCATION_LENGTH);
    return result;
}

void SNCL::setLocationCode(const std::string &str) noexcept
{
    constexpr size_t maxlen = LOCATION_LENGTH;
    size_t len = std::min(str.size(), maxlen);
    std::memset(pImpl->mLocation.data(), 0, LOCATION_LENGTH*sizeof(char));
    std::memcpy(pImpl->mLocation.data(), str.data(), len*sizeof(char));
}

bool SNCL::isEmpty() const noexcept
{
    size_t lenos = strnlen(pImpl->mNetwork.data(),  NETWORK_LENGTH)
                 + strnlen(pImpl->mStation.data(),  STATION_LENGTH)
                 + strnlen(pImpl->mChannel.data(),  CHANNEL_LENGTH)
                 + strnlen(pImpl->mLocation.data(), LOCATION_LENGTH);
    if (lenos == 0){return true;}
    return false;
}

/// std::cout << sncl << std::endl;
std::ostream&
SFF::MiniSEED::operator<<(std::ostream &os, const SNCL &sncl)
{
    std::string result;
    auto network = sncl.getNetwork();
    auto station = sncl.getStation();
    auto channel = sncl.getChannel();
    auto location = sncl.getLocationCode(); 
    if (!network.empty() || !station.empty() ||
        !channel.empty() || !location.empty())
    {
        if (!network.empty())
        {
            result = network;
            if (!station.empty() || !channel.empty() || !location.empty())
            {
                result = result + ".";
            }
        }
        if (!station.empty())
        {
            result = result + station;
            if (!channel.empty() || !location.empty())
            {
                result = result + ".";
            }
        }
        if (!channel.empty())
        {
            result = result + channel;
            if (!location.empty()){result = result + ".";}
        }
        if (!location.empty()){result = result + location;}
    }
    return os << result;
}
