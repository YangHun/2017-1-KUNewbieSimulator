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
void init_schedule_data();
void map_button_on_click_listener_func(object_t *o);
void move(int *pdx, int *pdy);
int today_Month;
int today_day;
int week_count;
void stat_update();
int timebar_object_starting;
schedule customSchedule; // to test
//-> use "mySchedule" !!!

// ------------------------------------
// event variable declaration
// ------------------------------------
event_function stochastic_event_func[STO_EVENTCOUNT];
event_function sequencial_event_func[SEQ_EVENTCOUNT];
event_function special_event_func[SPE_EVENTCOUNT];
ALLEGRO_TIMER* event_timer;
int event_timer_clock = 0;
bool event_choose = false;
bool is_seq_triggered;
// ------------------------------------
// stat
// ------------------------------------
float attendance_rate[6];
int grade_point;

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
Coord_2D start_point, end_point;

double nowx, nowy;
double x_velocity, y_velocity;

ALLEGRO_TIMER *timer;
int chr_timer_set = 0;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_CONFIG *conf;
ALLEGRO_CONFIG *conf_lecture;

char hp_str[10], sp_str[10];

//object_t player[4];

typedef struct character {

	position_t pos;

	int curr_point;
	int next_point;

	object_t* image[4];
	int current_image;
	
	bool is_moving_now;

}Character;

Character player;

static int edge_object_starting;
static int vertex_object_starting;
static int stat_object_starting;
int yes_or_no_UI_starting = 0;
void set_player_position_to_vertex(Character* chr, int index);


int scene_4_init() {

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	int i;

	printf("Scene 4 start! \n");

	object_t bg = create_object("Resources\\UI\\routegame\\bg.png", 0, 0);
	Background = bg;

	Stack.push(&Stack, create_object("Resources\\UI\\routegame\\map.jpg", 0, 0));
	map = &Stack.objs[Stack.counter - 1];

	

	// ------------------------------------
	// initial setting
	// ------------------------------------
	today_of_week = MON;
	today_day = 2;
	today_Month = 3;
	week_count = 1;
	test_custom_schedule();
	init_schedule_data();

	conf = al_load_config_file("Resources\\korean\\routegame.ini");
	conf_lecture = al_load_config_file("Resources\\korean\\lecture_info.ini");
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
	edge_object_starting = Stack.counter;
	make_edge_objects(myGraph);
	vertex_object_starting = Stack.counter;
	make_vertex_objects(myGraph, &map_button_ptr); // 9 ~ vertex캣수만큼 오름

	// ------------------------------------
	// graph test
	// ------------------------------------
	//print_graph(myGraph);

	timer = al_create_timer(1.0 / 1000);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);


	Stack.push(&Stack, create_object("Resources\\UI\\routegame\\move.png", 100, 150));
	Stack.push(&Stack, create_object("Resources\\UI\\routegame\\1.png", 100, 150));
	Stack.push(&Stack, create_object("Resources\\UI\\routegame\\2.png", 100, 150));
	Stack.push(&Stack, create_object("Resources\\UI\\routegame\\3.png", 100, 150));

	for (i = 0; i < 4; i++) {
		player.image[i] = &Stack.objs[Stack.counter - 4 + i];
		player.image[i]->enable = false;
	} // 171 + (# of edges) +  0, 1, 2, 3 (current : ~177)

	
#define VERTICE myGraph->Num_of_Vertex
#define EDGES myGraph->Num_of_Edge
//#define EDGES 0
//#define CHARACTER 4
/*
	current_state = VERTICE + EDGES + CHARACTER + 1;
	Stack.objs[current_state].enable = true;
	*/
	
	set_player_position_to_vertex(&player, 2);

	int dx = -400;
	int dy = -1200;
	move(&dx, &dy);

	// ------------------------------------
	// event setting
	// ------------------------------------
	
	init_event(stochastic_event_func, sequencial_event_func, special_event_func);
	event_timer = al_create_timer(1.0 / 1000);
	al_start_timer(event_timer);
	is_seq_triggered = false;
	yes_or_no_UI_starting = Stack.counter;
	Stack.push(&Stack, create_object("Resources\\UI\\tutorial\\kakaotalk.png", 365, 210));
	object_t yes_button = create_object("Resources\\UI\\tutorial\\yes_button.png", 365, 380); 
	object_t no_button = create_object("Resources\\UI\\tutorial\\no_button.png", 640, 380);
	
	ui_set_button(&yes_button);
	ui_set_button(&no_button);

	Stack.push(&Stack, yes_button);
	Stack.push(&Stack, no_button);  // (current : 178 + 0 1 2  = 180)

	for (i = 0; i < 3; i++) {
		Stack.objs[Stack.counter - 3 + i].enable = false;
	}

	// initial graph edge coloring

	for (int i = 0; i < myGraph->Num_of_Edge; i++)
	{
		edge e = myGraph->edgeArray[i];

		if (e.vertexindex_1 == player.curr_point || e.vertexindex_2 == player.curr_point)
		{
			object_t *eo = &Stack.objs[edge_object_starting + i];
			eo->color = al_map_rgb(255, 0, 0);
		}
	}

	// ----------------------------------
	// STAT WINDOW DARWING
	// ----------------------------------
	object_t stat_window = create_object("Resources\\UI\\routegame\\stat_window.png", 0, 0);
	Stack.push(&Stack, stat_window);

	object_t health = create_object(NULL, 60, 150);
	ui_set_text(&health, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, al_get_config_value(conf, "korean", "health"), 24);
	Stack.push(&Stack, health);
	object_t sociality = create_object(NULL, 60, 190);
	ui_set_text(&sociality, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, al_get_config_value(conf, "korean", "sociality"), 24);
	Stack.push(&Stack, sociality);
	object_t attend = create_object(NULL, 60, 230);
	ui_set_text(&attend, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, al_get_config_value(conf, "korean", "attend"), 24);
	Stack.push(&Stack, attend);

	stat_object_starting = Stack.counter;
	object_t hp = create_object(NULL, 240, 150);
	sprintf(hp_str, "%0.1f", health_point / 10.0);
	ui_set_text(&hp, al_map_rgb(0, 0, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, hp_str, 24);
	Stack.push(&Stack, hp);

	object_t sp = create_object(NULL, 240, 190);
	sprintf(sp_str, "%0.1f", social_point / 10.0);
	ui_set_text(&sp, al_map_rgb(0, 0, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, sp_str, 24);
	Stack.push(&Stack, sp);
	
	bool lecturerepeat;
	int k = 0;
	for (i = 0; i < 6; i++) {
		lectureindex[i] = -1;
	}
	for (i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			lecturerepeat = false;
			if (mySchedule.timeTable[i][j].isEmptyBit == NONEMPTY) {
				int lectureid = mySchedule.timeTable[i][j].index;
				for (int x = 0; x < 6; x++) {
					if (lectureid == lectureindex[x])
						lecturerepeat = true;
				}
				if (lecturerepeat == false)
					lectureindex[k++] = lectureid;
			}
		}
	}
	object_t lecture_name[6];
	for (i = 0; i < 6; i++) {
		lecture_name[i] = create_object(NULL, 850, 240 + i * 75);
		if (lectureindex[i] == -1)
			ui_set_text(&lecture_name[i], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, "", 36);
		else
			ui_set_text(&lecture_name[i], al_map_rgb(0, 0, 0), "Resources\\font\\BMDOHYEON.ttf", ALLEGRO_ALIGN_LEFT, al_get_config_value(conf_lecture, "name", lectureTable[lectureindex[i]].identifyNumber), 36);
		Stack.push(&Stack, lecture_name[i]);
	}
	// ------------------------------------
	// Timebar UI setting
	// ------------------------------------

	maingame_timer = al_create_timer(1.0 / 1000);
	al_start_timer(maingame_timer);
	timebar_object_starting = Stack.counter;

	object_t bar_bg = create_colored_object(al_map_rgb(238, 238, 238), 1280, 17, 0, 0);
	Stack.push(&Stack, bar_bg); 

	object_t red = create_colored_object(al_map_rgb(161, 20, 8), 0, 17, 0, 0);
	Stack.push(&Stack, red); 
	return 0;
}

void set_player_position_to_vertex(Character* chr, int index) {

	int image_x, image_y;

	image_x = chr->image[0]->rect.width/2;
	image_y = chr->image[0]->rect.height - 43;

	player.pos.x = myGraph->vertexArray[index].loc.x - image_x;
	player.pos.y = myGraph->vertexArray[index].loc.y - image_y;

	for (int i = 0; i < 4; i++) {
		chr->image[i]->pos.x = myGraph->vertexArray[index].loc.x - image_x;
		chr->image[i]->pos.y = myGraph->vertexArray[index].loc.y - image_y;
	}
	chr->curr_point = index;

}
void move_player(Character* chr, float x, float y) {
	player.pos.x += x;
	player.pos.y += y;
	for (int i = 0; i < 4; i++) {
		chr->image[i]->pos.x += x;
		chr->image[i]->pos.y += y;
	}

}

static double speed = 1000;
void setting()
{
	player.image[player.current_image]->enable = false;
	player.current_image = 0;
	player.image[player.current_image]->enable = true;
	nowx = player.pos.x;
	nowy = player.pos.y;
	if (player.is_moving_now) {
		end_point.x = myGraph->vertexArray[player.next_point].loc.x;
		end_point.y = myGraph->vertexArray[player.next_point].loc.y;
		start_point.x = myGraph->vertexArray[player.curr_point].loc.x;
		start_point.y = myGraph->vertexArray[player.curr_point].loc.y;

		float vector_x = end_point.x - start_point.x;
		float vector_y = end_point.y - start_point.y;

		move_player(&player, vector_x / speed, vector_y / speed);
		printf("%f %d\n", player.pos.x, myGraph->vertexArray[player.next_point].loc.x - 1);
		if (player.pos.x == myGraph->vertexArray[player.next_point].loc.x &&
			player.pos.y == myGraph->vertexArray[player.next_point].loc.y ) {
			
		}
	}
}
void move(int *pdx, int *pdy) {
	int prev_map_x = (*map).pos.x;
	int prev_map_y = (*map).pos.y;

	(*map).pos.x += *pdx;
	(*map).pos.y += *pdy;

	if ((*map).pos.x > 0) {
		(*map).pos.x = 0;
		*pdx = 0 - prev_map_x;
	}
	if ((*map).pos.y > 0) {
		(*map).pos.y = 0;
		*pdy = 0 - prev_map_y;
	}

	if ((*map).pos.x < SCREEN_W - map->rect.width) {
		(*map).pos.x = SCREEN_W - map->rect.width;
		*pdx = SCREEN_W - map->rect.width - prev_map_x;
	}
	if ((*map).pos.y < SCREEN_H - map->rect.height) {
		(*map).pos.y = SCREEN_H - map->rect.height;
		*pdy = SCREEN_H - map->rect.height - prev_map_y;
	}

	int dx = *pdx;
	int dy = *pdy;

	for (int i = 0; i < myGraph->Num_of_Edge; i++)
	{
		object_t *o = &Stack.objs[edge_object_starting + i];
		o->modifier.value.line.x1 += dx;
		o->modifier.value.line.y1 += dy;
		o->modifier.value.line.x2 += dx;
		o->modifier.value.line.y2 += dy;

	}

	for (int i = 0; i < myGraph->Num_of_Vertex; i++)
	{
		(map_button_ptr[i])->pos.x += dx;
		(map_button_ptr[i])->pos.y += dy;
		(map_button_ptr[i])->rect.left += dx;
		(map_button_ptr[i])->rect.top += dy;

	}

	for (int i = 0; i < 4; i++)
	{
		player.image[i]->pos.x += dx;
		player.image[i]->pos.y += dy;
		player.image[i]->rect.left += dx;
		player.image[i]->rect.top += dy;
	}

}
#define TIMEBAR_MAX 1280 // 1280 - 300
int scene_4_update() {

	int i;
	//Scene 0의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨
	// ------------------------------------
	// trigger sequencial event
	// ------------------------------------
	
	if (!is_seq_triggered) {
		int p = trigger_sequencial_event(today_Month, today_of_week, week_count, sequencial_event_func);
		if (p == 1) {
			al_set_timer_count(event_timer, 0);
			al_stop_timer(maingame_timer);
			al_stop_timer(event_timer);
			is_seq_triggered = true;
		}
	}

	// ------------------------------------
	// Timebar running
	// ------------------------------------
	
	if (al_get_timer_count(maingame_timer) - maingame_timer_set > 10) {
		maingame_timer_set = al_get_timer_count(maingame_timer);
		timebar_width += (TIMEBAR_MAX * 100) / (second_per_day[today_of_week] * 100.0); // 분자: (TIMEBAR_MAX * n) == n배 빠르게
		Stack.objs[timebar_object_starting + 1].rect.width = timebar_width + 5;
	}
	
	if (Stack.objs[timebar_object_starting + 1].rect.width > TIMEBAR_MAX) {
		if (today_of_week == FRI) {
			today_of_week = MON;
			today_day += 3;
			week_count++;
		}
		else {
			today_of_week++;
			today_day++;
		}
		if (today_day >= 29 && today_Month == 2) {
			today_Month++;
			today_day -= 28;
			week_count = 1;
		}
		if (today_day >= 31 && (today_Month == 4 || today_Month == 6 || today_Month == 9 || today_Month == 11)) {
			today_Month++;
			today_day -= 30;
			week_count = 1;
		}
		if (today_day >= 32 && (today_Month == 1 || today_Month == 3 || today_Month == 5 || today_Month == 7 || today_Month == 8 || today_Month == 10 || today_Month == 12)) {
			if (today_Month == 12) {
				today_Month = 1;
			}
			else {
				today_Month++;
			}
			today_day -= 31;
			week_count = 1;
		}
		is_seq_triggered = false;
		timebar_width = 0;
		Stack.objs[timebar_object_starting + 1].rect.width = 0;
		maingame_timer_set = 0;
		printf("%d 월 %d 일 %d주 ", today_Month, today_day, week_count);
		switch (today_of_week) {
		case MON:
			printf("월");
			break;
		case TUE:
			printf("화");
			break;
		case WED:
			printf("수");
			break;
		case THU:
			printf("목");
			break;
		case FRI:
			printf("금");
			break;
		}
		printf("\n");
		al_stop_timer(maingame_timer);
		al_start_timer(maingame_timer);
		
	}

	// ------------------------------------
	// Event Managing
	// ------------------------------------

	
#define EVENT_TIME_INTERVAL 5
	if (al_get_timer_count(event_timer) - event_timer_clock > (EVENT_TIME_INTERVAL * 1000)) {
		event_timer_clock = al_get_timer_count(event_timer);
		/*
		for (int i = 0; i < SEQ_EVENTCOUNT; i++) {
			if (sequencial_event_func[i].isStarted == false) {
				al_set_timer_count(event_timer, 0);
				al_stop_timer(maingame_timer);
				al_stop_timer(event_timer);
				sequencial_event_func[i].func();
				sequencial_event_func[i].isStarted = true;
				
				break;
			}
		}
		*/
		
	}
	
	if (event_choose) {
		stat_update();
		al_resume_timer(maingame_timer);
		al_start_timer(event_timer);
		event_timer_clock = 0;
		for (int i = 0; i < 3; i++) {
			Stack.objs[yes_or_no_UI_starting + i].enable = false;
		}
		event_choose = false;

	}
	
	if (!player.is_moving_now) {
		if (al_get_timer_count(timer) - chr_timer_set>500) {
			chr_timer_set = al_get_timer_count(timer);
			player.image[player.current_image]->enable = false;
			player.current_image = rand() % 3 + 1;
			player.image[player.current_image]->enable = true;
		}
	}
	else {
		
		setting();

		
		if (count >= speed) {

			// reached destination

			for (int i = 0; i < myGraph->Num_of_Edge; i++)
			{
				edge e = myGraph->edgeArray[i];

				if (e.vertexindex_1 == player.curr_point && e.vertexindex_2 == player.next_point ||
					e.vertexindex_2 == player.curr_point && e.vertexindex_1 == player.next_point)
				{
					object_t *eo = &Stack.objs[edge_object_starting + i];
					eo->color = al_map_rgb(127, 127, 127);
				}

				if (e.vertexindex_1 == player.next_point || e.vertexindex_2 == player.next_point)
				{
					object_t *eo = &Stack.objs[edge_object_starting + i];
					eo->color = al_map_rgb(255, 0, 0);
				}
			}
			
			player.is_moving_now = false;

			int image_x, image_y;

			image_x = player.image[0]->rect.width / 2;
			image_y = player.image[0]->rect.height - 43;

			player.curr_point = player.next_point;
			player.next_point = -1;
			//player.is_moving_now = false;

			for (i = 0; i < 4; i++) {
				player.image[i]->pos.x = end_point.x - image_x + (*map).pos.x;
				player.image[i]->pos.y = end_point.y - image_y + (*map).pos.y;
			}
			count = 0;
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

		int dx = (x - pre_mouse_x);
		int dy = (y - pre_mouse_y);

		move(&dx, &dy);

		pre_mouse_x += dx;
		pre_mouse_y += dy;

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
	al_destroy_timer(maingame_timer);
	al_destroy_timer(event_timer);
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
	customSchedule.timeTable[0][3].index = 2;
	customSchedule.timeTable[0][3].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][4].index = 2;
	customSchedule.timeTable[0][4].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][5].index = 2;
	customSchedule.timeTable[0][5].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][6].index = 2;
	customSchedule.timeTable[0][6].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][7].index = 2;
	customSchedule.timeTable[0][7].isEmptyBit = NONEMPTY;
	customSchedule.timeTable[0][8].index = 2;
	customSchedule.timeTable[0][8].isEmptyBit = NONEMPTY;
	calculate_second_per_day();

	printf("%d %d %d %d %d \n", second_per_day[0], second_per_day[1], second_per_day[2], second_per_day[3], second_per_day[4]);
}
void init_schedule_data(void) {
	
}
void map_button_on_click_listener_func(object_t *o)
{
	if (player.is_moving_now)
		return;
	ptrdiff_t clicked_vertex_idx = o - &Stack.objs[vertex_object_starting];
	printf("clicked! %d %d\n", player.curr_point, clicked_vertex_idx);
	for (int i = 0; i < myGraph->Num_of_Edge; i++)
	{
		edge e = myGraph->edgeArray[i];

		if (e.vertexindex_1 == player.curr_point || e.vertexindex_2 == player.curr_point)
		{
			object_t *eo = &Stack.objs[edge_object_starting + i];
			eo->color = al_map_rgb(127, 127, 127);
		}

		if (e.vertexindex_1 == player.curr_point && e.vertexindex_2 == clicked_vertex_idx ||
			e.vertexindex_2 == player.curr_point && e.vertexindex_1 == clicked_vertex_idx)
		{
			player.is_moving_now = true;
			player.next_point = clicked_vertex_idx;

			object_t *eo = &Stack.objs[edge_object_starting + i];
			eo->color = al_map_rgb(0, 0, 255);
		}
	}
	re_draw();
}

void stat_update()
{
	sprintf(sp_str, "%0.1f", social_point / 10.0);
	ui_set_text(&Stack.objs[stat_object_starting], al_map_rgb(0, 0, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, sp_str, 24);
	sprintf(hp_str, "%0.1f", health_point / 10.0);
	ui_set_text(&Stack.objs[stat_object_starting + 1], al_map_rgb(0, 0, 255), "Resources\\font\\NanumGothic.ttf", ALLEGRO_ALIGN_CENTER, hp_str, 24);
}