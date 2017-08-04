#pragma once
#include "schedule.h"
#include "lectureInfo.h"
#define MAX_CREDIT 19

void init_mySchedule(schedule* mySchedulePtr) {
	mySchedulePtr->idNumberList = (strListPtr)malloc(sizeof(strList));
	mySchedulePtr->idNumberList->str = NULL;
	mySchedulePtr->idNumberList->next = NULL;

	mySchedulePtr->credit = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			mySchedulePtr->timeTable[i][j].isEmptyBit = EMPTY;
			mySchedulePtr->timeTable[i][j].index = -1;
		}
	}
}

void printSchedule(schedule mySchedule) {
	printf("idNumber : ");
	for (strListPtr p = mySchedule.idNumberList->next; p != NULL; p = p->next) {
		printf("%s ", p->str);
	}
	printf("\n");

	printf("  MN TS WD TH FR");
	printf("\n");
	for (int i = 0; i < 10; i++) {
		printf("%d ", i);
		for (int j = 0; j < 5; j++) {
			if (mySchedule.timeTable[j][i].isEmptyBit == EMPTY) {
				printf("-  ");
			}
			else {
				printf("O  ");
			}
		}
		printf("\n");
	}
}
void addLectureToSchedule(lectureInfo lectureTable[], schedule* mySchedulePtr, int index) {
	mySchedulePtr->credit += lectureTable[index].credit;
	for (strListPtr p = mySchedulePtr->idNumberList; p != NULL; p = p->next) {
		if (p->next == NULL) {
			strListPtr tempNode = (strListPtr)malloc(sizeof(strList));
			tempNode->next = NULL;
			tempNode->str = lectureTable[index].identifyNumber;
			p->next = tempNode;
			break;
		}
	}

	for (timeListPtr k = lectureTable[index].lectureTime->next; k != NULL; k = k->next) {
		int i = k->timeblock.dayofWeek;
		int j = k->timeblock.period;
		int z = k->timeblock.interval;
		for (int w = 0; w < z; w++) {
			mySchedulePtr->timeTable[i][j + w].isEmptyBit = NONEMPTY;
			mySchedulePtr->timeTable[i][j + w].index = index;
		}
	}
}
void deleteLectureFromSchedule(lectureInfo lectureTable[], schedule* mySchedulePtr, int index) {
	strListPtr current = mySchedulePtr->idNumberList->next;
	strListPtr previous = NULL;

	char* target = lectureTable[index].identifyNumber;

	while (current != NULL) {
		if (!strncmp(target, current->str, 7)) {
			if (previous == NULL) {
				mySchedulePtr->idNumberList->next = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current);
			break;
		}
		else {
			previous = current;
			current = current->next;
		}

	}

	for (timeListPtr k = lectureTable[index].lectureTime->next; k != NULL; k = k->next) {
		int i = k->timeblock.dayofWeek;
		int j = k->timeblock.period;
		int z = k->timeblock.interval;
		for(int w = 0; w < z; w++){
			mySchedulePtr->timeTable[i][j + w].isEmptyBit = EMPTY;
			mySchedulePtr->timeTable[i][j + w].index = -1;
		}
	}
}
int analyzeSchedule(lectureInfo lectureTable[], schedule mySchedule, int index) {
	int i, j;
	int day, period, interval;

	lectureInfo target = lectureTable[index];
	timeListPtr currentPtr = target.lectureTime;
	strListPtr currentPtr_id = mySchedule.idNumberList;
	isEmpty targetTable[5][10] = { ISEMPTY_DEFAULT };


	//중복강의 확인
	//if (currentPtr_id = NULL)
	currentPtr_id = currentPtr_id->next;
	while (currentPtr_id != NULL) {
		if (!strncmp(currentPtr_id->str, target.identifyNumber, 7))
			return ALREADY_EXIST;
		else
			currentPtr_id = currentPtr_id->next;
	}

	//학점초과 확인
	if (mySchedule.credit + target.credit > MAX_CREDIT)
		return EXCEED_POINT;

	// if (currentPtr == NULL)
	currentPtr = currentPtr->next;
	while (currentPtr != NULL) {
		day = currentPtr->timeblock.dayofWeek;
		period = currentPtr->timeblock.period;
		interval = currentPtr->timeblock.interval;
		for (int w = 0; w < interval; w++) {
			targetTable[day][period + w] = NONEMPTY;
		}
		currentPtr = currentPtr->next;
	}

	//시간표 겹침 및 확인
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			if (mySchedule.timeTable[i][j].isEmptyBit == NONEMPTY) {
				if (targetTable[i][j] == NONEMPTY) //시간표 중복확인
					return TIME_OVERLAP;
			}
		}
	}

	return NO_OVERLAP; //상기 해당사항 없을 시
}
