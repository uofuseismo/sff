#ifndef PYSFF_TIME_HPP
#define PYSFF_TIME_HPP
#include <memory>
#include <pybind11/pybind11.h>

namespace SFF::Utilities
{
class Time;
}

namespace PBSFF
{
class Time
{
public:
    /// Constructor
    Time();
    /// Copy c'tors
    Time(const Time &time);
    Time(const SFF::Utilities::Time &time);
    /// Copy assignment
    Time& operator=(const Time &time);
    Time& operator=(const SFF::Utilities::Time &time);
    /// Add/subtract operators
    Time operator+(const Time &t);
    Time operator-(const Time &t);
    /// Add/subtract operators
    Time operator+(double t);
    Time operator-(double t);
    /// Destructor
    ~Time();

    /// Attributes
    void setEpochalTime(double epoch);
    double getEpochalTime() const;

    void setYear(int year);
    int getYear() const;

    void setDayOfYear(int jday);
    int getDayOfYear() const;

    void setMonthAndDay(const std::pair<int, int>  &md);
    int getMonth() const;

    int getDayOfMonth() const;

    void setHour(int hour);
    int getHour() const;

    void setMinute(int minute);
    int getMinute() const;

    void setSecond(int second);
    int getSecond() const;

    void setMicroSecond(int musec);
    int getMicroSecond() const; 

    SFF::Utilities::Time getNativeClass() const;

    std::string toString() const noexcept;
private:
    std::unique_ptr<SFF::Utilities::Time> mTime;
};
void initializeTime(pybind11::module &m);
}
#endif
