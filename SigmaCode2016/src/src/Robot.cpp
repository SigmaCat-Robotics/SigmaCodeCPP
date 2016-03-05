#include "WPILib.h"
#include "Option.h"
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
	Task *Operating;
	Encoder *leftEnc, *rightEnc, *shooterEnc;
	ADXRS450_Gyro *gyro;
	SendableChooser *chooser;
	Option *num;
	Image *frame;
	IMAQdxSession session;
	Relay *light;

public:
	void RobotInit() override {
		light = new Relay(0);
		gyro = new ADXRS450_Gyro();
		gyro->Calibrate();
		chooser = new SendableChooser();
		chooser->AddDefault("Low Bar", new Option(1));
		chooser->AddObject("Rock Wall", new Option(2));
		chooser->AddObject("Moat", new Option(3));
		chooser->AddObject("Rough Terrain", new Option(4));
		SmartDashboard::PutData("Auto", chooser);
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

//		QuickVisionRobot *bot = this;
//		Operating = new Task("Operating", (FUNCPTR)Wrapper, bot);
/*
		frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
		IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
		Wait(.5);
		IMAQdxConfigureGrab(session);
		Wait(.5);
		IMAQdxStartAcquisition(session);
		Wait(.5);
*/
	}

	void Autonomous(){

		num = (Option *) chooser->GetSelected();
		int state = 1;
		printf("start!\r\n");
		SmartDashboard::PutNumber("Auto Picked", num->Get());

		while(IsAutonomous() && IsEnabled())
		{

			switch(state)
			{
			case 1:
				printf("state 1!\r\n");
				//This is moving the arm down at the start of the match
				if(!Upperlimit->Get())
				{
				armMotor->Set(0.50);
				}
				else
				{
				armMotor->Set(0.0);
				state = 2;
			    }
				//This is intaking the ball
				intake->Set(0.7);//running at 70%
				break;
			case 2:
				printf("state 2!\r\n");
			    rightEnc->Reset();
				leftEnc->Reset();
				shifter->Set(DoubleSolenoid::kForward);
				drive108->TankDrive(0.7,0.7);
				state = 3;
				break;
			case 3:
		 		printf("state 3!\r\n");
				drive108->TankDrive(0.7,0.7);
				if (rightEnc->Get() >= 7833)
				{
					state = 4;
				}
				break;
			case 4:
				printf("state 4!\r\n");
				drive108->TankDrive(0.0,0.0);
				state = 5;
				break;
			case 5:
				printf("state 5!\r\n");
				gyro->Reset();
				drive108->TankDrive(0.7, -0.7);
				state = 6;
				break;
			case 6:
				printf("state 6!\r\n");
				drive108->TankDrive(0.7, -0.7);
				if (gyro->GetAngle() > 135)
				{
					state = 7;
				}
				break;
			case 7:
				printf("state 7!\r\n");
				//After we get the angle we will shoot the ball


				break;

			Wait(.005);
		    }
		}
	}

	void OperatorControl()
	{
		int counter = 1;
		int choice = 1;

	//	bool pulse = true;
	//	char buff[50];
	//	Operatineg->join();
		while (IsOperatorControl() && IsEnabled())
		{
			/** robot code here! **/
			light->Set(Relay::kForward);
			if(right->GetRawButton(1)){
				shifter->Set(DoubleSolenoid::kForward); // High Gear = reverse
			}else if(left->GetRawButton(1)){
				shifter->Set(DoubleSolenoid::kReverse); // Low Gear = forward
			}
			drive108->TankDrive(left->GetY(),right->GetY());
//			SmartDashboard::PutNumber("DB/Slider 0", left->GetY());
//			SmartDashboard::PutNumber("DB/Slider 1", right->GetY());

//			std::sprintf(buff, "%f %f %f\r\n", leftEnc->Get()/20.3, rightEnc->Get()/35.0, shooterEnc->Get());
//			std::sprintf(buff, "%d %d %d\r\n", leftEnc->Get(), rightEnc->Get(), shooterEnc->Get());
			SmartDashboard::PutBoolean("Ball In:", ballDetect->GetRangeInches()<3);
//			std::printf(buff);
			Wait(0.005);				// wait for a motor update time

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
								//pulse = true;
							}
							std::printf("CHOICE 1\r\n");
							break;
					case 2:	if(counter%64 == 0){
								leftIndexer->Set(0.0);
								rightIndexer->Set(0.0);
								choice = 3;
							}
/*
						if(pulse){
								leftIndexer->Set(-0.25);
								rightIndexer->Set(0.25);
								if(counter%50 == 0){
									pulse = false;
								}
							}else{
								leftIndexer->Set(0.0);
								rightIndexer->Set(0.0);
								if(counter%20 == 0){
									pulse = true;
									choice = 3;
								}
							}
*/
							counter++;
							//if(ballDetect->Get)
							std::printf("CHOICE 2\r\n");
							break;
					case 3: intake->Set(0.0);
							//choice = 1;
							std::printf("CHOICE 3\r\n");
							break;
				}
/*
				shooter->Set(0);
				intake->Set(-0.7);
				if(pulse){
					leftIndexer->Set(-0.25);
					rightIndexer->Set(0.25);
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
*/
			}
			else if(controller->GetRawButton(5)){//release
				shooter->Set(0);
				intake->Set(0.7);
				leftIndexer->Set(1.0);
				rightIndexer->Set(-1.0);
				choice = 1;
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

	/*
private:
	void ShootIntake(){
		SmartDashboard::PutString("Hi", "I'm Bob");
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
	*/
};

START_ROBOT_CLASS(QuickVisionRobot)

