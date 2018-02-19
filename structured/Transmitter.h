#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <queue>
#include <map>
#include "Event.h"

class Transmitter
{
    private:
        enum status {idle, busy};
        std::queue<Event> buffer;
        std::map<int, int> mean_queue;
        int drop, MAXBUFFERSIZE, busy_time;

    public:
        Transmitter(int buffer);
        void processArrivelEvent(Event &a, int &global_time, std::priority_queue<Event*, vector<Event*>, CompareEvent> &GEL);
        void processDepartureEvent(int &global_time);
};

#endif // TRANSMITTER_H
