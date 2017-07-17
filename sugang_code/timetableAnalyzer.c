#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"schedule.h"

//최대이수학점
#define MAX_CREDIT 19

void registerLecture(lectureInfo lectureTable[]);
void init_mySchedule(schedule* mySchedulePtr);
void addLectureToSchedule(lectureInfo lectureTable[], schedule* mySchedulePtr, int index);
void deleteLectureFromSchedule(lectureInfo lectureTable[], schedule* mySchedulePtr, int index);
int analyzeSchedule(schedule mySchedule, int index); //do yourself

lectureInfo lectureTable[5];


int main() {
	int analyzeMessage = MESSAGE_DEFAULT;

	registerLecture(lectureTable);
	
	schedule mySchedule;
	schedule* mySchedulePtr = &mySchedule;
	init_mySchedule(mySchedulePtr);

	int input = 0;
	while (1) {
		scanf("%d\n", &input);
		analyzeMessage = analyzeSchedule(mySchedule, input);
		switch (analyzeMessage)
		{
		EXCEED_POINT:
			printf("point Exceeded. delete other Lecture\n");
			break;

		NO_OVERLAP:
			addLectureToSchedule(lectureTable, mySchedulePtr, input);
			break;

		TIME_OVERLAP:
			printf("time overlapped. try again\n");
			break;

		ALREADY_EXIST:
			deleteLectureFromSchedule(lectureTable, mySchedulePtr, input);
			break;

		default:
			break;
		}
	}
}

//작업내용
int analyzeSchedule(schedule mySchedule, int index) {
	int i, j;
	int day, period;

	lectureInfo target = lectureTable[index];
	timeListPtr currentPtr = target.lectureTime;
	isEmpty targetTable[5][10] = { ISEMPTY_DEFAULT }; // 5 x 10의 시간표형태 배열에 target 과목의 시간표만 저장
	
	//학점초과 확인
	if (mySchedule.gradePoint + target.credit > MAX_CREDIT)
		return EXCEED_POINT;

	if (currentPtr == NULL)
		currentPtr = currentPtr->next;
	while (currentPtr != NULL) {
		day = currentPtr->timeblock.dayofWeek;
		period = currentPtr->timeblock.period;
		targetTable[day][period] = NONEMPTY;
		currentPtr = currentPtr->next;
	}

	//시간표 겹침 및 확인
	for (i = 0; i < 5; i++)
		for (j = 0; j < 10; j++)
			if (mySchedule.timeTable[i][j].isEmptyBit == NONEMPTY) {
				if (!strncmp(target.identifyNumber, target.identifyNumber, 7)) //학수번호 중복확인
					return ALREADY_EXIST;
				if (targetTable[i][j] == NONEMPTY) //시간표 중복확인
					return TIME_OVERLAP;
			}
	
	return NO_OVERLAP; //상기 해당사항 없을 시
}
//작업내용 끝

void init_mySchedule(schedule* mySchedulePtr) {
	mySchedulePtr->idNumberList = (strListPtr)malloc(sizeof(strList));
	mySchedulePtr->idNumberList->str = NULL;
	mySchedulePtr->idNumberList->next = NULL;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			mySchedulePtr->timeTable[i][j].isEmptyBit = EMPTY;
			mySchedulePtr->timeTable[i][j].name = NULL;
			mySchedulePtr->timeTable[i][j].room = ROOM_DEFAULT;
		}
	}
}
void registerLecture(lectureInfo lectureTable[]) {
	lectureInfo a1;
	a1.classify = NUCLEAR;
	a1.classNumber = 0;
	a1.credit = 3;
	a1.identifyNumber = "GELA050";
	a1.klueRating = NORMAL;
	a1.name = "한국현대시산책";
	a1.room = EDUCATE;
	a1.lectureTime = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a1_tempNode1 = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a1_tempNode2 = (timeListPtr)malloc(sizeof(timeList));
	a1_tempNode1->timeblock.dayofWeek = TUE;
	a1_tempNode1->timeblock.period = 2;
	a1_tempNode2->timeblock.dayofWeek = THU;
	a1_tempNode2->timeblock.period = 2;
	a1.lectureTime->next = a1_tempNode1;
	a1_tempNode1->next = a1_tempNode2;
	a1_tempNode2->next = NULL;

	lectureInfo a2;
	a2.classify = NUCLEAR;
	a2.classNumber = 0;
	a2.credit = 3;
	a2.identifyNumber = "GELA053";
	a2.klueRating = NORMAL;
	a2.name = "한국시속에살아있는독일문학";
	a2.room = REFINEMENT;
	a2.lectureTime = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a2_tempNode1 = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a2_tempNode2 = (timeListPtr)malloc(sizeof(timeList));
	a2_tempNode1->timeblock.dayofWeek = MON;
	a2_tempNode1->timeblock.period = 2;
	a2_tempNode2->timeblock.dayofWeek = WED;
	a2_tempNode2->timeblock.period = 2;
	a2.lectureTime->next = a2_tempNode1;
	a2_tempNode1->next = a2_tempNode2;
	a2_tempNode2->next = NULL;

	lectureInfo a3;
	a3.classify = NUCLEAR;
	a3.classNumber = 0;
	a3.credit = 3;
	a3.identifyNumber = "GELA107";
	a3.klueRating = NORMAL;
	a3.name = "한국고전문학과배경사상";
	a3.room = REFINEMENT;
	a3.lectureTime = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a3_tempNode1 = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a3_tempNode2 = (timeListPtr)malloc(sizeof(timeList));
	a3_tempNode1->timeblock.dayofWeek = MON;
	a3_tempNode1->timeblock.period = 6;
	a3_tempNode2->timeblock.dayofWeek = WED;
	a3_tempNode2->timeblock.period = 6;
	a3.lectureTime->next = a3_tempNode1;
	a3_tempNode1->next = a3_tempNode2;
	a3_tempNode2->next = NULL;

	lectureInfo a4;
	a4.classify = NUCLEAR;
	a4.classNumber = 0;
	a4.credit = 3;
	a4.identifyNumber = "GELA132";
	a4.klueRating = GOOD;
	a4.name = "현대음악의이해";
	a4.room = REFINEMENT;
	a4.lectureTime = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a4_tempNode1 = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a4_tempNode2 = (timeListPtr)malloc(sizeof(timeList));
	a4_tempNode1->timeblock.dayofWeek = MON;
	a4_tempNode1->timeblock.period = 5;
	a4_tempNode2->timeblock.dayofWeek = WED;
	a4_tempNode2->timeblock.period = 5;
	a4.lectureTime->next = a4_tempNode1;
	a4_tempNode1->next = a4_tempNode2;
	a4_tempNode2->next = NULL;

	lectureInfo a5;
	a5.classify = NUCLEAR;
	a5.classNumber = 0;
	a5.credit = 3;
	a5.identifyNumber = "GELA133";
	a5.klueRating = NORMAL;
	a5.name = "한시,영화와엮어읽기";
	a5.room = REFINEMENT;
	a5.lectureTime = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a5_tempNode1 = (timeListPtr)malloc(sizeof(timeList));
	timeListPtr a5_tempNode2 = (timeListPtr)malloc(sizeof(timeList));
	a5_tempNode1->timeblock.dayofWeek = MON;
	a5_tempNode1->timeblock.period = 2;
	a5_tempNode2->timeblock.dayofWeek = WED;
	a5_tempNode2->timeblock.period = 2;
	a5.lectureTime->next = a5_tempNode1;
	a5_tempNode1->next = a5_tempNode2;
	a5_tempNode2->next = NULL;

	lectureTable[0] = a1;
	lectureTable[1] = a2;
	lectureTable[2] = a3;
	lectureTable[3] = a4;
	lectureTable[4] = a5;
}