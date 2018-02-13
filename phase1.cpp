#include <iostream>
#include <queue>
#include <list>
#include <cstdlib>
#include <random>

using namespace std;

class Event{
  int time;
  int paketLength;
  char type;
  Event* next;
  Event* prv;

public:
  //Event();
  //~Event();

  void setTime(int t){time = t;}
  int getTime(){return time;}
  void setPacketLength(int l){paketLength = l;}
  int getPacketLength(){return paketLength;}
  void setType(char t){type = t;}
  int getType(){return type;}



};
int const BUFEERSIZE = 10;   // it could be any arbitarry number
std::list<Event> GEL;
std::queue<Event> buffer;


int main(){

  int time = 0;            // keep track of time
  int length = 0;          // number of packets in q
  double lambda = 1.0;             //arrival rate
  double miue =  0.5;             //service rate


  //Event A1 = new Event(setTime(interArrivalTime()),setPacketLength(lengthPacket()),
                       //setType('A') );
  //if

  //GEL.push_back(A1)


  cout << "Hello World ";
  return 0;
}

// functions
int interArrivalTime(int time){
  return time + (rand()% 10 + 1);
}
int lengthPacket(){
  return rand()%16 + 1;
}
//void processArrivelEvent(Event &A){
  //time = A.getTime();

//}
