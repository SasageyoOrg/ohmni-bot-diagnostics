cmake_minimum_required(VERSION 3.0.2)
project(diagnostic_updater)

# Load catkin and all dependencies required for this package
find_package(catkin REQUIRED diagnostic_msgs roscpp std_msgs)

catkin_package(CATKIN_DEPENDS diagnostic_msgs roscpp std_msgs
               INCLUDE_DIRS include
	       LIBRARIES ${PROJECT_NAME}
)

include_directories(include ${catkin_INCLUDE_DIRS})

# IMU UPDATER NODE
add_executable(${PROJECT_NAME}_imu_updater src/imu_updater.cpp )
add_library(${PROJECT_NAME}
  src/timestamp_status.cpp)
set_target_properties(${PROJECT_NAME}_imu_updater PROPERTIES OUTPUT_NAME imu_updater_node PREFIX "")
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_imu_updater ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_imu_updater sensor_msgs_generate_messages_cpp)

# NAVCAM UPDATER NODE
add_executable(${PROJECT_NAME}_navcam_updater src/navcam_updater.cpp )
set_target_properties(${PROJECT_NAME}_navcam_updater PROPERTIES OUTPUT_NAME navcam_updater_node PREFIX "")
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_navcam_updater ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_navcam_updater sensor_msgs_generate_messages_cpp)

# TELECAM UPDATER NODE
add_executable(${PROJECT_NAME}_telecam_updater src/telecam_updater.cpp )
set_target_properties(${PROJECT_NAME}_telecam_updater PROPERTIES OUTPUT_NAME telecam_updater_node PREFIX "")
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_telecam_updater ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_telecam_updater sensor_msgs_generate_messages_cpp)

# JOINT STATES UPDATER NODE
add_executable(${PROJECT_NAME}_jointstates_updater src/jointstates_updater.cpp )
set_target_properties(${PROJECT_NAME}_jointstates_updater PROPERTIES OUTPUT_NAME jointstates_updater_node PREFIX "")
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_jointstates_updater ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_jointstates_updater sensor_msgs_generate_messages_cpp)

# ODOM UPDATER NODE
add_executable(${PROJECT_NAME}_odom_updater src/odom_updater.cpp )
set_target_properties(${PROJECT_NAME}_odom_updater PROPERTIES OUTPUT_NAME odom_updater_node PREFIX "")
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_odom_updater ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_odom_updater sensor_msgs_generate_messages_cpp)

# SCAN UPDATER NODE
add_executable(${PROJECT_NAME}_scan_updater src/scan_updater.cpp )
set_target_properties(${PROJECT_NAME}_scan_updater PROPERTIES OUTPUT_NAME scan_updater_node PREFIX "")
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_scan_updater ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME}_scan_updater sensor_msgs_generate_messages_cpp)

#set(LOCAL_GTEST_DIR "gtest-1.7.0")
# gtest could be included in ${catkin_INCLUDE_DIRS}, prepend local gtest include directory so it's searched first
#include_directories(BEFORE ${LOCAL_GTEST_DIR}/include)

# if(CATKIN_ENABLE_TESTING)
#   find_package(rostest REQUIRED)
#   add_rostest_gtest(diagnostic_updater_test test/diagnostic_updater_test.xml test/diagnostic_updater_test.cpp)
#   add_rostest(test/diagnostic_updater_fast_test.xml)
#   target_link_libraries(diagnostic_updater_test ${catkin_LIBRARIES} ${PROJECT_NAME})
# endif()

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

