/*
 * Image viewer for Bebop Parrot
 * 
 * Author:	Victor Ayala Alfaro
 * 			Vision, Robotics and Artificial Intelligence Laboratory
 * 			LaViRIA
 * 
 * 03/2018
 * 
 * */
 
#include "image_viewer.h"

// Sliders parameters
int slider1=0;
int slider2=0;
int slider3=0;
int slider4=0;
int slider5=0;
int slider6=0;
const int slider_max = 255;
int lowH;
int lowS;
int lowV;
int highH;
int highS;
int highV;

static void on_trackbar1( int, void* )
{
  lowH = (int)(255.0*slider1/slider_max);
}

static void on_trackbar2( int, void* )
{
  lowS = (int)(255.0*slider2/slider_max);
}

static void on_trackbar3( int, void* )
{
  lowV = (int)(255.0*slider3/slider_max);
}

static void on_trackbar4( int, void* )
{
  highH = (int)(255.0*slider4/slider_max);
}

static void on_trackbar5( int, void* )
{
  highS = (int)(255.0*slider5/slider_max);
}

static void on_trackbar6( int, void* )
{
  highV = (int)(255.0*slider6/slider_max);
}


image_viewer::image_viewer():nh_("~"), it_(nh_)
{
	ROS_INFO("Init Camera Viewer");
	Image_ = it_.subscribe("/bebop/image_raw", 1, &image_viewer::imageCallback, this);
}

image_viewer::~image_viewer()
{

}

void image_viewer::imageCallback(const sensor_msgs::ImageConstPtr &msg)
{	
	try
	{
		imshow("Bebop camera", cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)-> image);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("Error: %s", e.what());
		return;
	}
	
	image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
	
	cvtColor(image, imgHSV, COLOR_BGR2HSV);
	
	createTrackbar( "LowH", "Threshold", &slider1, slider_max, on_trackbar1 );
	createTrackbar( "LowS", "Threshold", &slider2, slider_max, on_trackbar2 );
	createTrackbar( "LowV", "Threshold", &slider3, slider_max, on_trackbar3 );
	createTrackbar( "HighH", "Threshold", &slider4, slider_max, on_trackbar4 );
	createTrackbar( "HighS", "Threshold", &slider5, slider_max, on_trackbar5 );
	createTrackbar( "HighV", "Threshold", &slider6, slider_max, on_trackbar6 );
	
	Scalar min(lowH/2, lowS, lowV);
	Scalar max(highH/2, highS, highV);
	
	inRange(imgHSV, min, max, Threshold);
	imshow("Threshold", Threshold);
	
	waitKey(1);
	
}

