#pragma once
#include "engine.h"
#include "data.h"
#include "graph_manage.h"
#include "event_semester.h"
// ------------------------------------
// Timer variable declaration
// ------------------------------------
ALLEGRO_TIMER* maingame_timer;
int maingame_timer_set = 0;
float timebar_width = 0;
int second_per_day[5] = { 0, };
whatDay today_of_week; // 오늘의 요일
void calculate_second_per_day();
void test_custom_schedule();
schedule customSchedule; // to test

// ------------------------------------
// event variable declaration
// ------------------------------------
event_function stochastic_event_func[STO_EVENTCOUNT];
event_function sequencial_event_func[SEQ_EVENTCOUNT];

void selected1(object_t *o);
void selected2(object_t *o);
bool ongoing1 = false, ongoing2 = false;
bool isSet = false;
int moving = 0;
int count = 0;
int current_state;
Graph_structure* myGraph;

ALLEGRO_MOUSE_STATE state;

object_t* map_button;
object_t** map_button_ptr = &map_button;
object_t* map = NULL;
bool clicked_mouse = false;
bool move_map = false;
int pre_x = 0, pre_y = 0;
int pre_mouse_x = 0, pre_mouse_y = 0;
//int map_button_startnum = 0;

Coord_2D start_point, end_point;

double nowx, nowy;
double x_velocity, y_velocity;

ALLEGRO_TIMER *timer;
int chr_timer_set = 0;
ALLEGRO_EVENT_QUEUE *event_queue;

object_t player[4];

int scene_4_init() {

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	int i;

	printf("Scene 4 start! \n");

	object_t bg = create_object("Resources\\UI\\routegame\\bg.png", 0, 0);
	Background = bg;

	Stack.push(&Stack, create_object("Resources\\UI\\routegame\\map.jpg", 0, 0));
	map = &Stack.objs[Stack.counter - 1];


	// ------------------------------------
	// Timebar UI setting
	// ------------------------------------

	maingame_timer = al_create_timer(1.0 / 1000);
	al_start_timer(maingame_timer);

	object_t bar_bg = create_colored_object(al_map_rgb(238, 238, 238), 1280, 17, 0, 0);
	Stack.push(&Stack, bar_bg); //1

	object_t red = create_colored_object(al_map_rgb(161, 20, 8), 0, 17, 0, 0);
	Stack.push(&Stack, red); //2

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
	} // 3 4 5 6

#define CHARACTER 3
	current_state = CHARACTER + 1;
	Stack.objs[current_state].enable = true;
	/*
	object_t route1 = create_object("Resources\\UI\\routegame\\route1.png", 100, 100);
	ui_set_button(&route1);
	ui_set_on_click_listener(&route1, selected1);
	Stack.push(&Stack, route1); // 7
	object_t route2 = create_object("Resources\\UI\\routegame\\route2.png", 100, 200);
	ui_set_button(&route2);
	ui_set_on_click_listener(&route2, selected2);
	Stack.push(&Stack, route2); // 8
	*/
	// ------------------------------------
	// graph structure setting
	// ------------------------------------

	myGraph = (Graph_structure*)malloc(sizeof(Graph_structure));
	parse_graph(myGraph);
	register_button_to_vertex(myGraph, map_button_ptr); // 9 ~ vertex캣수만큼 오름

	// ------------------------------------
	// graph test
	// ------------------------------------
	//print_graph(myGraph);

	timer = al_create_timer(1.0 / 1000);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	start_point.x = 100;
	start_point.y = 150;

	// ------------------------------------
	// event setting
	// ------------------------------------
	init_event(stochastic_event_func, sequencial_event_func);
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
		x_velocity = (double)(end_point.x - start_point.x) / FPS; //FPS조절하여 캐릭터 속도 조절
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
	//Scene 0의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨

	// ------------------------------------
	// Timebar running
	// ------------------------------------
	
	if (al_get_timer_count(maingame_timer) - maingame_timer_set > 10) {
		maingame_timer_set = al_get_timer_count(maingame_timer);
		timebar_width += 1280 / (second_per_day[today_of_week] * 100.0);
		Stack.objs[2].rect.width = timebar_width + 5;
	}
	
	if (Stack.objs[2].rect.width > 1280) {
		if (today_of_week == FRI) {
			today_of_week = MON;
		}
		else {
			today_of_week++;
		}
		timebar_width = 0;
		Stack.objs[2].rect.width = 0;
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

	//--------------------------//
	//map moving setting By hasu//
	//--------------------------//
	
	al_get_mouse_state(&state);
	if (al_mouse_button_down(&state, 1)) // if mouse is pushed !! 
	{
		al_get_mouse_state(&state);
		int x = state.x;
		int y = state.y;

		(*map).pos.x += (x - pre_mouse_x);
		(*map).pos.y += (y - pre_mouse_y);

		pre_mouse_x = x;
		pre_mouse_y = y;

		for (int i = 0; i < myGraph->Num_of_Vertex; i++)
		{
			map_button[i].pos.x += (x - pre_mouse_x);
			map_button[i].pos.y += (y - pre_mouse_y);
		}
	}
	else
	{
		pre_mouse_x = state.x;
		pre_mouse_y = state.y;
	}
	

	re_draw();

	return 0;
}

int scene_4_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.
	free_graph_structure(myGraph);
	free(myGraph);
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
/*
void selected1(object_t *o)
{
	ongoing1 = true;
}

void selected2(object_t *o)
{
	ongoing2 = true;
}
*/