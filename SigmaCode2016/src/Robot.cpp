#include "WPILib.h"

RobotDrive *drive;
Joystick *lstick, *rstick;

/**
 * Uses the CameraServer class to automatically capture video from a USB webcam
 * and send it to the FRC dashboard without doing any vision processing. This
 * is the easiest way to get camera images to the dashboard. Just add this to the
 * RobotInit() method in your program.
 */
class Robot : public SampleRobot
{
	DoubleSolenoid *shifter;
public:
	void RobotInit() override {
		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		drive = new RobotDrive(1,2,3,4);
		lstick = new Joystick(0);
		rstick = new Joystick(1);
		shifter = new DoubleSolenoid(0,1);
		//std::thread shift(Shift,shifter,this);
		//shift.join();
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			/** robot code here! **/
			drive->TankDrive(lstick,rstick);
			if(lstick->GetRawButton(1)){
				shifter->Set(DoubleSolenoid::kForward);
			}
			else{
				shifter->Set(DoubleSolenoid::kReverse);
			}
			Wait(0.005);				// wait for a motor update time
		}
	}
/*
	static void Shift(DoubleSolenoid *shift, Robot *bot){
		while(bot->IsOperatorControl() && bot->IsEnabled()){
			if(lstick->GetRawButton(1)){
				shift->Set(DoubleSolenoid::kForward);
			}
			else{
				shift->Set(DoubleSolenoid::kReverse);
			}
		}
	}
*/
};

START_ROBOT_CLASS(Robot)

