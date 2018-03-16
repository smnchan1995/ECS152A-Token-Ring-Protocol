#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <queue>
#include <cmath>
#include <ctime>
#include <vector>
#include "Event.h"
#include "Packet.h"

struct SingleDataFrame
{
        double dlambda, dthroughput, DMAXTIME, dpacket_delay;
	int dnumber_host;
};

double rateTime(double rate);
void getInputs(double &input_lambda, int &input_number_host, double &INPUT_MAXTIME);

int main()
{
	//Variables
	int number_host = 0;
	double lambda = 0, MAXTIME = 0;
	std::vector<SingleDataFrame> dataframes;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(64, 1518);

	srand(time(NULL));

	getInputs(lambda, number_host, MAXTIME);
	while((lambda != 0) && (number_host != 0) && (MAXTIME != 0))
	{
		int total_bytes = 0;
		double total_delay = 0.0, global_time = 0.0;

		std::vector<int> present_hosts;
		std::vector<std::queue<Packet> > number_host_queues;
		std::priority_queue<Event*, std::vector<Event*>, CompareEvent> GEL;

		for(int i = 0; i < number_host; i++)
		{
			std::queue<Packet> host_queue;
			number_host_queues.push_back(host_queue);
			present_hosts.push_back(i + 1);
		}

		GEL.push(new Event(0, 1, 't'));
		
		for(int i = 0; i < number_host; i++)
		{
			GEL.push(new Event((global_time + rateTime(lambda)), (i + 1), 'a'));
		}

        	while(global_time < MAXTIME)
        	{
                	Event* n = GEL.top();
                	GEL.pop();

			int current = n->getHost();
			int* current_host = &current;

                	if(n->getType() == 'a')
                	{
				global_time = n->getTime();
				GEL.push(new Event((global_time + rateTime(lambda)), *current_host,'a')); 
				present_hosts.erase((present_hosts.begin() + (*current_host - 1)));
				Packet new_packet(global_time, dis(gen), present_hosts[rand() % present_hosts.size()]);
				present_hosts.insert(present_hosts.begin() + (*current_host - 1), *current_host);
				number_host_queues[*current_host - 1].push(new_packet);
				delete n;
			}
			else if(n->getType() == 't')
			{
				global_time = n->getTime();
				if(number_host_queues[*current_host - 1].size() == 0)
				{
					GEL.push(new Event((global_time + 0.00001), ((*current_host) % number_host) + 1,'t'));
					delete n;
				}
				else if(number_host_queues[*current_host - 1].size() > 0)
				{
					int total_bytes_current_queue = 0;
					double queue_delay_current = 0;
					while(number_host_queues[*current_host - 1].size() != 0)
					{
						int temp = 0;
						if(*current_host > number_host_queues[*current_host - 1].front().getDestination())
						{
							temp = number_host - (*current_host) + number_host_queues[*current_host - 1].front().getDestination();
						}
						else
						{
							temp = number_host_queues[*current_host - 1].front().getDestination() - *current_host;
						}
						queue_delay_current = temp * ((0.00001) + ((number_host_queues[*current_host - 1].front().getSize() * 8)/ 100000000)) + (global_time - number_host_queues[*current_host - 1].front().getArrivalTime());
						total_bytes += number_host_queues[*current_host - 1].front().getSize();
						total_bytes_current_queue += number_host_queues[*current_host - 1].front().getSize();
						number_host_queues[*current_host - 1].pop();
					}
					double delay = 0.0;
					delay += (((total_bytes_current_queue * 8)/ 10000000) + 0.00001);
					total_delay += queue_delay_current;
					delete n;
					GEL.push(new Event((global_time + (number_host * delay) + 0.00001), (*current_host % number_host) + 1,'t'));
				}
			}
		}

		SingleDataFrame insert;
		insert.dlambda = lambda;
		insert.dnumber_host = number_host;
		insert.DMAXTIME = MAXTIME;
		insert.dthroughput = ((double)total_bytes) / MAXTIME;
		insert.dpacket_delay = total_delay;

		dataframes.push_back(insert);

		getInputs(lambda, number_host, MAXTIME);
	}

	std::ofstream myfile;
	myfile.open("data.txt");
	myfile << std::setw(15) << "lambda"
	<< std::setw(15) << "num hosts"
	<< std::setw(15) << "MAXTIME"
	<< std::setw(15) << "throughput"
	<< std::setw(15) << "packet delay" << std::endl;

	while (!dataframes.empty())
	{
		SingleDataFrame frame = dataframes.back();
		dataframes.pop_back();
		myfile << std::setw(15) << frame.dlambda << " "
		<< std::setw(15) << frame.dnumber_host << " "
		<< std::setw(15) << frame.DMAXTIME << " "
		<< std::setw(15) << frame.dthroughput << " "
		<< std::setw(15) << frame.dpacket_delay << std::endl;
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

void getInputs(double &input_lambda, int &input_number_host, double &INPUT_MAXTIME)
{
	std::cout << "Enter 0 for lambda to exit." << std::endl;
	std::cout << "Enter lambda: ";
	std::cin >> input_lambda;
	if(input_lambda == 0)
		return;
	std::cout << std::endl;

	std::cout << "Enter number of hosts: ";
	std::cin >> input_number_host;
	std::cout << std::endl;

	std::cout << "Enter MAXTIME: "; 
	std::cin >> INPUT_MAXTIME;
	std::cout << std::endl;
	return;
}
