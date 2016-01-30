#include "WPILib.h"

class Robot: public SampleRobot
{
	RobotDrive *myRobot; // robot drive system
	Joystick *lstick,*rstick; // Left and Right Joysticks
	VictorSP *left1, *left2, *right1, *right2;

public:
	Robot(){

		left1 = new VictorSP(1);
		left2 = new VictorSP(2);
		right1 = new VictorSP(3);
		right2 = new VictorSP(4);

		printf("start!!!\r\n");

		myRobot = new RobotDrive(left1,left2, right1, right2);


		/*
		lstick = new Joystick(0),rstick = new Joystick(1);
//		myRobot = new RobotDrive();

	//	std::thread drive(driveTask);
	//	drive.detach();
*/
	}
	void RobotInit(){
		myRobot->SetExpiration(0.1);
		myRobot->SetSafetyEnabled(false);
		printf("Thuglife 2.0\n");
	}

	void DisabledInit(){
		printf("thuglife\r\n");
	}

	void DisabledPeriodic(){
		printf("Why??\n");
	}

	void Disabled(){
		printf("Work please\n");

	}

	void OperatorControl()
	{
		while(IsOperatorControl() && IsEnabled()){
			printf("OperatorControl\r\n");
			driveTask();
		}
	}
	void Autonomous(){
		printf("I'm a boss");
	}
private:
	void driveTask(){


			Wait(10.0);
		//myRobot->resetEncoders();
		while(IsAutonomous() && IsEnabled()){
			//Auto code here
		}
		while(IsOperatorControl() && IsEnabled()){
		//	myRobot->TankDrive(lstick->GetY(),rstick->GetY()); // drive with tank style
			Wait(0.005); // wait for a motor update time
		}
	}
};
START_ROBOT_CLASS(Robot)
