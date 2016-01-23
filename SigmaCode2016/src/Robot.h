#include "WPILib.h"

class Robot:public SampleRobot
{
  public:
    Robot();
    virtual ~Robot();
    void RobotMain(void);
    void RobotInit(void);

  private:
    RobotDrive *driveSystem; 			// robot drive system
    Joystick   *lstick,*rstick; 			// Left and Right Joysticks
    VictorSP   *left1, *left2, *right1, *right2;
}
