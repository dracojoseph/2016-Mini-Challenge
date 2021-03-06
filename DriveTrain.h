#include "WPILib.h"
#include "Position.h"
#include <math.h>
#include <fstream>
#include "HAL/CanTalonSRX.h"

#ifndef SRC_DRIVETRAIN_H
#define SRC_DRIVETRAIN_H

#define PI 3.14159265

class DriveTrain : public RobotDrive
{
	CANTalon leftMaster;
	CanTalonSRX leftSlave;
	CANTalon rightMaster;
	CanTalonSRX rightSlave;

	Position *position;
public:
	DriveTrain(uint32_t leftMasterDeviceID, uint32_t leftSlaveDeviceID, uint32_t rightMasterDeviceID, uint32_t rightSlaveDeviceID, Position *position_);
	void Enable();
	void Disable();
	void TurnToAngle(float angle);
	void TurnToRelativeAngle(float angle);
	void TankDriveStraight(float speed, float fieldAngle);
	void TankDriveSpeed(float leftspeed, float rightspeed);
	void AutoTurnToAngle(float angle);
	float CalculateAutoTurnError(float angle);
};

#endif
