#include "Event.h"

Event::Event()
{
    setTime(0.0); setServiceTime(0.0); setType('n');
}

Event::Event(double t, double l, char c)
{
    setTime(t); setServiceTime(l); setType(c);
}

void Event::setTime(double t)
{
    time = t;
}

double Event::getTime()const
{
    return time;
}

void Event::setServiceTime(double l)
{
    service_time = l;
}

double Event::getServiceTime()const
{
    return service_time;
}

void Event::setType(char t)
{
    type = t;
}

 char Event::getType()const
{
    return type;
}
