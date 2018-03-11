#include "Event.h"

Event::Event()
{
    setTime(0.0); setHost(0); setType('n');
}

Event::Event(double t, int h, char c)
{
    setTime(t); setHost(h); setType(c);
}

void Event::setTime(double t)
{
    time = t;
}

double Event::getTime()const
{
    return time;
}

void Event::setHost(int h)
{
    host = h;
}

double Event::getHost()const
{
    return host;
}

void Event::setType(char t)
{
    type = t;
}

 char Event::getType()const
{
    return type;
}
