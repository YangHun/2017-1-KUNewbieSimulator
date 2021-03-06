#pragma once
#define STO_EVENTCOUNT 3
#define SEQ_EVENTCOUNT 13
#define SPE_EVENTCOUNT 3
#include "engine.h"

#ifndef __SWITCHS_H__
#define __SWITCHS_H__

#include <string.h>
#include <stdbool.h>
#include "lectureInfo.h"

/** Begin a switch for the string x */
#define switchs(x) \
    { char *__sw = (x); bool __done = false; bool __cont = false; do {

/** Check if the string matches the cases argument (case sensitive) */
#define cases(x)    } if ( __cont || !strcmp ( __sw, x ) ) \
                        { __done = true; __cont = true;

/** Default behaviour */
#define defaults    } if ( !__done || __cont ) {

/** Close the switchs */
#define switchs_end } while ( 0 ); }

#endif // __SWITCHS_H__

struct event_function {
	void(*func)();
	bool isStarted;
	float prob;
};

typedef struct event_function event_function;

