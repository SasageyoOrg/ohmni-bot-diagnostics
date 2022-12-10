#include <diagnostic_updater/diagnostic_updater.h>
#include <std_msgs/Bool.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/JointState.h>
#include <string>
#ifdef ERROR
#undef ERROR
#endif
using namespace diagnostic_updater;

std::string name0, name1, name2, name3, name4;
float position0, position1, position2, position3, position4;

float js_position0_threshold;
float js_position1_threshold;
float js_position2_threshold;
float js_position3_threshold;
float js_position4_threshold;

// Callback function
void jointstates_callback(const sensor_msgs::JointState::ConstPtr& msg)
{
  name0 = msg->name[0];
  name1 = msg->name[1];
  name2 = msg->name[2];
  name3 = msg->name[3];
  name4 = msg->name[4];
  
  position0 = msg->position[0];
  position1 = msg->position[1];
  position2 = msg->position[2];
  position3 = msg->position[3];
  position4 = msg->position[4];
}

/* 
  Functions used to create DiagnosticTasks
  Monitoring angular velocity values and checking if are out of range
  Publish messages on /diagnostic topic (the aggregator will read from this topic)
*/ 

void check_position0(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if(position0 == js_position0_threshold) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "%s: OK [%f]", name0, position0);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "%s: ERROR [%f]", name0, position0);

  stat.add(name0, position0);
}

void check_position1(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if(position1 == js_position1_threshold) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "%s: OK [%f]", name1, position1);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "%s: OK [%f]", name1, position1);

  stat.add(name1, position0);
}

void check_position2(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if(position2 == js_position2_threshold) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "%s: OK [%f]", name2, position2);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "%s: OK [%f]", name2, position2);

  stat.add(name2, position2);
}

void check_position3(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if(position3 == js_position3_threshold) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "%s: OK [%f]", name3, position3);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "%s: OK [%f]", name3, position3);

  stat.add(name3, position3);
}

void check_position4(diagnostic_updater::DiagnosticStatusWrapper &stat)
{  
  if(position4 == js_position4_threshold) 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::OK, "%s: OK [%f]", name4, position4);
  else 
    stat.summaryf(diagnostic_msgs::DiagnosticStatus::WARN, "%s: OK [%f]", name4, position4);

  stat.add(name4, position4);
}
