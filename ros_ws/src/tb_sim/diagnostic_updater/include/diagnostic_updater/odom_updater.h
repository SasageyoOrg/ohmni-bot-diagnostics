#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <std_msgs/Header.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <nav_msgs/Odometry.h>
#ifdef ERROR
#undef ERROR
#endif
using namespace diagnostic_updater;

int header_seq;
int header_stamp_nsecs;
int header_stamp_secs;

float pose_orientation_w;
float pose_orientation_x;
float pose_orientation_y;
float pose_orientation_z;

float pose_position_x;
float pose_position_y;
float pose_position_z;

float twist_twist_angular_x;
float twist_twist_angular_y;
float twist_twist_angular_z;

float twist_twist_linear_x;
float twist_twist_linear_y;
float twist_twist_linear_z;

// Callback function
void odom_callback(const nav_msgs::Odometry::ConstPtr& msg)
{ 
  // header
  std_msgs::Header new_header;
  new_header = msg->header;
  header_seq = new_header.seq;

  ros::Time new_stamp;
  new_stamp = new_header.stamp;
  header_stamp_nsecs = new_stamp.nsec;
  header_stamp_secs = new_stamp.sec;

  // pose
  geometry_msgs::PoseStamped new_pose; 
  new_pose.pose = msg->pose.pose;
  
  pose_orientation_w = new_pose.pose.orientation.w;
  pose_orientation_x = new_pose.pose.orientation.x;
  pose_orientation_y = new_pose.pose.orientation.y;
  pose_orientation_z = new_pose.pose.orientation.z;

  pose_position_x = new_pose.pose.position.x;
  pose_position_y = new_pose.pose.position.y;
  pose_position_z = new_pose.pose.position.z;

  // twist
  geometry_msgs::TwistStamped new_twist; 
  new_twist.twist = msg->twist.twist;

  twist_twist_angular_x = new_twist.twist.angular.x;
  twist_twist_angular_y = new_twist.twist.angular.y;
  twist_twist_angular_z = new_twist.twist.angular.z;

  twist_twist_linear_x = new_twist.twist.linear.x;
  twist_twist_linear_y = new_twist.twist.linear.y;
  twist_twist_linear_z = new_twist.twist.linear.z;
}

/* 
  Functions used to create DiagnosticTasks
  Monitoring angular velocity values and checking if are out of range
  Publish messages on /diagnostic topic (the aggregator will read from this topic)
*/ 

void checking(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
  // todo: looking for good tresholds
  if(header_stamp_secs < 0) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "STATUS: BAD [%d]", header_stamp_secs);
  else
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "STATUS: OK [%d]", header_stamp_secs); 
}

void logging(diagnostic_updater::DiagnosticStatusWrapper &stat)
{
  stat.add("header_seq", header_seq);
  stat.add("header_stamp_nsecs", header_stamp_nsecs);
  stat.add("header_stamp_secs", header_stamp_secs);

  stat.add("pose_orientation_w", pose_orientation_w);
  stat.add("pose_orientation_x", pose_orientation_x);
  stat.add("pose_orientation_y", pose_orientation_y);
  stat.add("pose_orientation_z", pose_orientation_z);

  stat.add("pose_position_x", pose_position_x);
  stat.add("pose_position_y", pose_position_y);
  stat.add("pose_position_z", pose_position_z);

  stat.add("twist_twist_angular_x", twist_twist_angular_x);
  stat.add("twist_twist_angular_y", twist_twist_angular_y);
  stat.add("twist_twist_angular_z", twist_twist_angular_z);

  stat.add("twist_twist_linear_x", twist_twist_linear_x);
  stat.add("twist_twist_linear_y", twist_twist_linear_y);
  stat.add("twist_twist_linear_z", twist_twist_linear_z);
}

