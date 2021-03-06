#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include "sff/utilities/time.hpp"
#include "time.hpp"

using namespace PBSFF;

/// Constructor
Time::Time() :
    mTime(std::make_unique<SFF::Utilities::Time> ())
{
}

/// Copy c'tor
Time::Time(const Time &time)
{
    *this = time;
}

Time::Time(const SFF::Utilities::Time &time)
{
    *this = time;
}

SFF::Utilities::Time Time::getNativeClass() const
{
    SFF::Utilities::Time timeOut(*mTime);
    return timeOut;    
}

/// Copy assignment
Time& Time::operator=(const Time &time)
{
    if (&time == this){return *this;}
    mTime = std::make_unique<SFF::Utilities::Time> (*time.mTime);
    return *this; 
}

Time& Time::operator=(const SFF::Utilities::Time &time)
{
    mTime = std::make_unique<SFF::Utilities::Time> (time);
    return *this;
}

/// Operators
Time Time::operator+(const Time &y)
{
    Time tout(*mTime + *y.mTime);
    return tout;    
}

Time Time::operator+(const double y)
{
    Time tout(*mTime + y);
    return tout;    
}

Time Time::operator-(const Time &y) 
{
    Time tout(*mTime - *y.mTime);
    return tout;    
}

Time Time::operator-(const double y) 
{
    Time tout(*mTime - y);
    return tout;    
}

/// Destructor 
Time::~Time() = default;

/// Get/Set Epochal Time
void Time::setEpochalTime(const double time)
{
    mTime->setEpoch(time);    
}

double Time::getEpochalTime() const
{
    return mTime->getEpoch();
}

/// Get/Set Year
void Time::setYear(const int year)
{
    mTime->setYear(year);
}

int Time::getYear() const
{
    return mTime->getYear();
}

/// Get/Set day of year
void Time::setDayOfYear(const int jday)
{
    mTime->setDayOfYear(jday);
}

int Time::getDayOfYear() const
{
    return mTime->getDayOfYear();
}

/// Get/Set month
void Time::setMonthAndDay(const std::pair<int, int> &md)
{
    mTime->setMonthAndDay(md);
}

int Time::getMonth() const
{
    return mTime->getMonth();
}

int Time::getDayOfMonth() const
{
    return mTime->getDayOfMonth();
}

/// Get/Set Hour
void Time::setHour(const int hour)
{
    mTime->setHour(hour);
}

int Time::getHour() const
{
    return mTime->getHour();
}

/// Get/Set Minute
void Time::setMinute(const int minute)
{
    mTime->setMinute(minute);
}

int Time::getMinute() const
{
    return mTime->getMinute();
}

/// Get/Set Second
void Time::setSecond(const int second)
{
    mTime->setSecond(second);
}

int Time::getSecond() const
{
    return mTime->getSecond();
}

/// Get/Set Micro-Second
void Time::setMicroSecond(const int musec)
{
    mTime->setMicroSecond(musec);
}

int Time::getMicroSecond() const
{
    return mTime->getMicroSecond();
}

/// Converts a time to string
std::string Time::toString() const noexcept
{
    std::stringstream ss;
    ss << *mTime;
    return ss.str();
}

/// Creates the class
void PBSFF::initializeTime(pybind11::module &m)
{
    pybind11::class_<PBSFF::Time> time(m, "Time");
    time.def(pybind11::init<> ());
    time.def("__copy__", [](const PBSFF::Time &self)
    {
        return PBSFF::Time(self);
    });
    //time.def("__deepcopy__", [](const PBSFF::Time &self, pybind11::dict)
    //{
    //    return PBSFF::Time(self);
    //}, "memo"_a);
    time.def("__add__", [](PBSFF::Time &a, const PBSFF::Time &b)
    {
        return a + b;
    }, pybind11::is_operator());
    time.def("__add__", [](PBSFF::Time &a, const double b) 
    {   
        return a + b;
    }, pybind11::is_operator());
    time.def("__sub__", [](PBSFF::Time &a, const PBSFF::Time &b)
    {
        return a - b;
    }, pybind11::is_operator());
    time.def("__sub__", [](PBSFF::Time &a, const double b) 
    {   
        return a - b;
    }, pybind11::is_operator());
    time.def("__repr__", &PBSFF::Time::toString);
    time.doc() = "This is used for managing converting between epochal and date-times.";
    time.def("get_epoch",
             &PBSFF::Time::getEpochalTime,
             "Gets the UTC time in seconds since the epoch (Jan 1, 1970).");
    time.def("set_epoch",
             &PBSFF::Time::setEpochalTime,
             "This defines the UTC time in seconds since epoch (Jan 1, 1970).");
    time.def("get_year",
             &PBSFF::Time::getYear,
             "Gets the year.");
    time.def("set_year",
             &PBSFF::Time::setYear,
             "This defines the time's year - e.g., 2020 indicates the year 2020.");
    time.def("get_day_of_year",
             &PBSFF::Time::getDayOfYear,
             "Gets the day of the year.");
    time.def("set_day_of_year",
             &PBSFF::Time::setDayOfYear,
             "There are two ways to specify the day of the year.  The first is with this function.  In this case, this must be in the range [1,366] where 366 accounts for leap years.  Setting this variable will invalidate the month and day of the month.");
    time.def("get_month",
             &PBSFF::Time::getMonth,
             "Gets the month of the year.");
    time.def("set_month_and_day",
             &PBSFF::Time::setMonthAndDay,
             "Sets the day of the year by setting the month and day of month.  The month must be in the range [1,12] and day of the month must be in the range [1,31]");
    time.def("get_day_of_month",
             &PBSFF::Time::getDayOfMonth,
             "Gets the day of the month.");
    time.def("get_hour",
             &PBSFF::Time::getHour,
             "Gets the hour of the day.");
    time.def("set_hour",
             &PBSFF::Time::setHour,
             "This specifies the hour of the day and must be in the range [0,23].");
    time.def("get_minute",
              &PBSFF::Time::getMinute,
             "Gets the minute of the hour.");
    time.def("set_minute",
             &PBSFF::Time::setMinute,
             "This specifies the minute of the hour and must be in the range [0,59].");
    time.def("get_second",
             &PBSFF::Time::getSecond,
             "Gets the second.");
    time.def("set_second",
             &PBSFF::Time::setSecond,
            "This specifies the second of the minute and must be in the range [0,59].");
    time.def("get_microsecond",
             &PBSFF::Time::getMicroSecond,
             "Gets the microsecond."); 
    time.def("set_microsecond",
             &PBSFF::Time::setMicroSecond,
             "This specifies the microsecond and must be in the range [0,999999].");

    time.def("to_string",
             &PBSFF::Time::toString,
             "Converts a time to a string representation with the format: YYYY-MM-DDTHH:MM::SS.SSSSSS");
}
