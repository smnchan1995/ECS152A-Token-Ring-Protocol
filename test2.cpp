#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <ctime>

using namespace std;



 int main(){
   srand(time(NULL));
   double u = rand() / (RAND_MAX + 1.0);
   double  negativeExponentialNumber = (-1/.5)*log(1-u);
   cout << negativeExponentialNumber;
 }
