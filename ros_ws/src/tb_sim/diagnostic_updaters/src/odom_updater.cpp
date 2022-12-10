#include <diagnostic_updater/odom_updater.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odom_updater"); // Ros initialization function.
  ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
  diagnostic_updater::Updater odomUpdater; // Construct an updater class.

	odomUpdater.setHardwareID("/tb_sim/odom");

  /* Subscribing to /tb_sim/imu topic
	Message queue = 1000
	Callback function = imu_callback
  The updater will subscribe to the topic and will run the callback function
  */
  ros::Subscriber subImu = nh.subscribe("/tb_sim/odom", 1000, odom_callback);

  // Creating tasks using functions with FunctionDiagnosticTask
  diagnostic_updater::FunctionDiagnosticTask check("Checks", 
    boost::bind(&checking, boost::placeholders::_1));
  
  diagnostic_updater::CompositeDiagnosticTask odom("ODOM check");

  //Creates a new task, registers the task, and returns the instance.
  odom.addTask(&check);

  //Add the CompositeDiagnosticTask to our Updater.
  odomUpdater.add(odom);

  odomUpdater.broadcast(0, "Initializing ODOM updater");
  odomUpdater.force_update();

  while (nh.ok())
  {
    ros::Duration(0.1).sleep();
    //spinOnce() will call all the callbacks waiting to be called at that point in time.
    ros::spinOnce();
    //Call updater
    odomUpdater.update();    
  }

  return 0; 
}
