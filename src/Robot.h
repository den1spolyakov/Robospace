#ifndef ROBOT_H_
#define ROBOT_H_

#include <PolyScreenShape.h>

class Robot : public Polycode::ScreenShape {
public:
	explicit Robot();

	double forwardSpeed;
	double rotationSpeed;
};

#endif /* ROBOT_H_ */
