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
	DoubleSolenoid *shifter, *shooterAim;
	Ultrasonic *ballDetect;
	Task *Operating;

public:
	void RobotInit() override {
		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		left = new Joystick(1);
		right = new Joystick(0);
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

		shifter = new DoubleSolenoid(0,1);
		shooterAim = new DoubleSolenoid(2,3);

		ballDetect = new Ultrasonic(3, 2);
		ballDetect->SetEnabled(true);
		ballDetect->SetAutomaticMode(true); // turns on automatic mode

		QuickVisionRobot *bot = this;
		Operating = new Task("Operating", Wrapper, bot);
	}

	void OperatorControl()
	{
	//	int counter = 0;
	//	bool pulse = true;
		Operating->join();
		while (IsOperatorControl() && IsEnabled())
		{
			/** robot code here! **/
			/*if(left->GetRawButton(1) && right->GetRawButton(1)){
				shifter->Set(DoubleSolenoid::kForward);
			}else{
				shifter->Set(DoubleSolenoid::kReverse);
			}*/
			drive108->TankDrive(left->GetY(),right->GetY());
			SmartDashboard::PutNumber("DB/Slider 0", left->GetY());
			SmartDashboard::PutNumber("DB/Slider 1", right->GetY());
			SmartDashboard::PutNumber("Ball Detect", ballDetect->GetRangeInches());
			Wait(0.005);				// wait for a motor update time
/*
			if(controller->GetRawAxis(2)>0.2){//down
				if(!Upperlimit->Get()){
					armMotor->Set(0.50);
				}else{
					armMotor->Set(0.0);
				}
			}
			else if(controller->GetRawAxis(3)>0.2){//up
				if(!Lowerlimit->Get()){
					armMotor->Set(-0.28);
				}else{
					armMotor->Set(0.0);
				}
			}else{
				armMotor->Set(0.0);
			}

			if(controller->GetRawButton(4)){
				shooterAim->Set(DoubleSolenoid::kForward);
			}
			else if(controller->GetRawButton(2)){
				shooterAim->Set(DoubleSolenoid::kReverse);
			}

			if(controller->GetRawButton(5)){//intake
				shooter->Set(0);
				intake->Set(-0.7);
				if(pulse){
					leftIndexer->Set(-0.1);
					rightIndexer->Set(0.1);
					if(counter%20 == 0){
						pulse = false;
					}
				}else{
					leftIndexer->Set(0.0);
					rightIndexer->Set(0.0);
					if(counter%20 == 0){
						pulse = true;
					}
				}
			}
			else if(controller->GetRawButton(6)){//release
				shooter->Set(0);
				intake->Set(0.7);
				leftIndexer->Set(1.0);
				rightIndexer->Set(-1.0);
			}
			else if(controller->GetRawButton(3)){
				intake->Set(0.0);
				shooter->Set(0.9);
				if(controller->GetRawButton(1)){
					leftIndexer->Set(-1.0);
					rightIndexer->Set(1.0);
				}else{
					leftIndexer->Set(0.0);
					rightIndexer->Set(0.0);
				}
			}
			else{//stop
				shooter->Set(0);
				intake->Set(0.0);
				leftIndexer->Set(0.0);
				rightIndexer->Set(0.0);
			}
			counter = counter+1;*/
		}
	}

private:
	void ShootIntake(){
		int counter = 0;
		bool pulse = true;
		while(IsOperatorControl() && IsEnabled()){
			if(controller->GetRawAxis(2)>0.2){//down
				if(!Upperlimit->Get()){
					armMotor->Set(0.50);
				}else{
					armMotor->Set(0.0);
				}
			}
			else if(controller->GetRawAxis(3)>0.2){//up
				if(!Lowerlimit->Get()){
					armMotor->Set(-0.28);
				}else{
					armMotor->Set(0.0);
				}
			}else{
				armMotor->Set(0.0);
			}

			if(controller->GetRawButton(4)){
				shooterAim->Set(DoubleSolenoid::kForward);
			}
			else if(controller->GetRawButton(2)){
				shooterAim->Set(DoubleSolenoid::kReverse);
			}

			if(controller->GetRawButton(5)){//intake
				shooter->Set(0);
				intake->Set(-0.7);
				if(pulse){
					leftIndexer->Set(-0.1);
					rightIndexer->Set(0.1);
					if(counter%20 == 0){
						pulse = false;
					}
				}else{
					leftIndexer->Set(0.0);
					rightIndexer->Set(0.0);
					if(counter%20 == 0){
						pulse = true;
					}
				}
			}
			else if(controller->GetRawButton(6)){//release
				shooter->Set(0);
				intake->Set(0.7);
				leftIndexer->Set(1.0);
				rightIndexer->Set(-1.0);
			}
			else if(controller->GetRawButton(3)){
				intake->Set(0.0);
				shooter->Set(0.9);
				if(controller->GetRawButton(1)){
					leftIndexer->Set(-1.0);
					rightIndexer->Set(1.0);
				}else{
					leftIndexer->Set(0.0);
					rightIndexer->Set(0.0);
				}
			}
			else{//stop
				shooter->Set(0);
				intake->Set(0.0);
				leftIndexer->Set(0.0);
				rightIndexer->Set(0.0);
			}
			counter = counter+1;
		}
	}

	static void Wrapper(QuickVisionRobot *bot){
		bot->ShootIntake();
	}
};

START_ROBOT_CLASS(QuickVisionRobot)

