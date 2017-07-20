//#define _CRT_SECURE_NO_WARNINGS
//commit test
#include "engine.h"
#include "schedule.h"
#include"lectureInfo.h"
#include<libxml\parser.h>
#include "xmlParser.h"
#pragma comment(lib, "Ws2_32.lib")
#define MAX_CREDIT 19

void registerLecture();
void init_mySchedule(schedule* mySchedulePtr);
void printSchedule(schedule mySchedule);

//TODO
void addLectureToSchedule(schedule* mySchedulePtr, int index);
void deleteLectureFromSchedule(schedule* mySchedulePtr, int index);
int analyzeSchedule(schedule mySchedule, int index); //do yourself


//Global Variable
lectureInfo lectureTable[17];
int input = 0;
int analyzeMessage = MESSAGE_DEFAULT;


schedule mySchedule;
schedule* mySchedulePtr = &mySchedule;


int scene_2_init() {

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수

	printf("Scene 2 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;

	registerLecture();
	//xmlParse(lectureTable);
	init_mySchedule(mySchedulePtr);
	
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile("Resources\\xml\\dummy-data.xml");
	if (doc == NULL) {
		printf("Document not parsed successfully. \n");
		return;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		printf("empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	if (strcmp(cur->name, "root")) {
		printf("document of the wrong type, root node != root \n");
		xmlFreeDoc(doc);
		return;
	}
	return 0;
}


int scene_2_update() {

	//Scene 2의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
	printSchedule(mySchedule);

	scanf("%d", &input);
	fflush(stdin);

	analyzeMessage = analyzeSchedule(mySchedule, input);
	switch (analyzeMessage)
	{
	case EXCEED_POINT:
		printf("point Exceeded. delete other Lecture\n");
		break;

	case NO_OVERLAP:
		addLectureToSchedule(mySchedulePtr, input);
		break;

	case TIME_OVERLAP:
		printf("time overlapped. try again\n");
		break;

	case ALREADY_EXIST:
		deleteLectureFromSchedule(mySchedulePtr, input);
		break;

	default:
		break;
	}


	return 0;
}


int scene_2_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.




	return 0;
}

void init_mySchedule(schedule* mySchedulePtr) {
	mySchedulePtr->idNumberList = (strListPtr)malloc(sizeof(strList));
	mySchedulePtr->idNumberList->str = NULL;
	mySchedulePtr->idNumberList->next = NULL;

	mySchedulePtr->gradePoint = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			mySchedulePtr->timeTable[i][j].isEmptyBit = EMPTY;
			mySchedulePtr->timeTable[i][j].index = -1;
		}
	}
}
void registerLecture() {
	lectureInfo a1;
	a1.classify = CORE;
	a1.classNumber = 0;
	a1.credit = 3;
	strcpy_s(a1.identifyNumber, sizeof(a1.identifyNumber), "GELA050");
	a1.klueRating = NORMAL;
	strcpy_s(a1.name, sizeof(a1.name), u8"한국현대시산책");
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
	a1.distance = 20;
	strcpy_s(a1.timeString, sizeof(a1.timeString), u8"화(2) 목(2)");

	lectureInfo a2;
	a2.classify = CORE;
	a2.classNumber = 0;
	a2.credit = 3;
	strcpy_s(a2.identifyNumber, sizeof(a2.identifyNumber), "GELA053");
	a2.klueRating = NORMAL;
	strcpy_s(a2.name, sizeof(a2.name), u8"한국시속에살아있는독일문학");
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
	a2.distance = 10;
	strcpy_s(a2.timeString, sizeof(a2.timeString), u8"월(2) 수(2)");

	lectureInfo a3;
	a3.classify = CORE;
	a3.classNumber = 0;
	a3.credit = 3;
	strcpy_s(a3.identifyNumber, sizeof(a3.identifyNumber), "GELA107");
	a3.klueRating = NORMAL;
	strcpy_s(a3.name, sizeof(a3.name), u8"한국고전문학과배경사상");
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
	a3.distance = 10;
	strcpy_s(a3.timeString, sizeof(a3.timeString), u8"월(6) 수(6)");

	lectureInfo a4;
	a4.classify = CORE;
	a4.classNumber = 0;
	a4.credit = 3;
	strcpy_s(a4.identifyNumber, sizeof(a4.identifyNumber), "GELA132");
	a4.klueRating = GOOD;
	strcpy_s(a4.name, sizeof(a4.name), u8"현대음악의이해");
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
	a4.distance = 10;
	strcpy_s(a4.timeString, sizeof(a4.timeString), u8"월(5) 수(5)");

	lectureInfo a5;
	a5.classify = CORE;
	a5.classNumber = 0;
	a5.credit = 3;
	strcpy_s(a5.identifyNumber, sizeof(a5.identifyNumber), "GELA133");
	a5.klueRating = NORMAL;
	strcpy_s(a5.name, sizeof(a5.name), u8"한시,영화와엮어읽기");
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
	a5.distance = 10;
	strcpy_s(a5.timeString, sizeof(a5.timeString), u8"월(2) 수(2)");

	lectureTable[0] = a1;
	lectureTable[1] = a2;
	lectureTable[2] = a3;
	lectureTable[3] = a4;
	lectureTable[4] = a5;
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
void addLectureToSchedule(schedule* mySchedulePtr, int index) {
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
		mySchedulePtr->timeTable[i][j].isEmptyBit = NONEMPTY;
		mySchedulePtr->timeTable[i][j].index = -1;
	}
}
void deleteLectureFromSchedule(schedule* mySchedulePtr, int index) {
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
		mySchedulePtr->timeTable[i][j].isEmptyBit = EMPTY;
		mySchedulePtr->timeTable[i][j].index = index;
	}
}
int analyzeSchedule(schedule mySchedule, int index) {
	int i, j;
	int day, period;

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
	if (mySchedule.gradePoint + target.credit > MAX_CREDIT)
		return EXCEED_POINT;

	// if (currentPtr == NULL)
	currentPtr = currentPtr->next;
	while (currentPtr != NULL) {
		day = currentPtr->timeblock.dayofWeek;
		period = currentPtr->timeblock.period;
		targetTable[day][period] = NONEMPTY;
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
