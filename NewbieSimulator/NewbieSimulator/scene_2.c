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
void arrangeLectureList(int selectedScroll);
int canUseKlue; // 클루 사용 가능 여부
object_t listTextArray[11][5];

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
#define BUTTON_CORE Stack.objs[2] 

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

	object_t text_separate_class = create_object(NULL, 192, 22);
	ui_set_text(&text_separate_class, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "separate_class"), 18);
	Stack.push(&Stack, text_separate_class); //stack 12

	object_t text_lecture_name = create_object(NULL, 303, 22);
	ui_set_text(&text_lecture_name, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "lecture_name"), 18);
	Stack.push(&Stack, text_lecture_name);//stack 13

	object_t text_lecture_room = create_object(NULL, 445, 22);
	ui_set_text(&text_lecture_room, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "lecture_room"), 18);
	Stack.push(&Stack, text_lecture_room); //stack 14

	object_t text_lecture_time = create_object(NULL, 545, 22);
	ui_set_text(&text_lecture_time, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "lecture_time"), 18);
	Stack.push(&Stack, text_lecture_time); //stack 15

	object_t upscroll_button = create_object("Resources\\UI\\enroll\\b_scroll_up.jpg", 649, 18);
	Stack.push(&Stack, upscroll_button);//stack 16

	object_t downscroll_button = create_object("Resources\\UI\\enroll\\b_scroll_down.jpg", 649, 383);
	Stack.push(&Stack, downscroll_button); //stack 17
	
	
	initList(); //18 ~ 61
	int my_stackcounter_1 = 62;
	for (int p = 0; p < 11; p++) { //62 ~ 116
		listTextArray[p][0] = create_object(NULL, 100, 56 + (p * 33));
		listTextArray[p][1] = create_object(NULL, 197, 56 + (p * 33));
		listTextArray[p][2] = create_object(NULL, 237, 56 + (p * 33));
		listTextArray[p][3] = create_object(NULL, 449, 56 + (p * 33));
		listTextArray[p][4] = create_object(NULL, 520, 56 + (p * 33));

		
		Stack.push(&Stack, listTextArray[p][0]);
		Stack.push(&Stack, listTextArray[p][1]);
		Stack.push(&Stack, listTextArray[p][2]);
		Stack.push(&Stack, listTextArray[p][3]);
		Stack.push(&Stack, listTextArray[p][4]);

		ui_set_text(&Stack.objs[my_stackcounter_1++], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 16);
		ui_set_text(&Stack.objs[my_stackcounter_1++], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 16);
		ui_set_text(&Stack.objs[my_stackcounter_1++], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 16);
		ui_set_text(&Stack.objs[my_stackcounter_1++], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 16);
		ui_set_text(&Stack.objs[my_stackcounter_1++], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 16);
	}
	for (int i = 0; i < 11; i++) {
		onListLecture[i] = -1;
	}

	//------------------------------------------------
	// lecture showing
	//------------------------------------------------

	//y좌표 강의명460 | 시간/강의실 495 | 학수번호 530 | 이수구분 565 | 수업 방법 600 | 평가방법 670 (간격 35)
	//lecture_name : 강의명

	object_t lecture_name = create_object(NULL, 191, 460);
	ui_set_text(&lecture_name, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_name); //117

	//lecture_time : 시간/강의실
	object_t lecture_time = create_object(NULL, 191, 495);
	ui_set_text(&lecture_time, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_time); //118

	//lecture_number : 학수번호
	object_t lecture_number = create_object(NULL, 191, 530);
	ui_set_text(&lecture_number, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_number); //119

	//lecture_credit : 이수구분.학점
	object_t lecture_credit = create_object(NULL, 191, 565);
	ui_set_text(&lecture_credit, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_credit); //120

	//lecture_class : 수업 방법
	object_t lecture_class = create_object(NULL, 191, 600);
	ui_set_text(&lecture_class, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_class); //121

	//lecture_eval : 평가 방법
	object_t lecture_eval = create_object(NULL, 191, 670);
	ui_set_text(&lecture_eval, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_eval); //122

	//printLecture_test();
	return 0;
}

int scene_2_update() {

	//Scene 2의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨

	sprintf(gradepoint_str, "%d", mySchedule.gradePoint);
	re_draw();
	/*
	scanf("%d", &input);
	
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
	int input;
	for (int k = 0; k < LIST_SIZE; k++) {
		if (Stack.objs[21 + k * 4].enable == true) {
			input = onListLecture[k];
		}
	}
	printf("%d input \n", input);
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
}

void on_click_campus_map(void) {

}

void on_click_button_selective() {
	if (isActive != B_SELECTIVE) {
		toggle_button(B_SELECTIVE);
		arrangeLectureList(0);
	}
}

void on_click_button_major() {
	if (isActive != B_MAJOR) {
		toggle_button(B_MAJOR);
		arrangeLectureList(0);
	}
}

void on_click_button_core() {
	if (isActive != B_CORE) {
		toggle_button(B_CORE);
		arrangeLectureList(0);
	}
}

void toggle_button(ActiveButton active) { // 좌측 3개를 눌렀을 때
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


void printLecture(int index) { //좌측 하단 출력
	lectureInfo lecture = lectureTable[onListLecture[index]];
	// 117 강의명 118 시간/강의실 119 학수번호 120 이수구분/학점 121 수업방법 122 평가방법
	
	Stack.objs[117].modifier.value.font_value.text = al_get_config_value(conf, "name", lecture.identifyNumber);
	Stack.objs[118].modifier.value.font_value.text = al_get_config_value(conf, "time_room", lecture.identifyNumber);
	Stack.objs[119].modifier.value.font_value.text = lecture.identifyNumber;
	Stack.objs[120].modifier.value.font_value.text = al_get_config_value(conf, "classify_credit", lecture.identifyNumber);
	Stack.objs[121].modifier.value.font_value.text = al_get_config_value(conf, "tuition_method", lecture.identifyNumber);
	Stack.objs[122].modifier.value.font_value.text = al_get_config_value(conf, "evaluation_method", lecture.identifyNumber);
}

void resetLectureList(){ // List 색 초기화
	for (int k = 0; k < LIST_SIZE; k++) {
		Stack.objs[(4 * k) + 18].enable = true;
		Stack.objs[(4 * k) + 19].enable = false;
		Stack.objs[(4 * k) + 20].enable = false;
		Stack.objs[(4 * k) + 21].enable = false;
		if (onListLecture[k] >= 0) {
			if (lectureTable[onListLecture[k]].klueRating == GOOD) {
				Stack.objs[(4 * k) + 18].enable = false;
				Stack.objs[(4 * k) + 19].enable = true;
			}
			else if (lectureTable[onListLecture[k]].klueRating == BAD) {
				Stack.objs[(4 * k) + 18].enable = false;
				Stack.objs[(4 * k) + 20].enable = true;
			}
		}
	}
}

void arrangeLectureList(int selectedScroll) { // 좌측 버튼을 만질 경우 재정렬
	int i = 0;
	int j = 0;
	for (int k = 0; k < LIST_SIZE; k++) {
		onListLecture[k] = -1;
	}
	while (i < LIST_SIZE && j < LECTURE_SIZE) {
		if (lectureTable[j].classify == isActive) {
			onListLecture[i] = j;
			i++;
		}
		j++;
	}
	resetLectureList();
	for (int k = 0; k < LIST_SIZE; k++) {
		printf("%d ", onListLecture[k]);
	}
	printf("\n");
	int p = 62; // 62부터 116까지가 List text의 위치
	for (int k = 0; k < LIST_SIZE; k++) {
		if (onListLecture[k] != -1) {

			Stack.objs[p++].modifier.value.font_value.text = lectureTable[onListLecture[k]].identifyNumber;
			Stack.objs[p++].modifier.value.font_value.text = "00";
			Stack.objs[p++].modifier.value.font_value.text = al_get_config_value(conf, "name", lectureTable[onListLecture[k]].identifyNumber);
			Stack.objs[p++].modifier.value.font_value.text = al_get_config_value(conf, "room", lectureTable[onListLecture[k]].identifyNumber);
			Stack.objs[p++].modifier.value.font_value.text = al_get_config_value(conf, "time", lectureTable[onListLecture[k]].identifyNumber);	

		}
		else  {
			Stack.objs[p++].modifier.value.font_value.text = "";
			Stack.objs[p++].modifier.value.font_value.text = "";
			Stack.objs[p++].modifier.value.font_value.text = "";
			Stack.objs[p++].modifier.value.font_value.text = "";
			Stack.objs[p++].modifier.value.font_value.text = "";
		}
		
		
	}
	
}

void initList() { //강의 리스트 부분 초기화 // 18 ~ 61
	void(*fp)(void) = NULL;
	int i = 0;
	object_t lectureButton[LIST_SIZE * 4];
	for (i = 0; i < LIST_SIZE * 4; i += 4) {
		lectureButton[i] = create_object("Resources\\UI\\enroll\\bar_normal_lecture.jpg", 92, 45 + ((i/4) * 33));
		lectureButton[i + 1] = create_object("Resources\\UI\\enroll\\bar_honey_lecture.jpg", 92, 45 + ((i/4) * 33));
		lectureButton[i + 2] = create_object("Resources\\UI\\enroll\\bar_bomb_lecture.jpg", 92, 45 + ((i/4) * 33));
		lectureButton[i + 3] = create_object("Resources\\UI\\enroll\\bar_selected_lecture.jpg", 92, 45 + ((i/4) * 33));
		ui_set_button(&lectureButton[i]);
		ui_set_button(&lectureButton[i + 1]);
		ui_set_button(&lectureButton[i + 2]);
		ui_set_button(&lectureButton[i + 3]);
		switch (i/4)
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
		ui_set_on_click_listener(&lectureButton[i + 1], fp);
		ui_set_on_click_listener(&lectureButton[i + 2], fp);
		ui_set_on_click_listener(&lectureButton[i + 3], fp);

		Stack.push(&Stack, lectureButton[i]);
		Stack.push(&Stack, lectureButton[i + 1]);
		Stack.push(&Stack, lectureButton[i + 2]);
		Stack.push(&Stack, lectureButton[i + 3]);
		Stack.objs[19 + i].enable = false;
		Stack.objs[20 + i].enable = false;
		Stack.objs[21 + i].enable = false;
	}

}
/*
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
*/
static void on_click_lectureList_0() {
	if (onListLecture[0] != -1) { // 만약 이 칸에 강의가 채워져 있다면
		resetLectureList();
		Stack.objs[18].enable = false;
		Stack.objs[19].enable = false;
		Stack.objs[20].enable = false;
		Stack.objs[21].enable = true;
		printf("0 call \n");
		printLecture(0);
	}
}
static void on_click_lectureList_1() {
	if (onListLecture[1] != -1) {
		resetLectureList();
		Stack.objs[22].enable = false;
		Stack.objs[23].enable = false;
		Stack.objs[24].enable = false;
		Stack.objs[25].enable = true;
		printf("1 call \n");
		printLecture(1);
	}

}
static void on_click_lectureList_2() {
	if (onListLecture[2] != -1) {
		resetLectureList();
		Stack.objs[26].enable = false;
		Stack.objs[27].enable = false;
		Stack.objs[28].enable = false;
		Stack.objs[29].enable = true;
		printf("2 call \n");
		printLecture(2);
	}
}
static void on_click_lectureList_3() {
	if (onListLecture[3] != -1) {
		resetLectureList();
		Stack.objs[30].enable = false;
		Stack.objs[31].enable = false;
		Stack.objs[32].enable = false;
		Stack.objs[33].enable = true;
		printf("3 call \n");
		printLecture(3);
	}
}
static void on_click_lectureList_4() {
	if (onListLecture[4] != -1) {
		resetLectureList();
		Stack.objs[34].enable = false;
		Stack.objs[35].enable = false;
		Stack.objs[36].enable = false;
		Stack.objs[37].enable = true;
		printf("4 call \n");
		printLecture(4);
	}
}
static void on_click_lectureList_5() {
	if (onListLecture[5] != -1) {
		resetLectureList();
		Stack.objs[38].enable = false;
		Stack.objs[39].enable = false;
		Stack.objs[40].enable = false;
		Stack.objs[41].enable = true;
		printf("5 call \n");
		printLecture(5);
	}
}
static void on_click_lectureList_6() {
	if (onListLecture[6] != -1) {
		resetLectureList();
		Stack.objs[42].enable = false;
		Stack.objs[43].enable = false;
		Stack.objs[44].enable = false;
		Stack.objs[45].enable = true;
		printf("6 call \n");
		printLecture(6);
	}
}
static void on_click_lectureList_7() {
	if (onListLecture[7] != -1) {
		resetLectureList();
		Stack.objs[46].enable = false;
		Stack.objs[47].enable = false;
		Stack.objs[48].enable = false;
		Stack.objs[49].enable = true;
		printf("7 call \n");
		printLecture(7);
	}
}
static void on_click_lectureList_8() {
	if (onListLecture[8] != -1) {
		resetLectureList();
		Stack.objs[50].enable = false;
		Stack.objs[51].enable = false;
		Stack.objs[52].enable = false;
		Stack.objs[53].enable = true;
		printf("8 call \n");
		printLecture(8);
	}
}
static void on_click_lectureList_9() {
	if (onListLecture[9] != -1) {
		resetLectureList();
		Stack.objs[54].enable = false;
		Stack.objs[55].enable = false;
		Stack.objs[56].enable = false;
		Stack.objs[57].enable = true;
		printf("9 call \n");
		printLecture(9);
	}
}
static void on_click_lectureList_10() {
	if (onListLecture[10] != -1) {
		resetLectureList();
		Stack.objs[58].enable = false;
		Stack.objs[59].enable = false;
		Stack.objs[60].enable = false;
		Stack.objs[61].enable = true;
		printf("10 call \n");
		printLecture(10);
	}
}