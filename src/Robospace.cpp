#include "Robospace.h"

#include <Polycode.h>
#include <PolycodeView.h>

Robospace::Robospace() {
	view = new Polycode::PolycodeView("Robospace");

	core = new Polycode::POLYCODE_CORE(view, 640, 480, false, false, 0, 0, 90);

	Polycode::CoreServices::getInstance()->getResourceManager()->addArchive("res/default.pak");
	Polycode::CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	Polycode::Screen *screen = new Polycode::Screen();
	Polycode::ScreenLabel *label = new Polycode::ScreenLabel("Hello, Robospace!", 32);
	screen->addChild(label);
}

void Robospace::run() {
	while (core->updateAndRender());
}
