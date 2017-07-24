#include "engine.h"


static void scene_1_on_click_button_0();
float brightness, transparency;

#define EVENTCOUNT 6

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* timer_event_queue;
ALLEGRO_EVENT timer_event;
ALLEGRO_FONT *font;
ALLEGRO_CONFIG *conf;

void first_meeting();
void newbie_before_study();
void newbie_meeting();
void newbie_study();
void newbie_OT();
void scene_1_finish();

int timer_set = 0;
int explain_stat = 0;

float health_point = 0;
float social_point = 0;

struct event_function {
	void(*func)();
	bool isStarted;
};

typedef struct event_function event_function;
event_function event_func[EVENTCOUNT];

object_t timebar, popup;

int scene_1_init(){

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	printf("Scene 1 start!");

	al_clear_to_color(al_map_rgb(204, 225, 152));

	conf = al_load_config_file("Resources\\korean\\tutorial.ini");

	object_t bg = create_object("Resources\\dummy\\nothing.png", 0, 0);
	Background = bg;

	timer = al_create_timer(1.0 / 1000);
	timer_event_queue = al_create_event_queue();
	al_register_event_source(timer_event_queue, al_get_timer_event_source(timer));

	object_t stat_window = create_object("Resources\\dummy\\stat_window.png", 0, 0);
	Stack.push(&Stack, stat_window);
	timebar = create_object("Resources\\dummy\\timebar.png", 700, 0);
	Stack.push(&Stack, timebar);

	object_t health = create_object(NULL, 60, 300);
	ui_set_text(&health, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", al_get_config_value(conf, "korean", "health"), 24);
	Stack.push(&Stack, health);
	object_t sociality = create_object(NULL, 60, 350);
	ui_set_text(&sociality, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", al_get_config_value(conf, "korean", "sociality"), 24);
	Stack.push(&Stack, sociality);
	object_t attend = create_object(NULL, 60, 400);
	ui_set_text(&attend, al_map_rgb(0, 0, 0), "Resources\\font\\NanumGothic.ttf", al_get_config_value(conf, "korean", "attend"), 24);
	Stack.push(&Stack, attend);


	object_t hp = create_object(NULL, 300, 150);
	ui_set_text(&hp, al_map_rgb(1, 0, 0), "Resources\\font\\NanumGothic.ttf", (char)health_point, 24);
	Stack.push(&Stack, hp);

	font = al_load_font("Resources\\font\\NanumGothic.ttf", 36, 0);

	//이벤트 함수 모음
	event_func[0].func = first_meeting;
	event_func[1].func = newbie_before_study;
	event_func[2].func = newbie_meeting;
	event_func[3].func = newbie_study;
	event_func[4].func = newbie_OT;
	event_func[5].func = scene_1_finish;

	for (int i = 0; i < EVENTCOUNT; i++)
		event_func[i].isStarted = false;
	
	return 0;
}

int scene_1_update() {

	//Scene 1의 Main문
	//while문 안에 있다 --> 매 frame마다 실행됨

	if (!explain_stat) { //stat설명 팝업 띄우기
		explain_stat=1;
		popup = create_object("Resources\\dummy\\popup.png", 250, 120);
		Stack.push(&Stack, popup);
		object_t text1 = create_object(NULL, 280, 130);
		ui_set_text(&text1, al_map_rgb(1, 1, 1), "Resources\\font\\NanumGothic.ttf", al_get_config_value(conf, "korean", "explain_stat_1"), 36);
		Stack.push(&Stack, text1);
		object_t text2 = create_object(NULL, 280, 170);
		ui_set_text(&text2, al_map_rgb(1, 1, 1), "Resources\\font\\NanumGothic.ttf", al_get_config_value(conf, "korean", "explain_stat_2"), 36);
		Stack.push(&Stack, text2);
		object_t text3 = create_object(NULL, 280, 210);
		ui_set_text(&text3, al_map_rgb(1, 1, 1), "Resources\\font\\NanumGothic.ttf", al_get_config_value(conf, "korean", "explain_stat_3"), 36);
		Stack.push(&Stack, text3);
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && explain_stat) {//아무데나 누르면 팝업 없애기
		Stack.pull(&Stack);
		Stack.pull(&Stack);
		Stack.pull(&Stack);
		Stack.pull(&Stack);
	}

	/*if (Stack.objs[1].enable) {
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			Stack.objs[2].enable = false;
			al_start_timer(timer);
			printf("start timer\n");
			al_wait_for_event(timer_event_queue, &timer_event);
			printf("wait event\n");
		}
	}*/

	if (al_get_timer_count(timer) - timer_set > (5*1000)) {
		printf("timer : %lld\n", al_get_timer_count(timer));
		timer_set = al_get_timer_count(timer);
		al_stop_timer(timer);
		for (int i = 0; i < EVENTCOUNT; i++) {
			if (!event_func[i].isStarted) {
				
				event_func[i].func();
				break;
			}
		}
		al_start_timer(timer);
	}

	re_draw();

	return 0;
}


int scene_1_fin() {

	// 이 씬에서 다른 씬으로 넘어갈 때, 한 번 실행되는 함수.
	Stack.clear(&Stack);

	return 0;
}

void scene_1_on_click_button_0() {
	if (brightness != 1){
		brightness = 1;
	}
	else
	{
		brightness = 0.1;
	}
	puts("clicked");
}

//미리정모
void first_meeting() { 
	printf("first_meeting\n");
	event_func[0].isStarted = true;
} 

//새내기 미리배움터
void newbie_before_study() { 
	printf("newbie_before_study\n");
	event_func[1].isStarted = true;
}

//새내기 정모
void newbie_meeting() { 
	printf("newbie_meeting\n");
	event_func[2].isStarted = true;
}

//새내기 배움터
void newbie_study() { 
	printf("newbie_study\n");
	event_func[3].isStarted = true;
}

//신입생 OT
void newbie_OT() { 
	printf("newbie_OT\n");
	event_func[4].isStarted = true;
}

//마지막 이벤트 후 씬 종료
void scene_1_finish() {
	event_func[5].isStarted = true;
	al_destroy_config(conf);
	al_destroy_font(font);
	load_scene(Scenes.scenes[2]);

}