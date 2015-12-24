package org.usfirst.frc.team108.Drivetrain;

import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.VictorSP;
import org.usfirst.frc.team108.util.*;

public class SigmaDrive {

	DriveConstants driveData = new DriveConstants();
	
	RobotDrive drive108;
	VictorSP Left1 = new VictorSP(driveData.LeftMotor1);
	VictorSP Left2 = new VictorSP(driveData.LeftMotor2);
	
	VictorSP Right1 = new VictorSP(driveData.RightMotor1);
	VictorSP Right2 = new VictorSP(driveData.RightMotor2);
	
	SigmaEncoder leftEncoder = new SigmaEncoder(driveData.LeftEncoderAChannel, driveData.LeftEncoderBChannel,
												false, true);
	SigmaEncoder rightEncoder = new SigmaEncoder(driveData.RightEncoderAChannel, driveData.RightEncoderBChannel,
												true,true);
	
	boolean highFront;
	
	double driveSpeed;
	
	public SigmaDrive(boolean HighFront) {
		drive108 = new RobotDrive(Left1, Left2, Right1, Right2);
		highFront = HighFront;		
	}
	
	public double getSpeed(){
		driveSpeed = ((leftEncoder.getRate()+rightEncoder.getRate())/2)/12;
		return this.driveSpeed;
	}

}
