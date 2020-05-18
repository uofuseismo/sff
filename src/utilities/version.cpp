#include <string>
#include "sff/version.hpp"

using namespace SFF;

int Version::getMajor() noexcept
{
    return SFF_MAJOR;
}

int Version::getMinor() noexcept
{
    return SFF_MINOR;
}

int Version::getPatch() noexcept
{
    return SFF_PATCH;
}

bool Version::isAtLeast(const int major, const int minor,
                        const int patch) noexcept
{
    if (SFF_MAJOR < major){return false;}
    if (SFF_MAJOR > major){return true;}
    if (SFF_MINOR < minor){return false;}
    if (SFF_MINOR > minor){return true;}
    return SFF_PATCH >= patch;
}

std::string Version::getVersion() noexcept
{
    std::string version(std::to_string(getMajor()) + "."
                      + std::to_string(getMinor()) + "."
                      + std::to_string(getPatch()));
    return version;
}
