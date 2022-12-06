#include <diagnostic_updater/jointstates_updater.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "jointstates_updater"); // Ros initialization function.
  ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
  diagnostic_updater::Updater jointstatesUpdater; // Construct an updater class.

  nh.getParam("js_position0_threshold", js_position0_threshold); // Get parameters from .yaml file 
  nh.getParam("js_position1_threshold", js_position1_threshold);
  nh.getParam("js_position2_threshold", js_position2_threshold);
  nh.getParam("js_position3_threshold", js_position3_threshold);
  nh.getParam("js_position4_threshold", js_position4_threshold);
  
	jointstatesUpdater.setHardwareID("/joint_states");

  /* Subscribing to /joint_states topic
	Message queue = 1000
	Callback function = imu_callback
  The updater will subscribe to the topic and will run the callback function
  */
  ros::Subscriber subJointStates = nh.subscribe("/joint_states", 1000, jointstates_callback);

  // Creating tasks using functions with FunctionDiagnosticTask
  diagnostic_updater::FunctionDiagnosticTask pos0("wheel_left_joint",
    boost::bind(&check_position0, boost::placeholders::_1));

  diagnostic_updater::FunctionDiagnosticTask pos1("wheel_right_joint",
    boost::bind(&check_position1, boost::placeholders::_1));
  
  diagnostic_updater::FunctionDiagnosticTask pos2("caster_joint",
    boost::bind(&check_position2, boost::placeholders::_1));

  diagnostic_updater::FunctionDiagnosticTask pos3("caster_wheel_joint",
    boost::bind(&check_position3, boost::placeholders::_1));

  diagnostic_updater::FunctionDiagnosticTask pos4("neck_joint",
    boost::bind(&check_position4, boost::placeholders::_1));

  diagnostic_updater::CompositeDiagnosticTask joints("Joints States check");

  //Creates a new task, registers the task, and returns the instance.
  joints.addTask(&pos0);
  joints.addTask(&pos1);
  joints.addTask(&pos2);
  joints.addTask(&pos3);
  joints.addTask(&pos4);

  //Add the CompositeDiagnosticTask to our Updater.
  jointstatesUpdater.add(joints);

  jointstatesUpdater.broadcast(0, "Initializing Joint States updater");
  jointstatesUpdater.force_update();

  while (nh.ok())
  {
    ros::Duration(0.1).sleep();
    //spinOnce() will call all the callbacks waiting to be called at that point in time.
    ros::spinOnce();
    //Call updater
    jointstatesUpdater.update();    
  }

  return 0; 
}
