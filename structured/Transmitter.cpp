#include "Transmitter.h"

Transmitter::Transmitter(int buffer)
{
    this->MAXBUFFERSIZE = buffer;
    this->drop = 0;
    this->busy_time = 0;
    this->status = idle;
}

void Transmitter::processArrivelEvent(Event &a, int &global_time, std::priority_queue<Event*, vector<Event*>, CompareEvent> &GEL)
{
    this->mean_queue.insert(std::pair<int, int>(global_time, this->buffer.size()));
    if((this->status == idle) && (this->buffer.size() == 0))
    {
        this->status = busy;
        this->busy_time += a.getServiceTime();
        double depart_time = global_time + a.getServiceTime();
        GEL.push(new Event(depart_time, a.getServiceTime(), 'd'));
    }
    else if((this->status == busy) && (this->buffer.size() < MAXBUFFERSIZE))
    {
        this->buffer.push(a);
        this->busy_time += a.getServiceTime();
        //update stati
    }
    else if((this->status == busy) && (this->buffer.size() == MAXBUFFERSIZE))
    {
        this->drop += 1;
        //update stati
    }
}

void Transmitter::processDepartureEvent(int &global_time)
{
    if(this->buffer.size() > 0)
    {
        Event b = this->buffer.front();
        this->buffer.pop();
        double new_depart_time = global_time + b.getServiceTime();
        GEL.push(new Event(new_depart_time, b.getServiceTime(), 'd'));
    }
    else
    {
        this->status = idle;
    }
}
