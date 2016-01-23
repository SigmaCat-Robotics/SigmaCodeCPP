#include "WPILib.h"

class Robot:public SampleRobot
{
  public:
    Robot();
    virtual ~Robot();
    void RobotMain(void);
    void RobotInit(void);

  private:
    RobotDrive *driveSystem;
    Joystick   *leftStick,*rightStick; 
    VictorSP   *frontLeft, *frontRight, *rearLeft, *rearRight;
}
