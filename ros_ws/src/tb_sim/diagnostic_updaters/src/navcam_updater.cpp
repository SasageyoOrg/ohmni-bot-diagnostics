// #include <diagnostic_updater/navcam_updater.h>
#include <ros/ros.h>
#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/Image.h> 

ros::Time stamp;

void navcam_callback(const sensor_msgs::ImageConstPtr& msg)
{
	stamp = msg->header.stamp;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "navcam_updater"); // Ros initialization function.
	ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
	diagnostic_updater::Updater navcamUpdater; // Construct an updater class.
	navcamUpdater.setHardwareID("/nav_camera/image_raw");
	ros::Subscriber sub = nh.subscribe("/nav_camera/image_raw", 1000, &navcam_callback);

	double min_freq = 5;
	double max_freq = 100;

	const double min_ts = 0.001;
	const double max_ts = 0.15;

	diagnostic_updater::TopicDiagnostic pub1_freq(
		"/nav_camera/image_raw/", 
		navcamUpdater,
		diagnostic_updater::FrequencyStatusParam(&min_freq, &max_freq, 1, 100),
		diagnostic_updater::TimeStampStatusParam(min_ts, max_ts));


	
	navcamUpdater.force_update();

	while (nh.ok())
	{

		ros::Duration(0.01).sleep();
		ros::spinOnce();
		pub1_freq.tick(stamp);
		navcamUpdater.update();    

	}
	return 0; 
}