#ifndef GAZEBO_ROS_LIGHT_SENSOR_HH
#define GAZEBO_ROS_LIGHT_SENSOR_HH

#include <string>

// library for processing camera data for gazebo / ros conversions
#include <gazebo/plugins/CameraPlugin.hh>

#include <gazebo_plugins/gazebo_ros_camera_utils.h>

namespace gazebo
{
  class GazeboRosLight : public CameraPlugin, GazeboRosCameraUtils
  {
    /// brief Constructor
    /// param parent The parent entity, must be a Model or a Sensor
    public: GazeboRosLight();

    /// brief Destructor
    public: ~GazeboRosLight();

    /// brief Load the plugin
    /// param take in SDF root element
    public: void Load(sensors::SensorPtr _parent, sdf::ElementPtr _sdf);

    /// brief Update the controller
    protected: virtual void OnNewFrame(const unsigned char *_image,
    unsigned int _width, unsigned int _height,
    unsigned int _depth, const std::string &_format);

    ros::NodeHandle _nh;                // node handler to connect to the roscore
    ros::Publisher _sensorPublisher;    // defines a publisher that will publish messages containing the illuminance value

    // Two parameters have been defined: 
    // fov (field of view) and range. At present only fov is used to indicate the amount of 
    // pixels around the center of the image that will be taken into account to calculate the illuminance.
    double _fov;
    double _range;
  };
}
#endif