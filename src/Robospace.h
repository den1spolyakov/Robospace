#ifndef ROBOSPACE_H_
#define ROBOSPACE_H_

namespace Polycode {
	class Core;
	class PolycodeView;
}

/**
 * The main game class.
 */
class Robospace {
public:
	explicit Robospace();

	void run();

private:
	Polycode::Core *core;
	Polycode::PolycodeView *view;

};

#endif /* ROBOSPACE_H_ */
