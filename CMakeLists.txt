cmake_minimum_required(VERSION 2.8.3)
project(tf2pose)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  nav_msgs
  roscpp
  rospy
  std_msgs
  tf2_ros
  message_generation
)


## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
add_service_files(
   FILES
   tf2req.srv
 )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   geometry_msgs 
   std_msgs
 )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES tf2pose
#  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy std_msgs tf2_ros
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(tf2pose src/tf2pose.cpp)
target_link_libraries(tf2pose ${catkin_LIBRARIES})

add_executable(tf2srv src/tf2srv.cpp)
target_link_libraries(tf2srv ${catkin_LIBRARIES})

