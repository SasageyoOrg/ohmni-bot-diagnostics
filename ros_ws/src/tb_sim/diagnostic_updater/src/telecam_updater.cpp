#include <diagnostic_updater/telecam_updater.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "telecam_updater"); // Ros initialization function.
    ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
    diagnostic_updater::Updater telecamUpdater; // Construct an updater class.

    telecamUpdater.setHardwareID("/tele_camera/image_raw");

    ros::Subscriber subTelecam = nh.subscribe("/tele_camera/image_raw", 1000, telecam_callback);

    // Creating tasks using functions with FunctionDiagnosticTask
    diagnostic_updater::FunctionDiagnosticTask seq("Sequences",
        boost::bind(&check_seq, boost::placeholders::_1));

    diagnostic_updater::CompositeDiagnosticTask bounds("TELE-CAM check");

    //Creates a new task, registers the task, and returns the instance.
    bounds.addTask(&seq);

    //Add the CompositeDiagnosticTask to our Updater.
    telecamUpdater.add(bounds);
    telecamUpdater.broadcast(0, "Initializing TELE-CAM updater");
    telecamUpdater.force_update();

  while (nh.ok())
  {
    ros::Duration(0.1).sleep();
    //spinOnce() will call all the callbacks waiting to be called at that point in time.
    ros::spinOnce();
    //Call updater
    telecamUpdater.update();    
  }

  return 0; 
}
