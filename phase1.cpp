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
  double ServiceTime;
  char type;
public:
  Event(){
     setTime(0); setServiceTime(0); setType('n');   // n stands for no type intialization
  }
  Event(int t,int l, char c){
     setTime(t); setServiceTime(l); setType(c);
  }
  //~Event();

  void setTime(double t){time = t;}
  double getTime() const {return time;}
  void setServiceTime(double l){ServiceTime = l;}
  int getServiceTime() const {return ServiceTime;}
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
//int lengthPacket();
void processArrivelEvent(const Event&);
void processDepartureEvent(const Event&);

int const MAXBUFEERSIZE = 10;   // it could be any arbitarry number
double const lambda = 0.5;             //arrival rate
double const miue =  0.7;             //service rat
double GlobalTime = 0;            // keep track of time
std::queue<Event> buffer;
std::priority_queue<Event*, vector<Event*>, CompareEvent> GEL;
bool server = false;            // if server is false it is busy if not it is free
int length = 0;          // number of packets in q
int drop = 0;

int main(){
  srand(time(NULL));






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

  GEL.push(new Event(interArrivalTime(GlobalTime, lambda),interArrivalTime(GlobalTime, miue),'a'));



  cout << "Hello World ";
  return 0;
}

// functions
double interArrivalTime(int GlobalTime, double rate){
  double u = rand() / (RAND_MAX + 1.0);
  double  negativeExponentialNumber = (-1/rate)*log(1-u);
  return GlobalTime + negativeExponentialNumber;
}
// int lengthPacket(){
//   return rand()%16 + 1;
// }
void processArrivelEvent(const Event& A){
  GlobalTime = A.getTime();
  GEL.push(new Event(interArrivalTime(GlobalTime, lambda),interArrivalTime(GlobalTime, miue),'a'));
  //GEL.push(new Event(interArrivalTime(GlobalTime, lambda),lengthPacket(),'a'));
  if (server){
    if (length == 0){
      double departTime = GlobalTime + A.getServiceTime();
      GEL.push(new Event(departTime, A.getServiceTime(), 'd'));
    }
  }
  else{
    if (length < MAXBUFEERSIZE){
      buffer.push(A);
      length += 1;
    }
    else{
      drop += 1;
    }
    //update statistics
  }
}
void processDepartureEvent(const Event& A){
  GlobalTime = A.getTime();
  //update statistics
  length -= 1;
  if(length > 0){
     Event B = buffer.front();
     buffer.pop();
     double newDepartTime = GlobalTime + B.getServiceTime();
     GEL.push(new Event(newDepartTime, B.getServiceTime(), 'd'));
  }

}
