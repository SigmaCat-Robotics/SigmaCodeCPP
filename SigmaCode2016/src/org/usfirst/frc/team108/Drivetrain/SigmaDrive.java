package org.usfirst.frc.team108.Drivetrain;

import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.DoubleSolenoid.Value;
import org.usfirst.frc.team108.util.SigmaEncoder;
import org.usfirst.frc.team108.util.SigmaVictorSP;

public class SigmaDrive {

	DriveConstants driveData = new DriveConstants();
	
	RobotDrive drive108;
	
	DoubleSolenoid leftShifter = new DoubleSolenoid(driveData.LeftHighGear, driveData.LeftLowGear);
	DoubleSolenoid rightShifter = new DoubleSolenoid(driveData.RightHighGear, driveData.RightLowGear);
	
	SigmaEncoder leftEncoder = new SigmaEncoder(driveData.LeftEncoderAChannel, driveData.LeftEncoderBChannel,false, true);
	SigmaEncoder rightEncoder = new SigmaEncoder(driveData.RightEncoderAChannel, driveData.RightEncoderBChannel,true,true);
	
	SigmaVictorSP Left1 = new SigmaVictorSP(driveData.LeftMotor1,true);
	SigmaVictorSP Left2 = new SigmaVictorSP(driveData.LeftMotor2,true);
	
	SigmaVictorSP Right1 = new SigmaVictorSP(driveData.RightMotor1,true);
	SigmaVictorSP Right2 = new SigmaVictorSP(driveData.RightMotor2,true);
	
	boolean highFront;
	boolean highGear;
	double driveSpeed;
	
	public SigmaDrive(boolean HighFront) {
		drive108 = new RobotDrive(Left1, Left2, Right1, Right2);
		highFront = HighFront;		
	}
	
	public double getSpeed(){
		driveSpeed = ((leftEncoder.getRate()+rightEncoder.getRate())/2)/12;
		return this.driveSpeed;
	}
	
	public void shiftToLow(){
		if(highGear){
			leftShifter.set(Value.kReverse);
			rightShifter.set(Value.kReverse);
			highGear = false;
		}else{
			highGear = false;
		}
	}
	
	public void shiftToHigh(){
		if(highGear){
			leftShifter.set(Value.kForward);
			rightShifter.set(Value.kForward);
			highGear = true;
		}else{
			highGear = true;
		}
	}

}
