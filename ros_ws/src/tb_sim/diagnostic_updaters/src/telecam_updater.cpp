// #include <diagnostic_updater/navcam_updater.h>
#include <ros/ros.h>
#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/publisher.h>
#include <sensor_msgs/Image.h>

ros::Time stamp;

void telecam_callback(const sensor_msgs::ImageConstPtr& msg)
{
	stamp = msg->header.stamp;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "telecam_updater"); // Ros initialization function.
	ros::NodeHandle nh; // Construct a NodeHandle Class. This class is used for writing nodes. 
	diagnostic_updater::Updater telecamUpdater; // Construct an updater class.
	telecamUpdater.setHardwareID("/tele_camera/image_raw");
	ros::Subscriber sub = nh.subscribe("/tele_camera/image_raw", 1000, &telecam_callback);

	double min_freq = 5;
	double max_freq = 20;

	const double min_ts = 0.001;
	const double max_ts = 0.2;

	diagnostic_updater::TopicDiagnostic pub1_freq(
		"/tele_camera/image_raw/", 
		telecamUpdater,
		diagnostic_updater::FrequencyStatusParam(&min_freq, &max_freq, 1, 100),
		diagnostic_updater::TimeStampStatusParam(min_ts, max_ts));


	
	telecamUpdater.force_update();

	while (nh.ok())
	{

		ros::Duration(0.1).sleep();
		ros::spinOnce();
		pub1_freq.tick(stamp);
		telecamUpdater.update();    

	}
	return 0; 
}