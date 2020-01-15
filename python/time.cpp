#include <cstdio>
#include <cstdlib>
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
    mTime->setEpochalTime(time);    
}

double Time::getEpochalTime() const
{
    return mTime->getEpochalTime();
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

/// Get/Set Julian day
void Time::setJulianDay(const int jday)
{
    mTime->setJulianDay(jday);
printf("jday: %d\n", jday);
}

int Time::getJulianDay() const
{
    return mTime->getJulianDay();
}

/// Get/Set month
void Time::setMonth(const int month)
{
    mTime->setMonth(month);
printf("mon: %d\n", month);
}

int Time::getMonth() const
{
    return mTime->getMonth();
}

/// Get/Set day of month
void Time::setDayOfMonth(const int dom)
{
    mTime->setDayOfMonth(dom);
printf("dom: %d\n", dom);
}

int Time::getDayOfMonth() const
{
    return mTime->getDayOfMonth();
}

/// Get/Set Hour
void Time::setHour(const int hour)
{
    mTime->setHour(hour);
printf("hr: %d\n", hour);
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

/// Creates the class
void PBSFF::initializeTime(pybind11::module &m)
{
    pybind11::class_<PBSFF::Time> time(m, "Time");
    time.def(pybind11::init<> ());
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
    time.doc() = "This is used for managing converting between epochal and date-times.";
    time.def_property("epoch",
                      &PBSFF::Time::getEpochalTime,
                      &PBSFF::Time::setEpochalTime,
                      "epoch: This defines the UTC time in seconds since epoch (Jan 1, 1970).");
    time.def_property("year",
                      &PBSFF::Time::getYear,
                      &PBSFF::Time::setYear,
                      "This defines the time's year - e.g., 2020 indicates the year 2020.  This must be greater than 1900.");
    time.def_property("julian_day",
                      &PBSFF::Time::getJulianDay,
                      &PBSFF::Time::setJulianDay,
                      "There are two ways to specify the day of the year.  The first is the Julian day.  In this case, this must be in the range [1,366] where 366 accounts for leap years.  Setting this variable will invalidate the month and day of the month.");
    time.def_property("month",
                      &PBSFF::Time::getMonth,
                      &PBSFF::Time::setMonth,
                      "The other way to specify the day of the year is by specifying the month and the day of the month with the day_of_month attribute.   This is the month and must be in the range [1,12].  Setting this variable then this will invalidate the Julian day.");
    time.def_property("day_of_month",
                      &PBSFF::Time::getDayOfMonth,
                      &PBSFF::Time::setDayOfMonth,
                      "The other way to specify the day of the year is by speciyfing the month with the month attribute and the day of the month.  This is the day of the month and must be in the range [1,31].  Setting this variable will invalidate the Julian day.");
    time.def_property("hour",
                      &PBSFF::Time::getHour,
                      &PBSFF::Time::setHour,
                      "This specifies the hour of the day and must be in the range [0,23].");
    time.def_property("minute",
                      &PBSFF::Time::getMinute,
                      &PBSFF::Time::setMinute,
                      "This specifies the minute of the hour and must be in the range [0,59].");
    time.def_property("second",
                      &PBSFF::Time::getSecond,
                      &PBSFF::Time::setSecond,
                      "This specifies the second of the minute and must be in the range [0,59].");
    time.def_property("micro_second",
                      &PBSFF::Time::getMicroSecond,
                      &PBSFF::Time::setMicroSecond,
                      "This specifies the micro-second and must be in the range [0,999999].");
}
