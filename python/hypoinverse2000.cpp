#include "sff/hypoinverse2000/stationArchiveLine.hpp"
#include "sff/hypoinverse2000/eventSummaryLine.hpp"
#include "sff/hypoinverse2000/eventSummary.hpp"
#include "hypoinverse2000.hpp"
#include <pybind11/stl.h>
#include <vector>
#include <string>

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
    mStation->setAmplitudeMagnitude(magnitude);
}
double StationArchiveLine::getAmplitudeMagnitude() const
{
    return mStation->getAmplitudeMagnitude();
}
bool StationArchiveLine::haveAmplitudeMagnitude() const noexcept
{
    return mStation->haveAmplitudeMagnitude();
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
    mStation->setDurationMagnitude(magnitude);
}
double StationArchiveLine::getDurationMagnitude() const
{
    return mStation->getDurationMagnitude();
}
bool StationArchiveLine::haveDurationMagnitude() const noexcept
{
    return mStation->haveDurationMagnitude();
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

//---------------------------------------------------------------------------///
///                             EventSummaryLine                             ///
///--------------------------------------------------------------------------///
/// C'tors
EventSummaryLine::EventSummaryLine() :
    mEventLine(std::make_unique<SFF::HypoInverse2000::EventSummaryLine> ())
{
}

EventSummaryLine::EventSummaryLine(const EventSummaryLine &summary)
{
    *this = summary;
}

EventSummaryLine::EventSummaryLine(
    const SFF::HypoInverse2000::EventSummaryLine &summary)
{
    *this = summary;
}
SFF::HypoInverse2000::EventSummaryLine
EventSummaryLine::getNativeClass() const
{
    SFF::HypoInverse2000::EventSummaryLine archive(*mEventLine);
    return archive;
}
/// Operators
EventSummaryLine& EventSummaryLine::operator=(const EventSummaryLine &summary)
{
    if (&summary == this){return *this;}
    mEventLine = std::make_unique<SFF::HypoInverse2000::EventSummaryLine>
                 (*summary.mEventLine);
    return *this;
}

EventSummaryLine& EventSummaryLine::operator=(
    const SFF::HypoInverse2000::EventSummaryLine &summary)
{
    mEventLine = std::make_unique<SFF::HypoInverse2000::EventSummaryLine>
                 (summary);
    return *this;
}
/// Destructors
EventSummaryLine::~EventSummaryLine() = default;

void EventSummaryLine::clear() noexcept
{
    mEventLine->clear();
}
/// Pack/unpack
void EventSummaryLine::unpackString(const std::string &line)
{
    mEventLine->unpackString(line);
}
std::string EventSummaryLine::packString() const
{
    return mEventLine->packString();
}

/// Methods
void EventSummaryLine::setLatitude(const double latitude)
{
    mEventLine->setLatitude(latitude);
}
double EventSummaryLine::getLatitude() const
{
    return mEventLine->getLatitude();
}
bool EventSummaryLine::haveLatitude() const noexcept
{
    return mEventLine->haveLatitude();
}

void EventSummaryLine::setLongitude(const double longitude)
{
    mEventLine->setLongitude(longitude);
}
double EventSummaryLine::getLongitude() const
{
    return mEventLine->getLongitude();
}
bool EventSummaryLine::haveLongitude() const noexcept
{
    return mEventLine->haveLongitude();
}

void EventSummaryLine::setDepth(const double depth) noexcept
{
    mEventLine->setDepth(depth);
}
double EventSummaryLine::getDepth() const
{
    return mEventLine->getDepth();
}
bool EventSummaryLine::haveDepth() const noexcept
{
    return mEventLine->haveDepth();
}

void EventSummaryLine::setOriginTime(const PBSFF::Time &originTime) noexcept
{
    mEventLine->setOriginTime(originTime.getNativeClass());
}
PBSFF::Time EventSummaryLine::getOriginTime() const
{
    PBSFF::Time time(mEventLine->getOriginTime());
    return time;
}
bool EventSummaryLine::haveOriginTime() const noexcept
{
    return mEventLine->haveOriginTime();
}

void EventSummaryLine::setPreferredMagnitudeLabel(const char label)
{
    mEventLine->setPreferredMagnitudeLabel(label);
}
char EventSummaryLine::getPreferredMagnitudeLabel() const
{
    return mEventLine->getPreferredMagnitudeLabel();
}
bool EventSummaryLine::havePreferredMagnitudeLabel() const noexcept
{
    return mEventLine->havePreferredMagnitudeLabel();
}

void EventSummaryLine::setPreferredMagnitude(const double magnitude) noexcept
{
    mEventLine->setPreferredMagnitude(magnitude);
}
double EventSummaryLine::getPreferredMagnitude() const
{
    return mEventLine->getPreferredMagnitude();
}
bool EventSummaryLine::havePreferredMagnitude() const noexcept
{
    return mEventLine->havePreferredMagnitude();
}

void EventSummaryLine::setEventIdentifier(const uint64_t evid) noexcept
{
    mEventLine->setEventIdentifier(evid);
}
uint64_t EventSummaryLine::getEventIdentifier() const
{
    return mEventLine->getEventIdentifier();
}
bool EventSummaryLine::haveEventIdentifier() const noexcept
{
    return mEventLine->haveEventIdentifier();
}

void EventSummaryLine::setNumberOfFirstMotions(const int nFirstMotions)
{
    mEventLine->setNumberOfFirstMotions(nFirstMotions);
}
int EventSummaryLine::getNumberOfFirstMotions() const
{
    return mEventLine->getNumberOfFirstMotions();
}
bool EventSummaryLine::haveNumberOfFirstMotions() const noexcept
{
    return mEventLine->haveNumberOfFirstMotions();
}

void EventSummaryLine::setDistanceToClosestStation(const double distance)
{
    mEventLine->setDistanceToClosestStation(distance);
}
double EventSummaryLine::getDistanceToClosestStation() const
{
    return mEventLine->getDistanceToClosestStation();
}
bool EventSummaryLine::haveDistanceToClosestStation() const noexcept
{
    return mEventLine->haveDistanceToClosestStation();
}

void EventSummaryLine::setAzimuthalGap(const double gap)
{
    mEventLine->setAzimuthalGap(gap);
}
double EventSummaryLine::getAzimuthalGap() const
{
    return mEventLine->getAzimuthalGap();
}
bool EventSummaryLine::haveAzimuthalGap() const noexcept
{
    return mEventLine->haveAzimuthalGap();
}

void EventSummaryLine::setNumberOfWeightedResiduals(const int nResiduals)
{
    mEventLine->setNumberOfWeightedResiduals(nResiduals);
}
int EventSummaryLine::getNumberOfWeightedResiduals() const
{
    return mEventLine->getNumberOfWeightedResiduals();
}
bool EventSummaryLine::haveNumberOfWeightedResiduals() const noexcept
{
    return mEventLine->haveNumberOfWeightedResiduals();
}

void EventSummaryLine::setNumberOfSWeightedResiduals(const int nResiduals)
{
    mEventLine->setNumberOfSWeightedResiduals(nResiduals);
}
int EventSummaryLine::getNumberOfSWeightedResiduals() const
{
    return mEventLine->getNumberOfSWeightedResiduals();
}
bool EventSummaryLine::haveNumberOfSWeightedResiduals() const noexcept
{
    return mEventLine->haveNumberOfSWeightedResiduals();
}

void EventSummaryLine::setResidualTravelTimeRMS(const double rms)
{
    mEventLine->setResidualTravelTimeRMS(rms);
}
double EventSummaryLine::getResidualTravelTimeRMS() const
{
    return mEventLine->getResidualTravelTimeRMS();
}
bool EventSummaryLine::haveResidualTravelTimeRMS() const noexcept
{
    return mEventLine->haveResidualTravelTimeRMS();
}
///--------------------------------------------------------------------------///
///                            Create an Event                               ///
///--------------------------------------------------------------------------///
EventSummary::EventSummary() :
    mEvent(std::make_unique<SFF::HypoInverse2000::EventSummary> ())
{
}
EventSummary::EventSummary(const EventSummary &summary)
{
    *this = summary;
}
EventSummary::EventSummary(const SFF::HypoInverse2000::EventSummary &summary)
{
    *this = summary;
}
// Operators
EventSummary& EventSummary::operator=(const EventSummary &summary)
{
    if (&summary == this){return *this;}
    mEvent = std::make_unique<SFF::HypoInverse2000::EventSummary>
             (*summary.mEvent);
    return *this;
}
EventSummary&
EventSummary::operator=(const SFF::HypoInverse2000::EventSummary &summary)
{
    mEvent = std::make_unique<SFF::HypoInverse2000::EventSummary> (summary);
    return *this;
}
/// Destructors
EventSummary::~EventSummary() = default;
void EventSummary::clear() noexcept
{
    mEvent->clear();
}

SFF::HypoInverse2000::EventSummary EventSummary::getNativeClass() const
{
    SFF::HypoInverse2000::EventSummary result(*mEvent);
    return result;
}

void EventSummary::clearPicks() noexcept
{
    mEvent->clearPicks();
}
void EventSummary::addPPick(
    const PBSFF::HypoInverse2000::StationArchiveLine &pPick)
{
    mEvent->addPPick(pPick.getNativeClass());
}
void EventSummary::addSPick(
    const PBSFF::HypoInverse2000::StationArchiveLine &sPick)
{
    mEvent->addSPick(sPick.getNativeClass());
}
int EventSummary::getNumberOfPicks() const noexcept
{
    return mEvent->getNumberOfPicks();
}
void EventSummary::unpackString(const std::vector<std::string> &lines)
{
    if (lines.empty())
    {
        throw std::invalid_argument("Summary lines are empty");
    }
    //for (const auto &line: lines){std::cout << line << std::endl;}
    return mEvent->unpackString(lines);
}
std::string EventSummary::packString() const
{
    return mEvent->packString();
}
EventSummaryLine EventSummary::getEventInformation() const
{
    EventSummaryLine result(mEvent->getEventInformation());
    return result;
}

///--------------------------------------------------------------------------///
///                               Initialize                                 ///
///--------------------------------------------------------------------------///
void PBSFF::HypoInverse2000::initialize(pybind11::module &m)
{
    pybind11::class_<PBSFF::HypoInverse2000::StationArchiveLine> sta(m, "StationArchiveLine");
    sta.def(pybind11::init<> ());
    sta.doc() = "This is used for reading and writing HypoInverse2000 station archive lines.";

    pybind11::enum_<SFF::HypoInverse2000::AmplitudeUnits> (sta, "AmplitudeUnits")
        .value("peak_to_peak",   SFF::HypoInverse2000::AmplitudeUnits::PEAK_TO_PEAK, "Amplitude is measured peak-to-peak.")
        .value("zero_to_peak",   SFF::HypoInverse2000::AmplitudeUnits::ZERO_TO_PEAK, "Amplitude is measured zero-to-peak.")
        .value("digital_counts", SFF::HypoInverse2000::AmplitudeUnits::DIGITAL_COUNTS, "Amplitude is measured in digital counts.");

    sta.def("unpack_string", &StationArchiveLine::unpackString,
            "Unpacks a station archive line and populates members of this class.");
    sta.def("pack_string", &StationArchiveLine::packString,
            "Converts the members of this class to a string to write to an archive file.");
    sta.def("clear", &StationArchiveLine::clear, "Resets the class.");

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

    sta.def("set_amplitude_magnitude", &StationArchiveLine::setAmplitudeMagnitude,
            "Sets the amplitude magnitude, e.g., Richter magnitude.");
    sta.def("get_amplitude_magnitude", &StationArchiveLine::getAmplitudeMagnitude,
            "Gets the amplitude magnitude.");
    sta.def("have_amplitude_magnitude", &StationArchiveLine::haveAmplitudeMagnitude,
            "True indicates that the amplitude magnitude was set.");
   
    sta.def("set_amplitude_magnitude_weight_code", &StationArchiveLine::setAmplitudeMagnitudeWeightCode,
            "Sets the amplitude magnitude weight code.");
    sta.def("get_amplitude_magnitude_weight_code", &StationArchiveLine::getAmplitudeMagnitudeWeightCode,
            "Gets the amplitude magnitude weight code.");
    sta.def("have_amplitude_magnitude_weight_code", &StationArchiveLine::haveAmplitudeMagnitudeWeightCode,
            "True indicates that the amplitude magnitude weight code was set.");

    sta.def("set_amplitude_magnitude_label", &StationArchiveLine::setAmplitudeMagnitudeLabel,
            "Sets the amplitude magnitude label, e.g., 'L' could denote local.");
    sta.def("get_amplitude_magnitude_label", &StationArchiveLine::getAmplitudeMagnitudeLabel,
            "Gets the amplitude magnitude label.");
    sta.def("have_amplitude_magnitude_label", &StationArchiveLine::haveAmplitudeMagnitudeLabel,
            "True indicates that the amplitude magnitude label was set.");

    sta.def("set_period_of_amplitude_measurement", &StationArchiveLine::setPeriodOfAmplitudeMeasurement,
            "Sets the period, in seconds, at which the amplitude measurement was made.  There might be a bug in operations because this typically looks like a frequency.");
    sta.def("get_period_of_amplitude_measurement", &StationArchiveLine::getPeriodOfAmplitudeMeasurement,
            "Gets the period, in seconds, at which the amplitude measurement was made.");
    sta.def("have_period_of_amplitude_measurement", &StationArchiveLine::havePeriodOfAmplitudeMeasurement,
            "True inddicates that the period of the amplitude measurement was set.");
   
    sta.def("set_duration_magnitude", &StationArchiveLine::setDurationMagnitude,
            "Sets the duration magnitude, e.g., coda magnitude.");
    sta.def("get_duration_magnitude", &StationArchiveLine::getDurationMagnitude,
            "Gets the duration magnitude.");
    sta.def("have_duration_magnitude", &StationArchiveLine::haveDurationMagnitude,
            "True indicates that the duration magnitude was set.");

    sta.def("set_duration_magnitude_weight_code", &StationArchiveLine::setDurationMagnitudeWeightCode,
            "Sets the duration magnitude weight code.");
    sta.def("get_duration_magnitude_weight_code", &StationArchiveLine::getDurationMagnitudeWeightCode,
            "Gets the duration magnitude weight code.");
    sta.def("have_duration_magnitude_weight_code", &StationArchiveLine::haveDurationMagnitudeWeightCode,
            "True indicates that the duration magnitude weight code was set.");

    sta.def("set_duration_magnitude_label", &StationArchiveLine::setDurationMagnitudeLabel,
            "Sets the duration magnitude label, e.g., 'D' could denote a duration magnitude.");
    sta.def("get_duration_magnitude_label", &StationArchiveLine::getDurationMagnitudeLabel,
            "Gets the duration magnitude label.");
    sta.def("have_duration_magnitude_label", &StationArchiveLine::haveDurationMagnitudeLabel,
            "True indicates that the duration magnitude label was set.");

    sta.def("set_coda_duration", &StationArchiveLine::setCodaDuration,
            "Sets the coda duration in seconds.");
    sta.def("get_coda_duration", &StationArchiveLine::getCodaDuration,
            "Gets the coda duration in seconds.");
    sta.def("have_coda_duration", &StationArchiveLine::haveCodaDuration,
            "True indicates that the coda duration is set.");
   
    sta.def("set_data_source_code", &StationArchiveLine::setDataSourceCode,
            "Sets the data source from which the pick was generated.  For example 'J', could denote Jiggle."); 
    sta.def("get_data_source_code", &StationArchiveLine::getDataSourceCode,
            "Gets the data source from which the pick was generated.");
    sta.def("have_data_source_code", &StationArchiveLine::haveDataSourceCode,
            "True indicates that the data source code was set.");

    sta.def("set_amplitude_units", &StationArchiveLine::setAmplitudeUnits,
            "Sets the amplitude units.");
    sta.def("get_amplitude_units", &StationArchiveLine::getAmplitudeUnits,
            "Gets the amplitude units.");
    sta.def("have_amplitude_units", &StationArchiveLine::haveAmplitudeUnits,
            "True indicates that the amplitude units were set.");

    //------------------------------------------------------------------------//
    pybind11::class_<PBSFF::HypoInverse2000::EventSummaryLine> evl(m, "EventSummaryLine");
    evl.def(pybind11::init<> ());
    evl.doc() = "This is used for reading and writing HypoInverse2000 event summary lines in archive files.";
    evl.def("unpack_string", &EventSummaryLine::unpackString,
            "Unpacks an event summary line and populates members of this class.");
    evl.def("pack_string", &EventSummaryLine::packString,
            "Converts the members of this class to a string to write to an archive file.");
    evl.def("clear", &EventSummaryLine::clear, "Resets the class and releases memory.");

    evl.def("set_latitude", &EventSummaryLine::setLatitude,
            "Sets the event latitude in degrees.  This must be in the range [-90,90].");
    evl.def("get_latitude", &EventSummaryLine::getLatitude,
            "Gets the event latitude in degrees.");
    evl.def("have_latitude", &EventSummaryLine::haveLatitude,
            "True indicates that the event latitude is set.");

    evl.def("set_longitude", &EventSummaryLine::setLongitude,
            "Sets the event latitude in degrees.  This must be in the range [-540,540) and assumes positive is east.");
    evl.def("get_longitude", &EventSummaryLine::getLongitude,
            "Gets the event longitude in degrees.  This will be in the range [0,360]");
    evl.def("have_longitude", &EventSummaryLine::haveLongitude,
            "True indicates that the event longitude is set.");

    evl.def("set_depth", &EventSummaryLine::setDepth, "Sets the event depth.");
    evl.def("get_depth", &EventSummaryLine::getDepth, "Gets the event depth.");
    evl.def("have_depth", &EventSummaryLine::haveDepth, "True indicates that the event depth is set.");

    evl.def("set_origin_time", &EventSummaryLine::setOriginTime,
            "Sets the event's origin time.");
    evl.def("get_origin_time", &EventSummaryLine::getOriginTime,
            "Gets the event's origin time.");
    evl.def("have_origin_time", &EventSummaryLine::haveOriginTime,
            "True indicates that the event origin timeis set.");

    evl.def("set_preferred_magnitude_label", &EventSummaryLine::setPreferredMagnitudeLabel,
            "Sets the preferred magnitude label, e.g., 'L' for a local (Richter) magnitude.");
    evl.def("get_preferred_magnitude_label", &EventSummaryLine::getPreferredMagnitudeLabel,
            "Gets the preferred magnitude label.");
    evl.def("have_preferred_magnitude_label", &EventSummaryLine::havePreferredMagnitudeLabel,
            "True indicates preferred magnitude label is set.");

    evl.def("set_preferred_magnitude", &EventSummaryLine::setPreferredMagnitude,
            "Sets the preferred magnitude.");
    evl.def("get_preferred_magnitude", &EventSummaryLine::getPreferredMagnitude,
            "Gets the preferred magnitude.");
    evl.def("have_preferred_magnitude", &EventSummaryLine::havePreferredMagnitude,
            "True indicates preferred magnitude is set.");

    evl.def("set_event_identifier", &EventSummaryLine::setEventIdentifier,
            "Sets the event identifier number.");
    evl.def("get_event_identifier", &EventSummaryLine::getEventIdentifier,
            "Gets the event identifier.");
    evl.def("have_event_identifier", &EventSummaryLine::haveEventIdentifier,
            "True indicates that the event identifier is set.");

    evl.def("set_number_of_first_motions", &EventSummaryLine::setNumberOfFirstMotions,
            "Sets the number of first motions.");
    evl.def("get_number_of_first_motions", &EventSummaryLine::getNumberOfFirstMotions,
            "Gets the number of first motions.");
    evl.def("have_number_of_first_motions", &EventSummaryLine::haveNumberOfFirstMotions,
            "True indicates that the number of first motions is set.");

    evl.def("set_distance_to_closest_station", &EventSummaryLine::setDistanceToClosestStation,
            "Sets the minimum source-receiver epicentral distance in kilometers.");
    evl.def("get_distance_to_closest_station", &EventSummaryLine::getDistanceToClosestStation,
            "Gets the minimum source-receiver epicentral distance in kilomters.");
    evl.def("have_distance_to_closest_station", &EventSummaryLine::haveDistanceToClosestStation,
            "True indicates that minimum source-receiver distance is set.");

    evl.def("set_azimuthal_gap", &EventSummaryLine::setAzimuthalGap,
            "Sets the azimuthal gap in degress.  This must be in the range [0,360]");
    evl.def("get_azimuthal_gap", &EventSummaryLine::getAzimuthalGap, "Gets the azimuthal gap.");
    evl.def("have_azimuthal_gap", &EventSummaryLine::haveAzimuthalGap, "True indicates that the azimuthal gap was set.");

    evl.def("set_number_of_weighted_residuals", &EventSummaryLine::setNumberOfWeightedResiduals,
            "Sets the number of weighted residuals.");
    evl.def("get_number_of_weighted_residuals", &EventSummaryLine::getNumberOfWeightedResiduals,
            "Gets the number of weighted residuals.");
    evl.def("have_number_of_weighted_residuals", &EventSummaryLine::haveNumberOfWeightedResiduals,
            "True indicates that the number of weighted residuals is set.");

    evl.def("set_number_of_s_weighted_residuals", &EventSummaryLine::setNumberOfSWeightedResiduals,
            "Sets the number of S weighted residuals.");
    evl.def("get_number_of_s_weighted_residuals", &EventSummaryLine::getNumberOfSWeightedResiduals,
            "Gets the number of S weighted residuals.");
    evl.def("have_number_of_s_weighted_residuals", &EventSummaryLine::haveNumberOfSWeightedResiduals,
            "True indicates that the number of S weighted residuals is set.");

    evl.def("set_residual_traveltime_rms", &EventSummaryLine::setResidualTravelTimeRMS,
            "Sets the traveltime RMS residual in seconds.");
    evl.def("get_residual_traveltime_rms", &EventSummaryLine::getResidualTravelTimeRMS,
            "Gets the traveltime RMS residual in seconds.");
    evl.def("have_residual_traveltime_rms", &EventSummaryLine::haveResidualTravelTimeRMS,
            "True indicates that the RMS residual is set.");
    //------------------------------------------------------------------------//
    pybind11::class_<PBSFF::HypoInverse2000::EventSummary> ev(m, "EventSummary");
    ev.def(pybind11::init<> ());
    ev.doc() = "This is used for reading and writing HypoInverse2000 event summaries.  An event summary is comprised of an event summary line and its corresponding picks.";

    ev.def("pack_string", &EventSummary::packString, "Converts the class to an output string.");
    ev.def("unpack_string", &EventSummary::unpackString, "Unpacks the lines comprising an event.  Here the first line corresponds to the header while the subsequent lines correspond to a pick.");
    ev.def("get_event_information", &EventSummary::getEventInformation, "Gets the event summary line.");
    ev.def("clear", &EventSummary::clear, "Resets the class and releases memory.");
    ev.def("clear_picks", &EventSummary::clearPicks, "Removes the picks from the event.");
    ev.def("add_p_pick", &EventSummary::addPPick, "Adds a P pick to the event.");
    ev.def("add_s_pick", &EventSummary::addSPick, "Adds an S Pick to the event.");
}
