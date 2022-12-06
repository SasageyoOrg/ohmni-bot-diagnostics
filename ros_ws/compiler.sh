#!/bin/bash  

launch () {
    # launch gazebo simulation
    gnome-terminal --tab --title=GazeboSim -- $SHELL -c "source devel/setup.bash; roslaunch gazebo_environment empty.launch"
    echo ${!} > /var/tmp/MPRAIGazeboSim.pid
    sleep 1

    # launch diagnostic updater
    gnome-terminal --tab --title=DiagnosticUpdater -- $SHELL -c "source devel/setup.bash; roslaunch diagnostic_updater updaters_launcher.launch"
    echo ${!} > /var/tmp/MPRAIGDiagnosticUpdater.pid
    sleep 1

    # launch diagnostic aggregator
    gnome-terminal --tab --title=DiagnosticAggregator -- $SHELL -c "source devel/setup.bash; roslaunch diagnostic_aggregator aggregator_launcher.launch"
    echo ${!} > /var/tmp/MPRAIDiagnosticAggregator.pid
    sleep 1

    # run rqt_robot_monitor
    gnome-terminal --tab --title=RqtRobotMonitor -- $SHELL -c "rosrun rqt_robot_monitor rqt_robot_monitor"
    echo ${!} > /var/tmp/MPRAIRqtRobotMonitor.pid
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
    pclosed=0

    if [ -f /var/tmp/MPRAIGazeboSim.pid ]; then
        kill $(cat /var/tmp/MPRAIGazeboSim.pid)
        rm /var/tmp/MPRAIGazeboSim.pid
        let "i++" 
    fi
    if [ -f /var/tmp/MPRAIGDiagnosticUpdater.pid ]; then
        kill $(cat /var/tmp/MPRAIGDiagnosticUpdater.pid)
        rm /var/tmp/MPRAIGDiagnosticUpdater.pid
        let "i++" 
    fi
    if [ -f /var/tmp/MPRAIDiagnosticAggregator.pid ]; then
        kill $(cat /var/tmp/MPRAIDiagnosticAggregator.pid)
        rm /var/tmp/MPRAIDiagnosticAggregator.pid
        let "i++" 
    fi
    if [ -f /var/tmp/MPRAIRqtRobotMonitor.pid ]; then
        kill $(cat /var/tmp/MPRAIRqtRobotMonitor.pid)
        rm /var/tmp/MPRAIRqtRobotMonitor.pid
        let "i++" 
    fi

    if [ $pclosed -gt 0 ]; then
        echo "processes closed: " $pclosed
    else 
        echo "there aren't processes to close"
    fi
		rosnode kill --all

elif [ "$1" = "--help" ]; then
    echo -e "${bold}./compiler.sh --compile${normal} \t -> compile the catkin workspace"
    echo -e "${bold}./compiler.sh --cclean${normal} \t\t -> delete dev dirs and then compile"
    echo -e "${bold}./compiler.sh --launch${normal} \t\t -> compile and start the simulation"
    echo -e "${bold}./compiler.sh --close${normal} \t\t -> close all tab (not working yet)"
    echo -e "\n"
    echo -e "${bold}./compiler.sh [...] --launch${normal} \t -> start simulation (2nd parameter)"
    echo -e "${bold}./compiler.sh [...] --rqtgui${normal} \t -> start rqtgui (2nd/3rd parameter)"
    echo ""
else
    echo "Error, this option doesn't exist. Check this: \"./compiler.sh --help\""
fi

if [ "$2" = "--rqtgui" ] || [ "$3" = "--rqtgui" ]; then
    sleep 1
    gnome-terminal --tab --title=RqtGUI -- $SHELL -c "rosrun rqt_gui rqt_gui" 
fi

if [ "$2" = "--launch" ]; then
    source devel/setup.bash
    launch
fi