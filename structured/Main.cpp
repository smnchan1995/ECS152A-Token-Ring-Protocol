#include <iostream>
//#include <list>
#include <cstdlib>
#include <random>
#include <queue>
#include <cmath>
#include <ctime>
#include "Event.h"
#include "Transmitter.h"

struct CompareEvent
{
  bool operator()(const Event* lhs, const Event* rhs) const
  {
     return lhs->getTime() > rhs->getTime();
  }
};

struct SingleDataFrame
{
       	double dlambda, dmiue;
       	int DMAXBUFFERSIZE, drop, busy_time;
        std::map<int, int> mean_queue; 
};


//global stuff
std::priority_queue<Event*, vector<Event*>, CompareEvent> GEL;
int MAXBUFFERSIZE = 0, MAXTIME = 0;//can be any arbitarry number
double lambda = 0, miue =  0;//arrival rate, service rate
int interArrivalTime(int global_time, double rate);
void getInputs(double &lambda, double &miue, int &MAXBUFFERSIZE);
std::vector<double[6]> dataframe;
//global stuff ends

int main()
{
	getInputs(lambda, miue, MAXBUFFERSIZE);
	while((lambda != 0) && (miue != 0) && (MAXBUFFERSIZE != 0))
	{
		Transmitter server1(MAXBUFEERSIZE);
  		int global_time = 0;
  		while(global_time<MAXTIME)
  		{
      			Event n = EventGEL.front();
      			GEL.pop();
      			if(n.getType() == 'a')
      			{
          			global_time = n.getTime();
          			GEL.push(new Event(interArrivalTime(global_time, lambda),interArrivalTime(global_time, miue),'a')); // does not have to be in here
          			server1.processArrivelEvent(n, global_time, GEL);
      			}
      			else if(n.getType() == 'd')
      			{
          			global_time = n.getTime();
          			//update
          			server1.processDepartureEvent(global_time);
      			}
  		}
		//gather statistics
		//double lambda, miue
		//int MAXBUFFERSIZE, drop, busy_time
		//map<int, int> mean_queue
		SingleDataFrame insert;
		insert->dlambda = lambda;
		insert->dmiue = miue;
		insert->DMAXBUFFERSIZE = MAXBUFFERSIZE;
		insert->drop = 
		insert->busy_time = 
		insert->mean_queue = 
		double data[6] = {lambda, miue, MAXBUFFERSIZE, };
		getInputs();
	}
	return 0;
}

int interArrivalTime(int global_time, double rate)
{
  	double u = rand() / (RAND_MAX + 1.0);
  	double negative_exponential_number = (-1/rate)*log(1-u);
  	return global_time + negative_exponential_number;
}

void getInputs(double &ilambda, double &imiue, int &IMAXBUFFERSIZE)
{
	std::cout << "Enter 0 for any variables to exit." << endl;
	std::cout << "Enter lambda: ";
        std::cin >> ilambda;
        std::cout << endl;

        std::cout << "Enter miue: ";
        std::cin >> imiue;
        std::out << endl;

        std::cout << "Enter MAXBUFFERSIZE";
        std::cin >> IMAXBUFFERSIZE;
        std::cout << endl;

	std::cout << "Enter MAXTIME";
	std::cin >> MAXTIME;
	std::cout << endl;
	return;
}
// functions
// int lengthPacket(){
//   return rand()%16 + 1;
// }
