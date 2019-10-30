cmake_minimum_required(VERSION 2.8.3)
project(key2drone)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

find_package(Qt4 REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES example
#  CATKIN_DEPENDS roscpp sensor_msgs std_msgs image_transport
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${QT_INCLUDES} include include/key2drone)

## Declare a C++ executable
add_executable(key2drone
				src/main.cpp 
				src/key2drone.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(key2drone 
					${QT_LIBRARIES}
					${catkin_LIBRARIES})

