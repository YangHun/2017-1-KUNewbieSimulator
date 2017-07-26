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

ALLEGRO_CONFIG *conf;

static void on_click_button_0();
static void on_click_button_selective();
static void on_click_button_major();
static void on_click_button_core();

int scene_2_init() {
	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	system("chcp 65001");
	printf("Scene 2 start!");

	object_t bg = create_object("Resources\\UI\\enroll\\background.jpg", 0, 0);
	Background = bg;

	conf = al_load_config_file("Resources\\korean\\enroll.ini");


	//------------------------------------------------
	// Buttons
	//------------------------------------------------

	object_t button_selective = create_object("Resources\\UI\\enroll\\b_select_normal.png", 0, 34);
	ui_set_button(&button_selective);
	ui_set_on_click_listener(&button_selective, on_click_button_selective);
	Stack.push(&Stack, button_selective);
#define BUTTON_SELECTIVE Stack.objs[0]
	
	object_t button_major = create_object("Resources\\UI\\enroll\\b_major_normal.png", 0, 157);
	ui_set_button(&button_major);
	ui_set_on_click_listener(&button_major, on_click_button_major);
	Stack.push(&Stack, button_major);
#define BUTTON_MAJOR Stack.objs[1]

	object_t button_core = create_object("Resources\\UI\\enroll\\b_core_normal.png", 0, 280);
	ui_set_button(&button_core);
	ui_set_on_click_listener(&button_selective, on_click_button_core);
	Stack.push(&Stack, button_core);
#define BUTTON_CORE Stack.objs[2]

	//------------------------------------------------
	// Texts
	//------------------------------------------------

	object_t n = create_object(NULL, 1015, 567);
	ui_set_text(&n, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, "7", 24);
	Stack.push(&Stack, n);

	object_t number = create_object(NULL, 1026, 567);
	ui_set_text(&number, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "number"), 24);
	Stack.push(&Stack, number);


	xmlParse(lectureTable);
	init_mySchedule(mySchedulePtr);

	return 0;
}

int scene_2_update() {

	//Scene 2의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
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
	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.
	Stack.clear(&Stack);

	printf("counter : %d \n", Stack.counter);


	return 0;
}

void on_click_button_0() {
	load_scene(Scenes.scenes[1]);

}

void on_click_button_selective() {
	//do it!

}

void on_click_button_major() {
	//do it!

}

void on_click_button_core() {
	//do it!

}

