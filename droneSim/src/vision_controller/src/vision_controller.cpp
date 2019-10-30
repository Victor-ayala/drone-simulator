/*
 * Vision Controller for Bebop Parrot Simulation
 *
 * Author:	Victor Ayala Alfaro
 * 			Vision, Robotics and Artificial Intelligence Laboratory
 * 			LaViRIA
 *
 * 03/2018
 *
 * */

# include "vision_controller.h"



int lowH;
int lowS;
int lowV;
int highH;
int highS;
int highV;


float Kpx = 0.5, Kdx = -0.005;
float Kpy = 1.1, Kdy = -0.01;
float perrx = 0, errx = 0;
float perry = 0, erry = 0;
float Ts = 1/3;								// Sampling time for D constant
int erran = 10;									// Pixel error range


visionController::visionController():nh_("~"), it_(nh_)
{
	ROS_INFO("Init Vision Controller");
	img_sub = it_.subscribe("/bebop/image_raw", 1, &visionController::Callback, this);
	cmd_pub = nh_.advertise<geometry_msgs::Twist>("/bebop/cmd_vel", 1);

	//namedWindow("Bebop camera", 1);
	namedWindow( "Bebop camera", WINDOW_AUTOSIZE );

	ptime = ros::Time::now();
  ctime = ros::Time::now();
	while(ptime.toSec() == 0.0 || ctime.toSec() == 0.0)
	{
		ptime = ros::Time::now();
		ctime = ros::Time::now();
	}

	// vector<double> gainlist;
	// nh_.getParam("drone/gains", gainlist);
	// Kpx = gainlist[0];
	// Kdx = gainlist[1];
	// Kpy = gainlist[2];
	// Kdy = gainlist[3];
}

visionController::~visionController()
{

}

void visionController::Callback(const sensor_msgs::ImageConstPtr &msg)
{

	image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
	cvtColor(image, imgHSV, COLOR_BGR2HSV);

	int w = image.cols;
	int h = image.rows;
	float xsum = 0;
	float ysum = 0;
	int area = 0;

	lowH = 15;
	highH = 35;
	lowS = 120;
	highS = 255;
	lowV = 150;
	highV = 255;

	Scalar min(lowH/2, lowS, lowV);
	Scalar max(highH/2, highS, highV);

	inRange(imgHSV, min, max, Threshold);

	// Centroid calculus
	for(int y=0;y<Threshold.rows;y++)
  {
		for(int x=0;x<Threshold.cols;x++)
      {
				uint8_t pixel = Threshold.at<uint8_t>(y,x);
				if(pixel > 50)
				{
					xsum += x;
					ysum += y;
					area++;
				}
	    }
  }

	if(area != 0)
	{
		// Centroid obtention
		xsum = xsum/area;
		ysum = ysum/area;
		//ROS_INFO_STREAM("Centroide X: "<<xsum<<" Y: "<<ysum);

		ctime = ros::Time::now();
		d = ctime - ptime;
		double t = d.toSec();

		if(t >= Ts)
		{
    errx = h/2 - ysum;
    erry = w/2 - xsum;

		if(xsum > w/2 - erran && xsum < w/2 + erran){
			ROS_INFO_STREAM("X aligned");
			cmd_vel.linear.y = 0.0;
		}
		else {
			if(xsum < w/2 - erran)
			{

				ROS_INFO_STREAM("Right");
			}
			if(xsum > w/2 + erran)
			{
				ROS_INFO_STREAM("Left");

			}
			cmd_vel.linear.y = 2*Kpy*erry/w + 2*Kdy*(erry - perry)/(t*w);
		}
		if(ysum > h/2 - erran && ysum < h/2 + erran)
		{
			ROS_INFO_STREAM("Y aligned");
			//Kpx = 0.1;
			cmd_vel.linear.x = 0.0;
		}
		else {
			if(ysum < h/2 - erran)
			{
				ROS_INFO_STREAM("Front");
			}
			if(ysum > h/2 + erran)
			{
				ROS_INFO_STREAM("Back");
			}
			cmd_vel.linear.x = 2*Kpx*(errx)/h + 2*Kdx*(errx - perrx)/(t*h);
		}
		ptime = ctime;
		}
	}

	// Draw circle in centroid and on image's center
	cv::circle(image, Point2f(xsum , ysum), 5, cv::Scalar(0,255,0), -1);
	cv::circle(image, Point2f(image.cols/2, image.rows/2), 5, cv::Scalar(0,0,255), -1);

	cmd_vel.linear.z = 0;
	cmd_vel.angular.z = 0;

	cmd_pub.publish(cmd_vel);
	perrx = errx;
	perry = erry;

	// Camera image Display
	try
	{
		imshow("Bebop camera", image);
		//imshow("Threshold", Threshold);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("Error: %s", e.what());
		return;
	}

	waitKey(1);

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "vision_controller");
  visionController dr;
  ros::spin();
  return 0;
}
