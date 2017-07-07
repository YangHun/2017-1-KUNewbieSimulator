#pragma once
#include"lectureInfo.h"
typedef enum _isEmpty {
	ISEMPTY_DEFAULT, //초기값.
	EMPTY, // 이 시간대에 강의가 없음
	NONEMPTY // 있음
} isEmpty;

typedef struct _strList {
	char* str;
	struct _strList* next;
} strList;

typedef strList* strListPtr;

typedef struct _timetableInfo {
	char* name; // 강의명
	enum roomNumber room; // 강의실
	enum isEmpty isEmptyBit; // 비었는지 안비었는지 확인
} timetableInfo;

typedef struct _schedule {
	int gradePoint;
	strListPtr idNumberList;
	timetableInfo timeTable[5][10]; //5요일 10교시
} schedule;