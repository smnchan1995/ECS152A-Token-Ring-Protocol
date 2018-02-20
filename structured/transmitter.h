#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <queue>
#include <map>
#include <vector>
#include "Event.h"

enum status {idle, busy};

struct CompareEvent
{
  bool operator()(const Event* lhs, const Event* rhs) const
  {
     return lhs->getTime() > rhs->getTime();
  }
};

class Transmitter
{
    private:
        status state;
        int drop, MAXBUFFERSIZE, busy_time;

    public:
        std::queue<Event> buffer;
        std::map<int, int> mean_queue;

        Transmitter(int buffer);
        void processArrivelEvent(const Event &a, int &global_time, std::priority_queue<Event*, std::vector<Event*>, CompareEvent> &GEL);
        void processDepartureEvent(int &global_time, std::priority_queue<Event*, std::vector<Event*>, CompareEvent> &GEL);

        void setState(status s);
        const status getState();

        void setDrop(int d);
        const int getDrop();

        void setMAXBUFFERSIZE(int m);
        const int getMAXBUFFERSIZE();

        void setBusy(int b);
        const int getBusy();
};

#endif // TRANSMITTER_H
