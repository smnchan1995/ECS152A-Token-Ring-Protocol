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

int MAXBUFFERSIZE = 0, number_host = 0;//can be any arbitarry number
double lambda = 0, MAXTIME = 0;//arrival rate, service rate

//NEEDTODO: average global delay, for each simulation
double rateTime(double rate);
void getInputs(double &input_lambda, int &input_number_host, int &INPUT_MAXBUFFERSIZE, double &INPUT_MAXTIME);

//random packet size generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(64, 1518);

std::vector<SingleDataFrame> dataframes;
//global stuff ends

int main()
{
    getInputs(lambda, number_host, MAXBUFFERSIZE, MAXTIME);
    while((lambda != 0) && (number_host != 0) && (MAXBUFFERSIZE != 0))
    {

	std::random_device td;
	std::mt19937 ten(td());
	std::uniform_int_distribution<> tis(1, number_host);

	for(int i = 0; i < number_host; i++){
		// NEEDTODO: generate hosts
	}
        //Transmitter server1(MAXBUFFERSIZE);
        std::priority_queue<Event*, std::vector<Event*>, CompareEvent> GEL;
	double global_time = 0; // global time set to 0 at the start of simulation
	//host should be randomized
	GEL.push(new Event(0, 1, 't'));
	for(int i = 0; i < number_host; i++){
		GEL.push(new Event(((global_time + rateTime(lambda)), i, 'a'));
	}
	//GEL.push(new Event((rateTime(lambda), 1, 't'));
        while(global_time < MAXTIME)
        {
		int current_host = 0;
                Event* n = GEL.top();
                GEL.pop();
                if(n->getType() == 'a')
                {
                    global_time = n->getTime();
                    GEL.push(new Event((global_time + rateTime(lambda)), n->getHost(),'a')); 
                    //create new packet
		    //dis(gen) = packet size generator, randomize uniformly
		    //tis(ten) = destination host number genreator, randomize uniformly
		    Packet new_packet(global_time, dis(gen), tis(ten));
		    // NEEDTODO: in the queue of same host, push new_packet into current
		    //server1.processArrivalEvent(*n, global_time, GEL);
                }
                else if(n->getType() == 't')
                {
		    //current_host = n->getHost();
                    global_time = n->getTime();
		    //NEEDTODO: if host's queue is empty, then create next token event to push to gel, but the token event destination host is (n->host_number + 1)
		    GEL.push(new Event((global_time + 0.000001), n->getHost() + 1,'t'));
                    //NEEDTODO: if host's queue is not empty, then calculate delay and throughput
		    //pop all packets from queue
		    //get size of each packets, divide by 100Mbps, and add all together to get tranmission delay
		    //process delay = current time - arrive time of the packet, for each packet
                    //calculate, 4 transmission delay, 4 processing delay = 4 queuing delay + 4 propagation delay

		    GEL.push(new Event((/*calculate*/ + 0.000001), n->getHost() + 1,'t'));
 
		    //server1.processDepartureEvent(*n, global_time, GEL);
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

void getInputs(double &input_lambda, int &input_number_host, int &INPUT_MAXBUFFERSIZE, double &INPUT_MAXTIME)
{
    std::cout << "Enter 0 for any variables to exit." << std::endl;
    std::cout << "Enter lambda: ";
    std::cin >> input_lambda;
    if(input_lambda == 0)
	return;
    std::cout << std::endl;

    std::cout << "Enter number of hosts: ";
    std::cin >> input_number_host;
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
