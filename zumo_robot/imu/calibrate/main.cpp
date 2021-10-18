#include <iostream>
#include <cstdlib>         // exit
#include "calibrate.h"

void earlyTermination(ERROR_STATE estate)
{
   std::cerr << "Program terminating, "
            << ERROR_STATE_MSG[estate] <<  std::endl;
   exit(estate);
}


int main(void)
{
   imu_t expectedValue;
   imu_t biasOffset;
   ERROR_STATE estate;

   estate = readExpectedValues("./data/expectedValues.txt", &expectedValue);
   if( estate != GOOD)
   {
      earlyTermination(estate);
   }
 
   estate = calcBiasOffset("./data/calibrationData10.txt", &expectedValue, &biasOffset);
   if( estate != GOOD)
   {
      earlyTermination(estate);
   }

   estate = recordBiasOffset("./data/biasOffset.txt", &biasOffset);
   if( estate != GOOD)
   {
      earlyTermination(estate);
   }
   
   std::cout << "here\n";

   return 0;
}