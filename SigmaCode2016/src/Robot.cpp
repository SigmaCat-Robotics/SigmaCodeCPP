#include "WPILib.h"

/**
 * Uses the CameraServer class to automatically capture video from a USB webcam
 * and send it to the FRC dashboard without doing any vision processing. This
 * is the easiest way to get camera images to the dashboard. Just add this to the
 * RobotInit() method in your program.
 */
class QuickVisionRobot : public SampleRobot
{
	Joystick *left, *right,*controller;
	VictorSP *left1,*left2,*right1,*right2, *shooter;
	VictorSP *intake, *leftIndexer, *rightIndexer,  *armMotor;
	RobotDrive *drive108;
	DigitalInput *Upperlimit, *Lowerlimit;

public:
	void RobotInit() override {
		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		left = new Joystick(0);
		right = new Joystick(1);
		controller = new Joystick(2);

		left1 = new VictorSP(9);
		left2 = new VictorSP(8);
		right1 = new VictorSP(7);
		right2 = new VictorSP(6);
		armMotor = new VictorSP(5);
		intake = new VictorSP(4);
		leftIndexer = new VictorSP(3);
		rightIndexer = new VictorSP(2);
		shooter = new VictorSP(1);

		Lowerlimit = new DigitalInput(0);
		Upperlimit = new DigitalInput(1);

		drive108 = new RobotDrive(left1,left2,right1,right2);
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			/** robot code here! **/
			drive108->TankDrive(left->GetY(),right->GetY());
			SmartDashboard::PutNumber("DB/Slider 0", left->GetY());
			SmartDashboard::PutNumber("DB/Slider 1", right->GetY());
			armMotor->Set(1.0);
			Wait(0.005);				// wait for a motor update time
			if(controller->GetRawButton(1)){
				shooter->Set(1.0);
			}else{
				shooter->Set(0);
			}
		/*
			if(controller->GetRawAxis(2)>0.2){
				if(!Upperlimit->Get()){
					armMotor->Set(0.3);
				}else{
					armMotor->Set(0.0);
				}
			}
			else if(controller->GetRawAxis(3)>0.2){
				if(!Lowerlimit->Get()){
					armMotor->Set(-0.1);
				}else{
					armMotor->Set(0.0);
				}
			}else{
				armMotor->Set(0.0);
			}
		*/


			if(controller->GetRawButton(5)){
				intake->Set(1.0);
			}
			else{
				intake->Set(0.0);
			}
			if(controller->GetRawButton(6)){
				leftIndexer->Set(1.0);
				rightIndexer->Set(-1.0);
			}
			else{
				leftIndexer->Set(0.0);
				rightIndexer->Set(0.0);
			}		}
	}
};

START_ROBOT_CLASS(QuickVisionRobot)

