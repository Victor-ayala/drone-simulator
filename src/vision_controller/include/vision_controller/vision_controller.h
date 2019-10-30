#ifndef VISION_CONTROLLER
#define VISION_CONTROLLER

#include <ros/ros.h>
#include <ros/package.h>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <geometry_msgs/Twist.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class visionController
{


public:
	ros::NodeHandle nh_;

  image_transport::ImageTransport it_;
  image_transport::Subscriber img_sub;
  ros::Publisher cmd_pub;
  ros::Time ptime, ctime;
  ros::Duration d;

  geometry_msgs::Twist cmd_vel;
  Mat image;
	Mat imgHSV;
	Mat Threshold;


public:
	visionController();
	~visionController();

	void Callback(const sensor_msgs::ImageConstPtr &msg);
};

#endif
