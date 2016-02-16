#include "WPILib.h"
#include "SigmaDrive.h"
#include "ShooterIntake.h"
/**
 * Uses the CameraServer class to automatically capture video from a USB webcam
 * and send it to the FRC dashboard without doing any vision processing. This
 * is the easiest way to get camera images to the dashboard. Just add this to the
 * RobotInit() method in your program.
 */
class Robot : public SampleRobot
{
	ADXL362 *accel;
	ADXRS450_Gyro *gyro;
    SigmaDrive *myRobot;
    Joystick   *lstick,*rstick, *controller;
    ShooterIntake *mySword;
    Task *drive, *shoot;
public:
	void RobotInit() override {
		CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		accel = new ADXL362(ADXL362::kRange_4G);
		gyro = new ADXRS450_Gyro();
		gyro->Calibrate();
		lstick = new Joystick(0);
		rstick = new Joystick(1);
		controller = new Joystick(2);

		myRobot = new SigmaDrive();
		myRobot->setExpiration(0.1);
		mySword = new ShooterIntake();
		Robot* bot = this;
		drive = new Task("drive",driveWrapper, bot);
		shoot = new Task("shoot",shootWrapper, bot);

		myRobot->ResetDisplacement();
		myRobot->resetEncoders();
		mySword->ResetEncoder();

	}

	void OperatorControl()
	{
		myRobot->ResetDisplacement();
		drive->join();
		shoot->join();

		while (IsOperatorControl() && IsEnabled())
		{
			/** robot code here! **/
			SmartDashboard::PutNumber("Gyro Angle: ", gyro->GetAngle());
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
				if(controller->GetRawButton(5)){
					mySword->Intake();
				}
				else if(controller->GetRawButton(6)){
					mySword->Release();
				}
				else if(controller->GetRawButton(1)){
					mySword->Shoot();
				}
				else{
					mySword->StopIndexer();
					mySword->StopIntake();
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
					mySword->Prime();
				}
			}
			Wait(0.005);
		}
	}

};

START_ROBOT_CLASS(Robot)




