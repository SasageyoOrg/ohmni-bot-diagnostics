#include <diagnostic_updater/imu_updater.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "imu_updater"); // Ros initialization function.
  ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
  diagnostic_updater::Updater imuUpdater; // Construct an updater class.

  nh.getParam("imu_pitch_max", imu_pitch_max); // Get parameters from .yaml file 
  nh.getParam("imu_pitch_min", imu_pitch_min);

  nh.getParam("imu_roll_max", imu_roll_max);
  nh.getParam("imu_roll_min", imu_roll_min);

	imuUpdater.setHardwareID("/tb_sim/imu");

  /* Subscribing to /tb_sim/imu topic
	Message queue = 1000
	Callback function = imu_callback
  The updater will subscribe to the topic and will run the callback function
  */
  ros::Subscriber subImu = nh.subscribe("/tb_sim/imu", 1000, imu_callback);

  // Creating tasks using functions with FunctionDiagnosticTask
  diagnostic_updater::FunctionDiagnosticTask pitch("Pitch",
    boost::bind(&check_pitch, boost::placeholders::_1));

  diagnostic_updater::FunctionDiagnosticTask roll("Roll",
    boost::bind(&check_roll, boost::placeholders::_1));

  diagnostic_updater::CompositeDiagnosticTask bounds("IMU bounds check");

  //Creates a new task, registers the task, and returns the instance.
  bounds.addTask(&pitch);
  bounds.addTask(&roll);

  //Add the CompositeDiagnosticTask to our Updater.
  imuUpdater.add(bounds);

  imuUpdater.broadcast(0, "Initializing IMU updater");
  imuUpdater.force_update();

  while (nh.ok())
  {
    ros::Duration(0.1).sleep();
    //spinOnce() will call all the callbacks waiting to be called at that point in time.
    ros::spinOnce();
    //Call updater
    imuUpdater.update();    
  }

  return 0; 
}
