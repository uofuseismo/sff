#ifndef SFF_PYTHON_HYPOINVERSE2000_HPP
#define SFF_PYTHON_HYPOINVERSE2000_HPP
#include <memory>
#include <string>
#include <pybind11/numpy.h>
#include "time.hpp"

namespace SFF::HypoInverse2000
{
class EventSummary;
class EventSummaryLine;
class StationArchiveLine;
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

}
#endif
