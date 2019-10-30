cmake_minimum_required(VERSION 2.8.3)
project(image_viewer)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
)

find_package(OpenCV REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES image_viewer
#  CATKIN_DEPENDS cv_bridge image_transport roscpp
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

include_directories(include include/image_viewer)

## Declare a C++ executable
add_executable(image_viewer 
				src/image_viewer_node.cpp 
				src/image_viewer_nodelet.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(image_viewer 
				${catkin_LIBRARIES}
				${OpenCV_LIBS})
