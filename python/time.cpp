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
}

int Time::getJulianDay() const
{
    return mTime->getJulianDay();
}

/// Get/Set month
void Time::setMonth(const int month)
{
    mTime->setMonth(month);
}

int Time::getMonth() const
{
    return mTime->getMonth();
}

/// Get/Set day of month
void Time::setDayOfMonth(const int dom)
{
    mTime->setDayOfMonth(dom);
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

