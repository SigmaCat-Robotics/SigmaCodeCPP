package org.usfirst.frc.team108.util;

import edu.wpi.first.wpilibj.Encoder;
import org.usfirst.frc.team108.Drivetrain.*;

public class SigmaEncoder extends Encoder {
	
	boolean isDriveEncoder = false;
	DriveConstants driveData = new DriveConstants();

	public SigmaEncoder(int aChannel, int bChannel) {
		this(aChannel, bChannel, false, false);
		// TODO Auto-generated constructor stub
	}

	public SigmaEncoder(int aChannel, int bChannel, boolean reverseDirection, boolean isDrive) {
		super(aChannel, bChannel, reverseDirection);
		this.isDriveEncoder = isDrive;
		if(isDriveEncoder){
			this.setDistancePerPulse(driveData.CyclesPerPulse);
		}
	}

	public SigmaEncoder(int aChannel, int bChannel, int indexChannel) {
		this(aChannel, bChannel, indexChannel, false);
		// TODO Auto-generated constructor stub
	}

	public SigmaEncoder(int aChannel, int bChannel, int indexChannel, boolean reverseDirection) {
		super(aChannel, bChannel, indexChannel, reverseDirection);
		// TODO Auto-generated constructor stub
	}
	
	public void reset(){
		super.reset();
	}


}
