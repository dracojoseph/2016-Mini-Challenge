#include "Robot.h"

Robot::Robot() :
	position(),
	robotDrive(Constants::driveLeftPin, Constants::driveRightPin, position),
	driveStick(Constants::driveStickChannel),
	frontUltrasonic(Constants::frontUltrasonicPin),
	backUltrasonic(Constants::backUltrasonicPin),
	arm(),
	track(),
	compressor(Constants::compressorPin) //canbus number
{
	robotDrive.SetExpiration(0.1); //safety feature
}

void Robot::OperatorControl() //teleop code
{
	robotDrive.Enable();
	compressor.Start();

	track.openBottom();

	while(IsOperatorControl() && IsEnabled())
	{
		float leftValue = throttle * driveStick.GetRawAxis(Constants::PS4LeftJoystick);
		float rightValue = throttle * driveStick.GetRawAxis(Constants::PS4RightJoystick);
		robotDrive.TankDrive(leftValue, rightValue, true);
	}

	compressor.Stop();
	robotDrive.Disable();
}



void Robot::Autonomous() {
	//use navx mxp
	robotDrive.Enable();
	compressor.Start();

	track.closeBottom();
	track.closeTop();

	int fs = 0;
	while (frontUltrasonic.getVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,0);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);
	
	arm.gripOpen();
	
	arm.lower();

	arm.gripClose();

	arm.raise();
	
	arm.lower();
	
	arm.gripOpen();

	fs = 0;
	while (frontUltrasonic.getVoltage() * Constants::ultrasonicVoltageToInches > Constants::minDistanceToCheeseballs && fs < 500)
	{

		robotDrive.TankDriveStraight(.5,180);
		fs++;
		Wait(.01);

	}
	robotDrive.TankDriveSpeed(0,0);

	track.openTop();

	compressor.Stop();
	robotDrive.Disable();
}

START_ROBOT_CLASS(Robot);
