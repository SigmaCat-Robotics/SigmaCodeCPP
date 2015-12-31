package org.usfirst.frc.team108.auto;

import org.usfirst.frc.team108.Drivetrain.*;

import edu.wpi.first.wpilibj.Timer;
//import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class AutoDrive {
	
	DriveConstants driveData = new DriveConstants();
	SigmaDrive drive108 = new SigmaDrive(false);
	
	//private double currentSpeed;
	private double desiredSpeed;
	private double setValue;
	private boolean finished = false;
	
	public AutoDrive() {
		// TODO Auto-generated constructor stub
	}
	
	public void driveStraight(double d, double t, boolean stopWhenDone){
		//currentSpeed = drive108.getSpeed();
		desiredSpeed = d/t;
		//double accelVal = (desiredSpeed - currentSpeed)/t;
		//SmartDashboard.putNumber("acceleration Cap: ", accelVal);
		if(drive108.highGear){
			setValue = desiredSpeed/driveData.HighGearMaxSpeed;
		}else{
			setValue = desiredSpeed/driveData.LowGearMaxSpeed;
		}
		while(!finished){
			drive108.resetEncoders();
			drive108.tankDrive(setValue, setValue);
			Timer.delay(t);
			if(drive108.getDistance() <= d+6 && drive108.getDistance() >= d-6){
				finished = true;
			}else{
				d = d - drive108.getDistance();
				t = d/desiredSpeed;
				this.driveStraight(d, t, stopWhenDone);
			}
		}
		if(stopWhenDone){
			drive108.tankDrive(0, 0);
		}
	}
	
	public void turnOnSpot(double theta, double t){
		
	}
	
	public void followArc(double r, double theta, double t){
		
	}

}
