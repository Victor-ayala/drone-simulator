/*
 *
 *
 *
 *
 *
 *
 *
 *
 * */

 #include <QKeyEvent>
 #include "key2drone.h"

 KeyPress::KeyPress(QWidget *parent):
 		nh_("~"), QWidget(parent)
 {
 	ROS_INFO("Init Keyboard Controller");

 	takeoff_pub = nh_.advertise<std_msgs::Empty>("/bebop/takeoff", 3);
 	land_pub = nh_.advertise<std_msgs::Empty>("/bebop/land", 3);
 	cmd_pub = nh_.advertise<geometry_msgs::Twist>("/bebop/cmd_vel", 3);

 	cam_pub = nh_.advertise<geometry_msgs::Twist>("/bebop/camera_control", 3);

 	speed = 0.3;
 	altitude_speed = 1;
 	pitch = 0;
 	roll = 0;
 	yaw = 0;
 	altitude = 0;
 	fovea_y = 0;
 	fovea_z = 0;


 	Speed = new QLabel("Pitch", this);
 	Alt_speed = new QLabel("Roll", this);
 	Fovea_y = new QLabel("Fovea Y", this);
 	Fovea_z = new QLabel("Fovea Z", this);

 	Speed_value = new QLabel("0", this);
 	AltSpeed_value = new QLabel("0", this);
 	Fovea_value_y = new QLabel("  0", this);
 	Fovea_value_z = new QLabel("  0", this);
 	Command = new QLabel(" ", this);

 	font= Command->font();
 	font.setPointSize(20);
 	font.setBold(true);
 	Command->setFont(font);



  Speed->setText("Speed:");
  Alt_speed->setText("Altitude Speed:");
 	Fovea_y->setText("Fovea Y:");
 	Fovea_z->setText("Fovea Z:");

 	grid = new QGridLayout(this);

 	grid->addWidget(Speed, 1, 0);
 	grid->addWidget(Alt_speed, 2, 0);
 	grid->addWidget(Fovea_y, 4, 0);
 	grid->addWidget(Fovea_z, 6, 0);

 	grid->addWidget(Speed_value, 1 ,1);
 	grid->addWidget(AltSpeed_value, 2, 1);
 	grid->addWidget(Fovea_value_y, 4, 1);
 	grid->addWidget(Fovea_value_z, 6, 1);
 	grid->addWidget(Command, 7, 0);

   Speed_value->setText(QString::number(speed));
   AltSpeed_value->setText(QString::number(altitude_speed));

   setLayout(grid);
 }

 KeyPress::~KeyPress()
 {

 }

 void KeyPress::keyPressEvent(QKeyEvent *event)
 {
 	bool send_command = true;

 	cmd_vel.linear.x = 0.0;
 	cmd_vel.linear.y =  0.0;
 	cmd_vel.linear.z = 0.0;
 	cmd_vel.angular.z = 0.0;

 	pitch = 0;
 	roll = 0;
 	altitude = 0;
 	yaw = 0;

 	if(event->key() == Qt::Key_H)
 	{
 		pitch = 0.0;
 		roll = 0.0;
 		altitude = 0.0;
 		yaw = 0.0;
 		Command->setText("HOVERING");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_T)
 	{
 		takeoff_pub.publish(msgTakeoff);
 		Command->setText("TAKE OFF");
 		setLayout(grid);

 	}
 	else if(event->key() == Qt::Key_Space)
 	{

 		land_pub.publish(msgLand);
 		Command->setText("LANDING");
 		setLayout(grid);

 	}
 	else if(event->key() == Qt::Key_Q)
 	{
 		yaw += speed;
 		Command->setText("YAW LEFT");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_E)
 	{
 		yaw -= speed;
 		Command->setText("YAW RIGHT");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_W)
 	{
 		pitch += speed;
 		Command->setText("FORWARD");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_S)
 	{
 		pitch -= speed;
 		Command->setText("BACKWARD");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_A)
 	{
 		roll += speed;
 		Command->setText("LEFT");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_D)
 	{
 		roll -= speed;
 		Command->setText("RIGHT");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_Up)
 	{
 		altitude += altitude_speed;
 		Command->setText("UP");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_Down)
 	{
 		altitude -= altitude_speed;
 		Command->setText("DOWN");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_I)
 	{
 		fovea_y += 5;
 		if (fovea_y > 15)
 			fovea_y = 15;
 		Fovea_value_y->setText(QString::number(fovea_y));
 		Command->setText("FOVEA UP");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_K)
 	{
 		fovea_y -= 5;
 		if (fovea_y < -80)
 			fovea_y = -80;
 		Fovea_value_y->setText(QString::number(fovea_y));
 		Command->setText("FOVEA DOWN");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_J)
 	{
 		fovea_z -= 3;
 		if (fovea_z < -30)
 			fovea_z = -30;
 		Fovea_value_z->setText(QString::number(fovea_z));
 		Command->setText("FOVEA LEFT");
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_L)
 	{
 		fovea_z += 3;
 		if (fovea_z > 30)
 			fovea_z = 30;
 		Fovea_value_z->setText(QString::number(fovea_z));
 		Command->setText("FOVEA RIGHT");
 		setLayout(grid);
 	}
   else if(event->key() == Qt::Key_U)
 	{
 		fovea_z = 0;
    fovea_y = 0;
 		Fovea_value_z->setText(QString::number(fovea_z));
    Fovea_value_y->setText(QString::number(fovea_y));
 		Command->setText("FOVEA RESET");
 		setLayout(grid);
 	}
   else if(event->key() == Qt::Key_M)
 	{
    altitude_speed += 0.1;
    if(altitude_speed > 1)
      altitude_speed = 1;
    AltSpeed_value -> setText(QString::number(altitude_speed));
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_N)
 	{
 		altitude_speed -= 0.1;
    if(altitude_speed < 0.1)
      altitude_speed = 0.1;
    AltSpeed_value -> setText(QString::number(altitude_speed));
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_Left)
 	{
 		speed -= 0.1;
 		if(speed < 0.1)
 			speed = 0.1;
 		Speed_value -> setText(QString::number(speed));
 		setLayout(grid);
 	}
 	else if(event->key() == Qt::Key_Right)
 	{
 		speed += .1;
 		if(speed > 1)
 			speed = 1;
 		Speed_value->setText(QString::number(speed));
 		setLayout(grid);
 	}
 	if(event->key() == Qt::Key_Escape)
 	{
 		qApp->quit();
 	}

 	cmd_vel.linear.x = pitch;
 	cmd_vel.linear.y =  roll;
 	cmd_vel.linear.z = altitude;
 	cmd_vel.angular.z = yaw;

 	cmd_cam.angular.y = fovea_y;
 	cmd_cam.angular.z = fovea_z;

 	cmd_pub.publish(cmd_vel);
 	cam_pub.publish(cmd_cam);

 }
