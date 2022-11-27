#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/Imu.h>
#ifdef ERROR
#undef ERROR
#endif
using namespace diagnostic_updater;

float av_x;
float av_y;
float av_z;
float imu_av_min;
float imu_av_max;


// Callback function, runed
void imu_callback(const sensor_msgs::Imu::ConstPtr& msg)
{
  av_x = msg->angular_velocity.x;
  av_y = msg->angular_velocity.y;
  av_z = msg->angular_velocity.z;
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

  stat.add("imu max", imu_av_max);
  stat.add("imu min", imu_av_min);
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


