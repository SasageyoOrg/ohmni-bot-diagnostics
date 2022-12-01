#include <diagnostic_updater/navcam_updater.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "navcam_updater"); // Ros initialization function.
    ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
    diagnostic_updater::Updater navcamUpdater; // Construct an updater class.

    // nh.getParam("navcam_seq_old", navcam_seq_old); // Get parameters from .yaml file 

    navcamUpdater.setHardwareID("/nav_camera/image_raw");

    ros::Subscriber subNavcam = nh.subscribe("/nav_camera/image_raw", 1000, navcam_callback);

    // Creating tasks using functions with FunctionDiagnosticTask
    diagnostic_updater::FunctionDiagnosticTask seq("Sequences",
        boost::bind(&check_seq, boost::placeholders::_1));

    diagnostic_updater::CompositeDiagnosticTask bounds("NAV-CAM check");

    //Creates a new task, registers the task, and returns the instance.
    bounds.addTask(&seq);

    //Add the CompositeDiagnosticTask to our Updater.
    navcamUpdater.add(bounds);
    navcamUpdater.broadcast(0, "Initializing NAV-CAM updater");
    navcamUpdater.force_update();

  while (nh.ok())
  {
    ros::Duration(0.1).sleep();
    //spinOnce() will call all the callbacks waiting to be called at that point in time.
    ros::spinOnce();
    //Call updater
    navcamUpdater.update();    
  }

  return 0; 
}
