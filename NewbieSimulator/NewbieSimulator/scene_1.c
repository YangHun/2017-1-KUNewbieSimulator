#include "engine.h"

static void scene_1_on_click_button_0();
float brightness, transparency;

#define EVENTCOUNT 6

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* timer_event_queue;
ALLEGRO_EVENT timer_event;

void first_meeting();
void newbie_before_study();
void newbie_meeting();
void newbie_study();
void newbie_OT();
void scene_1_finish();

int timer_set = 0;

struct event_function {
	void(*func)();
	bool isStarted;
};

typedef struct event_function event_function;
event_function event_func[EVENTCOUNT];

int scene_1_init(){

	//해당 씬이 시작될 때, 딱 한 번 실행되는 함수
	printf("Scene 1 start!");

	object_t bg = create_object("Resources\\dummy\\tutorial.jpg", 0, 0);
	Background = bg;
	
	object_t hos = create_object("Resources\\dummy\\hos.png", 200, 200);
	ui_set_button(&hos);
	ui_set_on_click_listener(&hos, scene_1_on_click_button_0);
	Stack.push(&Stack, hos); //Stack.objs[0]
	
	timer = al_create_timer(1.0 / 1000);
	timer_event_queue = al_create_event_queue();
	al_register_event_source(timer_event_queue, al_get_timer_event_source(timer));

	object_t stat_popup = create_object("Resources\\dummy\\popup.png", 205, 120);
	Stack.push(&Stack, stat_popup); //Stack.objs[1]
	Stack.objs[1].enable = true;
	object_t event_popup = create_object("Resources\\dummy\\popup.png", 205, 120);
	Stack.push(&Stack, event_popup); //Stack.objs[2]
	Stack.objs[2].enable = false;
	object_t timebar = create_object("Resources\\dummy\\timebar.png", 700, 300); //Stack.objs[3]
	Stack.objs[3].enable = true;

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
	if (Stack.objs[1].enable) {
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			Stack.objs[1].enable = false;
			al_start_timer(timer);
			printf("start timer\n");
			al_wait_for_event(timer_event_queue, &timer_event);
			printf("wait event\n");
		}
	}

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
	load_scene(Scenes.scenes[2]);

}