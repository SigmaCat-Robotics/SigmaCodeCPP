#include "WPILib.h"
#include "Option.h"

#define FORWARD -1
#define BACKWARD 1

#define HIGHSPEED 1130
#define LOWSPEED 285.5

#define HIGHGEAR 1111
#define LOWGEAR 2222

#define TICKSPERFEET 421

//#include "LCameraServer.h"
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
	Encoder *leftEnc, *rightEnc, *shooterEnc;
	ADXRS450_Gyro *gyro;
	SendableChooser *chooser;
	Option *num;
	Relay *light;
	int state;
	bool cycle = false;
	int mach;

public:
	void RobotInit() override {
		light = new Relay(0);
		gyro = new ADXRS450_Gyro();
		gyro->Calibrate();

		chooser = new SendableChooser();
		chooser->AddDefault("Low Bar", new Option(1));
		chooser->AddObject("Defenses", new Option(2));
		chooser->AddObject("Two Point Auto", new Option(3));
		SmartDashboard::PutData("Auto", chooser);

		CameraServer::GetInstance()->SetQuality(50);
		//the camera name (ex "cam0") can be found through the roborio web interface
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		left = new Joystick(1);
		right = new Joystick(0);
		controller = new Joystick(2);

		left1 = new VictorSP(9);//og 9
		left2 = new VictorSP(8);
		right1 = new VictorSP(7);
		right2 = new VictorSP(6);
		armMotor = new VictorSP(5);
		intake = new VictorSP(4);
		leftIndexer = new VictorSP(3);
		rightIndexer = new VictorSP(2);
		shooter = new VictorSP(1);//og 1

		leftEnc = new Encoder(8,9, false, Encoder::EncodingType::k4X);
		rightEnc = new Encoder(6,7, true, Encoder::EncodingType::k4X);
		shooterEnc = new Encoder(4,5);

		Lowerlimit = new DigitalInput(0);
		Upperlimit = new DigitalInput(1);

		drive108 = new RobotDrive(left1,left2,right1,right2);

		shifter = new DoubleSolenoid(0,1);
		shooterAim = new DoubleSolenoid(2,3);

		ballDetect = new Ultrasonic(3, 2);
		ballDetect->SetEnabled(true);
		ballDetect->SetAutomaticMode(true); // turns on automatic mode

	}

	void autoMoat()
	{
		shifter->Set(DoubleSolenoid::kForward);//Low Gear
		shooterAim->Set(DoubleSolenoid::kReverse);//Shooter Up
		RunTobyRun(FORWARD, LOWGEAR, 12.5, 1.0);
	}

	void autoLowbar()
	{
		//shifter->Set(DoubleSolenoid::kForward);//Low Gear
		shooterAim->Set(DoubleSolenoid::kForward);//Shooter Down
		ArmDown();
	 	RunTobyRun(FORWARD, LOWGEAR, 12, 0.7);//og is 70%
	 	RunTobyRun(BACKWARD, LOWGEAR, 11, 0.7);//og is 70%
	}
	void twoPointAuto()
	{
		shooterAim->Set(DoubleSolenoid::kReverse);
		Wait(1);
		RunTobyRun(FORWARD, LOWGEAR, 7, 0.7);
	}

	void Autonomous()
	{
		rightEnc->Reset();
		leftEnc->Reset();
		num = (Option*) chooser->GetSelected();
		if(num->Get() == 1){
			autoLowbar();
		}
		else if(num->Get() == 2){
			autoMoat();
		}
		else if(num->Get() == 3){
			twoPointAuto();
		}
/*
		while(IsAutonomous() && IsEnabled()){
			CycleLight();
			Wait(0.5);
		}
*/			//Auto Pick
	}

	void OperatorControl()
	{
		int counter = 1;
		//int lightTime = 1;
		int choice = 1;

/*
		for(int x = 0; x < 7; x++){
			CycleLight();
			Wait(0.5);
		}
*/
		while (IsOperatorControl() && IsEnabled())
		{
			//printf ("r = %d l = %d\r\n", rightEnc->Get(), leftEnc->Get());

			/** robot code here! **/
			light->Set(Relay::kForward);
			if(right->GetRawButton(1)){
				shifter->Set(DoubleSolenoid::kForward); // High Gear = reverse
			}else if(left->GetRawButton(1)){
				shifter->Set(DoubleSolenoid::kReverse); // Low Gear = forward
			}
			drive108->TankDrive(left->GetY(),right->GetY());
			SmartDashboard::PutBoolean("Ball In:", ballDetect->GetRangeInches()<3);
			Wait(0.005);				// wait for a motor update time

			if(controller->GetRawAxis(2)>0.2){//down
				if(!Upperlimit->Get() && !(shooterAim->Get() == DoubleSolenoid::kReverse) ){
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

			if(controller->GetRawButton(2)){
				shooterAim->Set(DoubleSolenoid::kForward);
			}
			else if(controller->GetRawButton(4)){
				shooterAim->Set(DoubleSolenoid::kReverse);
			}



			if(controller->GetRawButton(6)){//intake
				switch(choice){
					case 1: intake->Set(-0.85);
							leftIndexer->Set(-0.50108);
							rightIndexer->Set(0.50108);
							if(ballDetect->GetRangeInches()<3){
								choice = 2;
								counter = 0;
							}
							std::printf("CHOICE 1\r\n");
							break;
					case 2:	if(counter%315 == 0){  //115
								leftIndexer->Set(0.0);
								rightIndexer->Set(0.0);
								choice = 3;
							}
							counter++;
							std::printf("CHOICE 2\r\n");
							break;
					case 3: intake->Set(0.0);
							std::printf("CHOICE 3\r\n");
							break;
				}
			}
			else if(controller->GetRawButton(5)){//release
				shooter->Set(0);
				intake->Set(0.7);
				leftIndexer->Set(1.0);
				rightIndexer->Set(-1.0);
				choice = 1;
			}
			else if(right->GetRawButton(3)){
				shooter->Set(0);
				intake->Set(0.8);
				leftIndexer->Set(0.0);
				rightIndexer->Set(0.0);
				choice = 1;
			}
			else if(controller->GetRawButton(3)){
				intake->Set(0.0);
				shooter->Set(0.9);
				if(controller->GetRawButton(1)){
					leftIndexer->Set(-1.0);
					rightIndexer->Set(1.0);
					//CycleLight();
				}else{
					leftIndexer->Set(0.0);
					rightIndexer->Set(0.0);
					//light->Set(Relay::kForward);
					//light->Set(Relay::kForward);
				}
				choice = 1;
			}
			else{//stop
				shooter->Set(0);
				intake->Set(0.0);
				leftIndexer->Set(0.0);
				rightIndexer->Set(0.0);
				choice = 1;
			}
		}
	}

private:
	void RunTobyRun(int Direction, int Gear, double Distance, double SpeedPWM)
	{//With Encoder
		bool done = false;
		int ticks = Distance * TICKSPERFEET;
/*
		if(Gear == HIGHSPEED)
		{
			shifter->Set(DoubleSolenoid::kForward);
		}
		else
		{
			shifter->Set(DoubleSolenoid::kReverse);
		}
*/
		if (Direction == FORWARD)
		{
			rightEnc->SetReverseDirection(false);
		}
		else
		{
			rightEnc->SetReverseDirection(true);
		}

		rightEnc->Reset();

		while(!done && IsAutonomous() && IsEnabled())
		{
			printf ("ticks = %d until %d\r\n", rightEnc->Get(), ticks);

			if(rightEnc->Get() < ticks)
			{
				drive108->TankDrive(SpeedPWM * Direction, SpeedPWM * Direction);
			}
			else
			{
				drive108->TankDrive(0.0, 0.0);
				done = true;
			}

			Wait(.005);
		}
	}
	void ArmDown()
	{
		bool finished = false;
		while (!finished && IsAutonomous() && IsEnabled())
		{
			if(!Upperlimit->Get())
			{
				armMotor->Set(0.50);
			}
			else
			{
				armMotor->Set(0.0);
				finished = true;
			}

			drive108->TankDrive(0.0, 0.0);
			Wait(.005);
		}
	}
	void CycleLight(){
		switch(mach){
			case 1:
				//light->Set(Relay::kOff);
				mach = 2;
				break;
			case 2:
				light->Set(Relay::kForward);
				mach = 3;
				break;
			case 3:
				light->Set(Relay::kOff);
				mach = 4;
				break;
			case 4:
				light->Set(Relay::kForward);
				mach = 5;
				break;
			case 5:
				light->Set(Relay::kOff);
				mach = 6;
				break;
			case 6:
				cycle = true;
				break;
		}
	}
};

START_ROBOT_CLASS(QuickVisionRobot)
