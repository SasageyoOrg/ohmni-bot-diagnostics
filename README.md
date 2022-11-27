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
    roslaunch diagnostic_updater updaters_launcher.launch 

    ```
4. Run diagnostic aggregator in a new console tab/window
    ```
    source devel/setup.bash
    roslaunch diagnostic_aggregator aggregator_launcher.launch
    ```

5. Run the monitor with
    ```
    rosrun rqt_robot_monitor rqt_robot_monitor 
    ```


# 🗂 Project Topology <a name="project-topology"></a>
```
.
└── src
    └── tb_sim
        ├── diagnostic_aggregator
        │   ├── include
        │   │   └── diagnostic_aggregator
        │   ├── launch
        │   │   └── yamls
        │   └── src
        ├── diagnostic_updater
        │   ├── include
        │   │   └── diagnostic_updater
        │   ├── launch
        │   └── src
        │       └── diagnostic_updater
        ├── gazebo_environment
        │   ├── launch
        │   ├── models
        │   │   ├── furniture
        │   │   │   ├── chair_1
        │   │   │   │   ├── materials
        │   │   │   │   │   ├── scripts
        │   │   │   │   │   └── textures
        │   │   │   │   └── meshes
        │   │   │   ├── desk_brown
        │   │   │   │   ├── materials
        │   │   │   │   │   ├── scripts
        │   │   │   │   │   └── textures
        │   │   │   │   └── meshes
        │   │   │   ├── human_female_1
        │   │   │   │   ├── materials
        │   │   │   │   │   ├── scripts
        │   │   │   │   │   └── textures
        │   │   │   │   └── meshes
        │   │   │   ├── kitchen_chair
        │   │   │   │   └── meshes
        │   │   │   ├── labtop_mac_1
        │   │   │   │   ├── materials
        │   │   │   │   │   ├── scripts
        │   │   │   │   │   └── textures
        │   │   │   │   └── meshes
        │   │   │   ├── recycle_bin_green
        │   │   │   │   └── meshes
        │   │   │   ├── sofa_set_1
        │   │   │   │   ├── materials
        │   │   │   │   │   ├── scripts
        │   │   │   │   │   └── textures
        │   │   │   │   └── meshes
        │   │   │   └── table_conference_2
        │   │   │       ├── materials
        │   │   │       │   ├── scripts
        │   │   │       │   └── textures
        │   │   │       └── meshes
        │   │   ├── kolvn_office_base
        │   │   │   └── blender_model
        │   │   │       └── texture
        │   │   ├── obstacles
        │   │   │   ├── wood_cube_10cm
        │   │   │   ├── wood_cube_2_5cm
        │   │   │   ├── wood_cube_5cm
        │   │   │   ├── wooden_board
        │   │   │   └── wooden_case
        │   │   └── willowgarage
        │   │       ├── materials
        │   │       │   └── textures
        │   │       └── meshes
        │   └── worlds
        │       └── obstacle_test
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
        │   │   └── tb_gazebo_plugins
        │   └── src
        └── tb_teleop
            └── launch

82 directories

```

# ✍️ Authors <a name = "authors"></a>
- Conti Edoardo [@edoardo-conti](https://github.com/edoardo-conti)
- Federici Lorenzo [@lorenzo-federici](https://github.com/lorenzo-federici)
- Melnic Andrian [@andrian-melnic](https://github.com/andrian-melnic)

# 🎉 Acknowledgements <a name = "acknowledgement"></a>
- Preventive Maintenance and Smart Automation Robotics Class - Professor <a href="https://www.univpm.it/Entra/Docenti_1/Ingegneria_1/docname/idsel/767/docname/ALESSANDRO%20FREDDI"> <i>Alessandro Freddi</i></a>
