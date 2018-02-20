#include "Event.h"

Event::Event()
{
    setTime(0); setServiceTime(0); setType('n');
}

Event::Event(int t, int l, char c)
{
    setTime(t); setServiceTime(l); setType(c);
}

void Event::setTime(int t)
{
    time = t;
}

const int Event::getTime()
{
    return time;
}

void Event::setServiceTime(int l)
{
    service_time = l;
}

const int Event::getServiceTime()
{
    return service_time;
}

void Event::setType(char t)
{
    type = t;
}

const char Event::getType()
{
    return type;
}
