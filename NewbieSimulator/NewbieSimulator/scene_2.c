//#define _CRT_SECURE_NO_WARNINGS

#include "engine.h"
#include "schedule.h"

#define MAX_CREDIT 19

void registerLecture();
void init_mySchedule(schedule* mySchedulePtr);
void printSchedule(schedule mySchedule);

//TODO
void addLectureToSchedule(schedule* mySchedulePtr, int index);
void deleteLectureFromSchedule(schedule* mySchedulePtr, int index);
int analyzeSchedule(schedule mySchedule, int index); //do yourself



//Global Variable
lectureInfo lectureTable[5];
int input = 0;
int analyzeMessage = MESSAGE_DEFAULT;


schedule mySchedule;
schedule* mySchedulePtr = &mySchedule;


int scene_2_init() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�

	printf("Scene 2 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;

	registerLecture();
	init_mySchedule(mySchedulePtr);
	

	return 0;
}


int scene_2_update() {

	//Scene 2�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
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

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.




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
			mySchedulePtr->timeTable[i][j].name = NULL;
			mySchedulePtr->timeTable[i][j].room = ROOM_DEFAULT;
		}
	}
}
void registerLecture() {
	lectureInfo a1;
	a1.classify = NUCLEAR;
	a1.classNumber = 0;
	a1.credit = 3;
	a1.identifyNumber = "GELA050";
	a1.klueRating = NORMAL;
	a1.name = "�ѱ�����û�å";
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
	a2.name = "�ѱ��üӿ�����ִµ��Ϲ���";
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
	a3.name = "�ѱ��������а������";
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
	a4.name = "��������������";
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
	a5.name = "�ѽ�,��ȭ�Ϳ����б�";
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
		mySchedulePtr->timeTable[i][j].name = lectureTable[index].name;
		mySchedulePtr->timeTable[i][j].room = lectureTable[index].room;
	}
}
void deleteLectureFromSchedule(schedule* mySchedulePtr, int index) {
	strListPtr current = mySchedulePtr->idNumberList->next;
	strListPtr previous = NULL;

	char* target = lectureTable[index].identifyNumber;

	while (current != NULL) {
		if (!strncmp(target, current->str, 7)) {
			if (previous == NULL)
				mySchedulePtr->idNumberList->next = current->next;
			else
				previous->next = current->next;
			//free(current->str);
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
		mySchedulePtr->timeTable[i][j].name = NULL; // null? free?
		mySchedulePtr->timeTable[i][j].room = ROOM_DEFAULT;
	}
}
int analyzeSchedule(schedule mySchedule, int index) {
	int i, j;
	int day, period;

	lectureInfo target = lectureTable[index];
	timeListPtr currentPtr = target.lectureTime;
	strListPtr currentPtr_id = mySchedule.idNumberList;
	isEmpty targetTable[5][10] = { ISEMPTY_DEFAULT };


	//�ߺ����� Ȯ��
	//if (currentPtr_id = NULL)
	currentPtr_id = currentPtr_id->next;
	while (currentPtr_id != NULL) {
		if (!strncmp(currentPtr_id->str, target.identifyNumber, 7))
			return ALREADY_EXIST;
		else
			currentPtr_id = currentPtr_id->next;
	}

	//�����ʰ� Ȯ��
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

	//�ð�ǥ ��ħ �� Ȯ��
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			if (mySchedule.timeTable[i][j].isEmptyBit == NONEMPTY) {
				if (targetTable[i][j] == NONEMPTY) //�ð�ǥ �ߺ�Ȯ��
					return TIME_OVERLAP;
			}
		}
	}

	return NO_OVERLAP; //��� �ش���� ���� ��
}
