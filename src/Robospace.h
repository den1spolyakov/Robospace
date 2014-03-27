#ifndef ROBOSPACE_H_
#define ROBOSPACE_H_

#include <PolyEventHandler.h>

namespace Polycode {
	class Core;
	class Event;
	class PolycodeView;
	class Screen;
	class ScreenShape;
}

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

	Polycode::Screen *screen;
	Polycode::ScreenShape *robot;

	double rotationSpeed;
	double forwardSpeed;

	double screenSpeedX;
	double screenSpeedY;

};

#endif /* ROBOSPACE_H_ */
