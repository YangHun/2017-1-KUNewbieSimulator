//#define _CRT_SECURE_NO_WARNINGS
//commit test
#include "engine.h"
#include "manageTimetable.h"
#include "xmlParser.h"
#pragma comment(lib, "Ws2_32.lib")
#define MAX_CREDIT 19
#define LIST_SIZE 11
#define LECTURE_SIZE 17
//Global Variable
lectureInfo lectureTable[LECTURE_SIZE];
int input = 0;
int analyzeMessage = MESSAGE_DEFAULT;

char gradepoint_str[3];

schedule mySchedule;
schedule* mySchedulePtr = &mySchedule;

ALLEGRO_BITMAP* tempimage = NULL;

ALLEGRO_FONT *font;
ALLEGRO_CONFIG *conf;

typedef enum { B_INIT, B_SELECTIVE, B_MAJOR, B_CORE, B_UPSCROLL, B_DOWNSCROLL }ActiveButton;
ActiveButton isActive = B_INIT;

object_t pushed_major;
object_t pushed_core;
object_t pushed_selective;


void printLecture(int index);
void printLecture_test(void);
void initList();


static void toggle_button(ActiveButton active);

static void on_click_button_0();
static void on_click_button_selective();
static void on_click_button_major();
static void on_click_button_core();

static void on_click_add_lecture();
static void on_click_campus_map();

static void on_click_lectureList_0();
static void on_click_lectureList_1();
static void on_click_lectureList_2();
static void on_click_lectureList_3();
static void on_click_lectureList_4();
static void on_click_lectureList_5();
static void on_click_lectureList_6();
static void on_click_lectureList_7();
static void on_click_lectureList_8();
static void on_click_lectureList_9();
static void on_click_lectureList_10();

int onListLecture[LIST_SIZE];
int previousListLecture[LIST_SIZE];
//void arrangeLectureList(int selectedScroll);
int canUseKlue; // 클루 사용 가능 여부

int scene_2_init() {
	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	system("chcp 65001");
	printf("Scene 2 start!");

	canUseKlue = 1; // true

	object_t bg = create_object("Resources\\UI\\enroll\\background.jpg", 0, 0);
	Background = bg;

	font = al_load_font("Resources\\font\\BMDOHYEON.ttf", 36, 0);
	conf = al_load_config_file("Resources\\korean\\lecture_info.ini");

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
	ui_set_on_click_listener(&button_core, on_click_button_core);
	Stack.push(&Stack, button_core);
#define BUTTON_CORE Stack.objs[2] //누르면 터진다???

	pushed_selective = create_object("Resources\\UI\\enroll\\b_select_pushed.png", 0, 34);
	Stack.push(&Stack, pushed_selective);
#define PUSHED_SELECTIVE Stack.objs[3]
	pushed_major = create_object("Resources\\UI\\enroll\\b_major_pushed.png", 0, 157);
	Stack.push(&Stack, pushed_major);
#define PUSHED_MAJOR Stack.objs[4]
	pushed_core = create_object("Resources\\UI\\enroll\\b_core_pushed.png", 0, 280);
	Stack.push(&Stack, pushed_core);
#define PUSHED_CORE Stack.objs[5]

	PUSHED_CORE.enable = false;
	PUSHED_MAJOR.enable = false;
	PUSHED_SELECTIVE.enable = false;

	object_t add_lecture = create_object("Resources\\UI\\enroll\\b_add_lecture.png", 128, 413);
	ui_set_button(&add_lecture);
	ui_set_on_click_listener(&add_lecture, on_click_add_lecture);
	Stack.push(&Stack, add_lecture);
#define ADD_LECTURE Stack.objs[6]

	object_t campus_map = create_object("Resources\\UI\\enroll\\b_campus_map.png", 546, 413);
	ui_set_button(&campus_map);
	ui_set_on_click_listener(&campus_map, on_click_campus_map);
	Stack.push(&Stack, campus_map);
#define CAMPUS_MAP Stack.objs[7]



	//------------------------------------------------
	// Texts
	//------------------------------------------------

	object_t n = create_object(NULL, 1026, 615);
	ui_set_text(&n, al_map_rgb(155, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, gradepoint_str, 30);
	Stack.push(&Stack, n); //stack 8

	object_t number = create_object(NULL, 1050, 615);
	ui_set_text(&number, al_map_rgb(155, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "credit"), 30);
	Stack.push(&Stack, number);//stack 9


	xmlParse(lectureTable);	
	init_mySchedule(mySchedulePtr);

	//------------------------------------------------
	// List
	//------------------------------------------------
	
	object_t list_column = create_object("Resources\\UI\\enroll\\list_column.png", 92, 18);
	Stack.push(&Stack, list_column); //stack 10
	
	object_t text_idnumber = create_object(NULL, 105, 22);
	ui_set_text(&text_idnumber, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "idnumber"), 18);
	Stack.push(&Stack, text_idnumber); //stack 11

	object_t text_separate_class = create_object(NULL, 195, 22);
	ui_set_text(&text_separate_class, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "separate_class"), 18);
	Stack.push(&Stack, text_separate_class); //stack 12

	object_t text_lecture_name = create_object(NULL, 303, 22);
	ui_set_text(&text_lecture_name, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "lecture_name"), 18);
	Stack.push(&Stack, text_lecture_name);//stack 13

	object_t text_lecture_room = create_object(NULL, 470, 22);
	ui_set_text(&text_lecture_room, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "lecture_room"), 18);
	Stack.push(&Stack, text_lecture_room); //stack 14

	object_t text_lecture_time = create_object(NULL, 570, 22);
	ui_set_text(&text_lecture_time, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "lecture_time"), 18);
	Stack.push(&Stack, text_lecture_time); //stack 15

	object_t upscroll_button = create_object("Resources\\UI\\enroll\\b_scroll_up.jpg", 649, 18);
	Stack.push(&Stack, upscroll_button);//stack 16

	object_t downscroll_button = create_object("Resources\\UI\\enroll\\b_scroll_down.jpg", 649, 383);
	Stack.push(&Stack, downscroll_button); //stack 17
	
	
	initList(); //18 ~ 28
	for (int i = 0; i < 11; i++) {
		onListLecture[i] = -1;
		previousListLecture[i] = -1;
	}
	printLecture(0);
	
	//printLecture_test();
	return 0;
}

int scene_2_update() {

	//Scene 2의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
	sprintf(gradepoint_str, "%d", mySchedule.gradePoint);
	re_draw();

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

	//clearing font related memory
	al_destroy_config(conf);
	al_destroy_font(font);


	return 0;
}

void on_click_add_lecture(void) {

}

void on_click_campus_map(void) {

}

void on_click_button_selective() {
	if (isActive != B_SELECTIVE) {
		toggle_button(B_SELECTIVE);
		//arrangeLectureList(0);
	}
}

void on_click_button_major() {
	if (isActive != B_MAJOR) {
		toggle_button(B_MAJOR);
		//arrangeLectureList(0);
	}
}

void on_click_button_core() {
	if (isActive != B_CORE) {
		toggle_button(B_CORE);
		//arrangeLectureList(0);
	}
}

void toggle_button(ActiveButton active) {
	PUSHED_CORE.enable = false;
	PUSHED_MAJOR.enable = false;
	PUSHED_SELECTIVE.enable = false;

	switch (active) {
	case B_SELECTIVE:
		PUSHED_SELECTIVE.enable = true;
		break;
	case B_MAJOR:
		PUSHED_MAJOR.enable = true;
		break;
	case B_CORE:
		PUSHED_CORE.enable = true;
		break;
	default:
		break;
	}

	isActive = active;

}

//---------------------------
//requires A LOT OF revision!
//---------------------------


void printLecture(int index) {
	lectureInfo lecture = lectureTable[index];

	printf("%s\n", lecture.identifyNumber);
	printf("<%s>\n", al_get_config_value(conf, "name", lecture.identifyNumber));
	//y좌표 강의명460 | 시간/강의실 495 | 학수번호 530 | 이수구분 565 | 수업 방법 600 | 평가방법 670 (간격 35)
	//lecture_name : 강의명

	object_t lecture_name = create_object(NULL, 191, 460);
	ui_set_text(&lecture_name, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "name", lecture.identifyNumber), 25);
	Stack.push(&Stack, lecture_name);

	//lecture_time : 시간/강의실
	object_t lecture_time = create_object(NULL, 191, 495);
	ui_set_text(&lecture_time, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "time", lecture.identifyNumber), 25);
	Stack.push(&Stack, lecture_time);


	//lecture_number : 학수번호
	object_t lecture_number = create_object(NULL, 191, 530);
	ui_set_text(&lecture_number, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, lecture.identifyNumber, 25);
	Stack.push(&Stack, lecture_number);

	//lecture_credit : 이수구분.학점
	object_t lecture_credit = create_object(NULL, 191, 565);
	ui_set_text(&lecture_credit, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "credit", lecture.identifyNumber), 25);
	Stack.push(&Stack, lecture_credit);

	//lecture_class : 수업 방법
	object_t lecture_class = create_object(NULL, 191, 600);
	ui_set_text(&lecture_class, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "tuition_method", lecture.identifyNumber), 25);
	Stack.push(&Stack, lecture_class);

	//lecture_eval : 평가 방법
	object_t lecture_eval = create_object(NULL, 191, 670);
	ui_set_text(&lecture_eval, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "evaluation_method", lecture.identifyNumber), 25);
	Stack.push(&Stack, lecture_eval);


}

void initList() {
	void(*fp)(void) = NULL;
	int i = 0;
	object_t lectureButton[LIST_SIZE];
	while (i != LIST_SIZE) {
		lectureButton[i] = create_object("Resources\\UI\\enroll\\bar_normal_lecture.jpg", 92, 45 + (i * 33));
		ui_set_button(&lectureButton[i]);
		switch (i)
		{
		case 0:
			fp = on_click_lectureList_0;
			break;
		case 1:
			fp = on_click_lectureList_1;
			break;
		case 2:
			fp = on_click_lectureList_2;
			break;
		case 3:
			fp = on_click_lectureList_3;
			break;
		case 4:
			fp = on_click_lectureList_4;
			break;
		case 5:
			fp = on_click_lectureList_5;
			break;
		case 6:
			fp = on_click_lectureList_6;
			break;
		case 7:
			fp = on_click_lectureList_7;
			break;
		case 8:
			fp = on_click_lectureList_8;
			break;
		case 9:
			fp = on_click_lectureList_9;
			break;
		case 10:
			fp = on_click_lectureList_10;
			break;
		default:
			break;
		}
		ui_set_on_click_listener(&lectureButton[i], fp);
		Stack.push(&Stack, lectureButton[i]);
		i++;
	}
	
}

void printLecture_test(void) {
	lectureInfo lecture = lectureTable[0];

	if (conf == NULL)
		printf("NULL!!\n");
	else
		printf("%x\n", conf);

	object_t aa = create_object(NULL, 191, 460);
	ui_set_text(&aa, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, lecture.identifyNumber, 30);
	Stack.push(&Stack, aa);

	object_t lecture_name = create_object(NULL, 191, 495);
	ui_set_text(&lecture_name, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "name", "COSE101"), 30);
	Stack.push(&Stack, lecture_name);
	al_get_config_value(conf, "name", lecture.identifyNumber);
	printf("%s hello", NULL);
	al_get_config_value(conf, "name", lecture.identifyNumber);

}

static void on_click_lectureList_0() {

}
static void on_click_lectureList_1() {

}
static void on_click_lectureList_2() {
	
}
static void on_click_lectureList_3() {
	
}
static void on_click_lectureList_4() {
	
}
static void on_click_lectureList_5() {
	
}
static void on_click_lectureList_6() {
	
}
static void on_click_lectureList_7() {
	
}
static void on_click_lectureList_8() {
	
}
static void on_click_lectureList_9() {
	
}
static void on_click_lectureList_10() {

}