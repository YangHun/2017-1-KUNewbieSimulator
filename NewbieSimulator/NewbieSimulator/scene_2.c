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

static void on_click_button_0();

int scene_2_init() {
	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	system("chcp 65001");
	printf("Scene 2 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;

	object_t hos = create_object("Resources\\dummy\\hos.png", 100, 100);
	ui_set_button(&hos);
	ui_set_on_click_listener(&hos, on_click_button_0);
	Stack.push(&Stack, hos);

	xmlParse(lectureTable);
	init_mySchedule(mySchedulePtr);

	return 0;
}

int scene_2_update() {

	//Scene 2�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����
	//re_draw();

	/*
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
	*/
	return 0;
}


int scene_2_fin() {
	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.
	Stack.clear(&Stack);

	printf("counter : %d \n", Stack.counter);


	return 0;
}

void on_click_button_0() {
	load_scene(Scenes.scenes[1]);

}

