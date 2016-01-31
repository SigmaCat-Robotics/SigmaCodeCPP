class Robot:public SampleRobot
{
  public:
    Robot();
    virtual ~Robot();
    void RobotInit(void);
    void Disabled(void);
    void Autonomous(void);
    void Test(void);
    void OperatorControl();
    void driveTask();
    void shootTask();

  private:

    //static void driveWrapper(Robot* bot);
    //static void shootWrapper(Robot* bot);
    SigmaDrive *myRobot;
    Joystick   *lstick,*rstick;
    ShooterIntake *mySword;
    //VictorSP   *frontLeft, *frontRight, *rearLeft, *rearRight;

};
