#include "Transmitter.h"

Transmitter::Transmitter(int buffer)
{
    setMAXBUFFERSIZE(buffer);
    setDrop(0);
    setBusy(0);
    setState(idle);
}

void Transmitter::processArrivelEvent(const Event &a, int &global_time, std::priority_queue<Event*, std::vector<Event*>, CompareEvent> &GEL)
{
    mean_queue.insert(std::pair<int, int>(global_time, buffer.size()));
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
        busy_time += a.getServiceTime();
        //update stati
    }
    else if((state == busy) && (buffer.size() == MAXBUFFERSIZE))
    {
        drop += 1;
        //update stati
    }
}

void Transmitter::processDepartureEvent(int &global_time, std::priority_queue<Event*, std::vector<Event*>, CompareEvent> &GEL)
{
    if(buffer.size() > 0)
    {
        Event b = buffer.front();
        buffer.pop();
        double new_depart_time = global_time + b.getServiceTime();
        GEL.push(new Event(new_depart_time, b.getServiceTime(), 'd'));
    }
    else
    {
        state = idle;
    }
}

void setState(status s)
{
    state = s;
}

const status getState()
{
    return state;
}

void setDrop(int d)
{
    drop = d;
}

const int getDrop()
{
    return drop;
}

void setMAXBUFFERSIZE(int m)
{
    MAXBUFFERSIZE = m;
}

const int getMAXBUFFERSIZE()
{
    return MAXBUFFERSIZE;
}

void setBusy(int b)
{
    busy_time = b;
}

const int getBusy()
{
    return busy_time;
}
