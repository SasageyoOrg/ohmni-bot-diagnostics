#!/bin/bash  

# compiling the code
#rm -r build
#rm -r devel
catkin_make

# sourcing the catkin setup
source devel/setup.bash

# launch gazebo simulation
gnome-terminal --tab --title=GazeboSim -- $SHELL -c "source devel/setup.bash; roslaunch gazebo_environment empty.launch"
sleep 1

# launch diagnostic updater
gnome-terminal --tab --title=DiagnosticUpdater -- $SHELL -c "source devel/setup.bash; roslaunch diagnostic_updater updaters_launcher.launch"
sleep 1

# launch diagnostic aggregator
gnome-terminal --tab --title=DiagnosticAggregator -- $SHELL -c "source devel/setup.bash; roslaunch diagnostic_aggregator aggregator_launcher.launch"
sleep 1

# run rqt_robot_monitor
gnome-terminal --tab --title=RqtRobotMonitor -- $SHELL -c "rosrun rqt_robot_monitor rqt_robot_monitor; bash"

