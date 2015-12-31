package org.usfirst.frc.team108.auto;

import org.usfirst.frc.team108.Drivetrain.*;

import edu.wpi.first.wpilibj.Timer;
//import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class AutoDrive {
	
	DriveConstants driveData = new DriveConstants();
	SigmaDrive drive108 = new SigmaDrive(false);
	
	//private double currentSpeed;
	private double desiredSpeed,leftSpeed, rightSpeed;
	private double setValue,leftValue,rightValue;
	private double arcRadius,leftRadius,rightRadius;
	private double distanceToTravel,leftDTT,rightDTT;
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
			//Timer.delay(t);
			if(drive108.getDistance() <= d+6 && drive108.getDistance() >= d-6){
				finished = true;
			}
			/*
			else{
				d = d - drive108.getDistance();
				t = d/desiredSpeed;
				this.driveStraight(d, t, stopWhenDone);
			}
			*/
		}
		if(stopWhenDone){
			drive108.tankDrive(0, 0);
		}
	}
	
	public void turnOnSpot(double theta, double t){
		finished = false;
		arcRadius = driveData.DriveWidth;
		desiredSpeed = (arcRadius*theta)/t;
		distanceToTravel = desiredSpeed*t;
		if(drive108.highGear){
			setValue = desiredSpeed/driveData.HighGearMaxSpeed;
		}else{
			setValue = desiredSpeed/driveData.LowGearMaxSpeed;
		}
		while(!finished){
			drive108.resetEncoders();
			drive108.tankDrive(setValue, -setValue);
			Timer.delay(0.5);
			if(drive108.getDistance() <= distanceToTravel+1 && drive108.getDistance() >= distanceToTravel-1){
				finished = true;
			}
			/*
			else{
				distanceToTravel = distanceToTravel - drive108.getDistance();
				t = distanceToTravel/desiredSpeed;
				this.turnOnSpot(theta, t);
			}
			*/
		}
	}
	
	public void followArc(double r, double theta, double t, boolean leftTurn, boolean stopWhenDone){
		finished = false;
		arcRadius = r;
		if(leftTurn){
			leftRadius = r - (driveData.DriveWidth/2);
			rightRadius = r + (driveData.DriveWidth/2);
		}else{
			leftRadius = r + (driveData.DriveWidth/2);
			rightRadius = r - (driveData.DriveWidth/2);
		}
		
		leftDTT = leftRadius*theta;
		rightDTT = rightRadius*theta;
		
		leftSpeed = leftDTT/t;
		rightSpeed = rightDTT/t;
		
		desiredSpeed = (leftSpeed+rightSpeed)/2;
		
		if(drive108.highGear){
			leftValue = leftSpeed/driveData.HighGearMaxSpeed;
			rightValue = rightSpeed/driveData.HighGearMaxSpeed;
		}else{
			leftValue = leftSpeed/driveData.LowGearMaxSpeed;
			rightValue = rightSpeed/driveData.LowGearMaxSpeed;
		}
		
		while(!finished){
			drive108.resetEncoders();
			drive108.tankDrive(leftValue, rightValue);
			Timer.delay(0.5);
			if(drive108.getLeftDistance() <= leftDTT+1 && drive108.getLeftDistance() >= leftDTT-1){
				if(drive108.getRightDistance() <= rightDTT+1 && drive108.getRightDistance() >= rightDTT-1){
					finished = true;
				}
			}
		}
		if(stopWhenDone){
			drive108.tankDrive(0, 0);
		}
	}

}
