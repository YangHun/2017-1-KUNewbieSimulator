#pragma once
#include "engine.h"
#include "data.h"
// ------------------------------------
// Timer variable declaration
// ------------------------------------
ALLEGRO_TIMER* maingame_timer;
int maingame_timer_set = 0;
float timebar_width = 0;
int second_per_day[5] = { 0, };
whatDay today_of_week; // ������ ����
void calculate_second_per_day();
void test_custom_schedule();
schedule customSchedule; // to test

void selected1();
void selected2();
bool ongoing1 = false, ongoing2 = false;
bool isSet = false;
int moving = 0;
int count = 0;
int current_state;

struct pos {
	int x, y;
}start_point, end_point;

double nowx, nowy;
double x_velocity, y_velocity;

ALLEGRO_TIMER *timer;
int chr_timer_set = 0;
ALLEGRO_EVENT_QUEUE *event_queue;

object_t player[4];

int scene_4_init() {

	//�ش� ���� ���۵� ��, �� �� �� ����Ǵ� �Լ�
	int i;

	printf("Scene 4 start! \n");

	object_t map = create_object("Resources\\UI\\routegame\\campus_map.jpg", 0, 0);
	Background = map;


	// ------------------------------------
	// Timebar UI setting
	// ------------------------------------

	maingame_timer = al_create_timer(1.0 / 1000);
	al_start_timer(maingame_timer);

	object_t bar_bg = create_colored_object(al_map_rgb(238, 238, 238), 1280, 17, 0, 0);
	Stack.push(&Stack, bar_bg); //0

	object_t red = create_colored_object(al_map_rgb(161, 20, 8), 0, 17, 0, 0);
	Stack.push(&Stack, red); //1

	// ------------------------------------
	// initial setting
	// ------------------------------------
	today_of_week = MON;
	test_custom_schedule();

	player[0] = create_object("Resources\\UI\\routegame\\move.png", 100, 150);
	player[1] = create_object("Resources\\UI\\routegame\\1.png", 100, 150);
	player[2] = create_object("Resources\\UI\\routegame\\2.png", 100, 150);
	player[3] = create_object("Resources\\UI\\routegame\\3.png", 100, 150);
	for (i = 0; i < 4; i++) {
		player[i].enable = false;
		Stack.push(&Stack, player[i]);
	}
#define CHARACTER 2
	current_state = CHARACTER + 1;
	Stack.objs[current_state].enable = true;

	object_t route1 = create_object("Resources\\UI\\routegame\\route1.png", 100, 100);
	ui_set_button(&route1);
	ui_set_on_click_listener(&route1, selected1);
	Stack.push(&Stack, route1);
	object_t route2 = create_object("Resources\\UI\\routegame\\route2.png", 100, 200);
	ui_set_button(&route2);
	ui_set_on_click_listener(&route2, selected2);
	Stack.push(&Stack, route2);

	timer = al_create_timer(1.0 / 1000);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	start_point.x = 100;
	start_point.y = 150;

	return 0;
}

static double FPS = 100.0;
void setting()
{
	Stack.objs[current_state].enable = false;
	current_state = CHARACTER;
	Stack.objs[current_state].enable = true;
	nowx = start_point.x;
	nowy = start_point.y;
	if (ongoing1) {
		end_point.x = 190;
		end_point.y = 100;
		x_velocity = (double)(end_point.x - start_point.x) / FPS; //FPS�����Ͽ� ĳ���� �ӵ� ����
		y_velocity = (double)(end_point.y - start_point.y) / FPS;
	}
	else {
		end_point.x = 190;
		end_point.y = 200;
		x_velocity = (double)(end_point.x - start_point.x) / FPS;
		y_velocity = (double)(end_point.y - start_point.y) / FPS;
	}
}

int scene_4_update() {

	int i;
	//Scene 0�� Main��
	//while�� �ȿ� �ִ� --> �� frame���� �����

	// ------------------------------------
	// Timebar running
	// ------------------------------------
	
	if (al_get_timer_count(maingame_timer) - maingame_timer_set > 10) {
		maingame_timer_set = al_get_timer_count(maingame_timer);
		timebar_width += 1280 / (second_per_day[today_of_week] * 100.0);
		printf("%f\n", timebar_width);
		Stack.objs[1].rect.width = timebar_width + 5;
	}
	
	if (Stack.objs[1].rect.width > 1280) {
		if (today_of_week == FRI) {
			today_of_week = MON;
		}
		else {
			today_of_week++;
		}
		timebar_width = 0;
		Stack.objs[1].rect.width = 0;
		maingame_timer_set = 0;

		al_stop_timer(maingame_timer);
		al_start_timer(maingame_timer);
	}

	if (!ongoing1 && !ongoing2) {
		if (al_get_timer_count(timer) - chr_timer_set>500) {
			chr_timer_set = al_get_timer_count(timer);
			Stack.objs[current_state].enable = false;
			current_state = CHARACTER + rand() % 3 + 1;
			Stack.objs[current_state].enable = true;
		}
	}
	else {
		if (!isSet) {
			isSet = true;
			setting();
		}

		if (count == FPS) {
			printf("reach the destination\n");
			ongoing1 = false;
			ongoing2 = false;
			for (i = 0; i < 4; i++) {
				Stack.objs[CHARACTER + i].pos.x = end_point.x;
				Stack.objs[CHARACTER + i].pos.y = end_point.y;
			}
			count = 0;
			isSet = false;
		}

		for (i = 0; i < 4; i++) {
			Stack.objs[CHARACTER + i].pos.x += x_velocity;
			Stack.objs[CHARACTER + i].pos.y += y_velocity;
		}
		count++;
	}

	re_draw();

	return 0;
}

int scene_4_fin() {

	// �� ������ �ٸ� ������ �Ѿ ��, �� �� ����Ǵ� �Լ�.
	Stack.clear(&Stack);
	al_destroy_timer(timer);

	printf("counter : %d \n", Stack.counter);

	return 0;
}

void calculate_second_per_day() {
	int lecture_cursor = -1;
	int num_of_lecture = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			if (customSchedule.timeTable[i][j].isEmptyBit == EMPTY && lecture_cursor != -1) {
				num_of_lecture++; 
				lecture_cursor = -1;
			}
			else {
				if (lecture_cursor != customSchedule.timeTable[i][j].index) {
					num_of_lecture++;
					lecture_cursor = customSchedule.timeTable[i][j].index;
				}
			}
		}

		second_per_day[i] = (int)(((9 - num_of_lecture) * 20) + (num_of_lecture * 0.5) + 4.5);
		num_of_lecture = 0;
		lecture_cursor = -1;
	}
}
void test_custom_schedule() { // to test
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			customSchedule.timeTable[i][j].isEmptyBit = EMPTY;
			customSchedule.timeTable[i][j].index = -1;
		}
	}
	customSchedule.timeTable[0][0].index = 0;
	customSchedule.timeTable[0][0].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][1].index = 1;
	customSchedule.timeTable[0][1].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][2].index = 2;
	customSchedule.timeTable[0][2].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][3].index = 3;
	customSchedule.timeTable[0][3].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][4].index = 4;
	customSchedule.timeTable[0][4].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][5].index = 5;
	customSchedule.timeTable[0][5].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][6].index = 6;
	customSchedule.timeTable[0][6].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][7].index = 7;
	customSchedule.timeTable[0][7].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][8].index = 8;
	customSchedule.timeTable[0][8].isEmptyBit = NONEMPTY;
	calculate_second_per_day();

	printf("%d %d %d %d %d \n", second_per_day[0], second_per_day[1], second_per_day[2], second_per_day[3], second_per_day[4]);
}

void selected1()
{
	ongoing1 = true;
}

void selected2()
{
	ongoing2 = true;
}