//#define _CRT_SECURE_NO_WARNINGS
//commit test
#include "engine.h"
#include "manageTimetable.h"
#include "xmlParser.h"
#pragma comment(lib, "Ws2_32.lib")
#define MAX_CREDIT 19
#define LIST_SIZE 11
#define MAX_DEFAULT_STACK 175
//Global Variable
lectureInfo lectureTable[LECTURE_SIZE];
int input = 0;
int analyzeMessage = MESSAGE_DEFAULT;
int protectOverlapClick = 0;
char gradepoint_str[3];

schedule mySchedule;
schedule* mySchedulePtr = &mySchedule;

ALLEGRO_BITMAP* tempimage = NULL;

ALLEGRO_FONT *font;
ALLEGRO_CONFIG *conf;

typedef enum { B_INIT, B_SELECTIVE, B_MAJOR, B_CORE }ActiveButton;
ActiveButton isActive = B_INIT;

object_t pushed_major;
object_t pushed_core;
object_t pushed_selective;

void printLecture(int index);
void initList();
static void toggle_button(ActiveButton active);

static void on_click_button_0();
static void on_click_button_selective();
static void on_click_button_major();
static void on_click_button_core();
static void on_click_button_scroll_up();
static void on_click_button_scroll_down();
static void on_click_reset();
static void on_click_finish();
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

char* getBlockImageAddr(int key);
int onListLecture[LIST_SIZE];
void arrangeLectureList(int selectedScroll);
void addTimeblockImage(int input, int isRegister);
void resetLectureList();
void deleteTimeblockImage(int input);
void popupHoney(int index);
void popupBomb(int index);
int estimateKLUE(lectureInfo target);
int canUseKlue; // 클루 사용 가능 여부
int colorArray[7]; // -1 미사용 index 사용중
int selectedLectureIndex;
int majorStart, majorEnd, coreStart, coreEnd, selectiveStart, selectiveEnd;
int grayblockNumber;
typedef enum _KLUElecture { KLUE_HONEY, KLUE_BOMB, KLUE_NORMAL } KLUElecture;
ALLEGRO_TIMER* sugang_timer;
ALLEGRO_EVENT_QUEUE* sugang_timer_event_queue;
int sugang_timer_set = 0;
float timeline_location = 0;
#define timeline Stack.objs[173]

int scene_2_init() {
	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	system("chcp 65001");
	printf("Scene 2 start!");

	canUseKlue = 1; // true
	selectedLectureIndex = -1;
	for (int i = 0; i < 7; i++) {
		colorArray[i] = -1;
	}

	object_t bg = create_object("Resources\\UI\\enroll\\background.jpg", 0, 0);
	Background = bg;

	font = al_load_font("Resources\\font\\BMDOHYEON.ttf", 36, 0);
	conf = al_load_config_file("Resources\\korean\\lecture_info_custom.ini");

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

	object_t n = create_object(NULL, 1020, 613);
	ui_set_text(&n, al_map_rgb(155, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, gradepoint_str, 30);
	Stack.push(&Stack, n); //stack 8

	object_t number = create_object(NULL, 1050, 615);
	ui_set_text(&number, al_map_rgb(155, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "credit"), 30);
	Stack.push(&Stack, number);//stack 9


	xmlParse(lectureTable);
	majorStart = majorEnd = coreStart = coreEnd = selectiveStart = selectiveEnd = -1;
	for (int i = 0; i < LECTURE_SIZE; i++) {
		if (majorStart == -1 && lectureTable[i].classify == MAJOR) {
			majorStart = i;
		}
		if (coreStart == -1 && lectureTable[i].classify == CORE) {
			coreStart = i;
		}
		if (selectiveStart == -1 && lectureTable[i].classify == SELECTIVE) {
			selectiveStart = i;
		}
		if (majorStart != -1 && lectureTable[i].classify == MAJOR) {
			majorEnd = i;
		}
		if (coreStart != -1 && lectureTable[i].classify == CORE) {
			coreEnd = i;
		}
		if (selectiveStart != -1 && lectureTable[i].classify == SELECTIVE) {
			selectiveEnd = i;
		}
	}
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
	ui_set_button(&upscroll_button);
	ui_set_on_click_listener(&upscroll_button, on_click_button_scroll_up);
	Stack.push(&Stack, upscroll_button);//stack 16

	object_t downscroll_button = create_object("Resources\\UI\\enroll\\b_scroll_down.jpg", 649, 383);
	ui_set_button(&downscroll_button);
	ui_set_on_click_listener(&downscroll_button, on_click_button_scroll_down);
	Stack.push(&Stack, downscroll_button); //stack 17


	initList(); //18 ~ 61
	int my_stackcounter_1 = 62;
	object_t listTextArray[11][5];;
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
	// lecture info screen
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

									  //------------------------------------------------
									  // timetable Block
									  //------------------------------------------------

	object_t timeBlockArray[5][9];
	for (int p = 0; p < 9; p++) { //123 ~ 167
		timeBlockArray[0][p] = create_object(NULL, 741, 37 + (p * 46));
		timeBlockArray[1][p] = create_object(NULL, 823, 37 + (p * 46));
		timeBlockArray[2][p] = create_object(NULL, 905, 37 + (p * 46));
		timeBlockArray[3][p] = create_object(NULL, 987, 37 + (p * 46));
		timeBlockArray[4][p] = create_object(NULL, 1069, 37 + (p * 46));

		Stack.push(&Stack, timeBlockArray[0][p]);
		Stack.push(&Stack, timeBlockArray[1][p]);
		Stack.push(&Stack, timeBlockArray[2][p]);
		Stack.push(&Stack, timeBlockArray[3][p]);
		Stack.push(&Stack, timeBlockArray[4][p]);
	}

	//------------------------------------------------
	// KLUE
	//------------------------------------------------

	object_t KlueHoneyPanel = create_object("Resources\\UI\\enroll\\popup_klue_honey.png", 679, 481);
	Stack.push(&Stack, KlueHoneyPanel); //168
	Stack.objs[168].enable = false;

	object_t KlueBombPanel = create_object("Resources\\UI\\enroll\\popup_klue_bomb.png", 679, 481);
	Stack.push(&Stack, KlueBombPanel); //169
	Stack.objs[169].enable = false;

	//------------------------------------------------
	// Big button
	//------------------------------------------------

	object_t Reset_button = create_object("Resources\\UI\\enroll\\b_reset.png", 1160, 254);
	ui_set_button(&Reset_button);
	ui_set_on_click_listener(&Reset_button, on_click_reset);
	Stack.push(&Stack, Reset_button); //170

	object_t Finish_button = create_object("Resources\\UI\\enroll\\b_finish.png", 1160, 365);
	ui_set_button(&Finish_button);
	ui_set_on_click_listener(&Finish_button, on_click_finish);
	Stack.push(&Stack, Finish_button); //171


									   //------------------------------------------------
									   // timer
									   //------------------------------------------------

	sugang_timer = al_create_timer(1.0 / 1000);
	sugang_timer_event_queue = al_create_event_queue();
	al_register_event_source(sugang_timer_event_queue, al_get_timer_event_source(sugang_timer));
	al_start_timer(sugang_timer);

	object_t bar_bg = create_colored_object(al_map_rgb(238, 238, 238), 1280, 17, 0, 0);
	Stack.push(&Stack, bar_bg); //172

	object_t red = create_colored_object(al_map_rgb(161, 20, 8), 0, 17, 0, 0);
	Stack.push(&Stack, red); //173

							 //------------------------------------------------
							 // KLUE Text
							 //------------------------------------------------

	object_t lecture_review = create_object(NULL, 908, 600);
	ui_set_text(&lecture_review, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_review); //174

	object_t lecture_Attdence = create_object(NULL, 908, 635);
	ui_set_text(&lecture_Attdence, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_Attdence); //175

	object_t lecture_Distance = create_object(NULL, 908, 670);
	ui_set_text(&lecture_Distance, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 25);
	Stack.push(&Stack, lecture_Distance); //176

	return 0;
}

int scene_2_update() {

	//Scene 2의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨

#define SUGANG_TIME 120.0
	if (al_get_timer_count(sugang_timer) - sugang_timer_set > 10) {
		sugang_timer_set = al_get_timer_count(sugang_timer);
		timeline_location += 1280 / (SUGANG_TIME * 100);
		timeline.rect.width = timeline_location + 5;
	}

	sprintf(gradepoint_str, "%d", mySchedule.credit);
	re_draw();
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
		selectedLectureIndex = -1;
		addLectureToSchedule(lectureTable, mySchedulePtr, input);
		addTimeblockImage(input, 1);
		break;

	case TIME_OVERLAP:
		printf("time overlapped. try again\n");
		break;

	case ALREADY_EXIST:
		selectedLectureIndex = -1;
		deleteLectureFromSchedule(lectureTable, mySchedulePtr, input);
		deleteTimeblockImage(input);
		break;

	default:
		break;
	}
}

void on_click_campus_map(void) {

}

void on_click_reset(void) {
	for (int i = 0; i < 7; i++) {
		if (colorArray[i] != -1) {
			selectedLectureIndex = -1;
			deleteLectureFromSchedule(lectureTable, mySchedulePtr, colorArray[i]);
			deleteTimeblockImage(colorArray[i]);
		}
	}
}

void on_click_finish(void) {
	load_scene(Scenes.scenes[3]);
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

void on_click_button_scroll_up() {
	int i = 0;
	int j = 0;
	int sw;
	int intv = 0;
	switch (isActive) {
	case B_MAJOR:
		sw = majorStart;
		break;
	case B_CORE:
		sw = coreStart;
		break;
	case B_SELECTIVE:
		sw = selectiveStart;
		break;
	default:
		sw = 0;
		break;
	}
	if (onListLecture[0] > sw) {
		for (i = onListLecture[0] - 1; i >= sw; i--) {
			if (lectureTable[i].classify == isActive) {
				intv++;
				if (intv == 11) { break; }
			}
		}
		if (intv == 11) {
			j = i;
		}
		else {
			j = i + 1;
		}
		i = 0;
		while (i < LIST_SIZE && j < LECTURE_SIZE) {
			if (lectureTable[j].classify == isActive) {
				onListLecture[i] = j;
				i++;
			}
			j++;
		}
		resetLectureList();
		selectedLectureIndex = -1;
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
			else {
				Stack.objs[p++].modifier.value.font_value.text = "";
				Stack.objs[p++].modifier.value.font_value.text = "";
				Stack.objs[p++].modifier.value.font_value.text = "";
				Stack.objs[p++].modifier.value.font_value.text = "";
				Stack.objs[p++].modifier.value.font_value.text = "";
			}


		}
	}
}

void on_click_button_scroll_down() {
	int i = 0;
	int j = 0;
	int sw;
	switch (isActive) {
	case B_MAJOR:
		sw = majorEnd;
		break;
	case B_CORE:
		sw = coreEnd;
		break;
	case B_SELECTIVE:
		sw = selectiveEnd;
		break;
	default:
		sw = 0;
		break;
	}
	if (onListLecture[10] != -1 && onListLecture[10] < sw) {
		j = onListLecture[10] + 1;
		for (int k = 0; k < LIST_SIZE; k++) {
			onListLecture[k] = -1;
		}
		while (i < LIST_SIZE && j <= sw) {
			if (lectureTable[j].classify == isActive) {
				onListLecture[i] = j;
				i++;
			}
			j++;
		}
		resetLectureList();
		selectedLectureIndex = -1;
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
			else {
				Stack.objs[p++].modifier.value.font_value.text = "";
				Stack.objs[p++].modifier.value.font_value.text = "";
				Stack.objs[p++].modifier.value.font_value.text = "";
				Stack.objs[p++].modifier.value.font_value.text = "";
				Stack.objs[p++].modifier.value.font_value.text = "";
			}
		}
	}
}

void addTimeblockImage(int input, int isRegister) { //시간표에 블록 모양 추가

	lectureInfo target = lectureTable[input];
	char blockString[200];
	char* blockString1;
	int chooseColor;
	if (isRegister == 1) {
		for (int i = 0; i < 7; i++) {
			if (colorArray[i] == -1) {
				colorArray[i] = input;
				chooseColor = i;
				break;
			}
		}
	}
	for (timeListPtr cur = target.lectureTime->next; cur != NULL; cur = cur->next) {
		whatDay dayofweek = cur->timeblock.dayofWeek;
		int peri = cur->timeblock.period;
		int intv = cur->timeblock.interval;
		int stackIndex = 123 + (5 * (peri - 1)) + dayofweek;
		object_t* obj = &Stack.objs[stackIndex];

		if (isRegister == 1) {
			int selectedColor = (10 * chooseColor) + intv;
			strcpy(blockString, getBlockImageAddr(selectedColor));
			//blockString = "Resources\\UI\\enroll\\table_1_gray.png";
			//printf("%d \n", strcmp(blockString, blockString1));
			if (obj->image != NULL) {
				al_destroy_bitmap(obj->image);
				obj->image = NULL;
			}
			obj->image = al_load_bitmap(blockString);
			obj->rect.width = al_get_bitmap_width(obj->image);
			obj->rect.height = al_get_bitmap_height(obj->image);
			obj->rect.left = obj->pos.x;
			obj->rect.top = obj->pos.y;
			while (grayblockNumber != 0) {
				if (Stack.counter > 0 && Stack.objs[Stack.counter - 1].image != NULL) {
					Stack.counter--;
					al_destroy_bitmap(Stack.objs[Stack.counter].image);
					grayblockNumber--;
				}
			}
			float textX = 781 + (82 * dayofweek);
			float textY = 50 + (46.4 * (peri - 1)) + (23 * (intv - 1));
			object_t blockText = create_object(NULL, textX, textY);
			ui_set_text(&blockText, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, al_get_config_value(conf, "room", target.identifyNumber), 17);
			Stack.push(&Stack, blockText);

		}
		else {
			object_t grayblock;
			char* addr;
			switch (intv) {
			case 1:
				addr = "Resources\\UI\\enroll\\table_1_gray.png";
				break;
			case 2:
				addr = "Resources\\UI\\enroll\\table_2_gray.png";
				break;
			case 3:
				addr = "Resources\\UI\\enroll\\table_3_gray.png";
				break;
			default:
				break;
			}
			grayblock = create_object(addr, obj->pos.x, obj->pos.y);
			Stack.push(&Stack, grayblock);
			grayblockNumber++;
		}
	}

}

void deleteTimeblockImage(int input) {
	lectureInfo target = lectureTable[input];
	int howManyLoop = 0;
	int i, k;
	for (timeListPtr cur = target.lectureTime->next; cur != NULL; cur = cur->next) {
		whatDay dayofweek = cur->timeblock.dayofWeek;
		int peri = cur->timeblock.period;
		int intv = cur->timeblock.interval;
		int stackIndex = 123 + (5 * (peri - 1)) + dayofweek;
		al_destroy_bitmap(Stack.objs[stackIndex].image);
		Stack.objs[stackIndex].image = NULL;
		float textX = 781 + (82 * dayofweek);
		float textY = 50 + (46.4 * (peri - 1)) + (23 * (intv - 1));
		i = Stack.counter - 1;
		while (i >= 0) {
			if (Stack.objs[i].pos.x - textX < 1 && Stack.objs[i].pos.x - textX > -1) {
				if (Stack.objs[i].pos.y - textY < 1 && Stack.objs[i].pos.y - textY > -1) {
					break;
				}
			}
			i--;
		}
		howManyLoop++;
	}
	for (k = i - (howManyLoop - 1); k + howManyLoop < Stack.counter; k++) {
		Stack.objs[k].modifier.value.font_value.text = Stack.objs[k + howManyLoop].modifier.value.font_value.text;
		Stack.objs[k].pos.x = Stack.objs[k + howManyLoop].pos.x;
		Stack.objs[k].pos.y = Stack.objs[k + howManyLoop].pos.y;
	}
	for (int i = k; i < Stack.counter; i++) {
		al_destroy_font(Stack.objs[i].modifier.value.font_value.font);
	}
	Stack.counter = k;
	for (int i = 0; i < 7; i++) {
		if (colorArray[i] == input) {
			colorArray[i] = -1;
		}
	}
}

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

void resetLectureList() { // List 색 초기화, 눌러보고 생긴 회색 블록 제거
	for (int k = 0; k < LIST_SIZE; k++) {
		Stack.objs[(4 * k) + 18].enable = true;
		Stack.objs[(4 * k) + 19].enable = false;
		Stack.objs[(4 * k) + 20].enable = false;
		Stack.objs[(4 * k) + 21].enable = false;
		if (onListLecture[k] >= 0 && canUseKlue == 1) {
			if (estimateKLUE(lectureTable[onListLecture[k]]) == KLUE_HONEY) {
				Stack.objs[(4 * k) + 18].enable = false;
				Stack.objs[(4 * k) + 19].enable = true;
			}
			else if (estimateKLUE(lectureTable[onListLecture[k]]) == KLUE_BOMB) {
				Stack.objs[(4 * k) + 18].enable = false;
				Stack.objs[(4 * k) + 20].enable = true;
			}
		}
	}
	if (selectedLectureIndex != -1) {
		while (grayblockNumber != 0) {
			if (Stack.counter > 0 && Stack.objs[Stack.counter - 1].image != NULL) {
				Stack.counter--;
				al_destroy_bitmap(Stack.objs[Stack.counter].image);
				grayblockNumber--;
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
	selectedLectureIndex = -1;
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
		else {
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
		lectureButton[i] = create_object("Resources\\UI\\enroll\\bar_normal_lecture.jpg", 92, 45 + ((i / 4) * 33));
		lectureButton[i + 1] = create_object("Resources\\UI\\enroll\\bar_honey_lecture.jpg", 92, 45 + ((i / 4) * 33));
		lectureButton[i + 2] = create_object("Resources\\UI\\enroll\\bar_bomb_lecture.jpg", 92, 45 + ((i / 4) * 33));
		lectureButton[i + 3] = create_object("Resources\\UI\\enroll\\bar_selected_lecture.jpg", 92, 45 + ((i / 4) * 33));
		ui_set_button(&lectureButton[i]);
		ui_set_button(&lectureButton[i + 1]);
		ui_set_button(&lectureButton[i + 2]);
		ui_set_button(&lectureButton[i + 3]);
		switch (i / 4)
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

/*

void printLecture(int index) {
lectureInfo lecture = lectureTable[index];

//y좌표 강의명460 | 시간/강의실 495 | 학수번호 530 | 이수구분 565 | 수업 방법 600 | 평가방법 670 (간격 35)
//lecture_name : 강의명

object_t lecture_name = create_object(NULL, 191, 460);
ui_set_text(&lecture_name, al_map_rgb(255, 255, 255), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "name", lecture.identifyNumber), 36);
Stack.push(&Stack, lecture_name);

//lecture_time : 시간/강의실
object_t lecture_time = create_object(NULL, 191, 495);
ui_set_text(&lecture_time, al_map_rgb(255, 255, 255), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "time", lecture.identifyNumber), 36);
Stack.push(&Stack, lecture_time);

//lecture_number : 학수번호
object_t lecture_number = create_object(NULL, 191, 530);
ui_set_text(&lecture_number, al_map_rgb(255, 255, 255), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "number", lecture.identifyNumber), 36);
Stack.push(&Stack, lecture_number);

//lecture_credit : 이수구분.학점
object_t lecture_credit = create_object(NULL, 191, 565);
ui_set_text(&lecture_credit, al_map_rgb(255, 255, 255), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "credit", lecture.identifyNumber), 36);
Stack.push(&Stack, lecture_credit);

//lecture_class : 수업 방법
object_t lecture_class = create_object(NULL, 191, 600);
ui_set_text(&lecture_class, al_map_rgb(255, 255, 255), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "class", lecture.identifyNumber), 36);
Stack.push(&Stack, lecture_class);

//lecture_eval : 평가 방법
object_t lecture_eval = create_object(NULL, 191, 670);
ui_set_text(&lecture_eval, al_map_rgb(255, 255, 255), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "eval", lecture.identifyNumber), 36);
Stack.push(&Stack, lecture_eval);


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
ui_set_text(&lecture_name, al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "COSE101"), 30);
Stack.push(&Stack, lecture_name);
printf("%s", al_get_config_value(conf, "korean", lecture.identifyNumber));


}

*/

static void on_click_lectureList_0() {
	if (protectOverlapClick == 0) {
		if (onListLecture[0] != -1) { // 만약 이 칸에 강의가 채워져 있다면
			resetLectureList();
			if (selectedLectureIndex == onListLecture[0]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[0];
			if (Stack.objs[18].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[19].enable == true) {
				popupHoney(0);
			}
			else if (Stack.objs[20].enable == true) {
				popupBomb(0);
			}
			Stack.objs[18].enable = false;
			Stack.objs[19].enable = false;
			Stack.objs[20].enable = false;
			Stack.objs[21].enable = true;
			printf("0 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[0]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[0], 0);
			}
			printLecture(0);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_1() {
	if (protectOverlapClick == 0) {
		if (onListLecture[1] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[1]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[1];
			if (Stack.objs[22].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[23].enable == true) {
				popupHoney(1);
			}
			else if (Stack.objs[24].enable == true) {
				popupBomb(1);
			}
			Stack.objs[22].enable = false;
			Stack.objs[23].enable = false;
			Stack.objs[24].enable = false;
			Stack.objs[25].enable = true;
			printf("1 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[1]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[1], 0);
			}
			printLecture(1);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_2() {
	if (protectOverlapClick == 0) {
		if (onListLecture[2] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[2]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[2];
			if (Stack.objs[26].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[27].enable == true) {
				popupHoney(2);
			}
			else if (Stack.objs[28].enable == true) {
				popupBomb(2);
			}
			Stack.objs[26].enable = false;
			Stack.objs[27].enable = false;
			Stack.objs[28].enable = false;
			Stack.objs[29].enable = true;
			printf("2 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[2]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[2], 0);
			}
			printLecture(2);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_3() {
	if (protectOverlapClick == 0) {
		if (onListLecture[3] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[3]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[3];
			if (Stack.objs[30].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[31].enable == true) {
				popupHoney(3);
			}
			else if (Stack.objs[32].enable == true) {
				popupBomb(3);
			}
			Stack.objs[30].enable = false;
			Stack.objs[31].enable = false;
			Stack.objs[32].enable = false;
			Stack.objs[33].enable = true;
			printf("3 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[3]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[3], 0);
			}
			printLecture(3);

		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_4() {
	if (protectOverlapClick == 0) {
		if (onListLecture[4] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[4]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[4];
			if (Stack.objs[34].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[35].enable == true) {
				popupHoney(4);
			}
			else if (Stack.objs[36].enable == true) {
				popupBomb(4);
			}
			Stack.objs[34].enable = false;
			Stack.objs[35].enable = false;
			Stack.objs[36].enable = false;
			Stack.objs[37].enable = true;
			printf("4 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[4]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[4], 0);
			}
			printLecture(4);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_5() {
	if (protectOverlapClick == 0) {
		if (onListLecture[5] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[5]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[5];
			if (Stack.objs[38].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[39].enable == true) {
				popupHoney(5);
			}
			else if (Stack.objs[40].enable == true) {
				popupBomb(5);
			}
			Stack.objs[38].enable = false;
			Stack.objs[39].enable = false;
			Stack.objs[40].enable = false;
			Stack.objs[41].enable = true;
			printf("5 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[5]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[5], 0);
			}
			printLecture(5);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_6() {
	if (protectOverlapClick == 0) {
		if (onListLecture[6] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[6]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[6];
			if (Stack.objs[42].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[43].enable == true) {
				popupHoney(6);
			}
			else if (Stack.objs[44].enable == true) {
				popupBomb(6);
			}
			Stack.objs[42].enable = false;
			Stack.objs[43].enable = false;
			Stack.objs[44].enable = false;
			Stack.objs[45].enable = true;
			printf("6 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[6]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[6], 0);
			}
			printLecture(6);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_7() {
	if (protectOverlapClick == 0) {
		if (onListLecture[7] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[7]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[7];
			if (Stack.objs[46].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[47].enable == true) {
				popupHoney(7);
			}
			else if (Stack.objs[48].enable == true) {
				popupBomb(7);
			}
			Stack.objs[46].enable = false;
			Stack.objs[47].enable = false;
			Stack.objs[48].enable = false;
			Stack.objs[49].enable = true;
			printf("7 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[7]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[7], 0);
			}
			printLecture(7);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_8() {
	if (protectOverlapClick == 0) {
		if (onListLecture[8] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[8]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[8];
			if (Stack.objs[50].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[51].enable == true) {
				popupHoney(8);
			}
			else if (Stack.objs[52].enable == true) {
				popupBomb(8);
			}
			Stack.objs[50].enable = false;
			Stack.objs[51].enable = false;
			Stack.objs[52].enable = false;
			Stack.objs[53].enable = true;
			printf("8 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[8]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[8], 0);
			}
			printLecture(8);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_9() {
	if (protectOverlapClick == 0) {
		if (onListLecture[9] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[9]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[9];
			if (Stack.objs[54].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[55].enable == true) {
				popupHoney(9);
			}
			else if (Stack.objs[56].enable == true) {
				popupBomb(9);
			}
			Stack.objs[54].enable = false;
			Stack.objs[55].enable = false;
			Stack.objs[56].enable = false;
			Stack.objs[57].enable = true;
			printf("9 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[9]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[9], 0);
			}
			printLecture(9);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
static void on_click_lectureList_10() {
	if (protectOverlapClick == 0) {
		if (onListLecture[10] != -1) {
			resetLectureList();
			if (selectedLectureIndex == onListLecture[10]) {
				protectOverlapClick = 0;
			}
			else {
				protectOverlapClick = 1;
			}
			selectedLectureIndex = onListLecture[10];
			if (Stack.objs[58].enable == true) {
				Stack.objs[168].enable = Stack.objs[169].enable = false;
				Stack.objs[174].modifier.value.font_value.text = "";
				Stack.objs[175].modifier.value.font_value.text = "";
				Stack.objs[176].modifier.value.font_value.text = "";
			}
			else if (Stack.objs[59].enable == true) {
				popupHoney(10);
			}
			else if (Stack.objs[60].enable == true) {
				popupBomb(10);
			}
			Stack.objs[58].enable = false;
			Stack.objs[59].enable = false;
			Stack.objs[60].enable = false;
			Stack.objs[61].enable = true;
			printf("10 call \n");
			int k = 1;
			for (int i = 0; i < 7; i++) {
				if (colorArray[i] == onListLecture[10]) { k = 0; break; }
			}
			if (k == 1) {
				addTimeblockImage(onListLecture[10], 0);
			}
			printLecture(10);
		}
	}
	else {
		protectOverlapClick = 0;
	}
}
void popupHoney(int index) {
	Stack.objs[169].enable = false;
	Stack.objs[168].enable = true;
	lectureInfo target = lectureTable[onListLecture[index]];
	Stack.objs[174].modifier.value.font_value.text = al_get_config_value(conf, "rating", target.identifyNumber);
	Stack.objs[175].modifier.value.font_value.text = al_get_config_value(conf, "Attendance", target.identifyNumber);
	Stack.objs[176].modifier.value.font_value.text = al_get_config_value(conf, "distance", target.identifyNumber);
}

void popupBomb(int index) {
	Stack.objs[168].enable = false;
	Stack.objs[169].enable = true;
	lectureInfo target = lectureTable[onListLecture[index]];
	Stack.objs[174].modifier.value.font_value.text = al_get_config_value(conf, "rating", target.identifyNumber);
	Stack.objs[175].modifier.value.font_value.text = al_get_config_value(conf, "Attendance", target.identifyNumber);
	Stack.objs[176].modifier.value.font_value.text = al_get_config_value(conf, "distance", target.identifyNumber);
}
char* getBlockImageAddr(int key) {
	char buf[200];
	int cx1;
	int cx2;
	cx1 = snprintf(buf, 200, "Resources\\UI\\enroll\\table_");
	switch (key % 10) {
	case 1:
		cx2 = snprintf(buf + cx1, 200 - cx1, "1_");
		break;
	case 2:
		cx2 = snprintf(buf + cx1, 200 - cx1, "2_");
		break;
	case 3:
		cx2 = snprintf(buf + cx1, 200 - cx1, "3_");
		break;
	default:
		break;
	}
	switch (key / 10) {
	case 0:
		snprintf(buf + cx1 + cx2, 200 - cx1 - cx2, "blue.png");
		break;
	case 1:
		snprintf(buf + cx1 + cx2, 200 - cx1 - cx2, "cyan.png");
		break;
	case 2:
		snprintf(buf + cx1 + cx2, 200 - cx1 - cx2, "green.png");
		break;
	case 3:
		snprintf(buf + cx1 + cx2, 200 - cx1 - cx2, "pink.png");
		break;
	case 4:
		snprintf(buf + cx1 + cx2, 200 - cx1 - cx2, "purple.png");
		break;
	case 5:
		snprintf(buf + cx1 + cx2, 200 - cx1 - cx2, "red.png");
		break;
	case 6:
		snprintf(buf + cx1 + cx2, 200 - cx1 - cx2, "yellow.png");
		break;
	case 9:
		snprintf(buf + cx1 + cx2, 200 - cx1 - cx2, "gray.png");
		break;
	default:
		break;
	}
	return buf;
}
int estimateKLUE(lectureInfo target) {
	if (target.klueRating == RATING_GOOD || target.klueRating == RATING_VGOOD) {
		if (target.Att == ATT_LOOSE || target.Att == ATT_VLOOSE) {
			if (target.distance < 10) {
				return KLUE_HONEY;
			}
		}
	}
	else if (target.Att == ATT_TIGHT || target.Att == ATT_VTIGHT) {
		if (target.distance > 15) {
			return KLUE_BOMB;
		}
	}
	return KLUE_NORMAL;
}