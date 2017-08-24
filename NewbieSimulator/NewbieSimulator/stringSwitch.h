#pragma once
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

typedef enum _XMLelementMessage {
	XML_MESSAGE_DEFAULT,
	CODE,
	CLASS,
	TYPE,
	NAME,
	CREDIT,
	TIME,
	ROOM,
	DISTANCE,
	KLUE,
	ATTENDANCE,
	EVAL,
	TUITION
} XMLelementMessage;

int getClassifyMessage(char* name);
int getKlueMessage(char* name);
int getAttMessage(char* name);
int getRoomMessage(char* name);
int getRoomMessage_little_change(char* name);
int getElementMessage(char* name);
int whatDayFunc(char hangul[]);
int getEvalMessage(char hangul[]);
int getTuitionMessage(char hangul[]);