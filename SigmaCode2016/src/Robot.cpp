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
	CANTalon *left1,*left2,*right1,*right2, *shooter, *armMotor;
	VictorSP *intake, *leftIndexer, *rightIndexer;
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
		left1 = new CANTalon(1);
		left2 = new CANTalon(2);
		right1 = new CANTalon(3);
		right2 = new CANTalon(4);
		shooter = new CANTalon(5);
		armMotor = new CANTalon(6);

		intake = new VictorSP(9);
		leftIndexer = new VictorSP(8);
		rightIndexer = new VictorSP(7);

		Lowerlimit = new DigitalInput(0);
		Upperlimit = new DigitalInput(1);

		left1->SetControlMode(CANSpeedController::kVoltage);
		left2->SetControlMode(CANSpeedController::kFollower);
		right1->SetControlMode(CANSpeedController::kVoltage);
		right2->SetControlMode(CANSpeedController::kFollower);

		left2->Set(1);
		right2->Set(3);

		drive108 = new RobotDrive(left1,right1);

		shooter->SetControlMode(CANSpeedController::kVoltage);

		armMotor->SetControlMode(CANSpeedController::kVoltage);
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			/** robot code here! **/
			//left1->Set(left->GetY()*12);
			//right1->Set(right->GetY()*12);
			drive108->TankDrive(left->GetY()*12,right->GetY()*12);
			SmartDashboard::PutNumber("DB/Slider 0", left->GetY()+1);
			SmartDashboard::PutNumber("DB/Slider 1", right->GetY()+1);
			Wait(0.005);				// wait for a motor update time
			if(controller->GetRawButton(1)){
				shooter->Set(12);
			}else{
				shooter->Set(0);
			}


			if(controller->GetRawAxis(2)>0.2){
				if(!Upperlimit->Get()){
					armMotor->Set(5.0);
				}else{
					armMotor->Set(0.0);
				}
			}
			else if(controller->GetRawAxis(3)>0.2){
				if(!Lowerlimit->Get()){
					armMotor->Set(-1.2);
				}else{
					armMotor->Set(0.0);
				}
			}else{
				armMotor->Set(0.0);
			}



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
			}
		}
	}
};

START_ROBOT_CLASS(QuickVisionRobot)

