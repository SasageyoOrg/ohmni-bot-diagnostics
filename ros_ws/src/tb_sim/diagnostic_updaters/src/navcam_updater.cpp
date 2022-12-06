#include <diagnostic_updater/navcam_updater.h>


ros::Time stamp(0.016);
int main(int argc, char **argv)
{
    ros::init(argc, argv, "navcam_updater"); // Ros initialization function.
    ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
    diagnostic_updater::Updater navcamUpdater; // Construct an updater class.

		double min_freq = 5;
		double max_freq = 20;

		const double min_ts = 1;
		const double max_ts = 5;

		diagnostic_updater::TopicDiagnostic pub1_freq(
			"/nav_camera/image_raw", 
			navcamUpdater,
			diagnostic_updater::FrequencyStatusParam(&min_freq, &max_freq, 0.1, 100),
			diagnostic_updater::TimeStampStatusParam(min_ts, max_ts));
    

		
    navcamUpdater.force_update();

  while (nh.ok())
  {
    ros::Duration(0.1).sleep();
	  std_msgs::Bool msg;
    msg.data = false;
    // pub1_freq.tick(stamp);
		
    navcamUpdater.update();
  }
  return 0; 
}


    // nh.getParam("navcam_seq_old", navcam_seq_old); // Get parameters from .yaml file 

    // navcamUpdater.setHardwareID("/nav_camera/image_raw");

    //ros::Subscriber subNavcam = nh.subscribe("/nav_camera/image_raw", 1000, navcam_callback);

    // // Creating tasks using functions with FunctionDiagnosticTask
    // diagnostic_updater::FunctionDiagnosticTask seq("Sequences",
    //     boost::bind(&check_seq, boost::placeholders::_1));

    // diagnostic_updater::CompositeDiagnosticTask bounds("NAV-CAM check");

    // //Creates a new task, registers the task, and returns the instance.
    // bounds.addTask(&seq);
		// //Add the CompositeDiagnosticTask to our Updater.
    // navcamUpdater.add(bounds);
    // navcamUpdater.broadcast(0, "Initializing NAV-CAM updater");

		// ros::Publisher pub1 = nh.advertise<std_msgs::Bool>("topic1", 1);

    //spinOnce() will call all the callbacks waiting to be called at that point in time.
    // ros::spinOnce();
    // //Call updater
    // navcamUpdater.update();    
	
    // ros::Duration(0.3).sleep();
    
    // // Calls to pub1 have to be accompanied by calls to pub1_freq to keep
    // // the statistics up to date.