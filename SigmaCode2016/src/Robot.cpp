#include "WPILib.h"
#include "SigmaDrive.h"


class Robot: public SampleRobot
{
	SigmaDrive *myRobot; // robot drive system
	Joystick *lstick,*rstick; // Left and Right Joysticks

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

	static void driveWrapper(Robot* bot){
		bot->driveTask();
	}


public:
	Robot(){
		lstick = new Joystick(0),rstick = new Joystick(1);
		myRobot = new SigmaDrive();
		myRobot->setExpiration(0.1);
		Robot* bot = this;
		std::thread drive(driveWrapper, bot);
		drive.join();
	}

	void OperatorControl()
	{
	}

};
START_ROBOT_CLASS(Robot)
