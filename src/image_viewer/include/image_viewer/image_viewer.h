#ifndef IMAGE_VIEWER
#define IMAGE_VIEWER

#include <ros/ros.h>
#include <ros/package.h>

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class image_viewer
{


public:
	ros::NodeHandle nh_;
	
  	image_transport::ImageTransport it_;
  	image_transport::Subscriber Image_;
  	
  	Mat image;
	Mat imgHSV;
	Mat Threshold;
	

public:
	image_viewer();
	~image_viewer();
	
	void imageCallback(const sensor_msgs::ImageConstPtr &msg);
};

#endif
