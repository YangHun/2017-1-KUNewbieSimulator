#pragma once
#define STO_EVENTCOUNT 3
#define SEQ_EVENTCOUNT 3
#include "engine.h"
struct event_function {
	void(*func)();
	bool isStarted;
};

typedef struct event_function event_function;

