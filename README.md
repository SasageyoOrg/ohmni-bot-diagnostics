# ohmni-bot-diagnostics

## WIP

# 📝 Table of Contents
- [📋 About ](#about-)
- [👩‍💻 Installation and Usage ](#installation-and-usage-)
- [🗂 Project Topology ](#-project-topology-)
- [✍️ Authors ](#️-authors-)
- [🎉 Acknowledgements ](#-acknowledgements-)

# 📋About <a name = "about"></a>

ROS Diagnostics based monitoring system for Ohmni telepresence robot
# 👩‍💻Installation and Usage <a name="ins-usage"></a>

### With script files:

- Build with:
    ```
    ./compiler.sh --compile
    ```
- Clean build with: 
    ```
    ./compiler.sh --cclean
    ```
- Run **gazebo simulation**, **diagnostic aggregator** & **updater** and the **monitor** with: 
    ```
    ./compiler.sh --launch
    ```
    Otherwise you can append this option to the previous build commands (es *./compiler.sh --cclean --launch*).
- Add **Rqt Gui** option to display multiple *Rqt plugins* into a single window:
    ```
    ./compiler.sh --cclean --launch --rqtgui
    ./compiler.sh --launch --rqtgui
    ```

### Without script files:

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

# 🗂 Project Topology <a name="project-topology"></a>
```
src
└── tb_sim
    ├── diagnostic_aggregator
    │   ├── include
    │   ├── launch
    │   └── src
    ├── diagnostic_updater
    │   ├── include
    │   ├── launch
    │   └── src
    ├── gazebo_environment
    │   ├── launch
    │   ├── models
    │   └── worlds
    ├── tb_description
    │   ├── launch
    │   ├── meshes
    │   ├── rviz
    │   └── urdf
    ├── tb_gazebo
    │   ├── launch
    │   ├── plugins
    │   └── rviz
    ├── tb_gazebo_plugins
    │   ├── include
    │   └── src
    └── tb_teleop
        └── launch

27 directories

```

# ✍️ Authors <a name = "authors"></a>
- Conti Edoardo [@edoardo-conti](https://github.com/edoardo-conti)
- Federici Lorenzo [@lorenzo-federici](https://github.com/lorenzo-federici)
- Melnic Andrian [@andrian-melnic](https://github.com/andrian-melnic)

# 🎉 Acknowledgements <a name = "acknowledgement"></a>
- Preventive Maintenance and Smart Automation Robotics Class - Professor <a href="https://www.univpm.it/Entra/Docenti_1/Ingegneria_1/docname/idsel/767/docname/ALESSANDRO%20FREDDI"> <i>Alessandro Freddi</i></a>
