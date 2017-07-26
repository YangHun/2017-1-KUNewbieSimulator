#pragma once
#ifndef __SWITCHS_H__
#define __SWITCHS_H__

#include <string.h>
#include <stdbool.h>

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
	KLUE
} XMLelementMessage;

int getClassifyMessage(char* name) {
	switchs(name) {
		cases("major")
			return MAJOR;
		cases("selective")
			return SELECTIVE;
		cases("core")
			return CORE;
		defaults
			return CLASSIFY_DEFAULT;

	} switchs_end;
	return 0;
}
int getKlueMessage(char* name) {
	switchs(name) {
		cases(u8"지뢰")
			return BAD;
		cases(u8"꿀강")
			return GOOD;
		defaults
			return NORMAL;
	} switchs_end;
	return 0;
}
int getRoomMessage(char* name) {
	switchs(name) {
		cases(u8"교육관")
			return EDUCATE;
		cases(u8"교양관")
			return REFINEMENT;
		cases(u8"정통관")
			return INFORMATICS;
		cases(u8"과도관")
			return SCI_LIBRARY;
		cases(u8"이학관")
			return SCIENCE_HALL;
		cases(u8"법학관신관")
			return NEW_LAW_HALL;
		cases(u8"L-P관")
			return LP_HALL;
		cases(u8"서관")
			return WEST_HALL;
		cases(u8"정경관")
			return POLITIC;
		defaults
			return ROOM_DEFAULT;
	} switchs_end;
	return 0;
}
int getElementMessage(char* name) {
	switchs(name) {
		cases("code")
			return CODE;
		cases("class")
			return CLASS;
		cases("type")
			return TYPE;
		cases("name")
			return NAME;
		cases("credit")
			return CREDIT;
		cases("time")
			return TIME;
		cases("room")
			return ROOM;
		cases("distance")
			return DISTANCE;
		cases("klue")
			return KLUE;
		defaults
			return XML_MESSAGE_DEFAULT;
	} switchs_end;
	return 0;
}
int whatDayFunc(char hangul[]) {
	switchs(hangul) {
		cases(u8"월")
			return MON;
		cases(u8"화")
			return TUE;
		cases(u8"수")
			return WED;
		cases(u8"목")
			return THU;
		cases(u8"금")
			return FRI;
		cases(u8"토")
			return SAT;
		cases(u8"일")
			return SUN;
		defaults
			return DAY_DEFAULT;

	} switchs_end;
	return 0;
}