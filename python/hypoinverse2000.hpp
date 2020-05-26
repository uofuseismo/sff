#ifndef SFF_PYTHON_HYPOINVERSE2000_HPP
#define SFF_PYTHON_HYPOINVERSE2000_HPP
#include <memory>
#include <string>
#include "sff/hypoinverse2000/stationArchiveLine.hpp"
#include "time.hpp"

namespace SFF::HypoInverse2000
{
class EventSummary;
class EventSummaryLine;
class StationArchiveLine;
}
namespace PBSFF
{
class Time;
}

namespace PBSFF::HypoInverse2000
{
class StationArchiveLine
{
public:
    /// C'tors
    StationArchiveLine();
    StationArchiveLine(const StationArchiveLine &summary);
    StationArchiveLine(const SFF::HypoInverse2000::StationArchiveLine &summary);
    /// Operators
    StationArchiveLine& operator=(const StationArchiveLine &summary);
    StationArchiveLine& operator=(const SFF::HypoInverse2000::StationArchiveLine &summary);
    /// Gets a copy of the native class
    SFF::HypoInverse2000::StationArchiveLine getNativeClass() const;
    /// Destructors
    ~StationArchiveLine();
    void clear() noexcept;
    /// Packs/unpacks class
    void unpackString(const std::string &line);
    [[nodiscard]] std::string packString() const noexcept;

    void setNetworkName(const std::string &network) noexcept;
    [[nodiscard]] std::string getNetworkName() const;
    [[nodiscard]] bool haveNetworkName() const noexcept;

    void setStationName(const std::string &station) noexcept;
    [[nodiscard]] std::string getStationName() const;
    [[nodiscard]] bool haveStationName() const noexcept;

    void setChannelName(const std::string &channel) noexcept;
    [[nodiscard]] std::string getChannelName() const;
    [[nodiscard]] bool haveChannelName() const noexcept;

    void setLocationCode(const std::string &location) noexcept;
    [[nodiscard]] std::string getLocationCode() const;
    [[nodiscard]] bool haveLocationCode() const noexcept;

    void setEpicentralDistance(double distance);
    [[nodiscard]] double getEpicentralDistance() const;
    [[nodiscard]] bool haveEpicentralDistance() const noexcept;

    void setAzimuth(double azimuth);
    [[nodiscard]] double getAzimuth() const;
    [[nodiscard]] bool haveAzimuth() const noexcept;

    void setTakeOffAngle(double angle);
    [[nodiscard]] double getTakeOffAngle() const;
    [[nodiscard]] bool haveTakeOffAngle() const noexcept;

    void setPPickTime(const PBSFF::Time &pickTime) noexcept;
    [[nodiscard]] PBSFF::Time getPPickTime() const;
    [[nodiscard]] bool havePPickTime() const noexcept;

    void setPRemark(const std::string &remark) noexcept;
    [[nodiscard]] std::string getPRemark() const;
    [[nodiscard]] bool havePRemark() const noexcept;

    void setFirstMotion(char firstMotion) noexcept;
    [[nodiscard]] char getFirstMotion() const;
    [[nodiscard]] bool haveFirstMotion() const noexcept;

    void setPResidual(double residual) noexcept;
    [[nodiscard]] double getPResidual() const;
    [[nodiscard]] bool havePResidual() const noexcept;

    void setPWeightCode(uint16_t weightCode) noexcept;
    [[nodiscard]] int getPWeightCode() const;
    [[nodiscard]] bool havePWeightCode() const noexcept;

    void setPWeightUsed(double weightUsed);
    [[nodiscard]] double getPWeightUsed() const;
    [[nodiscard]] bool havePWeightUsed() const noexcept;

    void setPDelayTime(double delay) noexcept;
    [[nodiscard]] double getPDelayTime() const;
    [[nodiscard]] bool havePDelayTime() const noexcept;

    void setPImportance(double importance);
    [[nodiscard]] double getPImportance() const;
    [[nodiscard]] bool havePImportance() const noexcept;

    void setSPickTime(const PBSFF::Time &pickTime) noexcept;
    [[nodiscard]] PBSFF::Time getSPickTime() const;
    [[nodiscard]] bool haveSPickTime() const noexcept;

    void setSRemark(const std::string &remark) noexcept;
    [[nodiscard]] std::string getSRemark() const;
    [[nodiscard]] bool haveSRemark() const noexcept;

    void setSResidual(double residual) noexcept;
    [[nodiscard]] double getSResidual() const;
    [[nodiscard]] bool haveSResidual() const noexcept;

    void setSWeightCode(uint16_t weightCode) noexcept;
    [[nodiscard]] int getSWeightCode() const;
    [[nodiscard]] bool haveSWeightCode() const noexcept;

    void setSWeightUsed(double weightUsed);
    [[nodiscard]] double getSWeightUsed() const;
    [[nodiscard]] bool haveSWeightUsed() const noexcept;

    void setSDelayTime(double correction) noexcept;
    [[nodiscard]] double getSDelayTime() const;
    [[nodiscard]] bool haveSDelayTime() const noexcept;

    void setSImportance(double importance);
    [[nodiscard]] double getSImportance() const;
    [[nodiscard]] bool haveSImportance() const noexcept;

    void setAmplitudeMagnitude(double magnitude) noexcept;
    [[nodiscard]] double getAmplitudeMagnitude() const;
    [[nodiscard]] bool haveAmplitudeMagnitude() const noexcept;

    void setAmplitudeMagnitudeWeightCode(int code);
    [[nodiscard]] int getAmplitudeMagnitudeWeightCode() const;
    [[nodiscard]] bool haveAmplitudeMagnitudeWeightCode() const noexcept;

    void setAmplitudeMagnitudeLabel(char label);
    [[nodiscard]] char getAmplitudeMagnitudeLabel() const;
    [[nodiscard]] bool haveAmplitudeMagnitudeLabel() const noexcept;

    void setPeriodOfAmplitudeMeasurement(double period);
    [[nodiscard]] double getPeriodOfAmplitudeMeasurement() const;
    [[nodiscard]] bool havePeriodOfAmplitudeMeasurement() const noexcept;

    void setDurationMagnitude(double magnitude) noexcept;
    [[nodiscard]] double getDurationMagnitude() const;
    [[nodiscard]] bool haveDurationMagnitude() const noexcept;

    void setDurationMagnitudeWeightCode(int code);
    [[nodiscard]] int getDurationMagnitudeWeightCode() const;
    [[nodiscard]] bool haveDurationMagnitudeWeightCode() const noexcept;

    void setDurationMagnitudeLabel(char label);
    [[nodiscard]] char getDurationMagnitudeLabel() const;
    [[nodiscard]] bool haveDurationMagnitudeLabel() const noexcept;

    void setCodaDuration(double duration);
    [[nodiscard]] double getCodaDuration() const;
    [[nodiscard]] bool haveCodaDuration() const noexcept;

    void setDataSourceCode(char code);
    [[nodiscard]] char getDataSourceCode() const;
    [[nodiscard]] bool haveDataSourceCode() const noexcept;

    void setAmplitude(double amplitude);
    [[nodiscard]] double getAmplitude() const;
    [[nodiscard]] bool haveAmplitude() const noexcept;

    void setAmplitudeUnits(SFF::HypoInverse2000::AmplitudeUnits units) noexcept;
    [[nodiscard]] SFF::HypoInverse2000::AmplitudeUnits getAmplitudeUnits() const;
    [[nodiscard]] bool haveAmplitudeUnits() const noexcept;

private:
    std::unique_ptr<SFF::HypoInverse2000::StationArchiveLine> mStation;
};

class EventSummaryLine
{
public:
    /// C'tors
    EventSummaryLine();
    EventSummaryLine(const EventSummaryLine &summary);
    EventSummaryLine(const SFF::HypoInverse2000::EventSummaryLine &summary);
    /// Operators
    EventSummaryLine& operator=(const EventSummaryLine &summary);
    EventSummaryLine& operator=(const SFF::HypoInverse2000::EventSummaryLine &summary);
    /// Gets a copy of the native class
    SFF::HypoInverse2000::EventSummaryLine getNativeClass() const;
    /// Destructors
    ~EventSummaryLine();
    void clear() noexcept;
private:
    std::unique_ptr<SFF::HypoInverse2000::EventSummaryLine> mEventLine;
};

class EventSummary
{
public:
    /// C'tors
    EventSummary();
    EventSummary(const EventSummary &summary);
    EventSummary(const SFF::HypoInverse2000::EventSummary &summary);
    /// Operators
    EventSummary& operator=(const EventSummary &summary);
    EventSummary& operator=(const SFF::HypoInverse2000::EventSummary &summary);
    /// Destructors
    ~EventSummary();
    void clear() noexcept;
private:
    std::unique_ptr<SFF::HypoInverse2000::EventSummary> mEvent;
};
void initialize(pybind11::module &m);
}
#endif
