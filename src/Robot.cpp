#include "Robot.h"

Robot::Robot()
	: Polycode::ScreenShape(Polycode::ScreenShape::SHAPE_RECT, 64, 64)
	, forwardSpeed(0)
	, rotationSpeed(0)
{
	setPositionMode(Polycode::ScreenEntity::POSITION_CENTER);
}
