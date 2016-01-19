#include "WPILib.h"

class Robot: public SampleRobot
{
	SigmaDrive *myRobot; // robot drive system
	Joystick *lstick,*rstick; // Left and Right Joysticks


public:
	Robot() :
			lstick(0),rstick(1)

	{
		myRobot = new SigmaDrive();
		myRobot->setExpiration(0.1);
		std::thread drive(driveTask);
		drive.detach();
	}

	void OperatorControl()
	{
	}
private:
	void driveTask(){
		myRobot->resetEncoders();
		while(IsAutonomous() && IsEnabled()){
			//Auto code here
		}
		while(IsOperatorControl() && IsEnabled()){
			myRobot->tankDrive(lstick->GetY(),rstick->GetY()); // drive with tank style
			Wait(0.005); // wait for a motor update time
		}
	}
};
START_ROBOT_CLASS(Robot)
