#include <iostream>
//#include <list>
#include <cstdlib>
#include <random>
#include <queue>
#include <cmath>
#include <ctime>
using namespace std;

class Event{
  double time;
  int paketLength;
  char type;
public:
  Event(){
     setTime(0); setPacketLength(0); setType('n');   // n stands for no type intialization
  }
  Event(int t,int l, char c){
     setTime(t); setPacketLength(l); setType(c);
  }
  //~Event();

  void setTime(double t){time = t;}
  double getTime() const {return time;}
  void setPacketLength(int l){paketLength = l;}
  int getPacketLength() const {return paketLength;}
  void setType(char t){type = t;}
  int getType() const {return type;}
};

struct CompareEvent{
  bool operator()(const Event* lhs, const Event* rhs) const
  {
     return lhs->getTime() > rhs->getTime();
  }
};

double interArrivalTime(int,double);
int lengthPacket();
void processArrivelEvent(Event&);

int const BUFEERSIZE = 10;   // it could be any arbitarry number
double const lambda = 1.0;             //arrival rate
double const miue =  0.5;             //service rat
double GlobalTime = 0;            // keep track of time
std::queue<Event> buffer;
std::priority_queue<Event*, vector<Event*>, CompareEvent> GEL;


int main(){
  srand(time(NULL));



  int length = 0;          // number of packets in q


  // GEL.push( new Event( 2, 0, 'a') );
  // GEL.push( new Event( 5,0, 'd' ) );
  // GEL.push( new Event( 3,0, 'd' ) );
  // GEL.push( new Event( 7,0, 'd' ) );
  //
  // while ( !GEL.empty() )
  // {
  //     Event* n = GEL.top();
  //     cout << n->getTime() << endl;
  //     GEL.pop();
  //
  //     // Delete pointer that vector contains
  //     delete n;
  // }
  // cin.get();

  GEL.push(new Event(interArrivalTime(GlobalTime, lambda),lengthPacket(),'a'));



  cout << "Hello World ";
  return 0;
}

// functions
double interArrivalTime(int GlobalTime, double rate){
  double u = rand() / (RAND_MAX + 1.0);
  double  negativeExponentialNumber = (-1/rate)*log(1-u);
  return GlobalTime + negativeExponentialNumber;
}
int lengthPacket(){
  return rand()%16 + 1;
}
void processArrivelEvent(Event& A){
  GlobalTime = A.getTime();
  GEL.push(new Event(interArrivalTime(GlobalTime, lambda),lengthPacket(),'a'));


}
