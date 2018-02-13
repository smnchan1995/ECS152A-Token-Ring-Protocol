#include <iostream>
#include <queue>
#include <list>
#include <cstdlib>
#include <random>

 using namespace std;
int main(){
  std::mt19937 e;
  std::exponential_distribution<double> distribution(1);

  for (int i=0; i<50; ++i) {
    int number = distribution(e);
     std::cout << number <<endl;
   }

 }
