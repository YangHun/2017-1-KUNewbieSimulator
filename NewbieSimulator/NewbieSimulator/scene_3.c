#pragma once
#include "engine.h"
#include "data.h"
#include "manageTimetable.h"
#include "audio.h"

ALLEGRO_CONFIG *conf;
ALLEGRO_CONFIG *conf2;
ALLEGRO_FONT *font;
ALLEGRO_TIMER *click_timer;
ALLEGRO_EVENT_QUEUE *click_event;

bool wait = false;	//시작전 대기화면
bool counting_start = false;	//초시계 시작
bool timer_started = false;	//타이머 시작
bool game_start = false;	//수강신청 시작
bool pressed[6];
bool success[6];
bool renew_timer_text = false;
bool lecturerepeat;
bool is_result = true;

int timer_text_count;
int lectureindex[6];

void on_click_startbt(object_t *o);
void pressed1(object_t *o);
void pressed2(object_t *o);
void pressed3(object_t *o);
void pressed4(object_t *o);
void pressed5(object_t *o);
void pressed6(object_t *o);
void result();

void reSchedule(void);

double std_dist(int t, int d);
bool probability_judge(double p);
void display_timer(void);
void displayresult(void);

void play_clock_sound_if_not_playing();

int pressed_time[6];

static int netfunnel_object_index;

int scene_3_init() {
	srand(time(NULL));
	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	int i, j, x;
	int k = 0;
	int lectureid;

	printf("Scene 3 start! \n");

	srand(time(NULL));

	object_t bg = create_object("Resources\\UI\\enroll_2\\background.jpg", 0, 0);
	Background = bg;
	for (i = 0; i < 6; i++) {
		lectureindex[i] = -1;
	}

	conf = al_load_config_file("Resources\\korean\\enroll_2.ini");
	conf2 = al_load_config_file("Resources\\korean\\lecture_info.ini");
	click_timer = al_create_timer(1.0 / 1000);
	click_event = al_create_event_queue();
	al_register_event_source(click_event, al_get_timer_event_source(click_timer));
	
	object_t navy_red = create_colored_object(al_map_rgb(255, 255, 255), 681, 679, 41, 0);
	Stack.push(&Stack, navy_red);
#define NAVY_RED Stack.objs[0]

	object_t navy_white = create_colored_object(al_map_rgb(255, 255, 255), 465, 75, 335, 0);
	Stack.push(&Stack, navy_white);
	
	object_t bt[6];	//신청버튼 출력
	for (i = 0; i < 6; i++)
		bt[i] = create_object("Resources\\UI\\enroll_2\\b_apply.png", 741, 235 + 74 * i);
	

	for (i = 0; i < 6; i++) {
		ui_set_button(&bt[i]);
		pressed[i] = false;
		success[i] = false;
	}

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			lecturerepeat = false;
			if (mySchedule.timeTable[i][j].isEmptyBit == NONEMPTY) {
				lectureid = mySchedule.timeTable[i][j].index;
				for (x = 0; x < 6; x++) {
					if (lectureid == lectureindex[x])
						lecturerepeat = true;
				}
				if(lecturerepeat == false)
					lectureindex[k++] = lectureid;
			}
		}
	}
	ui_set_on_click_listener(&bt[0], pressed1);
	ui_set_on_click_listener(&bt[1], pressed2);
	ui_set_on_click_listener(&bt[2], pressed3);
	ui_set_on_click_listener(&bt[3], pressed4);
	ui_set_on_click_listener(&bt[4], pressed5);
	ui_set_on_click_listener(&bt[5], pressed6);

	//과목이름 출력
	object_t lecture[6];
	for (i = 0; i < 6; i++) {
		lecture[i] = create_object(NULL, 850, 240 + i * 75);
		if (lectureindex[i] == -1)
			ui_set_text(&lecture[i], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 36);
		else
			ui_set_text(&lecture[i], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf2, "name", lectureTable[lectureindex[i]].identifyNumber), 36);
		Stack.push(&Stack, bt[i]);
	}

	for (i = 0; i < 6; i++) {
		Stack.push(&Stack, lecture[i]);
	}

	object_t navyism = create_object("Resources\\UI\\enroll_2\\navyism_background_edit.png", 0, 0);
	Stack.push(&Stack, navyism);

	object_t first_text = create_object(NULL, 0, 327);
	ui_set_text(&first_text, al_map_rgb(255, 104, 27), "Resources\\font\\malgun.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "time_0"), 64);
	Stack.push(&Stack, first_text);
#define TEXT_FIRST Stack.objs[15]
	
	object_t before_start = create_object("Resources\\UI\\enroll_2\\before_start.png", 0, 0);
	Stack.push(&Stack, before_start);
#define BEFORE_START Stack.objs[16]

	object_t start_bt = create_object("Resources\\UI\\enroll_2\\b_start.png", 500, 500);
	ui_set_button(&start_bt);
	ui_set_on_click_listener(&start_bt, on_click_startbt);
	Stack.push(&Stack, start_bt);
#define START_BT Stack.objs[17]

	netfunnel_object_index = Stack.counter;
	object_t netfunnel_obj = create_object("Resources\\UI\\enroll_2\\netfunnel.png", 0, 0);
	netfunnel_obj.blocks = true;
	netfunnel_obj.enable = false;
	Stack.push(&Stack, netfunnel_obj);

	play_audiosample(3, true);

	return 0;
}

int scene_3_update() {
	//Scene 0의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
	int i;
	
	if (counting_start) {
		if (!timer_started) {	//타이머 작동
			timer_started = true;
			al_start_timer(click_timer);
		}

		//시작전 초시계 구현
		//

#define GAMESTART_COUNT 10
		if (!game_start && al_get_timer_count(click_timer) > (GAMESTART_COUNT * 1000)) { //10초지나면 수강신청 열림
			game_start = true;

			stop_audiosample(3);
		}
		else if (game_start && al_get_timer_count(click_timer) > (GAMESTART_COUNT * 1500)) {
			if (is_result)
			{
				object_t *netfunnel_obj = &Stack.objs[netfunnel_object_index];
				netfunnel_obj->enable = false;
				result();
			}
		}

		if (game_start && al_get_timer_count(click_timer) > (GAMESTART_COUNT * 2000)) {

			load_scene(Scenes.scenes[4]);
		}
	}

	if (!game_start && al_get_timer_count(click_timer) > (865)) {
		play_clock_sound_if_not_playing();
	}

	display_timer();

	re_draw();

	return 0;
}

void on_click_startbt(object_t *o) {
	play_audiosample(0, false);

	if (counting_start)
		return;
	
	BEFORE_START.enable = false;
	START_BT.enable = false;

	counting_start = true;
}

void pressed1(object_t *o) {
	play_audiosample(0, false);

	if (!game_start || pressed[0]) return; //수강신청 안열렸으면 의미없음
	printf("pressed!");

	pressed[0] = true;
	pressed_time[0] = al_get_timer_count(click_timer);

	if (pressed[0] && pressed[1] && pressed[2] && pressed[3] && pressed[4] && pressed[5])
	{
		object_t *netfunnel_obj = &Stack.objs[netfunnel_object_index];
		netfunnel_obj->enable = true;
		re_draw();
	}
}

void pressed2(object_t *o) {
	play_audiosample(0, false);

	if (!game_start || pressed[1]) return;
	pressed[1] = true;
	pressed_time[1] = al_get_timer_count(click_timer);

	if (pressed[0] && pressed[1] && pressed[2] && pressed[3] && pressed[4] && pressed[5])
	{
		object_t *netfunnel_obj = &Stack.objs[netfunnel_object_index];
		netfunnel_obj->enable = true;
		re_draw();
	}
}

void pressed3(object_t *o) {
	play_audiosample(0, false);

	if (!game_start || pressed[2]) return;
	pressed[2] = true;
	pressed_time[2] = al_get_timer_count(click_timer);

	if (pressed[0] && pressed[1] && pressed[2] && pressed[3] && pressed[4] && pressed[5])
	{
		object_t *netfunnel_obj = &Stack.objs[netfunnel_object_index];
		netfunnel_obj->enable = true;
		re_draw();
	}
}

void pressed4(object_t *o) {
	play_audiosample(0, false);

	if (!game_start || pressed[3]) return;
	pressed[3] = true;
	pressed_time[3] = al_get_timer_count(click_timer);

	if (pressed[0] && pressed[1] && pressed[2] && pressed[3] && pressed[4] && pressed[5])
	{
		object_t *netfunnel_obj = &Stack.objs[netfunnel_object_index];
		netfunnel_obj->enable = true;
		re_draw();
	}
}

void pressed5(object_t *o) {
	play_audiosample(0, false);

	if (!game_start || pressed[4]) return;
	pressed[4] = true;
	pressed_time[4] = al_get_timer_count(click_timer);

	if (pressed[0] && pressed[1] && pressed[2] && pressed[3] && pressed[4] && pressed[5])
	{
		object_t *netfunnel_obj = &Stack.objs[netfunnel_object_index];
		netfunnel_obj->enable = true;
		re_draw();
	}
}

void pressed6(object_t *o) {
	play_audiosample(0, false);

	if (!game_start || pressed[5]) return;
	pressed[5] = true;
	pressed_time[5] = al_get_timer_count(click_timer);

	if (pressed[0] && pressed[1] && pressed[2] && pressed[3] && pressed[4] && pressed[5])
	{
		object_t *netfunnel_obj = &Stack.objs[netfunnel_object_index];
		netfunnel_obj->enable = true;
		re_draw();
	}
}

void result() {
	int i;
	printSchedule(mySchedule);
	for (i = 0; i < 6; i++) {
		if (!pressed[i]) {
			continue;
		}
		if (lectureTable[lectureindex[i]].classify == MAJOR) {
			success[i] = true;
		}
		else if (probability_judge(std_dist(pressed_time[i], 2))) {
			printf("[%d]time: %d\n",i, pressed_time[i]);
			printf("prob: %lf\n", std_dist(pressed_time[i], 2));
			printf("[%d]success!!\n", i);
			success[i] = true;
		}
		else {
			printf("[%d]time: %d\n", i, pressed_time[i]);
			printf("prob: %lf\n", std_dist(pressed_time[i], 2));
			printf("[%d]fail!!\n", i);
			success[i] = false;
		}
	}
	for (i = 0; i < 6; i++) {
		if (success[i] == false && lectureindex[i] != -1) {
			deleteLectureFromSchedule(lectureTable, mySchedulePtr, lectureindex[i]);
			lectureindex[i] = -1;
		}
	}
	printSchedule(mySchedule);
	displayresult();
	reSchedule();

	is_result = false;
}

void reSchedule() {
	int i, j;
	int newindex = 0;

	for (i = 0; i < 6; i++) {
		if (lectureindex[i] == -1) {
			for (j = 0; j < LECTURE_SIZE && lectureTable[newindex].klueRating != RATING_VBAD; j++) {
				newindex = j;
				if (analyzeSchedule(lectureTable, mySchedule, newindex) == NO_OVERLAP) {
					addLectureToSchedule(lectureTable, mySchedulePtr, newindex);
					break;
				}
			}			
		}
	}

	printSchedule(mySchedule);
}

double std_dist(int t, int d) { //standard_distribution
// t: timer tick, d: difficulty : 수강신청 난이도
//수강신청 난이도: 1:어려움 2:보통 3:쉬움

	double p;
	double sigma = 0.5 * d;
	double z = ((double)t - 10000) / 1000 / sigma;

	p = 1 - ((double)1 / 2 * z*z) + ((double)1 / 8 * z*z*z*z) - ((double)1 / 48 * z*z*z*z*z*z) + 
		((double)1 / 384 * z*z*z*z*z*z*z*z) - ((double)1 / 3840 * z*z*z*z*z*z*z*z*z*z); //taylor series

	return p;
}

bool probability_judge(double p) {
	int result = rand() % 10000;
	int range = p * 10000;

	if (result < range)
		return true;
	else
		return false;
}

void display_timer(void) {
	int count = al_get_timer_count(click_timer) / 1000;
	if (timer_text_count < count) {
		timer_text_count = count;
		renew_timer_text = true;
	} 

	if (count == 1 && renew_timer_text) {
		TEXT_FIRST.enable = false;
		object_t text = create_object(NULL, 0, 327);
		ui_set_text(&text, al_map_rgb(255, 104, 27), "Resources\\font\\malgun.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", "time_1"), 64);
		Stack.push(&Stack, text);
	}
	if (count > 1 && count < 16 && renew_timer_text) {
		char string[8];
		sprintf(string, "time_%d", count);
		printf(">%s<\n", string);

		Stack.pull(&Stack);
		object_t text = create_object(NULL, 0, 327);
		ui_set_text(&text, al_map_rgb(255, 104, 27), "Resources\\font\\malgun.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf, "korean", string), 64);
		Stack.push(&Stack, text);
	}
	if (renew_timer_text) {
		if (count < 10 && count > 1)
			NAVY_RED.color = al_map_rgb(255, 255 - 35 * (count-2), 255 - 35 * (count-2));
		else
			NAVY_RED.color = al_map_rgb(255, 255, 255);
	}
	

	renew_timer_text = false;
}

void displayresult(void) {
	int i = 0;
	object_t fin[6];

	for (i = 0; i < 6; i++) {
		if (success[i] == true)
			Stack.objs[2 + i].image = al_load_bitmap("Resources\\UI\\enroll_2\\pass.jpg");
		else
			Stack.objs[2 + i].image = al_load_bitmap("Resources\\UI\\enroll_2\\fail.jpg");
	}

}

void play_clock_sound_if_not_playing() {
	static bool playing = false;
	if (!playing) {
		playing = true;
		play_audiosample(1, false);
	}
}

int scene_3_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.
	Stack.clear(&Stack);

	printf("counter : %d \n", Stack.counter);

	return 0;
}



