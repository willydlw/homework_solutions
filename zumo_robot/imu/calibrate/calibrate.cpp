#include <iostream>
#include <fstream>
#include "calibrate.h"

// define in cpp file
std::string ERROR_STATE_MSG[] = 
{  "GOOD", 
   "FILE_OPEN_ERROR",
   "READ_ERROR"
};

ERROR_STATE readExpectedValues(const char* fileName, imu_t *expectedValue)
{
   std::ifstream infile;
   infile.open(fileName, std::ifstream::in);

   if(!infile)
   {
      std::cerr << __func__ 
            << ", failed to open file: " << fileName
            << '\n';
      return FILE_OPEN_ERROR;
   }
   
   int16_t val[IMU_DATA_FIELDS];
   int count = 0;
   while(count < IMU_DATA_FIELDS)
   {
      if(infile >> val[count])
         count += 1;
   }

   infile.close();

   if(count != IMU_DATA_FIELDS)
   {
      std::cerr << __func__ << ", error count: "
            << count << ", expected: " << IMU_DATA_FIELDS
            << '\n';
      return READ_ERROR;
   }
   
   expectedValue->accel.x = val[0]; 
   expectedValue->accel.y = val[1]; 
   expectedValue->accel.z = val[2]; 
   expectedValue->gyro.x = val[3]; 
   expectedValue->gyro.y = val[4]; 
   expectedValue->gyro.z = val[5];     

   return GOOD;
}


ERROR_STATE calcBiasOffset(const char* fileName, const imu_t* expectedValue, 
                           imu_t* biasOffset)
{  
   int64_t sum[IMU_DATA_FIELDS] = {0};
   int64_t data[IMU_DATA_FIELDS];
   int16_t avg[IMU_DATA_FIELDS];
   int lineCount = 0;
   int index;
   int k;

   std::ifstream infile;

   infile.open(fileName, std::ifstream::in);
   if(!infile)
   {
      std::cerr << __func__ 
            << ", failed to open file: " << fileName
            << '\n';
      return FILE_OPEN_ERROR;
   }

   while(!infile.eof())
   {
      index = 0;
      while(index < IMU_DATA_FIELDS)
      {
         if(infile >> data[index])
         {
            index += 1;
         }
         else
         {
            std::cerr << __func__ 
               << ", error reading data from file: "
               << fileName << ", line: " << lineCount + 1
               << ", column: " << index + 1 << '\n';
            infile.close();
            return READ_ERROR;
         }
      }

      lineCount += 1;      

      // add to totals
      for(k = 0; k < IMU_DATA_FIELDS; k++)
      {
         sum[k] = sum[k] + data[k];
      }
   }
   
   std::cerr << __func__ << ", filename: " << fileName << ", finished reading data\n";
   infile.close();

   // calc averages
   for(k = 0; k < IMU_DATA_FIELDS; k++)
   {
      avg[k] = static_cast<int16_t>(sum[k] / lineCount);
      std::cerr << "k: " << k << ", avg: " << avg[k] << ", sum: " << sum[k] << ", lineCount: " << lineCount << std::endl;
   }

   // calc bias offset
   biasOffset->accel.x = expectedValue->accel.x - avg[0];
   biasOffset->accel.y = expectedValue->accel.y - avg[1];
   biasOffset->accel.z = expectedValue->accel.z - avg[2];

   biasOffset->gyro.x = expectedValue->gyro.x - avg[3];
   biasOffset->gyro.y = expectedValue->gyro.y - avg[4];
   biasOffset->gyro.z = expectedValue->gyro.z - avg[5];

   return GOOD;
}


ERROR_STATE recordBiasOffset(const char* fileName, const imu_t* biasOffset)
{
   ERROR_STATE estate = GOOD;
   std::ofstream outFile;
   outFile.open(fileName, std::ofstream::out);
   if(!outFile)
   {
      std::cerr << __func__ << ", error opening " << fileName << '\n';
      return FILE_OPEN_ERROR;
   }

   outFile  << biasOffset->accel.x << " "
            << biasOffset->accel.y << " "
            << biasOffset->accel.z << " "
            << biasOffset->gyro.x << " "
            << biasOffset->gyro.y << " "
            << biasOffset->gyro.z;
   
   /* Optional: this very likely will never occur. */
   if(!outFile)
   {
      std::cerr << __func__ << "error writing bias offset data\n";
      estate =  WRITE_ERROR;
   }

   outFile.close();
   return estate;
}