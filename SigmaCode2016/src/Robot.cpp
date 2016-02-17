#include "WPILib.h"
#include "SigmaDrive.h"
#include "ShooterIntake.h"
#include "AutonomousModes.h"
#include "Option.h"

class Robot:public SampleRobot
{
	Joystick   *lstick,*rstick,*controller;
	Task *Drive, *Shooter_Intake;
	SendableChooser *chooser;


public:
	SigmaDrive *myRobot;
	ShooterIntake *mySword;
	AutonomousModes *Modes;

	void RobotInit() override {
		chooser = new SendableChooser();
		chooser->AddDefault("Low Bar Low Goal", new Option(1));
		chooser->AddObject("Low Bar High Goal", new Option(2));
		SmartDashboard::PutData("Auto", chooser);

		CameraServer::GetInstance()->SetQuality(30);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");

		lstick = new Joystick(0);
		rstick = new Joystick(1);
		controller = new Joystick(2);

		myRobot = new SigmaDrive();
		myRobot->setExpiration(0.1);

		mySword = new ShooterIntake();

		Robot *bot = this;
		Modes = new AutonomousModes(myRobot, mySword);

		Drive = new Task("Drive", driveWrapper, bot);
		Shooter_Intake= new Task("ShooterIntake", shootWrapper, bot);

		myRobot->ResetDisplacement();
		myRobot->gyro->Calibrate();
	}


	void Autonomous(){
		Option *num = (Option *) chooser->GetSelected();
		myRobot->ResetDisplacement();
		Modes->SetMode(num->Get());
		Modes->Run();
		while(IsAutonomous() && IsEnabled()){
			Wait(0.05);
			Scheduler::GetInstance()->Run();
		}
	}

	void OperatorControl(){
		myRobot->ResetDisplacement();

		Drive->SetPriority(1);
		Drive->join();
		Shooter_Intake->SetPriority(2);
		Shooter_Intake->join();

		while(IsOperatorControl() && IsEnabled()){
			Wait(2);
			printf("Teleop");
		}
	}

//	void Disabled(){}

//	void Test(){}

private:
	void driveTask(){
		while(true){
			if(lstick->GetRawButton(1) & rstick->GetRawButton(1)){
				myRobot->shiftToHigh();
			}else{
				myRobot->shiftToLow();
			}
			myRobot->tankDrive(lstick,rstick); // drive with tank style
			SmartDashboard::PutNumber("Gyro", myRobot->gyro->GetAngle());
			Wait(0.005); // wait for a motor update time
		}
	}

	void shootTask(){
		while(true){
			if(true){
				if(!controller->GetRawButton(1)||controller->GetRawButton(3)){
					if(controller->GetRawButton(5)||controller->GetRawButton(6)){
						if(controller->GetRawButton(5)){
							mySword->Intake(true);
						}
						else if(controller->GetRawButton(6)){
							mySword->Release();
						}
					}
					else{
						mySword->Intake(false);
						mySword->StopIntake();
						mySword->StopIndexer();
					}
				}
				else if(controller->GetRawButton(1)){
					mySword->Shoot();
				}
			}

			if(true){
				if(controller->GetZ() > 0.1){
					mySword->LiftIntake();
				}
				else if(controller->GetZ() < -0.1){
					mySword->LowerIntake();
				}
			}

			if(true){
				if(controller->GetRawButton(3)){
					mySword->Prime(true);
				}else{
					mySword->Prime(false);
				}
			}
		}
		Wait(0.005);
	}


	static void driveWrapper(Robot *bot){
		bot->driveTask();
	}

	static void shootWrapper(Robot *bot){
		bot->shootTask();
	}
};

START_ROBOT_CLASS(Robot)
