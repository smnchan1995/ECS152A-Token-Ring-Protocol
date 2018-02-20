#include <iostream>
#include <fstream>
#include <iomanip>
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
        double dlambda, dmiue, busy_time, dtotal_area, DMAXTIME;
        int DMAXBUFFERSIZE, drop;
};


//global stuff

int MAXBUFFERSIZE = 0;//can be any arbitarry number
double lambda = 0, miue =  0, MAXTIME = 0;//arrival rate, service rate

double rateTime(double rate);
void getInputs(double &input_lambda, double &input_miue, int &INPUT_MAXBUFFERSIZE, double &INPUT_MAXTIME);

std::vector<SingleDataFrame> dataframes;
//global stuff ends

int main()
{
    getInputs(lambda, miue, MAXBUFFERSIZE, MAXTIME);
    while((lambda != 0) && (miue != 0) && (MAXBUFFERSIZE != 0))
    {
        Transmitter server1(MAXBUFFERSIZE);
        std::priority_queue<Event*, std::vector<Event*>, CompareEvent> GEL;
	double global_time = 0;
	GEL.push(new Event((global_time + rateTime(lambda)),rateTime(miue),'a'));
        while(global_time<MAXTIME)
        {
                Event* n = GEL.top();
                GEL.pop();
                if(n->getType() == 'a')
                {
                    global_time = n->getTime();
                    GEL.push(new Event((global_time + rateTime(lambda)),rateTime(miue),'a')); 
                    server1.processArrivalEvent(*n, global_time, GEL);
                }
                else if(n->getType() == 'd')
                {
                    global_time = n->getTime();
                    //update
                    server1.processDepartureEvent(*n, global_time, GEL);
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
        insert.dtotal_area = server1.getTotalArea();
        insert.DMAXTIME = MAXTIME;

        dataframes.push_back(insert);

        getInputs(lambda, miue, MAXBUFFERSIZE, MAXTIME);
    }
    std::ofstream myfile;
    myfile.open("data1.txt");
    myfile << std::setw(15) << "lambda"
           << std::setw(15) << "miue"
           << std::setw(15) << "MAXBUFFER"
           << std::setw(15) << "drop"
           << std::setw(15) << "busy_time"
           << std::setw(15) << "mean_queue" << std::endl;
    while (!dataframes.empty())
    {
    	SingleDataFrame frame = dataframes.back();
    	dataframes.pop_back();
    	myfile << std::setw(15) << frame.dlambda << " "
               << std::setw(15) << frame.dmiue << " "
               << std::setw(15) << frame.DMAXBUFFERSIZE << " "
	       << std::setw(15) << frame.drop << " "
               << std::setw(15) << frame.busy_time << " "
	       << std::setw(15) << (frame.dtotal_area/frame.DMAXTIME) << std::endl;
    }
    myfile.close();
    return 0;
}

double rateTime(double rate)
{
    double u = rand() / (RAND_MAX + 1.0);
    double negative_exponential_number = (-1/rate)*log(1-u);
    return negative_exponential_number;
}

void getInputs(double &input_lambda, double &input_miue, int &INPUT_MAXBUFFERSIZE, double &INPUT_MAXTIME)
{
    std::cout << "Enter 0 for any variables to exit." << std::endl;
    std::cout << "Enter lambda: ";
    std::cin >> input_lambda;
    if(input_lambda == 0)
	return;
    std::cout << std::endl;

    std::cout << "Enter miue: ";
    std::cin >> input_miue;
    std::cout << std::endl;

    std::cout << "Enter MAXBUFFERSIZE: "; 
    std::cin >> INPUT_MAXBUFFERSIZE;
    std::cout << std::endl;

    std::cout << "Enter MAXTIME: "; 
    std::cin >> INPUT_MAXTIME;
    std::cout << std::endl;
    return;
}

// functions
// int lengthPacket(){
//   return rand()%16 + 1;
// }
