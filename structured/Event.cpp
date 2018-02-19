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
    this->time = t;
}

const int Event::getTime()
{
    return this->time;
}

void Event::setServiceTime(int l)
{
    this->service_time = l;
}

const int Event::getServiceTime()
{
    return this->service_time;
}

void Event::setType(char t)
{
    this->type = t;
}

const char Event::getType()
{
    return this->type;
}
