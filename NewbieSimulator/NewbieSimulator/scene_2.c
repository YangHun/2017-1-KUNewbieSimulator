//#define _CRT_SECURE_NO_WARNINGS
//commit test
#include "engine.h"
#include "manageTimetable.h"
#include "xmlParser.h"
#pragma comment(lib, "Ws2_32.lib")
#define MAX_CREDIT 19

//Global Variable
lectureInfo lectureTable[17];
int input = 0;
int analyzeMessage = MESSAGE_DEFAULT;

schedule mySchedule;
schedule* mySchedulePtr = &mySchedule;

int scene_2_init() {
	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	system("chcp 65001");
	printf("Scene 2 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;
	xmlParse(lectureTable);
	init_mySchedule(mySchedulePtr);
}

int scene_2_update() {

	//Scene 2�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	printSchedule(mySchedule);

	scanf("%d", &input);
	fflush(stdin);

	analyzeMessage = analyzeSchedule(lectureTable, mySchedule, input);
	switch (analyzeMessage)
	{
	case EXCEED_POINT:
		printf("point Exceeded. delete other Lecture\n");
		break;

	case NO_OVERLAP:
		addLectureToSchedule(lectureTable, mySchedulePtr, input);
		break;

	case TIME_OVERLAP:
		printf("time overlapped. try again\n");
		break;

	case ALREADY_EXIST:
		deleteLectureFromSchedule(lectureTable, mySchedulePtr, input);
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

