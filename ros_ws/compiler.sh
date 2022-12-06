#!/bin/bash  

<<<<<<< Updated upstream
# compiling the code
#rm -r build
#rm -r devel
catkin_make
=======
launch () {
    # launch gazebo simulation
    gnome-terminal --tab --title=GazeboSim -- $SHELL -c "source devel/setup.bash; roslaunch gazebo_environment empty.launch"
    sleep 1

    # launch diagnostic updater
    gnome-terminal --tab --title=DiagnosticUpdaters -- $SHELL -c "source devel/setup.bash; roslaunch diagnostic_updaters updaters_launcher.launch"
    sleep 1

    # launch diagnostic aggregator
    gnome-terminal --tab --title=DiagnosticAggregator -- $SHELL -c "source devel/setup.bash; roslaunch diagnostic_aggregator aggregator_launcher.launch"
    sleep 1
>>>>>>> Stashed changes

# sourcing the catkin setup
source devel/setup.bash

# launch gazebo simulation
gnome-terminal --tab --title=GazeboSim -- $SHELL -c "source devel/setup.bash; roslaunch gazebo_environment empty.launch"
sleep 1

<<<<<<< Updated upstream
# launch diagnostic updater
gnome-terminal --tab --title=DiagnosticUpdater -- $SHELL -c "source devel/setup.bash; roslaunch diagnostic_updater updaters_launcher.launch"
sleep 1
=======
if [ "$1" = "--compile" ] || [ $# -eq 0 ] ; then
    compile
elif [ "$1" = "--cclean" ] ; then
    rm -r build/
    rm -r devel/
    echo "build dirs removed."
    compile
elif [ "$1" = "--launch" ] ; then 
    compile
    if [ $exitcode -eq 0 ] ; then
        # sourcing the catkin setup
        source devel/setup.bash
        launch
    else
        echo "compilation error, exit."
    fi
elif [ "$1" = "--close" ] ; then
    APP1PID=`pgrep roslaunch`
    APP1PPID=`ps j $APP1PID | awk 'NR>1 {print $1}'`
    kill -9 $APP1PID
		rosnode kill --all
elif [ "$1" = "--help" ]; then
    echo -e "${bold}--clean${normal} \t -> start compiling packages"
    echo -e "${bold}--cclean${normal} \t -> clean & start compiling packages"
    echo -e "${bold}--launch${normal} \t -> start simulation"
    echo -e "${bold}--close${normal} \t -> close all tab"
    echo -e "\n"
    echo -e "${bold}.. --launch${normal} \t -> start simulation as the second parameter"
    echo -e "${bold}.. --rqtgui${normal} \t -> start rqtgui"
    echo ""
else
    echo "Error, this option doesn't exist. Check this: \"./compiler.sh --help\""
fi
>>>>>>> Stashed changes

# launch diagnostic aggregator
gnome-terminal --tab --title=DiagnosticAggregator -- $SHELL -c "source devel/setup.bash; roslaunch diagnostic_aggregator aggregator_launcher.launch"
sleep 1

# run rqt_robot_monitor
gnome-terminal --tab --title=RqtRobotMonitor -- $SHELL -c "rosrun rqt_robot_monitor rqt_robot_monitor"