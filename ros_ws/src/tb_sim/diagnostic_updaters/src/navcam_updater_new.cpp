#include <ros/ros.h>
#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/publisher.h>

#include <string>
int main(int argc, char** argv)
{
  // Initialize the ROS node.
  ros::init(argc, argv, "timestamp_status_example");
  ros::NodeHandle nh;

  // Create a diagnostic navcam_updater.
  diagnostic_updater::Updater navcam_updater;
	std::string topic_name = "/nav_camera/image_raw/";

	// Create a TopicDiagnostic object to monitor the "sensor_data" topic.
	// Specify that the topic is expected to publish messages of type "sensor_msgs/LaserScan".
	double freq_min = 5;
	double freq_max = 20;
	diagnostic_updater::TopicDiagnostic camera_status(topic_name, navcam_updater,
																											diagnostic_updater::FrequencyStatusParam(&freq_min, &freq_max, 0.1, 10),
																											diagnostic_updater::TimeStampStatusParam(-1, 0.1));

  // Set a callback function to be called whenever a message is received on the "/nav_camera/image_raw/" topic.
  // This callback will update the timestamp of the last received message.
  ros::Subscriber sub = nh.subscribe(topic_name, 1000, &diagnostic_updater::TimeStampStatus::tick, &camera_status);

  // Run the ROS event loop.
  ros::spin();

  return 0;
}