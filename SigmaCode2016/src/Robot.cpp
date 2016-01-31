#include "WPILib.h"
#include "SigmaDrive.h"
#include "ShooterIntake.h"
#include "Robot.h"

void Robot::driveTask(){
		myRobot->resetEncoders();
		while(IsAutonomous() && IsEnabled()){
			//Auto code here
		}
		while(IsOperatorControl() && IsEnabled()){
			myRobot->tankDrive(lstick->GetY(),rstick->GetY()); // drive with tank style
			Wait(0.005); // wait for a motor update time
		}
	}

void Robot::shootTask(){
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


Robot::Robot(){
		lstick = new Joystick(0);
		rstick = new Joystick(1);

		myRobot = new SigmaDrive();
		myRobot->setExpiration(0.1);
		mySword = new ShooterIntake();
		Robot* bot = this;
		std::thread drive(driveWrapper, bot);
		std::thread shoot(shootWrapper, bot);
		drive.join();
		shoot.join();
}

Robot::~Robot(){
	delete myRobot;
	delete mySword;
	delete lstick;
	delete rstick;
}

void Robot::RobotInit(void){
	myRobot->ResetDisplacement();
	myRobot->resetEncoders();
	mySword->ResetEncoder();
}

void Robot::Autonomous(void){

}

void Robot::OperatorControl(){

}

void Robot::Disabled(void){

}

void Robot::Test(void){

}
START_ROBOT_CLASS(Robot)
