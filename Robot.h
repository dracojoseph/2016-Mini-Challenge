#include "WPILib.h"

#include "Constants.h"
#include "Shooter.h"

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

class Robot : public SampleRobot {

private:
	RobotDrive robotDrive;
	Joystick driveStick;
	Shooter shooter;
	AnalogInput ultrasonicFront, unltrasonicBack;
	Compressor compressor;
public:
	Robot();
	void OperatorControl();
	void Autonomous();
};

#endif /* SRC_ROBOT_H_ */
