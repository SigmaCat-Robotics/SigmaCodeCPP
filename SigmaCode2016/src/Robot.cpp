#include "WPILib.h"
#include "SigmaDrive.h"
#include "ShooterIntake.h"


class Robot: public SampleRobot
{
	SigmaDrive *myRobot; // robot drive system
	ShooterIntake *mySword;
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

	void shootTask(){
		while(IsAutonomous() && IsEnabled()){
			//Auto code here
		}
		while(IsOperatorControl() && IsEnabled()){
			if(true){
				if(lstick->GetRawButton(5)||rstick->GetRawButton(4)){
					mySword->Intake();
				}
				else if(lstick->GetRawButton(4)||rstick->GetRawButton(5)){
					mySword->Release();
				}
			}

			if(true){
				if(lstick->GetRawButton(3)||rstick->GetRawButton(3)){
					mySword->LiftIntake();
				}
				else if(lstick->GetRawButton(2)||rstick->GetRawButton(2)){
					mySword->LowerIntake();
				}
			}

			if(true){
				if(lstick->GetRawButton(1)){
					mySword->Prime();
				}
				if(rstick->GetRawButton(1)){
					mySword->Shoot();
				}
			}
			Wait(0.005);
		}
	}

	static void driveWrapper(Robot* bot){
		bot->driveTask();
	}

	static void shootWrapper(Robot* bot){
		bot->shootTask();
	}


public:
	Robot(){
		lstick = new Joystick(0),rstick = new Joystick(1);
		myRobot = new SigmaDrive();
		myRobot->setExpiration(0.1);
		mySword = new ShooterIntake();
		Robot* bot = this;
		std::thread drive(driveWrapper, bot);
		std::thread shoot(shootWrapper, bot);
		drive.join();
		shoot.join();
	}

	void OperatorControl()
	{
	}

};
START_ROBOT_CLASS(Robot)
