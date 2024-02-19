#pragma once

#include <event/Event.h>

class MouseEvent : public Event {
public:
	int btn;
	int action;
	int mods;

	MouseEvent(int btn, int action, int mods) : btn(btn), action(action), mods(mods) {}
};