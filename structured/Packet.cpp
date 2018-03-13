#include "Packet.h"
//random uniform gen for size in main 

Packet::Packet()
{
    setArrivalTime(0.0); setSize(0); setDestination(0);
}

Packet::Packet(double t, int s, int d)
{
    setArrivalTime(t); setSize(s); setDestination(d);
}

void Packet::setArrivalTime(double t)
{
    arrival_time = t;
}

double Packet::getArrivalTime()const
{
    return arrival_time;
}

void Packet::setSize(int s)
{
    size = s;
}

int Packet::getSize()const
{
    return size;
}

void Packet::setDestination(int d)
{
    destination = d;
}

int Packet::getDestination()const
{
    return destination;
}
