cmake_minimum_required(VERSION 2.8.3)
project(optiga_node)

find_package(catkin REQUIRED COMPONENTS roscpp std_srvs message_runtime roboy_middleware_msgs)
include_directories( ${catkin_INCLUDE_DIRS})
link_directories("/home/pi/workspace/personalize-optiga-trust-x/source/build/")
catkin_package(CATKIN_DEPENDS roscpp message_runtime std_srvs roboy_middleware_msgs)
add_executable(optiga_node src/optiga_signee.cpp)
target_link_libraries(optiga_node optiga ${catkin_LIBRARIES})
