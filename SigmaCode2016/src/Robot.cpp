#include "WPILib.h"

Robot::Robot(void)
{
  frontLeft  = new VictorSP(1);
  frontRight = new VictorSP(2);
  rearLeft   = new VictorSP(3);
  rearRight  = new VictorSP(4);
  
  driveSystem = new RobotDrive(frontLeft, frontRight, rearLeft, rearRight);
  
  // What's this for?
  //driveSystem->SetExpiration(0.1);
  
  leftStick =  new Joystick(1);
  rightStick = new Joystick(2);
}

Robot::~Robot(void)
{
  delete frontLeft;
  delete frontRight;
  delete readLeft;
  delete readRight;
  delete driveSystem;
  delete leftStick;
  delete rightStick;
}

void Robot::RobotMain(void)
{
  while(1)
  {
    driveSystem->TankDrive(leftStick, rightStick);
    Wait(0.01);
    // This doesn't match the example code:
    //myRobot->TankDrive(lstick->GetY(),rstick->GetY()); // drive with tank style
    //Wait(0.005); // wait for a motor update time
  }
}

void Robot::Autonomous(void)
{
  printf("auto");
}

void Robot::OperatorControl(void)
{
  printf("op control");
}

	
