#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/Imu.h>
#ifdef ERROR
#undef ERROR
#endif
using namespace diagnostic_updater;

#define PI 3.141593

float av_x;
float av_y;
float av_z;

float la_x;
float la_y;
float la_z;

float imu_av_min;
float imu_av_max;

float imu_la_min;
float imu_la_max;

int pitch;
int roll;

// Callback function
void imu_callback(const sensor_msgs::Imu::ConstPtr& msg)
{
  av_x = msg->angular_velocity.x;
  av_y = msg->angular_velocity.y;
  av_z = msg->angular_velocity.z;

  la_x = msg->linear_acceleration.x;
  la_y = msg->linear_acceleration.y;
  la_z = msg->linear_acceleration.z;
}

/* 
  Functions used to create DiagnosticTasks
  Monitoring angular velocity values and checking if are out of range
  Publish messages on /diagnostic topic (the aggregator will read from this topic)
*/ 

void check_av_x(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if (av_x > imu_av_min && av_x < imu_av_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "angular velocity x-axis: OK [%f]", av_x);
  else if ( av_x > imu_av_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "angular velocity x-axis: Too high [%f]", av_x);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "angular velocity x-axis: Too low [%f]", av_x);
  stat.add("Top-Side Margin x", 10 - av_x);

  stat.add("imu la max", imu_av_max);
  stat.add("imu la min", imu_av_min);
}

void check_av_y(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if (av_y > imu_av_min && av_y < imu_av_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "angular velocity y-axis: OK [%f]", av_y);
  else if ( av_y > imu_av_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "angular velocity y-axis: Too high [%f]", av_y);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "angular velocity y-axis: Too low [%f]", av_y);
  stat.add("Top-Side Margin y", 10 - av_y);
}

void check_av_z(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if (av_z > imu_av_min && av_z < imu_av_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "angular velocity z-axis: OK [%f]", av_z);
  else if ( av_z > imu_av_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "angular velocity z-axis: Too high [%f]", av_z);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "angular velocity z-axis: Too low [%f]", av_z);
  stat.add("Top-Side Margin z", 10 - av_z);
}

// Linear acceleration
void check_la_x(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if (la_x > imu_la_min && la_x < imu_la_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "linear acceleration x-axis: OK [%f]", la_x);
  else if ( la_x > imu_la_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "linear acceleration x-axis: Too high [%f]", la_x);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "linear acceleration x-axis: Too low [%f]", la_x);
  stat.add("Top-Side Margin x", 10 - la_x);

  stat.add("imu la max", imu_la_max);
  stat.add("imu la min", imu_la_min);
}

void check_la_y(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if (la_y > imu_la_min && la_y < imu_la_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "linear acceleration y-axis: OK [%f]", la_y);
  else if ( la_y > imu_la_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "linear acceleration y-axis: Too high [%f]", la_y);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "linear acceleration y-axis: Too low [%f]", la_y);
  stat.add("Top-Side Margin y", 10 - la_y);
}

void check_la_z(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if (la_z > imu_la_min && la_z < imu_la_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "linear acceleration z-axis: OK [%f]", la_z);
  else if ( la_z > imu_la_max)
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "linear acceleration z-axis: Too high [%f]", la_z);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "linear acceleration z-axis: Too low [%f]", la_z);
  stat.add("Top-Side Margin z", 10 - la_z);
}

/* 
  WIP
  Getting Pitch and Roll from Acceleromter data
*/ 

// source 1: https://wiki.dfrobot.com/How_to_Use_a_Three-Axis_Accelerometer_for_Tilt_Sensing
// source 2: https://engineering.stackexchange.com/questions/3348/calculating-pitch-yaw-and-roll-from-mag-acc-and-gyro-data

void check_pitch(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  pitch = atan2((-la_x) , sqrt(la_y * la_y + la_z * la_z)) * 57.3;

  // ranges: [-40, +40] ° OK 
  if(pitch < -40) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "PITCH: TOO LOW [%d]", pitch);
  else if(pitch > 40) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "PITCH: TOO HIGH [%d]", pitch);
  else
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "PITCH: OK [%d]", pitch);

  stat.add("pitch", pitch);
}

void check_roll(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  roll = atan2(la_y , la_z) * 57.3;
  
  // ranges: [-50, +50] ° OK 
  if(roll < -50) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "ROLL: TOO LOW [%d]", roll);
  else if(roll > 50) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "ROLL: TOO HIGH [%d]", roll);
  else
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "ROLL: OK [%d]", roll);

  stat.add("roll", roll);
}


