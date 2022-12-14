<p align="center">
  <a href="" rel="noopener">
  <img width=180px height=200px src="https://i.imgur.com/jrRtO9Z.png" alt="Project logo"></a>
</p>

<h1 align="center">Monitoring System for Ohmni Telepresence Robot based on ROS DIAGNOSTICS</br><sub></sub></h1>

<div align="center">
  
![ROS](https://img.shields.io/ros/v/melodic/diagnostics)
![UNIVPM](https://img.shields.io/badge/organization-UNIVPM-red)
![GitHub](https://img.shields.io/github/license/SasageyoOrg/ohmni-bot-diagnostics?color=green)
</div>

# ๐ Table of Contents
- [๐ About ](#about-)
- [๐ฉโ๐ป Installation and Usage ](#installation-and-usage-)
- [๐ Project Topology ](#-project-topology-)
- [โ๏ธ Authors ](#๏ธ-authors-)
- [๐ Acknowledgements ](#-acknowledgements-)

# ๐About <a name = "about"></a>

ROS Diagnostics based monitoring system for Ohmni telepresence robot. It features
diagnostics for the following sensors:
- Navigation camera
- Camera
- Scan sensor
- IMU (Inertial Measurement Unit)
- Joint States (Left/ Right wheels, caster, caster wheel, neck)
- Odometry 


# ๐ฉโ๐ปInstallation and Usage <a name="ins-usage"></a>

### With bash script:
For easy compilation and running, a bash script is provided:

- Build with:
    ```
    ./compiler.sh --compile
    ```
- Clean build with: 
    ```
    ./compiler.sh --cclean
    ```
- Run **gazebo simulation**, **diagnostic aggregator**, **diagnostic updater** and the **rqt monitor** with: 
    ```
    ./compiler.sh --launch
    ```
    Otherwise you can append this option to the previous build commands (es *./compiler.sh --cclean --launch*).
- Add **Rqt Gui** option to display multiple *Rqt plugins* into a single window:
    ```
    ./compiler.sh --cclean --launch --rqtgui
    ./compiler.sh --launch --rqtgui
    ```
### Without script:
If you're having trubles with the script, you can start the simulation manually:

1. Build with
    ```
    cd ros_ws
    catkin_make
    ```
2. Run **gazebo simulation**
    ```
    source devel/setup.bash
    roslaunch gazebo_environment empty.launch
    ```
3. Run **diagnostic updater** in a new console tab/window
    ```
    source devel/setup.bash
    roslaunch diagnostic_updater updaters_launcher.launch 
    ```
4. Run **diagnostic aggregator** in a new console tab/window
    ```
    source devel/setup.bash
    roslaunch diagnostic_aggregator aggregator_launcher.launch
    ```
5. Run the **monitor** with
    ```
    rosrun rqt_robot_monitor rqt_robot_monitor 
    ```

# ๐ Project Topology <a name="project-topology"></a>
```
src
โโโ tb_sim
    โโโ diagnostic_aggregator
    โย?ย? โโโ include
    โย?ย? โโโ launch
    โย?ย? โโโ src
    โโโ diagnostic_updater
    โย?ย? โโโ include
    โย?ย? โโโ launch
    โย?ย? โโโ src
    โโโ gazebo_environment
    โย?ย? โโโ launch
    โย?ย? โโโ models
    โย?ย? โโโ worlds
    โโโ tb_description
    โย?ย? โโโ launch
    โย?ย? โโโ meshes
    โย?ย? โโโ rviz
    โย?ย? โโโ urdf
    โโโ tb_gazebo
    โย?ย? โโโ launch
    โย?ย? โโโ plugins
    โย?ย? โโโ rviz
    โโโ tb_gazebo_plugins
    โย?ย? โโโ include
    โย?ย? โโโ src
    โโโ tb_teleop
        โโโ launch
```

# โ๏ธ Authors <a name = "authors"></a>
- Conti Edoardo [@edoardo-conti](https://github.com/edoardo-conti)
- Federici Lorenzo [@lorenzo-federici](https://github.com/lorenzo-federici)
- Melnic Andrian [@andrian-melnic](https://github.com/andrian-melnic)

# ๐ Acknowledgements <a name = "acknowledgement"></a>
- Preventive Maintenance and Smart Automation Robotics Class - Professor <a href="https://www.univpm.it/Entra/Docenti_1/Ingegneria_1/docname/idsel/767/docname/ALESSANDRO%20FREDDI"> <i>Alessandro Freddi</i></a>
