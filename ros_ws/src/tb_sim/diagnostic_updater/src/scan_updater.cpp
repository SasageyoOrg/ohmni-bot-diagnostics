#include <diagnostic_updater/scan_updater.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "scan_updater"); // Ros initialization function.
    ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
    diagnostic_updater::Updater scanUpdater; // Construct an updater class.

    scanUpdater.setHardwareID("/scan");

    ros::Subscriber subScan = nh.subscribe("/scan", 1000, scan_callback);

    // Creating tasks using functions with FunctionDiagnosticTask
    diagnostic_updater::FunctionDiagnosticTask seq("Sequences",
        boost::bind(&check_seq, boost::placeholders::_1));
    diagnostic_updater::FunctionDiagnosticTask range("Ranges",
        boost::bind(&check_range, boost::placeholders::_1));

    diagnostic_updater::CompositeDiagnosticTask bounds("SCAN check");

    //Creates a new task, registers the task, and returns the instance.
    bounds.addTask(&seq);
    bounds.addTask(&range);

    //Add the CompositeDiagnosticTask to our Updater.
    scanUpdater.add(bounds);
    scanUpdater.broadcast(0, "Initializing SCAN updater");
    scanUpdater.force_update();

  while (nh.ok())
  {
    ros::Duration(0.1).sleep();
    //spinOnce() will call all the callbacks waiting to be called at that point in time.
    ros::spinOnce();
    //Call updater
    scanUpdater.update();    
  }

  return 0; 
}
