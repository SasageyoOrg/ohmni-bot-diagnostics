#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/Imu.h>
#include <math.h>
#ifdef ERROR
#undef ERROR
#endif
using namespace diagnostic_updater;

// conversion factor used to output the pitch and roll in degree
#define CONVERSION_FACTOR 180/M_PI

float la_x;
float la_y;
float la_z;

int pitch;
int roll;

float imu_pitch_max;
float imu_pitch_min;

float imu_roll_max;
float imu_roll_min;

// Callback function
void imu_callback(const sensor_msgs::Imu::ConstPtr& msg)
{
  la_x = msg->linear_acceleration.x;
  la_y = msg->linear_acceleration.y;
  la_z = msg->linear_acceleration.z;
}

/* 
  Functions used to create DiagnosticTasks
  Monitoring angular velocity values and checking if are out of range
  Publish messages on /diagnostic topic (the aggregator will read from this topic)
*/ 

/* 
 * Getting Pitch and Roll from Acceleromter data
 * source 1: https://wiki.dfrobot.com/How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing
 * source 2: https://engineering.stackexchange.com/questions/3348/calculating-pitch-yaw-and-roll-from-mag-acc-and-gyro-data
*/ 
void check_pitch(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  pitch = atan2((-la_x) , sqrt(la_y * la_y + la_z * la_z)) * CONVERSION_FACTOR;

  // ranges: [-40, +40] ° OK (valori calcolati empiricamente)
  if(pitch > 80 && pitch < 90) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "PITCH: FALLEN FRONT [%d]", pitch);
  else if(pitch < imu_pitch_min) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "PITCH: TOO LOW [%d]", pitch);
  else if(pitch > imu_pitch_max) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "PITCH: TOO HIGH [%d]", pitch);
  else
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "PITCH: OK [%d]", pitch);

  stat.add("pitch", pitch);
}

void check_roll(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  roll = atan2(la_y , la_z) * CONVERSION_FACTOR;

  // ranges: [-30, +30] ° OK (valori calcolati empiricamente)
  if(roll > 85 && roll < 95) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "ROLL: FALLEN DX [%d]", roll);
  else if (roll < -85 && roll > -95) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "ROLL: FALLEN SX [%d]", roll);
  else if(roll < imu_roll_min) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "ROLL: TOO LOW [%d]", roll);
  else if(roll > imu_roll_max) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "ROLL: TOO HIGH [%d]", roll);
  else
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "ROLL: OK [%d]", roll);

  stat.add("roll", roll);
}


