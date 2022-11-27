# ohmni-bot-diagnostics
ROS Diagnostics based monitoring system for Ohmni telepresence robot

## WIP

## Usage

1. Build with
    ```
    cd ros_ws
    catkin_make
    ```
2. Run gazebo simulation
    ```
    source devel/setup.bash
    roslaunch gazebo_environment empty.launch
    ```
3. Run diagnostic updater in a new console tab/window
    ```
    source devel/setup.bash
    roslaunch gazebo_environment empty.launch
    ```
4. Run diagnostic aggregator in a new console tab/window
    ```
    source devel/setup.bash
    roslaunch gazebo_environment empty.launch
    ```

5. Run the monitor with
    ```
    rosrun rqt_robot_monitor rqt_robot_monitor 
    ```