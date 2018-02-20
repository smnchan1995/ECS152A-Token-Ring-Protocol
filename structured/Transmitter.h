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
        int drop, MAXBUFFERSIZE; 
	double busy_time, total_area;

    public:
        std::queue<Event> buffer;

        Transmitter(int buffer);
        void processArrivalEvent(Event &a, double &global_time, std::priority_queue<Event*, std::vector<Event*>, CompareEvent> &GEL);
        void processDepartureEvent(Event &d, double &global_time, std::priority_queue<Event*, std::vector<Event*>, CompareEvent> &GEL);

        void setState(status s);
        const status getState();

        void setDrop(int d);
        const int getDrop();

        void setMAXBUFFERSIZE(int m);
        const int getMAXBUFFERSIZE();

        void setBusy(double b);
        const double getBusy();

	void setTotalArea(double ta);
	const double getTotalArea();
};

#endif // TRANSMITTER_H
