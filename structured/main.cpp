#include <iostream>
//#include <list>
#include <cstdlib>
#include <random>
#include <queue>
#include <cmath>
#include <ctime>
#include "Event.h"
#include "Transmitter.h"

struct SingleDataFrame
{
        double dlambda, dmiue;
        int DMAXBUFFERSIZE, drop, busy_time;
        std::map<int, int> mean_queue;
};


//global stuff
std::priority_queue<Event*, std::vector<Event*>, CompareEvent> GEL;
int MAXBUFFERSIZE = 0, MAXTIME = 0;//can be any arbitarry number
double lambda = 0, miue =  0;//arrival rate, service rate

int interArrivalTime(int global_time, double rate);
void getInputs(double &input_lambda, double &input_miue, int &INPUT_MAXBUFFERSIZE, int &INPUT_MAXTIME);

std::vector<SingleDataFrame> dataframes;
//global stuff ends

int main()
{
    getInputs(lambda, miue, MAXBUFFERSIZE, MAXTIME);
    while((lambda != 0) && (miue != 0) && (MAXBUFFERSIZE != 0))
    {
        Transmitter server1(MAXBUFFERSIZE);
        int global_time = 0;
        while(global_time<MAXTIME)
        {
                Event* n = GEL.top();
                GEL.pop();
                if(n->getType() == 'a')
                {
                    global_time = n->getTime();
                    GEL.push(new Event(interArrivalTime(global_time, lambda),interArrivalTime(global_time, miue),'a')); // does not have to be in here
                    server1.processArrivelEvent(n, global_time, GEL);
                }
                else if(n->getType() == 'd')
                {
                    global_time = n->getTime();
                    //update
                    server1.processDepartureEvent(global_time, GEL);
                }
        }

        //gather statistics
        //double lambda, miue
        //int MAXBUFFERSIZE, drop, busy_time
        //map<int, int> mean_queue

        SingleDataFrame insert;
        insert.dlambda = lambda;
        insert.dmiue = miue;
        insert.DMAXBUFFERSIZE = MAXBUFFERSIZE;
        insert.drop = server1.getDrop();
        insert.busy_time = server1.getBusy();
        insert.mean_queue = server1.mean_queue;

        dataframes.push_back(insert);

        getInputs(lambda, miue, MAXBUFFERSIZE, MAXTIME);
    }
    return 0;
}

int interArrivalTime(int global_time, double rate)
{
    double u = rand() / (RAND_MAX + 1.0);
    double negative_exponential_number = (-1/rate)*log(1-u);
    return global_time + negative_exponential_number;
}

void getInputs(double &input_lambda, double &input_miue, int &INPUT_MAXBUFFERSIZE, int &INPUT_MAXTIME)
{
    std::cout << "Enter 0 for any variables to exit." << std::endl;
    std::cout << "Enter lambda: ";
    std::cin >> input_lambda;
    std::cout << std::endl;

    std::cout << "Enter miue: ";
    std::cin >> input_miue;
    std::cout << std::endl;

    std::cout << "Enter MAXBUFFERSIZE";
    std::cin >> INPUT_MAXBUFFERSIZE;
    std::cout << std::endl;

    std::cout << "Enter MAXTIME";
    std::cin >> INPUT_MAXTIME;
    std::cout << std::endl;
    return;
}
// functions
// int lengthPacket(){
//   return rand()%16 + 1;
// }
