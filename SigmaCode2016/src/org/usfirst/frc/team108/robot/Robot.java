
package org.usfirst.frc.team108.robot;


import edu.wpi.first.wpilibj.SampleRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import org.usfirst.frc.team108.Drivetrain.SigmaDrive;


public class Robot extends SampleRobot {
    SigmaDrive myRobot;
    Joystick leftStick, rightStick;

    public Robot() {
        myRobot = new SigmaDrive(SmartDashboard.getBoolean("Is Front High: ", false));
        myRobot.setExpiration(0.1);
        leftStick = new Joystick(0);
        rightStick = new Joystick(1);
    }

    
    public void autonomous() {

    }

    
    public void operatorControl() {

        while (isOperatorControl() && isEnabled()) {
            myRobot.tankDrive(leftStick, rightStick);
            if(leftStick.getRawButton(0) && rightStick.getRawButton(0)){
            	myRobot.shiftToLow();
            }else{
            	myRobot.shiftToHigh();
            }
            Timer.delay(0.005);
        }
    }


    public void test() {
    }
}
