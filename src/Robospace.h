#ifndef ROBOSPACE_H_
#define ROBOSPACE_H_

#include <vector>

#include <PolyEventHandler.h>

namespace Polycode {
	class Core;
	class Event;
	class PolycodeView;
	class PhysicsScreen;
	class ScreenShape;
}

class Robot;

/**
 * The main game class.
 */
class Robospace : public Polycode::EventHandler {
public:
	explicit Robospace();

	void run();

	void handleEvent(Polycode::Event *e);

private:
	Polycode::Core *core;
	Polycode::PolycodeView *view;

	Polycode::PhysicsScreen *screen;
	std::vector<Robot *> robots;

	Robot *robot;

	double rotationSpeed;
	double forwardSpeed;

	double screenSpeedX;
	double screenSpeedY;

};

#endif /* ROBOSPACE_H_ */
