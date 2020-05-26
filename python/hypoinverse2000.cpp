#include "sff/hypoinverse2000/stationArchiveLine.hpp"
#include "sff/hypoinverse2000/eventSummaryLine.hpp"
#include "sff/hypoinverse2000/eventSummary.hpp"
#include "hypoinverse2000.hpp"

using namespace PBSFF::HypoInverse2000;

///--------------------------------------------------------------------------///
///                            Station Archive Line                          ///
///--------------------------------------------------------------------------///
StationArchiveLine::StationArchiveLine() : 
    mStation(std::make_unique<SFF::HypoInverse2000::StationArchiveLine> ())
{
}

StationArchiveLine::StationArchiveLine(const StationArchiveLine &station)
{
    *this = station;
}

StationArchiveLine::StationArchiveLine(
    const SFF::HypoInverse2000::StationArchiveLine &station)
{
    *this = station;
}

/// Operators
StationArchiveLine& StationArchiveLine::operator=(
    const StationArchiveLine &station)
{
    if (&station == this){return *this;}
    mStation = std::make_unique<SFF::HypoInverse2000::StationArchiveLine>
               (*station.mStation);
    return *this;
}

StationArchiveLine& StationArchiveLine::operator=(
    const SFF::HypoInverse2000::StationArchiveLine &station)
{
    mStation = std::make_unique<SFF::HypoInverse2000::StationArchiveLine>
               (station);
    return *this;
}

/// Native class
SFF::HypoInverse2000::StationArchiveLine
StationArchiveLine::getNativeClass() const
{
    SFF::HypoInverse2000::StationArchiveLine archive(*mStation);
    return archive;
}

/// Destructors
StationArchiveLine::~StationArchiveLine() = default;

void StationArchiveLine::clear() noexcept
{
    mStation->clear();
}

/// Unpack/pack a string
void StationArchiveLine::unpackString(const std::string &line)
{
    mStation->unpackString(line);
}
std::string StationArchiveLine::packString() const noexcept
{
    return mStation->packString();
}

/// SNCL
void StationArchiveLine::setNetworkName(const std::string &network) noexcept
{
    mStation->setNetworkName(network);
}
std::string StationArchiveLine::getNetworkName() const
{
    return mStation->getNetworkName();
}
bool StationArchiveLine::haveNetworkName() const noexcept
{
    return mStation->haveNetworkName();
}

void StationArchiveLine::setStationName(const std::string &station) noexcept
{
    mStation->setStationName(station);
}
std::string StationArchiveLine::getStationName() const
{
    return mStation->getStationName();
}
bool StationArchiveLine::haveStationName() const noexcept
{
    return mStation->haveStationName();
}

void StationArchiveLine::setChannelName(const std::string &channel) noexcept
{
    mStation->setChannelName(channel);
}
std::string StationArchiveLine::getChannelName() const
{
    return mStation->getChannelName();
}
bool StationArchiveLine::haveChannelName() const noexcept
{
    return mStation->haveChannelName();
}

void StationArchiveLine::setLocationCode(const std::string &location) noexcept
{
    mStation->setLocationCode(location);
}
std::string StationArchiveLine::getLocationCode() const
{
    return mStation->getLocationCode();
}
bool StationArchiveLine::haveLocationCode() const noexcept
{
    return mStation->haveLocationCode();
}

void StationArchiveLine::setEpicentralDistance(const double distance)
{
    mStation->setEpicentralDistance(distance);
}
double StationArchiveLine::getEpicentralDistance() const
{
    return mStation->getEpicentralDistance();
}
bool StationArchiveLine::haveEpicentralDistance() const noexcept
{
    return mStation->haveEpicentralDistance();
}

void StationArchiveLine::setAzimuth(const double azimuth)
{
    mStation->setAzimuth(azimuth);
}
double StationArchiveLine::getAzimuth() const
{
    return mStation->getAzimuth();
}
bool StationArchiveLine::haveAzimuth() const noexcept
{
    return mStation->haveAzimuth();
}

void StationArchiveLine::setTakeOffAngle(double angle)
{
    mStation->setTakeOffAngle(angle);
}
double StationArchiveLine::getTakeOffAngle() const
{
    return mStation->getTakeOffAngle();
}
bool StationArchiveLine::haveTakeOffAngle() const noexcept
{
    return mStation->haveTakeOffAngle();
}

// P Pick
void StationArchiveLine::setPPickTime(const PBSFF::Time &pickTime) noexcept
{
    mStation->setPPickTime(pickTime.getNativeClass());
}
PBSFF::Time StationArchiveLine::getPPickTime() const
{
    PBSFF::Time pickTime(mStation->getPPickTime());
    return pickTime;
}
bool StationArchiveLine::havePPickTime() const noexcept
{
    return mStation->havePPickTime();
}

void StationArchiveLine::setPRemark(const std::string &remark) noexcept
{
    mStation->setPRemark(remark);
}
std::string StationArchiveLine::getPRemark() const
{
    return mStation->getPRemark();
}
bool StationArchiveLine::havePRemark() const noexcept
{
    return mStation->havePRemark();
}

void StationArchiveLine::setFirstMotion(const char firstMotion) noexcept
{
    mStation->setFirstMotion(firstMotion);
}
char StationArchiveLine::getFirstMotion() const
{
    return mStation->getFirstMotion();
}
bool StationArchiveLine::haveFirstMotion() const noexcept
{
    return mStation->haveFirstMotion();
}

void StationArchiveLine::setPResidual(const double residual) noexcept
{
    mStation->setPResidual(residual);
}
double StationArchiveLine::getPResidual() const
{
    return mStation->getPResidual();
}
bool StationArchiveLine::havePResidual() const noexcept
{
    return mStation->havePResidual();
}

void StationArchiveLine::setPWeightCode(const uint16_t weightCode) noexcept
{
    mStation->setPWeightCode(weightCode);
}
int StationArchiveLine::getPWeightCode() const
{
    return mStation->getPWeightCode();
}
bool StationArchiveLine::havePWeightCode() const noexcept
{
    return mStation->havePWeightCode();
}

void StationArchiveLine::setPWeightUsed(const double weightUsed)
{
    mStation->setPWeightUsed(weightUsed);
}
double StationArchiveLine::getPWeightUsed() const
{
    return mStation->getPWeightUsed();
}
bool StationArchiveLine::havePWeightUsed() const noexcept
{
    return mStation->havePWeightUsed();
}

void StationArchiveLine::setPDelayTime(const double delay) noexcept
{
    mStation->setPDelayTime(delay);
}
double StationArchiveLine::getPDelayTime() const
{
    return mStation->getPDelayTime();
}
bool StationArchiveLine::havePDelayTime() const noexcept
{
    return mStation->havePDelayTime();
}

void StationArchiveLine::setPImportance(const double importance)
{
    mStation->setPImportance(importance);
}
double StationArchiveLine::getPImportance() const
{
    return mStation->getPImportance();
}
bool StationArchiveLine::havePImportance() const noexcept
{
    return mStation->havePImportance();
}

// S Pick
void StationArchiveLine::setSPickTime(const PBSFF::Time &pickTime) noexcept
{
    mStation->setSPickTime(pickTime.getNativeClass());
}
PBSFF::Time StationArchiveLine::getSPickTime() const
{
    PBSFF::Time pickTime(mStation->getSPickTime());
    return pickTime;
}
bool StationArchiveLine::haveSPickTime() const noexcept
{
    return mStation->haveSPickTime();
}

void StationArchiveLine::setSRemark(const std::string &remark) noexcept
{
    mStation->setSRemark(remark);
}
std::string StationArchiveLine::getSRemark() const
{
    return mStation->getSRemark();
}
bool StationArchiveLine::haveSRemark() const noexcept
{
    return mStation->haveSRemark();
}

void StationArchiveLine::setSResidual(const double residual) noexcept
{
    mStation->setSResidual(residual);
}
double StationArchiveLine::getSResidual() const
{
    return mStation->getSResidual();
}
bool StationArchiveLine::haveSResidual() const noexcept
{
    return mStation->haveSResidual();
}

void StationArchiveLine::setSWeightCode(const uint16_t weightCode) noexcept
{
    mStation->setSWeightCode(weightCode);
}
int StationArchiveLine::getSWeightCode() const
{
    return mStation->getSWeightCode();
}
bool StationArchiveLine::haveSWeightCode() const noexcept
{
    return mStation->haveSWeightCode();
}

void StationArchiveLine::setSWeightUsed(const double weightUsed)
{
    mStation->setSWeightUsed(weightUsed);
}
double StationArchiveLine::getSWeightUsed() const
{
    return mStation->getSWeightUsed();
}
bool StationArchiveLine::haveSWeightUsed() const noexcept
{
    return mStation->haveSWeightUsed();
}

void StationArchiveLine::setSDelayTime(const double delay) noexcept
{
    mStation->setSDelayTime(delay);
}
double StationArchiveLine::getSDelayTime() const
{
    return mStation->getSDelayTime();
}
bool StationArchiveLine::haveSDelayTime() const noexcept
{
    return mStation->haveSDelayTime();
}

void StationArchiveLine::setSImportance(const double importance)
{
    mStation->setSImportance(importance);
}
double StationArchiveLine::getSImportance() const
{
    return mStation->getSImportance();
}
bool StationArchiveLine::haveSImportance() const noexcept
{
    return mStation->haveSImportance();
}

// Magnitudes and miscellaneous
void StationArchiveLine::setAmplitudeMagnitude(const double magnitude) noexcept
{
    mStation->setAmplitudeMagnitudeLabel(magnitude);
}
double StationArchiveLine::getAmplitudeMagnitude() const
{
    return mStation->getAmplitudeMagnitudeLabel();
}
bool StationArchiveLine::haveAmplitudeMagnitude() const noexcept
{
    return mStation->haveAmplitudeMagnitudeLabel();
}

void StationArchiveLine::setAmplitudeMagnitudeWeightCode(const int code)
{
    mStation->setAmplitudeMagnitudeWeightCode(code);
}
int StationArchiveLine::getAmplitudeMagnitudeWeightCode() const
{
    return mStation->getAmplitudeMagnitudeWeightCode();
}
bool StationArchiveLine::haveAmplitudeMagnitudeWeightCode() const noexcept
{
    return mStation->haveAmplitudeMagnitudeWeightCode();
}

void StationArchiveLine::setAmplitudeMagnitudeLabel(const char label)
{
    mStation->setAmplitudeMagnitudeLabel(label);
}
char StationArchiveLine::getAmplitudeMagnitudeLabel() const
{
    return mStation->getAmplitudeMagnitudeLabel();
}
bool StationArchiveLine::haveAmplitudeMagnitudeLabel() const noexcept
{
    return mStation->haveAmplitudeMagnitudeLabel();
}

void StationArchiveLine::setPeriodOfAmplitudeMeasurement(const double period)
{
    mStation->setPeriodOfAmplitudeMeasurement(period);
}
double StationArchiveLine::getPeriodOfAmplitudeMeasurement() const
{
    return mStation->getPeriodOfAmplitudeMeasurement();
}
bool StationArchiveLine::havePeriodOfAmplitudeMeasurement() const noexcept
{
    return mStation->havePeriodOfAmplitudeMeasurement();
}

void StationArchiveLine::setDurationMagnitude(const double magnitude) noexcept
{
    mStation->setDurationMagnitudeLabel(magnitude);
}
double StationArchiveLine::getDurationMagnitude() const
{
    return mStation->getDurationMagnitudeLabel();
}
bool StationArchiveLine::haveDurationMagnitude() const noexcept
{
    return mStation->haveDurationMagnitudeLabel();
}

void StationArchiveLine::setDurationMagnitudeWeightCode(const int code)
{
    mStation->setDurationMagnitudeWeightCode(code);
}
int StationArchiveLine::getDurationMagnitudeWeightCode() const
{
    return mStation->getDurationMagnitudeWeightCode();
}
bool StationArchiveLine::haveDurationMagnitudeWeightCode() const noexcept
{
    return mStation->haveDurationMagnitudeWeightCode();
}

void StationArchiveLine::setDurationMagnitudeLabel(const char label)
{
    mStation->setDurationMagnitudeLabel(label);
}
char StationArchiveLine::getDurationMagnitudeLabel() const
{
    return mStation->getDurationMagnitudeLabel();
}
bool StationArchiveLine::haveDurationMagnitudeLabel() const noexcept
{
    return mStation->haveDurationMagnitudeLabel();
}

void StationArchiveLine::setCodaDuration(const double duration)
{
    mStation->setCodaDuration(duration);
}
double StationArchiveLine::getCodaDuration() const
{
    return mStation->getCodaDuration();
}
bool StationArchiveLine::haveCodaDuration() const noexcept
{
    return mStation->haveCodaDuration();
}

void StationArchiveLine::setDataSourceCode(const char code)
{
    mStation->setDataSourceCode(code);
}
char StationArchiveLine::getDataSourceCode() const
{
    return mStation->getDataSourceCode();
}
bool StationArchiveLine::haveDataSourceCode() const noexcept
{
    return mStation->haveDataSourceCode();
}

void StationArchiveLine::setAmplitude(const double amplitude)
{
    mStation->setAmplitude(amplitude);
}
double StationArchiveLine::getAmplitude() const
{
    return mStation->getAmplitude();
}
bool StationArchiveLine::haveAmplitude() const noexcept
{
    return mStation->haveAmplitude();
}

void StationArchiveLine::setAmplitudeUnits(
    const SFF::HypoInverse2000::AmplitudeUnits units) noexcept
{
    mStation->setAmplitudeUnits(units);
}
SFF::HypoInverse2000::AmplitudeUnits
StationArchiveLine::getAmplitudeUnits() const
{
    return mStation->getAmplitudeUnits();
}
bool StationArchiveLine::haveAmplitudeUnits() const noexcept
{
    return mStation->haveAmplitudeUnits();
}

///--------------------------------------------------------------------------///
///                               Initialize                                 ///
///--------------------------------------------------------------------------///
void PBSFF::HypoInverse2000::initialize(pybind11::module &m)
{
    pybind11::class_<PBSFF::HypoInverse2000::StationArchiveLine> sta(m, "StationArchiveLine");
    sta.def(pybind11::init<> ());
    sta.doc() = "This is used for reading and writing HypoInverse2000 station archive lines.";

    sta.def("unpack_string", &StationArchiveLine::unpackString,
            "Unpacks a station archive line and populates members of this class.");
    sta.def("pack_string", &StationArchiveLine::packString,
            "Converts the members of this class to a string to write to an archive file.");

    sta.def("set_network_name", &StationArchiveLine::setNetworkName,
            "Sets the network name.");
    sta.def("get_network_name", &StationArchiveLine::getNetworkName,
            "Gets the network name.");
    sta.def("have_network_name", &StationArchiveLine::haveNetworkName,
            "True indicates that the network name was set.");

    sta.def("set_station_name", &StationArchiveLine::setStationName,
            "Sets the station's name.");
    sta.def("get_station_name", &StationArchiveLine::getStationName,
            "Gets the station's name.");
    sta.def("have_station_name", &StationArchiveLine::haveStationName,
            "True indicates that the station name was set.");

    sta.def("set_channel_name", &StationArchiveLine::setChannelName,
            "Sets the channel on which the pick was made.");
    sta.def("get_channel_name", &StationArchiveLine::getChannelName,
            "Gets the channel on which the pick was made.");
    sta.def("have_channel_name", &StationArchiveLine::haveChannelName,
            "True indicates that the channel name was set.");

    sta.def("set_location_code", &StationArchiveLine::setLocationCode,
            "Sets the location code.");
    sta.def("get_location_code", &StationArchiveLine::getLocationCode,
            "Gets the location code.");
    sta.def("have_location_code", &StationArchiveLine::haveLocationCode,
            "True indicates that the location code was set.");

    sta.def("set_epicentral_distance", &StationArchiveLine::setEpicentralDistance,
            "Sets the source-receiver epicentral distance in kilometers.");
    sta.def("get_epicentral_distance", &StationArchiveLine::getEpicentralDistance,
            "Gets the source-receiver epicentral distance in kilometers.");
    sta.def("have_epicentral_distance", &StationArchiveLine::haveEpicentralDistance,
            "True indicates that the source-receiver epicentral distance was set.");

    sta.def("set_azimuth", &StationArchiveLine::setAzimuth,
            "Sets the source-receiver azimuth.  This is measured in degrees and is positive east of north.");
    sta.def("get_azimuth", &StationArchiveLine::getAzimuth,
            "Gets the source-receiver azimuth in degrees.");
    sta.def("have_azimuth", &StationArchiveLine::haveAzimuth,
            "True indicates that the source-receiver azimuth was set.");

    sta.def("set_takeoff_angle", &StationArchiveLine::setTakeOffAngle,
            "Sets the takeoff angle (degrees) where 0 is up and 180 is down.");
    sta.def("get_takeoff_angle", &StationArchiveLine::getTakeOffAngle,
            "Gets the takeoff angle in degrees.");
    sta.def("have_takeoff_angle", &StationArchiveLine::haveTakeOffAngle,
            "True indicates that the takeoff angle was set.");

    sta.def("set_p_pick_time", &StationArchiveLine::setPPickTime,
            "Sets the P-pick time.");
    sta.def("get_p_pick_time", &StationArchiveLine::getPPickTime,
            "Gets the P-Pick time.");
    sta.def("have_p_pick_time", &StationArchiveLine::havePPickTime,
            "True indicates that the P-Pick time was set.");
    sta.def("set_p_remark", &StationArchiveLine::setPRemark,
            "Sets the P remark.  For example, an emergent P pick may be denoted by eP.");
    sta.def("get_p_remark", &StationArchiveLine::getPRemark,
            "Gets the P remark.");
    sta.def("have_p_remark", &StationArchiveLine::havePRemark,
            "True indicates that the P remark was set.");
    sta.def("set_first_motion", &StationArchiveLine::setFirstMotion,
            "Sets the first motion of the P wave.  For example, U may indicate Up.");
    sta.def("get_first_motion", &StationArchiveLine::getFirstMotion,
            "Gets the first motion of the P wave.");
    sta.def("have_first_motion", &StationArchiveLine::haveFirstMotion,
            "True indicates that the first motion was set.");
    sta.def("set_p_residual", &StationArchiveLine::setPResidual,
            "Sets the P travel time residual in seconds.");
    sta.def("get_p_residual", &StationArchiveLine::getPResidual,
            "Gets the P travel time residual in seconds.");
    sta.def("have_p_residual", &StationArchiveLine::havePResidual,
            "True indicates that the P residual travel time was set.");
    sta.def("set_p_weight_code", &StationArchiveLine::setPWeightCode,
            "Sets the P weight code.");
    sta.def("get_p_weight_code", &StationArchiveLine::getPWeightCode,
            "Gets the P weight code.");
    sta.def("have_p_weight_code", &StationArchiveLine::havePWeightCode,
            "True indicates that the P weight code was set.");
    sta.def("set_p_weight_used", &StationArchiveLine::setPWeightUsed,
            "Sets the P weight used by HypoInverse2000.");
    sta.def("get_p_weight_used", &StationArchiveLine::getPWeightUsed,
            "Gets the P weight used by HypoInverse2000.");
    sta.def("have_p_weight_used", &StationArchiveLine::havePWeightUsed,
            "True indicates that the P weight used by HypoInverse2000 is set.");
    sta.def("set_p_delay_time", &StationArchiveLine::setPDelayTime,
            "Sets the P delay time (static correction) in seconds.");
    sta.def("get_p_delay_time", &StationArchiveLine::getPDelayTime,
            "Gets the P delay time in seconds.");
    sta.def("have_p_delay_time", &StationArchiveLine::havePDelayTime,
            "True indicates that the P delay time is set.");
    sta.def("set_p_importance", &StationArchiveLine::setPImportance,
            "Sets the P importance determined by HypoInverse2000.");
    sta.def("get_p_importance", &StationArchiveLine::getPImportance,
            "Gets the P importance determined by HypoInverse2000.");
    sta.def("have_p_importance", &StationArchiveLine::havePImportance,
            "True indicates that the P importance is set.");

    sta.def("set_s_pick_time", &StationArchiveLine::setSPickTime,
            "Sets the S-pick time.");
    sta.def("get_s_pick_time", &StationArchiveLine::getSPickTime,
            "Gets the S-Pick time.");
    sta.def("have_s_pick_time", &StationArchiveLine::haveSPickTime,
            "True indicates that the S-Pick time was set.");
    sta.def("set_s_remark", &StationArchiveLine::setSRemark,
            "Sets the S remark.  For example, an impulsive S pick may be denoted by iS.");
    sta.def("get_s_remark", &StationArchiveLine::getSRemark,
            "Gets the S remark.");
    sta.def("have_s_remark", &StationArchiveLine::haveSRemark,
            "True indicates that the S remark was set.");
    sta.def("set_s_residual", &StationArchiveLine::setSResidual,
            "Sets the S travel time residual in seconds.");
    sta.def("get_s_residual", &StationArchiveLine::getSResidual,
            "Gets the S travel time residual in seconds.");
    sta.def("have_s_residual", &StationArchiveLine::haveSResidual,
            "True indicates that the S residual travel time was set.");
    sta.def("set_s_weight_code", &StationArchiveLine::setSWeightCode,
            "Sets the S weight code.");
    sta.def("get_s_weight_code", &StationArchiveLine::getSWeightCode,
            "Gets the S weight code.");
    sta.def("have_s_weight_code", &StationArchiveLine::haveSWeightCode,
            "True indicates that the P weight code was set.");
    sta.def("set_s_weight_used", &StationArchiveLine::setSWeightUsed,
            "Sets the S weight used by HypoInverse2000.");
    sta.def("get_s_weight_used", &StationArchiveLine::getSWeightUsed,
            "Gets the S weight used by HypoInverse2000.");
    sta.def("have_s_weight_used", &StationArchiveLine::haveSWeightUsed,
            "True indicates that the S weight used by HypoInverse2000 is set.");
    sta.def("set_s_delay_time", &StationArchiveLine::setSDelayTime,
            "Sets the S delay time (static correction) in seconds.");
    sta.def("get_s_delay_time", &StationArchiveLine::getSDelayTime,
            "Gets the S delay time in seconds.");
    sta.def("have_s_delay_time", &StationArchiveLine::haveSDelayTime,
            "True indicates that the S delay time is set.");
    sta.def("set_s_importance", &StationArchiveLine::setSImportance,
            "Sets the S importance determined by HypoInverse2000.");
    sta.def("get_s_importance", &StationArchiveLine::getSImportance,
            "Gets the S importance determined by HypoInverse2000.");
    sta.def("have_s_importance", &StationArchiveLine::haveSImportance,
            "True indicates that the S importance is set.");

    sta.def("set_amplitude", &StationArchiveLine::getAmplitude,
            "Sets the amplitude, e.g., the peak-to-peak amplitude.");
    sta.def("get_amplitude", &StationArchiveLine::getAmplitude,
            "Gets the amplitude");
    sta.def("have_amplitude", &StationArchiveLine::haveAmplitude,
            "True indicates that the amplitude was set.");

    sta.def("set_amplitude_units", &StationArchiveLine::getAmplitudeUnits,
            "Sets the amplitude units.");
    sta.def("get_amplitude_units", &StationArchiveLine::getAmplitudeUnits,
            "Gets the amplitude units.");
    sta.def("have_amplitude_units", &StationArchiveLine::haveAmplitudeUnits,
            "True indicates that the amplitude units were set.");
}
