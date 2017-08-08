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
	KLUE,
	ATTENDANCE,
	EVAL,
	TUITION
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
			return KLUE_BAD;
		cases(u8"꿀강")
			return KLUE_GOOD;
		defaults
			return KLUE_NORMAL;
	} switchs_end;
	return 0;
}

int getAttMessage(char* name) {
	switchs(name) {
		cases("VTIGHT")
			return ATT_VTIGHT;
		cases("TIGHT")
			return ATT_TIGHT;
		cases("LOOSE")
			return ATT_LOOSE;
		cases("VLOOSE")
			return ATT_VLOOSE;
		cases("NORMAL")
			return ATT_NORMAL;
		defaults
			return ATT_NORMAL;
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
		cases("attendance")
			return ATTENDANCE;
		cases("eval")
			return EVAL;
		cases("tuition")
			return TUITION;
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

int getEvalMessage(char hangul[]) {
	switchs(hangul) {
		cases(u8"중간")
			return EVAL_MIDDLE_EXAM;
		cases(u8"기말")
			return EVAL_FINAL_EXAM;
		cases(u8"과제")
			return EVAL_ASSIGNMENT;
		cases(u8"발표")
			return EVAL_PRESENTATION;
		cases(u8"출석")
			return EVAL_ATTENDANCE;
		cases(u8"미1")
			return EVAL_UNDETERMINED_1;
		cases(u8"미2")
			return EVAL_UNDETERMINED_2;
		defaults
			return EVAL_DEFALUT;

	} switchs_end;
	return 0;
}

int getTuitionMessage(char hangul[]) {
	switchs(hangul) {
		cases(u8"강의")
			return TUI_LECTURE;
		cases(u8"발표")
			return TUI_PRESENTATION;
		cases(u8"토론")
			return TUI_DEBATION;
		cases(u8"퀴즈")
			return TUI_QUIZ;
		cases(u8"미3")
			return TUI_UNDETERMINED_3;
		cases(u8"미4")
			return TUI_UNDETERMINED_4;
		defaults
			return TUI_DEFAULT;

	} switchs_end;
	return 0;
}