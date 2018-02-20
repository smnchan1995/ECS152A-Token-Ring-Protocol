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

int Event::getTime()const
{
    return time;
}

void Event::setServiceTime(int l)
{
    service_time = l;
}

int Event::getServiceTime()const
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
