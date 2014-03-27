#include "Robospace.h"

#include <Polycode.h>
#include <PolycodeView.h>
#include <PolyEvent.h>
#include <PolyScreenShape.h>
#include <PolyVector2.h>

#include <cmath>

Robospace::Robospace() {
	view = new Polycode::PolycodeView("Robospace");

	core = new Polycode::POLYCODE_CORE(view, 640, 480, false, false, 0, 0, 90);

	Polycode::CoreServices::getInstance()->getResourceManager()->addArchive("res/default.pak");
	Polycode::CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Polycode::Screen *screen = new Polycode::Screen();
	Polycode::ScreenLabel *label = new Polycode::ScreenLabel("Hello, Robospace!", 32);
	screen->addChild(label);

	robot = new Polycode::ScreenShape(Polycode::ScreenShape::SHAPE_RECT, 64, 64);
	robot->setPositionMode(Polycode::ScreenEntity::POSITION_CENTER);
	robot->setPosition(320, 240);
	screen->addChild(robot);
	rotationSpeed = 0;
	forwardSpeed = 0;

	core->getInput()->addEventListener(this, Polycode::InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, Polycode::InputEvent::EVENT_KEYUP);
}

void Robospace::handleEvent(Polycode::Event *e) {
	using Polycode::InputEvent;

	if (e->getDispatcher() == core->getInput()) {
		InputEvent *event = static_cast<InputEvent *>(e);

		switch (e->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
				switch (event->keyCode()) {
					case Polycode::KEY_UP:
						forwardSpeed = 100;
						break;

					case Polycode::KEY_DOWN:
						forwardSpeed = -100;
						break;

					case Polycode::KEY_LEFT:
						rotationSpeed = -100;
						break;

					case Polycode::KEY_RIGHT:
						rotationSpeed = 100;
						break;
				}
				break;
			case InputEvent::EVENT_KEYUP:
				switch (event->keyCode()) {
					case Polycode::KEY_LEFT:
					case Polycode::KEY_RIGHT:
						rotationSpeed = 0;
						break;

					case Polycode::KEY_UP:
					case Polycode::KEY_DOWN:
						forwardSpeed = 0;
						break;
				}
				break;
		}
	}
}

void Robospace::run() {
	do {
		Number elapsed = core->getElapsed();

		Polycode::Vector2 pos = robot->getPosition2D();
		pos.x += elapsed * forwardSpeed * std::cos(robot->getRotation() / 180 * M_PI);
		pos.y += elapsed * forwardSpeed * std::sin(robot->getRotation() / 180 * M_PI);

		robot->setPosition(pos);
		if (forwardSpeed) {
			robot->setRotation(robot->getRotation() +
					elapsed * rotationSpeed * (forwardSpeed > 0 ? 1 : -1));
		}
	} while (core->updateAndRender());
}
