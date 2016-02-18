#include "WPILib.h"
#include "SigmaDrive.h"
#include "ShooterIntake.h"
#include "AutonomousModes.h"
#include "Option.h"
/**
 * Uses the CameraServer class to automatically capture video from a USB webcam
 * and send it to the FRC dashboard without doing any vision processing. This
 * is the easiest way to get camera images to the dashboard. Just add this to the
 * RobotInit() method in your program.
 */
class Robot : public SampleRobot
{
	Joystick   *lstick,*rstick,*controller;
	Task *drive, *shoot;
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

		CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");

		lstick = new Joystick(0);
		rstick = new Joystick(1);
		controller = new Joystick(2);

		myRobot = new SigmaDrive();
		myRobot->setExpiration(0.1);
		mySword = new ShooterIntake();
		Robot* bot = this;

		Modes = new AutonomousModes(myRobot, mySword);

		drive = new Task("drive",driveWrapper, bot);
		shoot = new Task("shoot",shootWrapper, bot);

		myRobot->ResetDisplacement();
		myRobot->resetEncoders();
		mySword->ResetEncoder();

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

	void OperatorControl()
	{
		myRobot->ResetDisplacement();
		drive->join();
		shoot->join();

		while (IsOperatorControl() && IsEnabled())
		{
			/** robot code here! **/
			myRobot->UpdateDiplacement(0.005);
			SmartDashboard::PutNumber("Displacement: ", myRobot->GetDisplacement());
			Wait(0.005);				// wait for a motor update time
		}
	}

private:
	static void driveWrapper(Robot* bot){
		bot->driveTask();
	}

	static void shootWrapper(Robot* bot){
		bot->shootTask();
	}

	void driveTask(){
			myRobot->resetEncoders();
			while(true){
				if(lstick->GetRawButton(1) & rstick->GetRawButton(1)){
					myRobot->shiftToHigh();
				}else{
					myRobot->shiftToLow();
				}
				myRobot->tankDrive(lstick,rstick); // drive with tank style
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
			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot)




