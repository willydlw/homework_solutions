#ifndef CALIBRATE_H
#define CALIBRATE_H

#include <string>
#include <cstdint>      // int16_t

const int IMU_DATA_FIELDS = 6;

enum ERROR_STATE 
{  GOOD = 0, 
   FILE_OPEN_ERROR = 1, 
   READ_ERROR  = 2,
   WRITE_ERROR = 3
};

// declare in header file
extern std::string ERROR_STATE_MSG[3];


struct axes_t
{
   int16_t x;
   int16_t y;
   int16_t z;
};

struct imu_t
{
   axes_t accel;
   axes_t gyro;
};

/* Description: reads expected imu sensor values from file
                and stores values in expectedValues.
   
   Parameters

   Input:
   fileName - name of file containing accelerometer and gyroscope
              values in units of LSB, type int16_t

   Output:
   expectedValues - contains sensors values read from file

   Return:
      Success - GOOD
      Failure - FILE_OPEN_ERROR if file cannot be opened
                READ_ERROR if not all data is read

   File Requirements
      File must contain six int16_t data values, whitespace delimited
      Data must be in the following order

      accelerometer X   accelerometer Y   accelerometer Z
      gyroscope X       gyroscope     Y   gyroscope     Z
*/
ERROR_STATE readExpectedValues(const char* fileName, imu_t *expectedValue);

/* Description: reads imu sensor values from file
                calculates the average bias offset
   
   Parameters

   Input:
   fileName - name of file containing accelerometer and gyroscope
              data values in units of LSB, type int16_t

   expectedValues - contains expected sensor values

   Output:
   biasOffset - difference between expected value and average value
  
   Return:
      Success - GOOD
      Failure - error state

   File Requirements
      Each line of the file contains six whitespace delimited 
      data values, type int16_t. 

      Data must be in the following order:
      accelX   accelY   accelZ gyroX  gyroY   gyroZ

      The number of lines in the file, which corresponds to the
      number of data measurements cannot exceed 65636. 

      The end of file marker occurs immediately after the last value
      in the file. There is no trailing whitespace.
*/
ERROR_STATE calcBiasOffset(const char* fileName, const imu_t* expectedValue, 
            imu_t* biasOffset);


ERROR_STATE recordBiasOffset(const char* fileName, const imu_t* biasOffset);

#endif 