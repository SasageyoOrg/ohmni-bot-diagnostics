#!/bin/bash  

launch () {
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
    gnome-terminal --tab --title=RqtRobotMonitor -- $SHELL -c "rosrun rqt_robot_monitor rqt_robot_monitor"
}

# compiling the code
compile () {
    catkin_make
    exitcode=$?
}

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
fi

if [ "$2" = "--rqtgui" ] ; then
    sleep 1
    gnome-terminal --tab --title=RqtGUI -- $SHELL -c "rosrun rqt_gui rqt_gui" 
fi