#include "Transmitter.h"

Transmitter::Transmitter(int buffer)
{
    setMAXBUFFERSIZE(buffer);
    setDrop(0);
    setBusy(0.0);
    setState(idle);
    setTotalArea(0);
}

void Transmitter::processArrivalEvent(Event &a, double &global_time, std::priority_queue<Event*, std::vector<Event*>, CompareEvent> &GEL)
{
    if((state == idle) && (buffer.size() == 0))
    {
        state = busy;
        busy_time += a.getServiceTime();
        double depart_time = global_time + a.getServiceTime();
        GEL.push(new Event(depart_time, a.getServiceTime(), 'd'));
    }
    else if((state == busy) && (buffer.size() < MAXBUFFERSIZE))
    {
        buffer.push(a);
	Event* m = GEL.top();
        double temp = getTotalArea();
        double new_area_to_add = ((m->getTime() - a.getTime()) * buffer.size());
        setTotalArea(temp + new_area_to_add);

    }
    else if((state == busy) && (buffer.size() == MAXBUFFERSIZE))
    {
        drop += 1;
        Event* m = GEL.top();
        double temp = getTotalArea();
        double new_area_to_add = ((m->getTime() - a.getTime()) * buffer.size());
        setTotalArea(temp + new_area_to_add);

    }
}

void Transmitter::processDepartureEvent(Event &d, double &global_time, std::priority_queue<Event*, std::vector<Event*>, CompareEvent> &GEL)
{
    if(buffer.size() > 0)
    {
        Event b = buffer.front();
        buffer.pop();
	busy_time += b.getServiceTime();
        double new_depart_time = global_time + b.getServiceTime();
        GEL.push(new Event(new_depart_time, b.getServiceTime(), 'd'));
	
	Event* m = GEL.top();
        double temp = getTotalArea();
        double new_area_to_add = ((m->getTime() - d.getTime()) * buffer.size());
        setTotalArea(temp + new_area_to_add);
    }
    else
    {
        state = idle;
    }
}

void Transmitter::setState(status s)
{
    state = s;
}

const status Transmitter::getState()
{
    return state;
}

void Transmitter::setDrop(int d)
{
    drop = d;
}

const int Transmitter::getDrop()
{
    return drop;
}

void Transmitter::setMAXBUFFERSIZE(int m)
{
    MAXBUFFERSIZE = m;
}

const int Transmitter::getMAXBUFFERSIZE()
{
    return MAXBUFFERSIZE;
}

void Transmitter::setBusy(double b)
{
    busy_time = b;
}

const double Transmitter::getBusy()
{
    return busy_time;
}

void Transmitter::setTotalArea(double ta)
{
    total_area = ta;
}

const double Transmitter::getTotalArea()
{
    return total_area;
}
