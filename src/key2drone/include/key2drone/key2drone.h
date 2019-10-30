#ifndef KEY2DRONE
#define KEY2DRONE

#include <ros/ros.h>
#include <ros/package.h>
#include <geometry_msgs/TwistStamped.h>

#include <std_msgs/Int8.h>
#include "std_msgs/Empty.h"

#include <QWidget>
#include <QtGui>

#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QKeyEvent>

using namespace std;

class KeyPress: public QWidget
{

  public:
    KeyPress(QWidget *parent = 0);
    ~KeyPress();

  protected:
    void keyPressEvent(QKeyEvent * e);

  private:

  ros::NodeHandle nh_;

	ros::Publisher land_pub;
	ros::Publisher takeoff_pub;
	ros::Publisher cmd_pub;
	ros::Publisher cam_pub;

	geometry_msgs::Twist cmd_vel;
	std_msgs::Empty msgLand;
	std_msgs::Empty msgTakeoff;

	geometry_msgs::Twist cmd_cam;

	QGridLayout *grid;
	QLabel *Speed;
	QLabel *Alt_speed;
	QLabel *Fovea_y;
	QLabel *Fovea_z;

	QLabel *Speed_value;
	QLabel *AltSpeed_value;
	QLabel *Fovea_value_y;
	QLabel *Fovea_value_z;
	QLabel *Command;

	QFont font;

	float speed;
	float altitude_speed;
	float fovea_y;
	float fovea_z;

	float pitch;
	float roll;
	float yaw;
	float altitude;

};

#endif
