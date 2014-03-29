#include "Robospace.h"

#include <Polycode.h>
#include <PolycodeView.h>
#include <PolyEvent.h>
#include <PolyScreenShape.h>
#include <PolyVector2.h>

#include <PolyPhysicsScreen.h>
#include <PolyPhysicsScreenEntity.h>

#include <cmath>

#include "Robot.h"

Robospace::Robospace() {
	view = new Polycode::PolycodeView("Robospace");

	core = new Polycode::POLYCODE_CORE(view, 640, 480, false, false, 0, 0, 90);

	Polycode::CoreServices::getInstance()->getResourceManager()->addArchive("res/default.pak");
	Polycode::CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	screen = new Polycode::PhysicsScreen();
	Polycode::ScreenLabel *label = new Polycode::ScreenLabel("Hello, Robospace!", 32);
	screen->addChild(label);

	robot = new Robot();
	robots.push_back(robot);
	robot->setPosition(120, 240);
	screen->addCollisionChild(robot, Polycode::PhysicsScreenEntity::ENTITY_RECT);

	robot = new Robot();
	robots.push_back(robot);
	robot->setPosition(480, 240);
	screen->addCollisionChild(robot, Polycode::PhysicsScreenEntity::ENTITY_RECT);

	core->getInput()->addEventListener(this, Polycode::InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, Polycode::InputEvent::EVENT_KEYUP);

	core->getInput()->addEventListener(this, Polycode::InputEvent::EVENT_MOUSEDOWN);
}

void Robospace::handleEvent(Polycode::Event *e) {
	using Polycode::InputEvent;

	if (e->getDispatcher() == core->getInput()) {
		InputEvent *event = static_cast<InputEvent *>(e);

		switch (e->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN: {
					Polycode::Vector2 mouse = core->getInput()->getMousePosition();
					Polycode::ScreenEntity *entity = screen->getEntityAtPosition(mouse.x, mouse.y);
					Robot *r0 = dynamic_cast<Robot *>(entity);
					if (r0) {
					    robot = r0;
					}
				}
				break;
			case InputEvent::EVENT_KEYDOWN:
				switch (event->keyCode()) {
					case Polycode::KEY_w:
						screenSpeedY = 100;
						break;
					case Polycode::KEY_s:
						screenSpeedY = -100;
						break;
					case Polycode::KEY_a:
						screenSpeedX = 100;
						break;
					case Polycode::KEY_d:
						screenSpeedX = -100;
						break;

					case Polycode::KEY_UP:
						robot->forwardSpeed = 100;
						break;

					case Polycode::KEY_DOWN:
						robot->forwardSpeed = -100;
						break;

					case Polycode::KEY_LEFT:
						robot->rotationSpeed = -100;
						break;

					case Polycode::KEY_RIGHT:
						robot->rotationSpeed = 100;
						break;
				}
				break;
			case InputEvent::EVENT_KEYUP:
				switch (event->keyCode()) {
					case Polycode::KEY_w:
					case Polycode::KEY_s:
						screenSpeedY = 0;
						break;

					case Polycode::KEY_a:
					case Polycode::KEY_d:
						screenSpeedX = 0;
						break;

					case Polycode::KEY_LEFT:
					case Polycode::KEY_RIGHT:
						robot->rotationSpeed = 0;
						break;

					case Polycode::KEY_UP:
					case Polycode::KEY_DOWN:
						robot->forwardSpeed = 0;
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
		pos.x += elapsed * robot->forwardSpeed * std::cos(robot->getRotation() / 180 * M_PI);
		pos.y += elapsed * robot->forwardSpeed * std::sin(robot->getRotation() / 180 * M_PI);

		robot->setPosition(pos);
		if (robot->forwardSpeed) {
			robot->setRotation(robot->getRotation() +
					elapsed * robot->rotationSpeed * (robot->forwardSpeed > 0 ? 1 : -1));
		}

		Polycode::Vector2 offset = screen->getScreenOffset();
		screen->setScreenOffset(offset.x + screenSpeedX*elapsed,
				offset.y + screenSpeedY*elapsed);
	} while (core->updateAndRender());
}
